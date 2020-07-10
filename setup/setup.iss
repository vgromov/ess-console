#include "setup_defs.iss"
; Localized messages file
#include "setup_messages.iss"

[Setup]
AlwaysShowGroupOnReadyPage=True
AlwaysShowDirOnReadyPage=True
AppName={#PRODUCT_NAME}
AppVersion={#PRODUCT_VERSION_STRING}
AppCopyright={#VENDOR_SHORT} {#COPYRIGHT}
AppMutex={#APP_UID},Global\{#APP_UID}
AppId={#APP_UID}
SetupIconFile={#APP_ICO_SRC}\{#INSTALLER_ICON}
AppPublisher={#VENDOR}
AppPublisherURL={#VENDOR_URL}
AppSupportURL={#SUPPORT_URL}
AppUpdatesURL={#UPDATES_URL}
AppContact={#VENDOR_EMAIL}
AppSupportPhone={#VENDOR_PHONE}
UninstallDisplayName={cm:MSG_UNINSTALL_SHORTCUT_NAME}
UninstallDisplayIcon={uninstallexe}
VersionInfoVersion={#PRODUCT_VERSION_STRING}
VersionInfoCompany={#VENDOR}
VersionInfoDescription={#PRODUCT_NAME}
VersionInfoTextVersion={#PRODUCT_VERSION_STRING}
VersionInfoCopyright={#COPYRIGHT}
VersionInfoProductName={#PRODUCT_NAME}
VersionInfoProductVersion={#PRODUCT_VERSION_STRING}
VersionInfoProductTextVersion={#PRODUCT_VERSION_STRING}
OutputDir={#SETUP_OUTPUT_DIR}
OutputBaseFilename={#PRODUCT_NAME_INTERNAL}.{#PRODUCT_VERSION_STRING}.{#SETUP_SUFFIX}
OutputManifestFile={#PRODUCT_NAME_INTERNAL}.{#PRODUCT_VERSION_STRING}.{#SETUP_SUFFIX}.manifest.txt
DefaultDirName={reg:{#HKLM_UNINSTALL_KEY},InstallLocation|{commonpf}\{#VENDOR_SHORT}\{#APP_DIR}}
DefaultGroupName={#VENDOR_SHORT}\{#PRODUCT_NAME}{#SETUP_BITS}
SignTool=signtoolEV
SignedUninstaller=True
SolidCompression=True
MinVersion=0,6.0
#if "64" == SETUP_BITS
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
#endif

#include "winsparkle\winsparkle.iss"

[Files]
; MSVC Redist
Source: "{#VCREDIST_ROOT}\vc_redist.{#VCREDIST_BITS_SUFFIX}.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall; Components: Prerequisites

; WX libraries
Source: "{#WX_REDIST}\wxbase{#WX_VER}_{#COMPILER_VER}{#WX_BITS_SUFFIX}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#WX_REDIST}\wxmsw{#WX_VER}_core_{#COMPILER_VER}{#WX_BITS_SUFFIX}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#WX_REDIST}\wxmsw{#WX_VER}_adv_{#COMPILER_VER}{#WX_BITS_SUFFIX}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#WX_REDIST}\wxmsw{#WX_VER}_aui_{#COMPILER_VER}{#WX_BITS_SUFFIX}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#WX_REDIST}\wxmsw{#WX_VER}_stc_{#COMPILER_VER}{#WX_BITS_SUFFIX}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program

; ESFWX libraries
Source: "{#APP_BIN_SRC}\escore_{#ESCORE_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\escomm_{#ESCOMM_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\esmath_{#ESMATH_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\esscript_{#ESSCRIPT_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\esmdi_{#ESMDI_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\escoregui_{#ESCOREGUI_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program
Source: "{#APP_BIN_SRC}\esmdigui_{#ESMDIGUI_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Program

; ESFWX GUI libraries
Source: "{#APP_BIN_SRC}\escoregui_{#ESCOREGUI_VER_SUFFIX}_{#COMPILER_VER}.dll"; DestDir: "{app}"; Components: Program

; Main application
Source: "{#APP_BIN_SRC}\ess-console_{#APP_VER_SUFFIX}_{#COMPILER_VER}.exe"; DestDir: "{app}"; DestName: "ess-console.exe"; Components: Program

; Help files
Source: "{#HELP_CORE_DIR}\*.pdf"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Help

[Components]
Name: "Prerequisites"; Description: "{cm:MSG_PREREQUISITES_COMP_DESCRIPTION}"; Types: custom compact full
Name: "Common"; Description: "{cm:MSG_COMMON_COMP_DESCRIPTION}"; Types: custom compact full
Name: "Help"; Description: "{cm:MSG_HELP_COMP_DESCRIPTION}"; Types: custom compact full
Name: "Program"; Description: "{cm:MSG_PROGRAM_COMP_DESCRIPTION}"; Types: custom compact full
Name: "AutoUpdate"; Description: "{cm:MSG_AUTOUPDATE_COMP_DESCRIPTION}"; Types: custom compact full

[Tasks]
; Tasks: Shortcuts
Name: "desktop_shortcut"; Description: {cm:MSG_CREATE_DESKTOP_SHORTCUT}; Components: Program; Flags: unchecked
Name: "desktop_shortcut\user"; Description: {cm:MSG_CREATE_DESKTOP_SHORTCUT_USER}; Components: Program; Flags: exclusive unchecked
Name: "desktop_shortcut\all"; Description: {cm:MSG_CREATE_DESKTOP_SHORTCUT_ALL}; Components: Program; Flags: exclusive
Name: "quicklaunch_shortcut"; Description: {cm:MSG_CREATE_QUICK_LAUNCH}; Components: Program; Flags: unchecked

; Postinstall run
Name: "run_postinstall"; Description: "{cm:MSG_RUN_APP_AFTER_INSTALLATION}"; Components: Program

[Languages]
Name: en; MessagesFile: compiler:Default.isl
Name: ru; MessagesFile: compiler:Languages\Russian.isl

[Dirs]
Name: "{app}"; Flags: uninsalwaysuninstall; Components: Common
Name: "{app}\doc"; Flags: uninsalwaysuninstall; Components: Help

[Run]
; Tasks: vcrt_install
Filename: "{tmp}\vc_redist.{#VCREDIST_BITS_SUFFIX}.exe"; Parameters: "/q"; Flags: waituntilterminated; StatusMsg: "{cm:MSG_INSTALLING_VCRT}"; Components: Prerequisites; Check: not vcrtInstalled('{#VCREDIST_YEAR}', '{#VCREDIST_BITS_SUFFIX}')

; Tasks: run_postinstall
Filename: "{app}\{#APP_FILE_DEST}"; WorkingDir: "{app}"; Flags: nowait postinstall skipifsilent; Description: "{cm:MSG_POSTINSTALL_RUN_SHELL}"; Components: Program

[Icons]
Name: "{group}\{cm:MSG_SHORTCUT_NAME}"; Filename: "{app}\{#APP_FILE_DEST}"; WorkingDir: "{app}"; IconFilename: "{app}\{#APP_FILE_DEST}"; Comment: "{cm:MSG_SHELL_SHORTCUT_COMMENT}"; Components: Program
Name: "{group}\{cm:MSG_UNINSTALL_SHORTCUT_NAME}"; Filename: "{uninstallexe}"; WorkingDir: "{app}"; Comment: "{cm:MSG_UNINSTALL_SHORTCUT_COMMENT}"; Components: Program
Name: "{userdesktop}\{cm:MSG_SHORTCUT_NAME}"; Filename: "{app}\{#APP_FILE_DEST}"; WorkingDir: "{app}"; IconFilename: "{app}\{#APP_FILE_DEST}"; Comment: "{cm:MSG_SHELL_SHORTCUT_COMMENT}"; Components: Program; Tasks: desktop_shortcut\user
Name: "{commondesktop}\{cm:MSG_SHORTCUT_NAME}"; Filename: "{app}\{#APP_FILE_DEST}"; WorkingDir: "{app}"; IconFilename: "{app}\{#APP_FILE_DEST}"; Comment: "{cm:MSG_SHELL_SHORTCUT_COMMENT}"; Components: Program; Tasks: desktop_shortcut\all
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{cm:MSG_SHORTCUT_NAME}"; Filename: "{app}\{#APP_FILE_DEST}"; WorkingDir: "{app}"; IconFilename: "{app}\{#APP_FILE_DEST}"; Comment: "{cm:MSG_SHELL_SHORTCUT_COMMENT}"; Components: Program; Tasks: quicklaunch_shortcut

[UninstallDelete]
Type: dirifempty; Name: "{app}"

[Code]
// 'Uninstall an old version' shared code
#include "iss-es\esOldVersionUninstall.iss"
// Find VC Redistributable version
#include "iss-es\esVcRedistFind.iss"

// check-install prerequisites
function InitializeSetup(): Boolean;
begin
  result := True;

  // Optionally remove an old version with legacy APP_UID string '{..UID..}'
  esAppUninstallOldVersion(
    '%7b{#UNINSTALL_KEY}%7d', 
    ''
  );
  
  if not esAppUninstallOldVersion( 
      '{#UNINSTALL_KEY}',
      CustomMessage('MSG_WILL_AUTO_UNINSTALL')
  ) 
  then 
    result := False
end;

/// Skip some pages
///
function ShouldSkipPage(PageID: Integer): Boolean;
begin
	result := (PageID = wpSelectComponents);
end;
//---------------------------------------------------------------------------