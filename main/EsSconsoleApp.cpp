#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSconsoleApp.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

ES_REFLECTION_REGISTRAR_BEGIN(essconsole)
  ES_REFLECTION_REGISTRAR_ENTRY(EsDocumentManager)
  ES_REFLECTION_REGISTRAR_ENTRY(EsDocument)
  ES_REFLECTION_REGISTRAR_ENTRY(EsScriptDocument)
  ES_REFLECTION_REGISTRAR_ENTRY(EsTextDocument)
  ES_REFLECTION_REGISTRAR_ENTRY(EsCompiledScriptDocument)
ES_REFLECTION_REGISTRAR_END
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

wxIMPLEMENT_APP(EsSconsoleApp);
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

static EsString _appFolderExtract()
{
  const EsPath& path = EsPath::createFromFilePath(EsPath::stdAppPathGet());
  return path.pathGet(
    as_<ulong>(EsPathFlag::ExcludeFile)|
    as_<ulong>(EsPathFlag::AppendSeparator)
  );
}
//--------------------------------------------------------------------------------

const EsString& EsSconsoleApp::appFolderGet()
{
  static const EsString sc_path = _appFolderExtract();

  return sc_path;
}
//--------------------------------------------------------------------------------

static EsString _settingsFolderGet()
{
  EsPath path = EsPath::createFromPath(EsPath::stdHomeGet());
  path.dirAppend(FRAMEWORK_VENDOR_SHORT);
  path.dirAppend(PRODUCT_NAME);

  if( !path.exists() )
    EsPath::pathCreate(path.pathGet(), EsString::null());

  return path.pathGet();
}
//--------------------------------------------------------------------------------

const EsString& EsSconsoleApp::settingsFolderGet()
{
  static const EsString sc_path = _settingsFolderGet();

  return sc_path;
}
//--------------------------------------------------------------------------------

EsString EsSconsoleApp::commonSettingsPathGet()
{
  const EsPath& path = EsPath::create(
    settingsFolderGet(),
    esT("settings"),
    esT("xml")
  );

  return path.pathGet();
}
//--------------------------------------------------------------------------------

const EsString& EsSconsoleApp::i18nFolderGet()
{
  static const EsString sc_path = EsString::format(
#ifdef ES_DEBUG
    esT("%s../locale"),
#else
    esT("%slocale"),
#endif
    appFolderGet()
  );

  return sc_path;
}
//--------------------------------------------------------------------------------

const EsString& EsSconsoleApp::docsFolderGet()
{
  static const EsString sc_path = EsString::format(
#ifdef ES_DEBUG
    esT("%s../../esfwx/doc"),
#else
    esT("%sdoc"),
#endif
    appFolderGet()
  );

  return sc_path;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleApp::EsSconsoleApp() :
wxApp(),
m_main(nullptr)
{
  m_singleInstGuard.Create(
    ES_ESSCONSOLE_APP_MUTEX
  );

  SetVendorName(
    PRODUCT_VENDOR_SHORT
  );
  SetVendorDisplayName(
    PRODUCT_VENDOR
  );
  SetAppDisplayName(
    PRODUCT_NAME esT(" ") PRODUCT_VERSION
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleApp::OnInitCmdLine(wxCmdLineParser& parser)
{
  // NB! this call resets all default parser options
  EsSconsoleCommandLineParams::parserInit(parser);
}
//--------------------------------------------------------------------------------

bool EsSconsoleApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
  m_cmdParams.parse(
    parser,
    m_params
  );

  if( !m_cmdParams.m_empty && m_cmdParams.m_showUsage )
  {
    parser.Usage();
    return false;
  }

  return true;
}
//--------------------------------------------------------------------------------

bool EsSconsoleApp::OnInit()
{
  bool ok = false;
  try
  {
    escore::reflectionInit();
    escomm::reflectionInit();
    esmath::reflectionInit();
    esscript::reflectionInit();

    essconsole::reflectionInit();

    // Set-up locale paths
    const EsString::Array& localePaths = { EsSconsoleApp::i18nFolderGet() };
    EsStringI18n& i18n = EsStringI18n::instanceGet();
    i18n.translationSearchPathsSet(
      localePaths
    );
    i18n.defaultLocaleSet( esT("en_EN") );

    const EsString& osLoc = EsStringI18n::osLocaleIdGet();
    const EsVariant& allLocs = i18n.availableLocalesGet();

    if( allLocs.has(osLoc) )
      i18n.currentLocaleSet(osLoc);

    // Load common application settings
    settingsLoad();

    // Perform basic initialization && cmdline parsing here
    if( !wxApp::OnInit() )
      return false;

    // Enable global tooltips by default
    wxToolTip::Enable(true);

    // Enable support for all known image formats
    wxInitAllImageHandlers();

    // Init application-specific global options
    appOptionsInit();

    // Create the main frame window
    m_main = new EsSconsoleMain;
    ES_ASSERT(m_main);

    // Perform one-time main form initialization as a separate step,
    // because application's m_main member should be set first
    //
    m_main->init();

    // We may want to execute console in command-line mode, without main window shown
    if(!m_cmdParams.m_empty)
      m_main->batchExecute(
        m_cmdParams
      );
    else
      m_main->commonAppSettingsApply();

    // Load main form settings from file
    m_main->settingsLoad();
    ok = m_main->Show();
  }
  catch(const EsException& ex)
  {
    wxLogError(
      ex.messageGet().as<wxString>()
    );
  }

  return ok;
}
//--------------------------------------------------------------------------------

int EsSconsoleApp::OnExit()
{
  return 0;
}
//--------------------------------------------------------------------------------

void EsSconsoleApp::appOptionsInit()
{
  wxSystemOptions::SetOption(
    ES_APP_OPT_MENU_IMG_WH,
    16
  );

  wxSystemOptions::SetOption(
    ES_APP_OPT_TOOLBAR_IMG_WH,
    16
  );

  wxSystemOptions::SetOption(
    ES_APP_OPT_TAB_IMG_WH,
    16
  );

  wxSystemOptions::SetOption(
    ES_APP_OPT_PANE_MIN_WIDTH,
    300
  );
  wxSystemOptions::SetOption(
    ES_APP_OPT_PANE_MIN_HEIGHT,
    140
  );

  wxSystemOptions::SetOption(
    ES_APP_OPT_MAINFRM_MIN_WIDTH,
    800
  );
  wxSystemOptions::SetOption(
    ES_APP_OPT_MAINFRM_MIN_HEIGHT,
    600
  );

#if defined(__WXMSW__)
  wxSystemOptions::SetOption(
    ES_APP_OPT_AUTO_UPDATE_URL,
    esT("http://vgromov.ru/dl/esfwx/tools/essconsole/updcast.xml")
  );
#endif
}
//--------------------------------------------------------------------------------

void EsSconsoleApp::settingsLoad()
{
  const EsString& path = commonSettingsPathGet();
  EsStreamIntf::Ptr settings = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::Read)|
    as_<ulong>(EsStreamFlag::File),
    path
  );

  m_params.load(settings);
}
//--------------------------------------------------------------------------------

void EsSconsoleApp::settingsSave()
{
  const EsString& path = commonSettingsPathGet();
  EsStreamIntf::Ptr settings = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::Write)|
    as_<ulong>(EsStreamFlag::File),
    path
  );

  m_params.save(settings);
}
//--------------------------------------------------------------------------------
