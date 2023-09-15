using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace WebTecLr2_Server
{
    public class Logger
    {
        StreamWriter file { get; set; }
        public Logger(string fileName)
        {
            file = new StreamWriter(fileName, true);
        }

        public void Log(string message)
        {
            Console.WriteLine(message);
            file.WriteLine($"[{DateTime.Now}] {message}");
            file.Flush();
        }

        ~Logger()
        {
            file.Dispose();
        }
    }
}
