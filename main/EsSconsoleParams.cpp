#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSconsoleParams.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleCommandLineParams::EsSconsoleCommandLineParams() :
m_inFileIsBin(false),
m_inFileIsEncrypted(false),
m_encryptOutput(false),
m_runScript(false),
m_exitUponCompletion(false),
m_showUsage(false),
m_empty(true)
{}
//--------------------------------------------------------------------------------

const wxString& EsSconsoleCommandLineParams::usageStringGet()
{
  static wxString s_result = esT("ess-console command-line usage:\n")
    esT("ess-console.exe [options] [switches]\nOptions:\n")
    esT("\t-f - input script file <filename>.<ess|cess|cesse>\n")
    esT("\t-o - script compiled output directory or file <filename>.<cess|cesse>\n")
    esT("\t-i - optional script include path(s), semicolon-separated\n")
    esT("\t-l - optional script binary link path(s), semicolon-separated\n")
    esT("\t-e - script execution entry point, optionally followed by parameter values, semicolon-separated\n")
    esT("\t     example: -e <someFunction>[;\"param 0\";\"param 1\";\"param 2\"]\n")
    esT("Switches:\n")
    esT("\t-d - preserve debug information in compiled script\n")
    esT("\t-c - encrypt the compiled binary file\n")
    esT("\t-r - run loaded script file\n")
    esT("\t-x - exit console upon successfull operation completion\n")
    esT("\t-n - export translatable strings to the *.pot file alongside compiled script binary when saving the latter\n")
    esT("\t-? - show this information\n")
    esT("\t-h - alias of -?\n");

  return s_result;
}
//---------------------------------------------------------------------------

void EsSconsoleCommandLineParams::parserInit(wxCmdLineParser& parser)
{
  parser.Reset();
  parser.DisableLongOptions();
  parser.AddUsageText(
    usageStringGet()
  );

  parser.AddOption("f");
  parser.AddOption("o");
  parser.AddOption("i");
  parser.AddOption("l");
  parser.AddOption("e");

  parser.AddSwitch("d");
  parser.AddSwitch("c");
  parser.AddSwitch("r");
  parser.AddSwitch("x");
  parser.AddSwitch("n");
  parser.AddSwitch("?");
  parser.AddSwitch("h");
}
//--------------------------------------------------------------------------------

void EsSconsoleCommandLineParams::parse(wxCmdLineParser& parser, EsSconsoleParams& params)
{
  if(
    wxCMD_SWITCH_ON == parser.FoundSwitch("h") ||
    wxCMD_SWITCH_ON == parser.FoundSwitch("?")
  )
  {
    m_showUsage = true;
    m_empty = false;

    return;
  }

  if( wxCMD_SWITCH_ON == parser.FoundSwitch("c") )
  {
    m_encryptOutput = true;
    m_empty = false;
  }

  if( wxCMD_SWITCH_ON == parser.FoundSwitch("r") )
  {
    m_runScript = true;
    m_empty = false;
  }

  if( wxCMD_SWITCH_ON == parser.FoundSwitch("x") )
  {
    m_exitUponCompletion = true;
    m_empty = false;
  }

  if( wxCMD_SWITCH_ON == parser.FoundSwitch("d") )
  {
    params.m_inclDebugInfo = true;
    m_empty = false;
  }

  if( wxCMD_SWITCH_ON == parser.FoundSwitch("n") )
  {
    params.m_translatablesSave = true;
    m_empty = false;
  }

  wxString tmp;
  if(parser.Found("i", &tmp))
  {
    EsStringTokenizer tok(tmp.t_str(), esT(";"));
    while(tok.get_moreTokens())
    {
      const EsPath& fname = EsPath::createFromPath(tok.get_nextToken());

      params.m_includes.push_back(
        fname.pathGet(
          as_<ulong>(EsPathFlag::AsIs)
        )
      );
    }

    m_empty = false;
  }

  if(parser.Found("l", &tmp))
  {
    EsStringTokenizer tok(tmp.t_str(), esT(";"));
    while(tok.get_moreTokens())
    {
      const EsPath& fname = EsPath::createFromPath(tok.get_nextToken());

      params.m_linkPaths.push_back(
        fname.pathGet(
          as_<ulong>(EsPathFlag::AsIs)
        )
      );
    }

    m_empty = false;
  }

  if(parser.Found("f", &tmp))
  {
    m_inFile = tmp.t_str();
    const EsPath& fname = EsPath::createFromFilePath(m_inFile);

    if( esT("cess") == fname.fileExtGet() )
      m_inFileIsBin = true;
    else if( esT("cesse") == fname.fileExtGet() )
    {
      m_inFileIsBin = true;
      m_inFileIsEncrypted = true;
    }

    if(!m_inFileIsBin)
    {
      // Try to locate input file
      bool exists = fname.fileExists();
      if(!exists)
      {
        for(auto const& path : params.m_includes)
        {
          if(!fname.fileExists(path))
            continue;

          m_inFile = fname.pathGet(
            as_<ulong>(EsPathFlag::Default), 
            path
          );
          exists = true;
          break;
        }
      }

      if(!exists)
      {
        for(auto const& path : params.m_linkPaths)
        {
          if(!fname.fileExists(path))
            continue;

          m_inFile = fname.pathGet(
            as_<ulong>(EsPathFlag::Default),
            path
          );
          exists = true;
          break;
        }
      }

      if(!exists)
        EsException::Throw(
          esT("Input file '%s' specified in command line option 'f' could not be found"),
          m_inFile
        );
    }

    m_empty = false;
  }

  bool ofnameIsFile = false;
  if( parser.Found("o", &tmp) && !m_inFileIsBin )
  {
    EsPath ofname = EsPath::createFromFilePath(tmp.t_str());
    const EsString& ext = ofname.fileExtGet();

    if( esT("cesse") == ext )
    {
      m_encryptOutput = true;
      ofnameIsFile = true;
    }
    else if( esT("cess") == ext )
      ofnameIsFile = true;

    if( !ofnameIsFile )
    {
      const EsPath& ifname = EsPath::createFromFilePath(m_inFile);

      ofname = EsPath::create(
        tmp.t_str(),
        ifname.fileNameGet(),
        m_encryptOutput ?
        esT("cesse") :
        esT("cess")
      );

      m_ofile = ofname.pathGet(
        as_<ulong>(EsPathFlag::AsIs)
      ).c_str();
    }

    m_empty = false;
  }

  if( parser.Found("e", &tmp) )
  {
    EsStringTokenizer tok(tmp.t_str(), esT(";"));
    EsVariant::Array eparams;

    if( tok.get_moreTokens() )
    {
      size_t cnt = 0;
      while( tok.get_moreTokens() )
      {
        const EsString& token = tok.get_nextToken();
        if( 0 == cnt )
          m_entry = EsString::fromString(
            token,
            EsString::StrQuote
          );
        else
        {
          const EsString& arg = EsString::fromString(
            token,
            EsString::StrQuote|
            EsString::StrNoCEscape
          );

          eparams.push_back(arg);
        }
        ++cnt;
      }
    }
    else
      m_entry = tmp.t_str();

    m_params = eparams;
    m_empty = false;
  }
}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleParams::EsSconsoleParams() :
m_inclDebugInfo(false),
m_translatablesSave(false)
{}
//--------------------------------------------------------------------------------

void EsSconsoleParams::load(const EsStreamIntf::Ptr& stream)
{
  EsStreamContextExistingScope scope(stream, esT("Params"));
  if( scope.isOk() )
  {
    m_inclDebugInfo = stream->valueRead(
      esT("IncludeDebug"), 
      false
    ).asBool();
    
    m_translatablesSave = stream->valueRead(
      esT("SaveTranslatables"), 
      false
    ).asBool();
    
    m_includes = stream->valueRead(
      esT("IncludesSearch"), 
      EsString::nullArray()
    ).asStringCollection();
    
    m_linkPaths = stream->valueRead(
      esT("LibrariesSearch"), 
      EsString::nullArray()
    ).asStringCollection();
  }
}
//---------------------------------------------------------------------------

void EsSconsoleParams::save(const EsStreamIntf::Ptr& stream) const
{
  EsStreamContextExistingOrNewScope scope(stream, esT("Params"));
  if( scope.isOk() )
  {
    stream->valueWrite(
      esT("IncludeDebug"), 
      m_inclDebugInfo
    );

    stream->valueWrite(
      esT("SaveTranslatables"), 
      m_translatablesSave
    );

    stream->valueWrite(
      esT("IncludesSearch"), 
      m_includes
    );

    stream->valueWrite(
      esT("LibrariesSearch"), 
      m_linkPaths
    );
  }
}
//--------------------------------------------------------------------------------
