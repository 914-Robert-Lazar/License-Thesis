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
        public ProgramEntry(string? numberOfMessagesToExecute, string? inputFilePath)
        {
            RunProgramCommand = new RelayCommand(RunProgram);
            NumberOfMessagesToExecute = numberOfMessagesToExecute;
            InputFilePath = inputFilePath;
        }
        public required string Path { get; set; }
        public required string Language { get; set; }
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
        public string? InputFilePath { get; set; }
        private void RunProgram(object? obj)
        {
            if (string.IsNullOrEmpty(InputFilePath)) return;

            var processStartInfo = new ProcessStartInfo()
            {
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true
            };

            NumberOfMessagesExecuted = NumberOfMessagesToExecute;
            switch (Language)
            {
                case "C++":
                    processStartInfo.FileName = Path;
                    processStartInfo.Arguments = $"{ExecutionType.ToString().ToLower()} \"{InputFilePath}\" " +
                        $"{NumberOfMessagesToExecute ?? string.Empty}";  
                    break;
                default:
                    break;
            }

            var process = Process.Start(processStartInfo);
            if (process == null) return;
            process.WaitForExit();
            ExecutionTime = process.StandardOutput.ReadToEnd();
        }
    }
}
