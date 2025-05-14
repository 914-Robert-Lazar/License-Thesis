using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using ITCHDecodeBenchmark.Util;
using ITCHDecodeBenchmark.ViewModels;

namespace ITCHDecodeBenchmark.Models
{
    class ProgramEntry : PropertyChangedBase
    {
        public RelayCommand RunProgramCommand { get; }
        public ProgramEntry(string path, string language, string? numberOfMessagesToExecute, string? inputFilePath)
        {
            Path = path;
            Language = language;
            RunProgramCommand = new RelayCommand(async _ => await RunProgramAsync());
            NumberOfMessagesToExecute = numberOfMessagesToExecute;
            InputFilePath = inputFilePath;
        }

        [JsonIgnore]
        private string? _path;
        public string? Path
        {
            get => _path;
            set => SetProperty(ref _path, value, onChanged: LoadNotesFromFile);
        }

        public Array ExecutionTypes { get; private set; } = Enum.GetValues(typeof(ExecutionType));

        private void LoadNotesFromFile()
        {
            if (string.IsNullOrEmpty(Path)) return;

            var directory = System.IO.Path.GetDirectoryName(Path);
            var notesFile = System.IO.Path.Combine(directory ?? "", "notes.txt");

            if (File.Exists(notesFile))
            {
                string note = File.ReadAllText(notesFile);
                if (note == "parse")
                {
                    Notes = "Only parsing solution available for this program";
                    ExecutionTypes = new[] { ExecutionType.Parse };
                }
                else if (note == "build")
                {
                    Notes = "Only order book building solution available for this program";
                    ExecutionTypes = new[] { ExecutionType.Build };
                }
            }
            else
            {
                Notes = null;
            }
        }

        public string Language { get; set; }
        public ExecutionType ExecutionType { get; set; }

        [JsonIgnore]
        public string? NumberOfMessagesToExecute { get; set; }

        [JsonIgnore]
        private string? _numberOfMessagesExecuted;
        public string? NumberOfMessagesExecuted 
        {
            get => _numberOfMessagesExecuted;
            set => SetProperty(ref _numberOfMessagesExecuted, value);
        }

        [JsonIgnore]
        private string? _executionTime;
        public string? ExecutionTime
        {
            get => _executionTime;
            set => SetProperty(ref _executionTime, value);
        }

        [JsonIgnore]
        private bool _isRunning = false;

        [JsonIgnore]
        public bool IsRunning
        {
            get => _isRunning;
            set => SetProperty(ref _isRunning, value);
        }

        [JsonIgnore]
        public string? InputFilePath { get; set; }

        public async Task RunProgramAsync()
        {
            await Task.Run(() => RunProgram());
        }

        [JsonIgnore]
        private string? _notes;
        public string? Notes
        {
            get => _notes;
            set => SetProperty(ref _notes, value);
        }

        public void RunProgram()
        {
            if (string.IsNullOrEmpty(InputFilePath)) return;
            IsRunning = true;
            var processStartInfo = new ProcessStartInfo()
            {
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                CreateNoWindow = true
            };
            string arguments = $"{ExecutionType.ToString().ToLower()} \"{InputFilePath}\" " +
                        $"{NumberOfMessagesToExecute ?? string.Empty}";


            switch (Language)
            {
                case "C++":
                    processStartInfo.FileName = Path;
                    processStartInfo.Arguments = arguments;  
                    break;
                case "Python":
                    processStartInfo.FileName = "python";
                    processStartInfo.Arguments = $"\"{Path}\" {arguments}";
                    break;
                case "Packaged Java":
                    processStartInfo.FileName = "java";
                    processStartInfo.Arguments = $" -jar \"{Path}\" {arguments}";
                    break;
                default:
                    break;
            }

            var process = Process.Start(processStartInfo);
            if (process == null) return;
            process.WaitForExit();
            NumberOfMessagesExecuted = NumberOfMessagesToExecute;
            ExecutionTime = process.StandardOutput.ReadToEnd();
            IsRunning = false;
        }
    }
}
