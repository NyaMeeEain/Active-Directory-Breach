Set req = CreateObject("MSXML2.ServerXMLHTTP.6.0")
req.Open "GET", "http://google.com", False
req.setRequestHeader "User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"
req.Send
MsgBox req.responseText