from time import time
import gzip
import sys
import pandas as pd
from struct import unpack
from collections import namedtuple
from datetime import timedelta

formats = {
    ('integer', 2): 'H',
    ('integer', 4): 'I',
    ('integer', 6): '6s',
    ('integer', 8): 'Q',
    ('alpha', 1)  : 's',
    ('alpha', 2)  : '2s',
    ('alpha', 4)  : '4s',
    ('alpha', 8)  : '8s',
    ('price_4', 4): 'I',
    ('price_8', 8): 'Q',
}

if len(sys.argv) < 3:
    print(f"Usage {sys.argv[0]} <parse or build> <binary_itch_file.gz> [<number of order related messages to be executed>]")
else:
    file_name = sys.argv[2]
    order_related_messages_to_be_executed = 0
    if len(sys.argv) >= 3:
        order_related_messages_to_be_executed = int(sys.argv[3])

    event_codes = {'O': 'Start of Messages',
               'S': 'Start of System Hours',
               'Q': 'Start of Market Hours',
               'M': 'End of Market Hours',
               'E': 'End of System Hours',
               'C': 'End of Messages'}

    message_types = pd.read_csv('C:\\Programs\\Informatics-University-Projects\\Informatics University\\License Thesis\\License-Thesis\\src\\changed_python_parser\\message_types\\message_types.csv')
    message_types.loc[:, 'formats'] = (message_types[['value', 'length']].apply(tuple, axis=1).map(formats))

    message_fields, fstring = {}, {}
    for t, message in message_types.groupby('message_type'):
        message_fields[t] = namedtuple(typename=t, field_names=message.name.tolist())
        fstring[t] = '>' + ''.join(message.formats.tolist())

    messages = {}
    order_related_message_count = 0

    start = time()
    with gzip.open(file_name, 'rb') as data:
        while order_related_messages_to_be_executed == 0 or order_related_message_count < order_related_messages_to_be_executed:
            
            # determine message size in bytes
            message_size = int.from_bytes(data.read(2), byteorder='big', signed=False)
            
            # get message type by reading first byte
            message_type = data.read(1).decode('ascii')
            
            # create data structure to capture result
            if not messages.get(message_type):
                messages[message_type] = []

            # read & store message
            record = data.read(message_size - 1)
            message = message_fields[message_type]._make(unpack(fstring[message_type], record))
            messages[message_type].append(message)
            
            # deal with system events
            if message_type == 'S' and message.event_code.decode('ascii') == 'C':
                break

            if message_type in ['A', 'F', 'U', 'E', 'C', 'X', 'D']:
                order_related_message_count += 1          
            
    print(timedelta(seconds=time() - start).total_seconds())