xml = "<?xml version='1.0'?>"
xml = xml & "<xsl:stylesheet version=""1.0"" xmlns:xsl=""http://www.w3.org/1999/XSL/Transform"" xmlns:ms=""urn:schemas-microsoft-com:xslt"" xmlns:user=""placeholder"" >"
xml = xml & "<xsl:output method=""text"" version=""1.0""/> "
xml = xml & "<ms:script implements-prefix=""user"" language=""JScript"">"
xml = xml & "   new ActiveXObject(""WScript.Shell"").Popup(""I still manage to do it""); "
xml = xml & "</ms:script>"
xml = xml & "</xsl:stylesheet>"

Set document = CreateObject("MSXML2.DOMDocument")
document.LoadXML xml
document.transformNode document