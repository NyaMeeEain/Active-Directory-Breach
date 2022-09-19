Function XmlTime(t)
    tTime = Right("0" & Hour(t), 2) & ":" & Right("0" & Minute(t), 2) & ":" & Right("0" & Second(t), 2)
    tDate = Year(t) & "-" & Right("0" & Month(t), 2) & "-" & Right("0" & Day(t), 2)
    XmlTime = tDate & "T" & tTime
End Function


Set service = CreateObject("Schedule.Service")
Call service.Connect

Set folder = service.GetFolder("\")
Set task = service.NewTask(0)

Set trigger = task.triggers.Create(1)
trigger.StartBoundary = XmlTime(DateAdd("s", 10, Now))
trigger.Enabled = True

Set action = task.Actions.Create(0)
action.Path = "calc.exe"

Call folder.RegisterTaskDefinition("MyTask", task, 6, , , 3)

MsgBox "Calc incoming ..."