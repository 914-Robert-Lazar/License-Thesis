using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using ITCHDecodeBenchmark.Models;

namespace ITCHDecodeBenchmark.Util
{
    class JsonHelper
    {
        public static void SaveData(string saveFilePath, object programs, object? inputFilePath, object? numberOfMessagesToExecute)
        {
            string? json = JsonSerializer.Serialize(new Tuple<object, object?, object?>(programs, inputFilePath, numberOfMessagesToExecute));
            File.WriteAllText(saveFilePath, json);
        }

        public static Tuple<ObservableCollection<ProgramEntry>, string?, string?>? LoadData(string saveFilePath)
        {
            try
            {
                if (File.Exists(saveFilePath))
                {
                    string json = File.ReadAllText(saveFilePath);
                    var loaded = JsonSerializer.Deserialize<Tuple<ObservableCollection<ProgramEntry>, string?, string?>>(json);

                    return loaded;
                }
                return null;
            }
            catch (Exception)
            {
                return null;
            }
        }
    }
}
