Set service = GetObject("winmgmts:\\.\root\cimv2")
Set startup = service.Get("Win32_ProcessStartup")
Set config = startup.SpawnInstance_
Set proc = service.Get("Win32_Process")

proc.Create _
"calc.exe" , _
null, config, null