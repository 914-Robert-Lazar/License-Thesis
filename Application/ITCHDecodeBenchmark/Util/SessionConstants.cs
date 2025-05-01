using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ITCHDecodeBenchmark.Util
{
    class SessionConstants
    {
        public static SessionConstants Instance = new();

        public static string AppDataLocal = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);

        public static string ProgramEntriesFilePath = Path.Combine(AppDataLocal, "Programs.json");

    }
}
