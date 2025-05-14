using System.Collections.ObjectModel;
using System.IO;
using ITCHDecodeBenchmark.Models;
using ITCHDecodeBenchmark.Util;
using Microsoft.Win32;

namespace ITCHDecodeBenchmark.ViewModels
{
    public enum ExecutionType
    {
        Build,
        Parse
    }
    class MainWindowViewModel : PropertyChangedBase  
    {
        public ObservableCollection<ProgramEntry> Programs { get; set; } = new();

        public RelayCommand AddProgramCommand { get; }
        public RelayCommand SelectInputFileCommand { get; }
        public RelayCommand RunBenchmarksCommand { get; }

        private string? _inputFilePath;
        public string? InputFilePath {
            get => _inputFilePath;
            set
            {
                if (_inputFilePath != value)
                {
                    _inputFilePath = value;
                    OnPropertyChanged(nameof(InputFile));
                    foreach (var p in Programs)
                        p.InputFilePath = value;
                }
            }
        }

        private string? _numberOfMessagesToExecute;

        public string? NumberOfMessagesToExecute
        {
            get => _numberOfMessagesToExecute;
            set
            {
                if (_numberOfMessagesToExecute != value)
                {
                    _numberOfMessagesToExecute = value;
                    OnPropertyChanged(nameof(NumberOfMessagesToExecute));
                    foreach (var p in Programs)
                        p.NumberOfMessagesToExecute = value;
                }
            }
        }

        private string? _numberOfRuns;

        public string? NumberOfRuns
        {
            get => _numberOfRuns;
            set
            {
                if (_numberOfRuns != value)
                {
                    _numberOfRuns = value;
                    OnPropertyChanged(nameof(NumberOfRuns));
                    foreach (var p in Programs)
                        p.NumberOfRuns = value;
                }
            }
        }

        public string? InputFile => InputFilePath == null ? null : Path.GetFileName(InputFilePath);

        public MainWindowViewModel()
        {
            AddProgramCommand = new RelayCommand(AddProgram);
            SelectInputFileCommand = new RelayCommand(SelectInputFile);
            RunBenchmarksCommand = new RelayCommand(async _ => await RunBenchmarks());
        }

        private void AddProgram(object? obj)
        {
            OpenFileDialog dialog = new OpenFileDialog { Title = "Select Program" };
            if (dialog.ShowDialog() == true)
            {
                string path = dialog.FileName;
                string language = Path.GetExtension(path).ToLower() switch
                {
                    ".py" => "Python",
                    ".java" => "Java",
                    ".exe" => "C++",
                    ".jar" => "Packaged Java",
                    _ => "Unknown"
                };
                Programs.Add(new ProgramEntry(path, language, NumberOfMessagesToExecute, InputFilePath));
            }
        }

        private void SelectInputFile(object? obj)
        {
            var dialog = new OpenFileDialog { Title = "Select Input File" };
            if (dialog.ShowDialog() == true)
            {
                InputFilePath = dialog.FileName;
            }
        }

        private async Task RunBenchmarks()
        {
            var tasks = Programs.Select(program => Task.Run(() => program.RunProgram()));
            await Task.WhenAll(tasks);
        }

        public void SaveData()
        {
            JsonHelper.SaveData(SessionConstants.ProgramEntriesFilePath, Programs, InputFilePath, NumberOfMessagesToExecute);
        }

        public void LoadData()
        {
            var data = JsonHelper.LoadData(SessionConstants.ProgramEntriesFilePath);
            if (data != null)
            {
                foreach (ProgramEntry entry in data.Item1)
                {
                    Programs.Add(entry);
                }

                InputFilePath = data.Item2;
                NumberOfMessagesToExecute = data.Item3;
            }
        }
    }
}
