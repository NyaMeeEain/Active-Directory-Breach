# Custom Tradecraft Windows Services With C#

 

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace weaponlize
{
    class Program
    {
        static void Main(string[] args)
        {

            using var process = new Process();

            process.StartInfo.FileName = "notepad.exe"; #Powershell 
            process.StartInfo.Arguments = @"C:\Users\NyaMeeEain\Desktop\acl.txt"; #Powershell argument
            process.Start();
        }
    }

```
