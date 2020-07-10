#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSconsoleOutputBase.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleOutputBase::EsSconsoleOutputBase(wxWindow* parent) :
wxStyledTextCtrl(
  parent
),
m_ptb(nullptr)
{
  SetUndoCollection(false);
  SetReadOnly(true);

  Bind(
    wxEVT_CONTEXT_MENU,
    &EsSconsoleOutputBase::onContextMenu,
    this
  );

  Bind(
    wxEVT_STC_DOUBLECLICK,
    &EsSconsoleOutputBase::onDoubleClick,
    this
  );
}
//--------------------------------------------------------------------------------

EsSconsoleOutputBase::~EsSconsoleOutputBase()
{
  Unbind(
    wxEVT_CONTEXT_MENU,
    &EsSconsoleOutputBase::onContextMenu,
    this
  );

  Unbind(
    wxEVT_STC_DOUBLECLICK,
    &EsSconsoleOutputBase::onDoubleClick,
    this
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::ctxMenuInit()
{
  ES_ASSERT(m_pmnu);

  m_pmnu->Append(
    usrID_COPY,
    _("Copy\tCTRL-C").as<wxString>(),
    _("Copy selected log contents to clipboard").as<wxString>()
  );
  m_pmnu->AppendSeparator();
  m_pmnu->Append(
    usrID_SELECT_ALL,
    _("Select all\tCTRL-A").as<wxString>(),
    _("Select all log contents").as<wxString>()
  );
  m_pmnu->Append(
    usrID_CLEARALL,
    _("Clear all").as<wxString>(),
    _("Clear entire log contents").as<wxString>()
  );
  m_pmnu->AppendSeparator();
  m_pmnu->Append(
    usrID_GOTO,
    _("Goto location").as<wxString>(),
    _("Goto specified source location").as<wxString>()
  );

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_pmnu.get(),
    usrID_COPY,
    mnuimgsze,
    wxART_OTHER,
    wxART_COPY
  );
  EsUtilities::menuItemBitmapSet(
    m_pmnu.get(),
    usrID_CLEARALL,
    mnuimgsze,
    wxART_OTHER,
    wxART_DELETE
  );
  EsUtilities::menuItemBitmapSet(
    m_pmnu.get(),
    usrID_GOTO,
    mnuimgsze,
    wxART_OTHER,
    wxART_GOTO_FIRST
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::toolBarInit()
{
  wxMenuSharedPtr pmnu = ctxMenuGet();

  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_SELECT_ALL,
    wxART_TOOLBAR,
    esART_SELECT_ALL
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_COPY,
    wxART_TOOLBAR,
    wxART_COPY
  );
  m_ptb->AddSeparator();
  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_CLEARALL,
    wxART_TOOLBAR,
    wxART_DELETE
  );
  m_ptb->AddSeparator();
  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_GOTO,
    wxART_TOOLBAR,
    wxART_GOTO_FIRST
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::evtHandlersSet(wxEvtHandler* subj, bool set)
{
  ES_ASSERT(subj);

  if(set)
  {
    subj->Bind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onSelectAll,
      this,
      usrID_SELECT_ALL
    );
    subj->Bind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onCopy,
      this,
      usrID_COPY
    );
    subj->Bind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onClearAll,
      this,
      usrID_CLEARALL
    );
    subj->Bind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onGoto,
      this,
      usrID_GOTO
    );
  }
  else
  {
    subj->Unbind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onSelectAll,
      this,
      usrID_SELECT_ALL
    );
    subj->Unbind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onCopy,
      this,
      usrID_COPY
    );
    subj->Unbind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onClearAll,
      this,
      usrID_CLEARALL
    );
    subj->Unbind(
      wxEVT_MENU,
      &EsSconsoleOutputBase::onGoto,
      this,
      usrID_GOTO
    );
  }
}
//--------------------------------------------------------------------------------

wxMenuSharedPtr EsSconsoleOutputBase::ctxMenuGet()
{
  if(m_pmnu)
    return m_pmnu;

  m_pmnu = ES_MAKE_SHARED(wxMenu);
  ES_ASSERT(m_pmnu);

  ctxMenuInit();

  evtHandlersSet(
    this,
    true
  );

  return m_pmnu;
}
//--------------------------------------------------------------------------------

wxToolBar* EsSconsoleOutputBase::toolBarGet(wxWindow* parent)
{
  if(m_ptb)
    return m_ptb;

  m_ptb = new wxToolBar(
    parent,
    wxID_ANY,
    wxDefaultPosition,
    wxDefaultSize,
    wxTB_FLAT|wxTB_TOP|wxTB_HORZ_TEXT
  );
  ES_ASSERT(m_ptb);

  m_ptb->SetToolBitmapSize(
    EsUtilities::appSizePropertyGet(ES_APP_OPT_TOOLBAR_IMG_WH)
  );

  toolBarInit();

  m_ptb->AddStretchableSpace();
  m_ptb->Realize();

  evtHandlersSet(
    m_ptb,
    true
  );

  return m_ptb;
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onContextMenu(wxContextMenuEvent& evt)
{
  wxMenuSharedPtr pmenu = ctxMenuGet();
  ES_ASSERT(pmenu);

  PopupMenu(
    pmenu.get()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onDoubleClick(wxStyledTextEvent& evt)
{
  // Parse error position, open file and select position
  const wxString& txt = GetLine(
    evt.GetLine()
  );

  txtParseForFilePositionAndGoto(txt);
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onSelectAll(wxCommandEvent& ES_UNUSED(evt))
{
  SetSelection(
    -1,
    -1
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onCopy(wxCommandEvent& ES_UNUSED(evt))
{
  Copy();
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onClearAll(wxCommandEvent& ES_UNUSED(evt))
{
  textClearAll();
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::onGoto(wxCommandEvent& ES_UNUSED(evt))
{
  txtParseForFilePositionAndGoto(
    GetLine(
      GetCurrentLine()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::styleInit(int lexerId)
{
  const EsSconsoleOptions& opts = wxGetApp().mainWindowGet().optionsGet();
  StyleClearAll();
  SetLexer(lexerId);
  StyleSetFont(
    wxSTC_STYLE_DEFAULT,
    *opts.m_fntTxt
  );
  StyleSetFont(
    wxSTC_STYLE_CONTROLCHAR,
    *opts.m_fntLineNum
  );
  SetCaretLineVisible(true);
  SetBackSpaceUnIndents(true);
  SetTabIndents(true);
  SetUseTabs(false);
  SetIndent(2);
  SetWrapMode(wxSTC_WRAP_NONE);

  EsSyntaxHighlighter::lexStylesApply(
    this,
    EsSyntaxHighlighter::lexNodeByLexIdGet(lexerId)
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::textClearAll()
{
  wxWindowUpdateLocker lock(this);

  SetReadOnly(false);
  ClearAll();
  SetReadOnly(true);
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::textLineAppend(const wxString& txt)
{
  wxWindowUpdateLocker lock(this);

  bool scrollToEnd = GetLastPosition() == GetCurrentPos();

  SetReadOnly(false);
  AppendText(txt + esT("\n"));
  SetReadOnly(true);

  if(scrollToEnd)
  {
    int pos = GetLastPosition();
    SetCurrentPos( pos );
    ShowPosition(pos);
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleOutputBase::txtParseForFilePositionAndGoto(const wxString& txt, bool isExecMode /*= false*/)
{
  if(txt.IsEmpty())
    return;

  EsRegEx re(
    esT("(?:in\\s+'([^']+)'\\s+)?at\\s+\\(([0-9]+)(?:,\\s?([0-9]+))?\\)"),
    as_<ulong>(EsRegExCompileFlag::DEFAULT)|
    as_<ulong>(EsRegExCompileFlag::ICASE)
  );
  ES_ASSERT(re.isOk());

  EsString in = txt.t_str();
  re.set_text(in);
  if(!re.get_matches())
    return;

  ulong start = 0;
  ulong len = 0;

  EsString file;
  ulong line = 0;
  ulong col = 0;
  if(
    re.matchGet(
      start,
      len,
      1            //< File match
    ) &&
    len
  )
  {
    file = in.substr(
      start,
      len
    );

    if(file.empty())
      return;

    start += len;
  }

  if(
    re.matchGet(
      start,
      len,
      2           //< Line match
    ) &&
    len
  )
  {
    line = EsString::toULong(
      in.substr(
        start,
        len
      )
    );

    start += len;
  }

  if(
    re.matchGet(
      start,
      len,
      3           //< Column match
    ) &&
    len
    )
  {
    col = EsString::toULong(
      in.substr(
        start,
        len
      )
    );
  }

  if(line)
    --line;
  if(col)
    --col;

  const EsVariant::Array& payload = {
    file,
    line,
    col,
    isExecMode
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::ScriptOpenAndSetPosition),
    payload
  );
}
//--------------------------------------------------------------------------------
