# AppLocker
AppLocker is an application whitelisting technology native to Windows that can restrict the applications, DLLs and scripts that are permitted to run on a machine.Rules are defined based on file attributes such as path, publisher or hash and are managed through Window GPO enforcement. There are several way to circumvent restricted environment enforced AppLocker. The Most Effective way to circumvent is to enumerate corrctly. my favourite way to enumerate is to go through GPO rules.

The following rule doesn't allow you runing INSTALLUTIL
```
KeyName     : Software\Policies\Microsoft\Windows\SrpV2\Exe\451f43f7-5300-4991-b9ca-73b0c17150de
ValueName   : Value
ValueType   : REG_SZ
ValueLength : 854
ValueData   : <FilePublisherRule Id="451f43f7-5300-4991-b9ca-73b0c17150de" Name="INSTALLUTIL.EXE" Description="" UserOrGroupSid="S-1-1-0"
              Action="Deny"><Conditions><FilePublisherCondition PublisherName="O=MICROSOFT CORPORATION, L=REDMOND, S=WASHINGTON, C=US"
              ProductName="MICROSOFT® .NET FRAMEWORK" BinaryName="INSTALLUTIL.EXE"><BinaryVersionRange LowSection="*"
              HighSection="*"/></FilePublisherCondition></Conditions></FilePublisherRule>
```              

The following rule is enforced by GPO allwoing any things from Window Directory
```
KeyName     : Software\Policies\Microsoft\Windows\SrpV2\Script\9428c672-5fc3-47f4-808a-a0011f36dd2c
ValueName   : Value
ValueType   : REG_SZ
ValueLength : 694
ValueData   : <FilePathRule Id="9428c672-5fc3-47f4-808a-a0011f36dd2c" Name="(Default Rule) All scripts located in the Windows folder"
              Description="Allows members of the Everyone group to run scripts that are located in the Windows folder." UserOrGroupSid="S-1-1-0"
              Action="Allow"><Conditions><FilePathCondition Path="%WINDIR%\*"/></Conditions></FilePathRule>
 ```            
