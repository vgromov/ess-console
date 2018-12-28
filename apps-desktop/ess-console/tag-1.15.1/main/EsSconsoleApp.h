#ifndef _es_sconsole_app_h_
#define _es_sconsole_app_h_

// Forward decls
class EsSconsoleMain;

// Define a new application
class EsSconsoleApp : public wxApp
{
public:
  EsSconsoleApp();

  bool OnInit() ES_OVERRIDE;
  int OnExit() ES_OVERRIDE;

  // Override default cmdline parsing
  void OnInitCmdLine(wxCmdLineParser& parser) ES_OVERRIDE;
  bool OnCmdLineParsed(wxCmdLineParser& parser) ES_OVERRIDE;

  // Common settings access
  EsSconsoleParams& settingsAccess() ES_NOTHROW { return m_params; }

  // Main window access
  EsSconsoleMain& mainWindowGet() ES_NOTHROW { return *m_main; }

  // Common settings serialization
  void settingsSave();

  // Static services for standard paths and files
  static const EsString& appFolderGet();
  static const EsString& settingsFolderGet();
  static EsString commonSettingsPathGet();
  static const EsString& i18nFolderGet();
  static const EsString& docsFolderGet();

protected:
  // Global application-specific options init
  void appOptionsInit();

  // Common settings serialization
  void settingsLoad();

protected:
  wxSingleInstanceChecker m_singleInstGuard;
  EsSconsoleParams m_params;
  EsSconsoleCommandLineParams m_cmdParams;
  EsSconsoleMain* m_main;
};

wxDECLARE_APP(EsSconsoleApp);
ES_DECL_REFLECTION_REGISTRAR_NO_EXPORT(essconsole)

#endif // _es_sconsole_app_h_
