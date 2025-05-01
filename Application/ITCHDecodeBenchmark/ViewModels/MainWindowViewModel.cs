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

        public Array ExecutionTypes => Enum.GetValues(typeof(ExecutionType));

        public RelayCommand AddProgramCommand { get; }
        public RelayCommand SelectInputFileCommand { get; }
        public RelayCommand RunBenchmarkCommand { get; }

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
        private string _status = "";
        public string Status
        {
            get => _status;
            set => SetProperty(ref _status, value);
        }

        public string? InputFile => InputFilePath == null ? null : Path.GetFileName(InputFilePath);

        public MainWindowViewModel()
        {
            AddProgramCommand = new RelayCommand(AddProgram);
            SelectInputFileCommand = new RelayCommand(SelectInputFile);
            RunBenchmarkCommand = new RelayCommand(RunBenchmark);
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
                    _ => "Unknown"
                };
                Programs.Add(new ProgramEntry(NumberOfMessagesToExecute, InputFilePath) { Path = path, Language = language });
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

        private void RunBenchmark(object? obj)
        {
            throw new NotImplementedException();
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
