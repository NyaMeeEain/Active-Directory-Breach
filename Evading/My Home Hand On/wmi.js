var service = GetObject("winmgmts:\\\\.\\root\\cimv2");
var startup = service.Get("Win32_ProcessStartup");
var config = startup.SpawnInstance_();
var proc = service.Get("Win32_Process");

proc.Create("powershell.exe", null, config, null);