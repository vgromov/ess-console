#ifndef _es_sconsole_params_h_
#define _es_sconsole_params_h_

/// Common ES Console application parameters
///
struct EsSconsoleParams
{
  EsSconsoleParams();

  /// Parameters serialization
  void load(const EsStreamIntf::Ptr& stream);
  void save(const EsStreamIntf::Ptr& stream) const;

  /// Parameters data
  EsString::Array m_includes;
  EsString::Array m_linkPaths;
  bool m_inclDebugInfo;
  bool m_translatablesSave;
};
//---------------------------------------------------------------------------

/// Command line ES console parameters && settings overrides
/// 
struct EsSconsoleCommandLineParams
{
  EsSconsoleCommandLineParams();

  /// Init command line parser
  static void parserInit(wxCmdLineParser& parser);

  /// Parse command line into parameters
  void parse(wxCmdLineParser& parser, EsSconsoleParams& params);

  /// Execute specific entry with parameters
  EsVariant m_params;
  EsString m_entry;

  /// The rest of command line data
  EsString m_inFile;
  EsString m_ofile;
  bool m_inFileIsBin;
  bool m_inFileIsEncrypted;
  bool m_encryptOutput;
  bool m_runScript;
  bool m_exitUponCompletion;
  bool m_showUsage;
  bool m_empty;                        ///< No command line parameters were parsed (empty command line)

private:
  /// Get command line usage info
  static const wxString& usageStringGet();

private:
  EsSconsoleCommandLineParams(const EsSconsoleCommandLineParams&) ES_REMOVEDECL;
  EsSconsoleCommandLineParams& operator=(const EsSconsoleCommandLineParams&) ES_REMOVEDECL;
};
//--------------------------------------------------------------------------------

#endif // _es_sconsole_params_h_
