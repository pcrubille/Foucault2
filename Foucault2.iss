; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Foucault2
AppVerName=Foucault2 2.04
AppPublisher=Etienne de Foras
AppPublisherURL=http://edeforas.free.fr
AppSupportURL=http://edeforas.free.fr
AppUpdatesURL=http://edeforas.free.fr
DefaultDirName={pf}\Foucault2
DefaultGroupName=Foucault2
AllowNoIcons=yes
Compression=lzma
SolidCompression=yes
ChangesAssociations=yes
SetupIconFile=".\Foucault2.ico"
UninstallDisplayIcon="{app}\Foucault2.exe"
OutputBaseFilename="setup_Foucault2" 

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: ".\Foucault2.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\*.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\*.h"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.cpp"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\Util\*.*"; DestDir: "{app}\src\Util"; Flags: ignoreversion
Source: ".\*.pro"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.ui"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.ico"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.iss"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.qrc"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.rc"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\*.ts"; DestDir: "{app}\src\Foucault2"; Flags: ignoreversion
Source: ".\samples\*.foucault2"; DestDir: "{app}\samples"; Flags: ignoreversion
Source: ".\samples\*.mir"; DestDir: "{app}\samples"; Flags: ignoreversion

Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\Qt5Core.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\Qt5Gui.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\Qt5Widgets.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\Qt5PrintSupport.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\icuin54.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\icuuc54.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\icudt54.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\libstdc++-6.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\libwinpthread-1.dll"; DestDir: "{app}"
Source: "C:\Qt\Qt5.6.0\5.6\mingw49_32\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"

[INI]
Filename: "{app}\Foucault2.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://edeforas.free.fr"

[Icons]
Name: "{group}\Foucault2"; Filename: "{app}\Foucault2.exe"; WorkingDir: "{app}"
Name: "{group}\{cm:ProgramOnTheWeb,Foucault2}"; Filename: "{app}\Foucault2.url"
Name: "{group}\{cm:UninstallProgram,Foucault2}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Foucault2"; Filename: "{app}\Foucault2.exe"; Tasks: desktopicon; WorkingDir: "{app}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Foucault2"; Filename: "{app}\Foucault2.exe"; Tasks: quicklaunchicon; WorkingDir: "{app}"

[Run]
Filename: "{app}\Foucault2.exe"; Description: "{cm:LaunchProgram,Foucault2}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\Foucault2.url"

[Registry]
Root: HKCR; Subkey: ".foucault2"; ValueType: string; ValueName: ""; ValueData: "Foucault2"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Foucault2"; ValueType: string; ValueName: ""; ValueData: "Foucault2Mirror File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Foucault2\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\Foucault2.exe,0"
Root: HKCR; Subkey: "Foucault2\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\Foucault2.exe"" ""%1"""

