import pandas as pd

def clean_message_types(df):
    df.columns = [c.lower().strip() for c in df.columns]
    df.value = df.value.str.strip()
    df.name = (df.name
               .str.strip() # remove whitespace
               .str.lower()
               .str.replace(' ', '_')
               .str.replace('-', '_')
               .str.replace('/', '_'))
    df.notes = df.notes.str.strip()
    df['message_type'] = df.loc[df.name == 'message_type', 'value']
    return df

message_data = (pd.read_excel('src\changed_python_parser\message_types\message_types.xlsx',
                              sheet_name='messages')
                .sort_values('id')
                .drop('id', axis=1))
    
message_types = clean_message_types(message_data)

message_labels = (message_types.loc[:, ['message_type', 'notes']]
                .dropna()
                .rename(columns={'notes': 'name'}))
message_labels.name = (message_labels.name
                    .str.lower()
                    .str.replace('message', '')
                    .str.replace('.', '')
                    .str.strip().str.replace(' ', '_'))

message_types.message_type = message_types.message_type.ffill()
message_types = message_types[message_types.name != 'message_type']
message_types.value = (message_types.value
                    .str.lower()
                    .str.replace(' ', '_')
                    .str.replace('(', '')
                    .str.replace(')', ''))

message_types.to_csv('message_types.csv', index=False)