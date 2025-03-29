# bin_data = open('input/ny4-xpsx-tvitch-a-20230822T071000.pcap', 'rb')
# message_size_bytes = bin_data.read()
# message_size = int.from_bytes(message_size_bytes, byteorder='big', signed=False)
# message_type = bin_data.read(1).decode('ascii')
# record = bin_data.read(message_size - 1)
# print("size: " + str(message_size) + " type: " + message_type)
import gzip
import struct

# List of valid ITCH message types (First byte in payload)
VALID_ITCH_MSG_TYPES = {
    b'S', b'R', b'H', b'Y', b'L', b'V', b'W', b'K', b'J', b'h', b'A', b'F', b'E', b'C', b'X', b'D', b'U', b'P', b'Q', b'B', b'I', b'O'
}

def is_valid_itch_message(data):
    """Check if a message starts with a valid ITCH type."""
    return data[:1] in VALID_ITCH_MSG_TYPES

def validate_binary_itch(filename):
    """Validate if a BinaryFILE contains ITCH messages."""
    try:
        with gzip.open(filename, 'rb') as f:  # Open GZ file in binary mode
            total_messages = 0
            valid_messages = 0
            messages = {}

            while True:
                length_bytes = f.read(2)  # Read the 2-byte length prefix
                if len(length_bytes) < 2:
                    break  # End of file

                length = struct.unpack('>H', length_bytes)[0]  # Convert big-endian to int
                
                if length == 0:
                    print("✅ End of session marker found.")
                    break  # End of session

                message = f.read(length)  # Read the ITCH message
                total_messages += 1

                if is_valid_itch_message(message):
                    valid_messages += 1
                    if not message[:1] in messages.keys():
                        messages[message[:1]] = 1
                    else:
                        messages[message[:1]] += 1
            
            if valid_messages > 0:
                print(f"✅ Valid ITCH BinaryFILE: {valid_messages}/{total_messages} messages recognized.")
                with open("output/message_types.txt", "w") as out:
                    for message_type in messages.keys():
                        out.write(f"{message_type}: {messages[message_type]}")
                return True
            else:
                print("❌ No valid ITCH messages found.")
                return False

    except Exception as e:
        print(f"❌ Error reading file: {e}")
        return False

if __name__ == "__main__":
    binary_file = "input/01302019.NASDAQ_ITCH50.gz"
    validate_binary_itch(binary_file)
