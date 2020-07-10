#include "ess_console_pch.h"
#pragma hdrstop

#include "EsTextEditorViewBase.h"
#include <wx/tokenzr.h>
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsTextEditorViewBase::EvtHandler::EvtHandler(EsTextEditorViewBase& owner) ES_NOTHROW :
EsEventSubscriber(
  ES_EVTC_MDI ES_EVTC_AND
  ES_EVTC_I18N
),
m_owner(owner)
{}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  ES_ASSERT(evt);

  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if(ES_EVTC_MDI == cat)
  {
    if(!m_owner.m_doc)
      return;

    const EsString& key = payload.isEmpty() ?
      EsString::null() :
      payload[0].asString();

    if(m_owner.m_doc->keyGet() != key)
      return;

    void* sender = nullptr;

    switch(as_<EsMdiEvt>(id))
    {
    case EsMdiEvt::DocumentChanged:
      sender = payload[2].asPointer();
      if(sender == &m_owner)
        return;
      m_owner.onDocumentChanged(
        payload[1].asString()
      );
      break;
    case EsMdiEvt::DocumentOpened:
      m_owner.onDocumentOpened();
      break;
    case EsMdiEvt::DocumentSideloadChanged:
      sender = payload[2].asPointer();
      if(sender == &m_owner)
        return;
      m_owner.onDocumentSideloadChanged(
        payload[1].asString()
      );
      break;
    case EsMdiEvt::DocumentStateChanged:
      m_owner.onDocumentStateChanged();
      break;
    }
  }
  else if(ES_EVTC_I18N == cat && EsEvtI18n::LocaleChanged == as_<EsEvtI18n>(id))
  {
    m_owner.onI18nLocaleChanged(
      evt->payloadGet().asString()
    );
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsTextEditorViewBase::EsTextEditorViewBase(wxWindow *parent, wxWindowID id, long style, const wxString& className) :
  wxStyledTextCtrl(
    parent,
    id,
    wxDefaultPosition,
    wxDefaultSize,
    style,
    className
  ),
  m_handler(*this),
  m_mnuEditBm(nullptr),
  m_lexNode(nullptr),
  m_searchReplacePos(0),
  m_braceBeg(-1),
  m_braceEnd(-1),
  m_searchReplaceDirection(true)
{
  Bind(wxEVT_CONTEXT_MENU, &EsTextEditorViewBase::onContextMenu, this);
  Bind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);
  Bind(wxEVT_STC_DOUBLECLICK, &EsTextEditorViewBase::onDblClick, this);
  Bind(wxEVT_STC_UPDATEUI, &EsTextEditorViewBase::onStcUiUpdate, this);
  Bind(wxEVT_STC_MARGINCLICK, &EsTextEditorViewBase::onMarginClick, this);
  Bind(wxEVT_STC_AUTOCOMP_SELECTION, &EsTextEditorViewBase::onAutoCompleting, this);
}
//--------------------------------------------------------------------------------

EsTextEditorViewBase::~EsTextEditorViewBase()
{
  Unbind(wxEVT_CONTEXT_MENU, &EsTextEditorViewBase::onContextMenu, this);
  Unbind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);
  Unbind(wxEVT_STC_DOUBLECLICK, &EsTextEditorViewBase::onDblClick, this);
  Unbind(wxEVT_STC_UPDATEUI, &EsTextEditorViewBase::onStcUiUpdate, this);
  Unbind(wxEVT_STC_MARGINCLICK, &EsTextEditorViewBase::onMarginClick, this);
  Unbind(wxEVT_STC_AUTOCOMP_SELECTION, &EsTextEditorViewBase::onAutoCompleting, this);
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::isStyle(int hlStyleId, EsSyntaxHighlighterId hlId) const ES_NOTHROW
{
  if( !isStyled() )
    return false;

  ES_ASSERT(m_lexNode);
  ES_ASSERT(hlId > -1);
  ES_ASSERT(hlId < stcItemsCount);

  return hlStyleId == m_lexNode->highlighters[hlId].lexHlId;
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::isStyleInRange(int hlStyleId, EsSyntaxHighlighterId hlIdStart, EsSyntaxHighlighterId hlIdEnd) const ES_NOTHROW
{
  if( !isStyled() )
    return false;

  ES_ASSERT(m_lexNode);
  ES_ASSERT(hlIdStart > -1);
  ES_ASSERT(hlIdStart < stcItemsCount);
  ES_ASSERT(hlIdEnd > -1);
  ES_ASSERT(hlIdEnd < stcItemsCount);
  if( hlIdStart > hlIdEnd )
    std::swap(hlIdStart, hlIdEnd);
  
  for(int hlId = hlIdStart; hlId <= hlIdEnd; ++hlId)
    if(hlStyleId == m_lexNode->highlighters[hlId].lexHlId)
      return true;

  return false;
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSearchReplaceReset()
{
  if(m_searchReplaceDirection)
    m_searchReplacePos = 0;
  else
    m_searchReplacePos = GetLastPosition();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSearchReplaceDirectionSet(bool down)
{
  m_searchReplaceDirection = down;
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSearchReplaceCurrentRangeGet(int& fromPos, int& toPos)
{
  fromPos = -1;
  toPos = -1;

  if( m_txtLookup.IsEmpty() )
    return;

  if( textSearchReplaceDirectionGet() )
  {
    fromPos = textSearchReplacePosGet()-m_txtLookup.Length();
    toPos = textSearchReplacePosGet();
  }
  else
  {
    fromPos = textSearchReplacePosGet();
    toPos = textSearchReplacePosGet()+m_txtLookup.Length();
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSearchReplacePositionSetCurrent()
{
  m_searchReplacePos = GetCurrentPos();
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::textSearch(const wxString& txt, int flags)
{
  m_txtLookup = txt;

  if(txt.IsEmpty())
    return false;

  if(textSearchIsFinished())
    return false;

  int pos = -1;
  if(m_searchReplaceDirection)
  {
    pos = FindText(
      m_searchReplacePos,
      GetLastPosition(),
      txt,
      flags
    );

    if(-1 < pos)
      m_searchReplacePos = pos + txt.Length();
    else
      m_searchReplacePos = GetLastPosition();
  }
  else
  {
    pos = FindText(
      m_searchReplacePos,
      0,
      txt,
      flags
    );

    if(-1 < pos)
      m_searchReplacePos = pos;
    else
      m_searchReplacePos = 0;
  }

  return !textSearchIsFinished();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSearchReplacePosFixup()
{
  if(m_searchReplacePos > GetLastPosition())
    m_searchReplacePos = GetLastPosition();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textReplaceInternal(const wxString& txtOld, const wxString& txtNew)
{
  if(m_searchReplaceDirection)
    Replace(
      m_searchReplacePos-txtOld.Length(),
      m_searchReplacePos,
      txtNew
    );
  else
    Replace(
      m_searchReplacePos,
      m_searchReplacePos+txtOld.Length(),
      txtNew
    );

  // Fixup m_searchReplacePos after replace
  textSearchReplacePosFixup();
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::textReplace(const wxString& txtOld, const wxString& txtNew, int flags, bool all)
{
  if(txtOld.IsEmpty())
    return false;

  if(all)
  {
    textSearchReplaceReset();

    while(textSearch(txtOld, flags))
      textReplaceInternal(
        txtOld,
        txtNew
      );

    return true;
  }
  else
  {
    if(textSearch(txtOld, flags))
    {
      textReplaceInternal(
        txtOld,
        txtNew
      );

      return true;
    }
  }

  return false;
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::textSearchIsFinished() const
{
  if(m_searchReplaceDirection)
    return m_searchReplacePos == GetLastPosition();
  else
    return 0 == m_searchReplacePos;
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::currentPositionSet(int line, int col)
{
  if(-1 >= line)
    return;

  if(-1 >= col)
    col = 0;

  int pos = PositionFromLine(line)+col;
  GotoPos(pos);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onEditorContentChange(wxStyledTextEvent& evt)
{
  if(!m_doc)
    return;

  int modType = evt.GetModificationType();
  static const int sc_modmaskContent =
    wxSTC_MOD_INSERTTEXT|
    wxSTC_MOD_DELETETEXT|
    wxSTC_PERFORMED_UNDO|
    wxSTC_PERFORMED_REDO|
    wxSTC_MULTISTEPUNDOREDO|
    wxSTC_LASTSTEPINUNDOREDO|
    wxSTC_MULTILINEUNDOREDO;

  if(modType & sc_modmaskContent)
  {
    m_doc->valueSet(
      esT("content"),
      textGet()
    );

    m_doc->documentChangedNotify(
      esT("content"),
      this
    );

    // Synchronize markers
    if(
      (modType & (wxSTC_MOD_INSERTTEXT|wxSTC_MOD_DELETETEXT)) &&
      evt.GetLinesAdded()
    )
    {
      onEditorLinesChanged();
    }
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onDblClick(wxStyledTextEvent& ES_UNUSED(evt))
{
  int pos = GetCurrentPos();
  int fromPos = -1;
  if( -1 < pos )
    fromPos = WordStartPosition(
      pos,
      true
    );

  if( 0 > fromPos )
    return;

  int toPos = WordEndPosition(
    pos,
    true
  );
  if( 0 > toPos )
    return;

  SetSelection(
    fromPos,
    toPos
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onStcUiUpdate(wxStyledTextEvent& evt)
{
  int flags = evt.GetUpdated();

  if( flags & wxSTC_UPDATE_SELECTION )
  {
    int fromPos;
    int toPos;
    GetSelection(
      &fromPos,
      &toPos
    );

    highlightClear();

    if(
      canHighlightSelection(
        fromPos,
        toPos
      )
    )
    {
      const wxString& word = GetTextRange(
        fromPos,
        toPos
      );
      ES_ASSERT(!word.IsEmpty());

      highlight(
        word,
        -1,
        -1,
        true
      );
    }

    braceHighlightUpdate(fromPos);
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onMarginClick(wxStyledTextEvent& evt)
{
  // Do nothing by default
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onAutoCompleting(wxStyledTextEvent& evt)
{
  // Do nothing by defaul
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onContextMenu(wxContextMenuEvent& evt)
{
  wxMenuSharedPtr pmenu = ctxMenuGet();
  ES_ASSERT(pmenu);

  PopupMenu(
    pmenu.get()
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onGotoClosingBrace(wxCommandEvent& ES_UNUSED(evt))
{
  if(-1 == m_braceEnd)
    return;

  GotoPos(m_braceEnd);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onGotoOpeningBrace(wxCommandEvent& ES_UNUSED(evt))
{
  if(-1 == m_braceBeg)
    return;

  GotoPos(m_braceBeg);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onCmdUiUpdate(wxUpdateUIEvent& evt)
{
  switch(evt.GetId())
  {
  case EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE:
    {
      int pos = GetCurrentPos();
      evt.Enable(
        -1 < pos &&
        m_braceBeg == pos
      );
    }
    break;
  case EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE:
    {
      int pos = GetCurrentPos();
      evt.Enable(
        -1 < pos &&
        m_braceEnd == pos
      );
    }
    break;
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onDocumentOpened()
{
  ES_ASSERT(m_doc);

  textFromDocAssign();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onDocumentChanged(const EsString& subj)
{
  ES_ASSERT(m_doc);

  if(subj.empty() || esT("content") == subj)
    textFromDocAssign();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onDocumentSideloadChanged(const EsString& subj)
{
  ES_ASSERT(m_doc);

  if(subj.empty() || esT("bookmarks") == subj)
    bookmarksSynchronize();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onDocumentStateChanged()
{
  ES_ASSERT(m_doc);

  if(!m_doc->isModified())
    EmptyUndoBuffer();
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::stylesInit()
{
  // Reset all
  StyleClearAll();

  stylesSetCommon();

  cmdsInit();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::deduceLexerFromFilePath(const EsString& fpath)
{
  if(fpath.empty())
  {
    lexerSet(
      EsLexDbNode::null()
    );
    return;
  }

  const EsPath& path = EsPath::createFromFilePath(fpath);
  const EsString& ext = path.fileExtGet();

  lexerSet(
    EsSyntaxHighlighter::lexNodeByExtGet(ext)
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::lexerSet(const EsLexDbNode& lexNode)
{
  StyleClearAll();

  if(lexNode.isNull())
  {
    m_lexNode = nullptr;
    SetLexer(wxSTC_LEX_NULL);
  }
  else
  {
    m_lexNode = &lexNode;
    SetLexer(lexNode.lexId);
  }

  stylesSetCommon();
  lexerStylesApply(lexNode);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::documentConnect(const EsDocumentIntf::Ptr& doc) ES_NOTHROW
{
  m_doc = doc;
  if( m_doc )
  {
    textFromDocAssign();
    bookmarksSynchronize();
  }
  else
  {
    Unbind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);

    ClearAll();
    EmptyUndoBuffer();

    Bind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);
  }
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::hasBookmarks() const
{
  return !m_tags.empty() || -1 != const_cast<EsTextEditorViewBase*>(this)->MarkerNext(
    0, 
    markerBmGenericMask
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarksClearAll()
{
  MarkerDeleteAll(markerBmGeneric);
  for(int bmId = markerBm0; bmId <= markerBm9; ++bmId)
    if( hasBookmark(bmId) )
      MarkerDeleteAll(bmId);
  m_tags.clear();

  // Change document BM sideload
  EsTextDocument* doc = ES_INTFPTR_TO_OBJECTPTR<EsTextDocument>(m_doc);
  ES_ASSERT(doc);

  doc->bookmarksClear(this);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarkToggle(int tag)
{
  if(!m_doc)
    return;

  int line = GetCurrentLine();
  if(0 > line)
    return;

  doBookmarkToggle(line, tag);
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::hasBookmark(int tag) const
{
  ES_ASSERT(-1 < tag);
  ES_ASSERT(tag <= markerIdMax-markerBm0);

  return m_tags.end() != m_tags.find(tag);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarkGotoPrev()
{
  int startLine = GetCurrentLine();
  if(0 == startLine)
    startLine = GetLineCount()-1;
  else
    --startLine;

  int line = MarkerPrevious(
    startLine,
    markerBmMask
  );

  if(-1 < line)
    GotoLine(line);
  else if(startLine != GetLineCount()-1)
  {
    startLine = GetLineCount()-1;

    line = MarkerPrevious(
      startLine,
      markerBmMask
    );

    if( -1 < line )
      GotoLine(line);
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarkGotoNext()
{
  int startLine = GetCurrentLine();
  if(GetLineCount()-1 == startLine)
    startLine = 0;
  else
    ++startLine;

  int line = MarkerNext(
    startLine,
    markerBmMask
  );

  if(-1 < line)
    GotoLine(line);
  else if(startLine != 0)
  {
    startLine = 0;

    line = MarkerNext(
      startLine,
      markerBmMask
    );

    if(-1 < line)
      GotoLine(line);
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarkGoto(int tag)
{
  wxASSERT(-1 < tag);
  wxASSERT(tag <= markerIdMax-markerBm0);

  int startLine = GetCurrentLine();
  int mmask = (1 << (markerBm0+tag));

  int mask = MarkerGet(startLine);
  if(mask & mmask)
    return;

  int line = MarkerNext(
    startLine,
    mmask
  );

  if(-1 == line)
    line = MarkerPrevious(
      startLine,
      mmask
    );

  if(-1 < line)
    GotoLine(line);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::doBookmarkToggle(int line, int tag)
{
  ES_ASSERT(-1 < line);
  ES_ASSERT(m_doc);
  ES_ASSERT(tag < (markerIdMax-markerBm0));

  // Manage our bookmark markers here ourselves

  // We're settings numbered BM tag. First - remove BM with the
  // same tag, if there are any on other lines
  if(-1 < tag)
    taggedBookmarkRemoveAllExcl(
      tag,
      line
    );

  int oldTag = -1;
  if(
     bookmarkFromLineGet(  //< One of our BM markers
       line,
       oldTag
     )
  )
  {
    if(-1 < oldTag) // Was tagged BM
    {
      ES_ASSERT(oldTag < (markerIdMax-markerBm0));

      // Remove tagged marker on the same line
      MarkerDelete(
        line,
        markerBm0+oldTag
      );
      m_tags.erase(oldTag);
    }
    else
      MarkerDelete(
        line,
        markerBmGeneric
      );

    if(-1 < tag && oldTag != tag) // Will be tagged, and not the same as an old one
    {
      MarkerAdd(
        line,
        markerBm0+tag
      );
      m_tags.insert(tag);
    }
    else if(-1 < oldTag && -1 == tag) //< Will be not tagged
      MarkerAdd(
        line,
        markerBmGeneric
      );
  }
  else
  {
    // Just set new marker
    bookmarkSet(
      line,
      tag
    );
  }

  // Change document BM sideload
  EsTextDocument* doc = ES_INTFPTR_TO_OBJECTPTR<EsTextDocument>(m_doc);
  ES_ASSERT(doc);

  doc->bookmarkToggle(
    this,
    line,
    tag
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onI18nLocaleChanged(const EsString& loc)
{
  // TODO:
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::markersEnumerate(int mask, std::function<void(int line, int mask, int maskFound)> onMarkerEnumerate)
{
  if( !onMarkerEnumerate )
    return;

  int line = 0;

  while( 1 )
  {
    line = MarkerNext(
      line,
      mask
    );

    if( -1 < line )
    {
      onMarkerEnumerate(
        line,
        mask,
        MarkerGet(line)
      );

      ++line;
    }
    else
      break;
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::onEditorLinesChanged()
{
  if( !m_doc )
    return;

  EsAssocContainerIntf::Ptr ctr = EsAssocContainer::create();
  ES_ASSERT(ctr);

  markersEnumerate(
    markerBmMask,
    [this, ctr](int line, int mask, int maskFound) {

      int tag;
      if(
        bookmarkFromMaskGet(
          maskFound,
          tag
        )
      )
      {
        if( -1 == tag )
          ctr->newValueSet(
            line,
            EsVariant::null()
          );
        else
          ctr->newValueSet(
            line,
            tag
          );
      }
    }
  );

  m_doc->valueSet(
    "bookmarks",
    ctr
  );
  m_doc->documentSideloadChangedNotify(
    "bookmarks",
    this
  );
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::bookmarkFromMaskGet(int mask, int& tag)
{
  tag = -1;

  if( !(mask & markerBmMask) ) //< One of our BM markers
    return false;

    // Get tag from mask
  if( mask & markerBmNumberedMask )
  {
    mask >>= 1; //< Proceed to the first tagged BM marker mask bit
    tag = 0;

    while( !(mask & 0x1) )
    {
      ++tag;
      mask >>= 1;
    }

    ES_ASSERT(tag < (markerIdMax-markerBm0));
  }

  return true;
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::bookmarkFromLineGet(int line, int& tag)
{
  return bookmarkFromMaskGet(
    MarkerGet(line),
    tag
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarkSet(int line, int tag)
{
  ES_ASSERT(tag < markerIdMax-markerBm0);

  MarkerAdd(
    line,
    ((-1 < tag) ? (markerBm0+tag): markerBmGeneric)
  );
  if( -1 < tag )
    m_tags.insert(tag);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::taggedBookmarkRemoveAllExcl(int tag, int excl)
{
  ES_ASSERT(-1 < tag);

  for(int line = 0; line < GetLineCount(); ++line)
  {
    if(line == excl)
      continue;

    int bmtag = -1;
    if(bookmarkFromLineGet(line, bmtag) && tag==bmtag)
    {
      if( -1 < bmtag )
      {
        MarkerDelete(line, markerBm0+bmtag);
        m_tags.erase(bmtag);
      }
      else
        MarkerDelete(line, markerBmGeneric);

      break;
    }
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::bookmarksSynchronize()
{
  EsAssocContainerIntf::Ptr bms = m_doc->valueGet(esT("bookmarks")).asExistingObject();
  ES_ASSERT(bms);

  wxWindowUpdateLocker lock(this);
  // Remove all bookmarks from all lines
  int bmId = markerBmGeneric;
  while(bmId < markerIdMax)
    MarkerDeleteAll(bmId++);
  m_tags.clear();

  const EsVariant::Array& keys = bms->allKeysGet().asVariantCollection();
  for(const EsVariant& key : keys)
  {
    int line = key.asInt();
    const EsVariant& val = bms->valueGet(key);
    int tag = -1;

    if(val.isNumeric())
      tag = val.asInt();

    bookmarkSet(
      line,
      tag
    );
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textFromDocAssign()
{
  ES_ASSERT(m_doc);

  textSet(
    m_doc->valueGet(
      esT("content")
    ).doInterpretAsString().c_str()
  );

  deduceLexerFromFilePath(
    m_doc->keyGet().asString()
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::stylesSetCommon()
{
  const EsSconsoleOptions& opts = wxGetApp().mainWindowGet().optionsGet();

  // Common styling
  StyleSetFont(
    wxSTC_STYLE_DEFAULT,
    *opts.m_fntTxt
  );

  StyleSetFont(
    wxSTC_STYLE_LINENUMBER,
    *opts.m_fntLineNum
  );
  StyleSetSpec(
    wxSTC_STYLE_LINENUMBER,
    "fore:brown"
  );

  StyleSetFont(
    wxSTC_STYLE_CONTROLCHAR,
    *opts.m_fntLineNum
  );

  // Current line
  SetCaretLineVisible(true);

  // Indentation
  SetBackSpaceUnIndents(true);
  SetTabIndents(true);
  SetUseTabs(false);
  SetIndent(2);

  // Margin
  SetMarginType(1, wxSTC_MARGIN_NUMBER);
  SetMarginWidth(
    1,
    5*GetCharWidth()
  );
  SetMarginMask(
    1,
    0
  );

  SetMarginType(2, wxSTC_MARGIN_SYMBOL); //< Bookmark margin
  SetMarginWidth(
    2,
    16
  );
  SetMarginMask(
    2,
    wxSTC_MASK_FOLDERS|markerBmMask
  );

  // Set-up bookmark symbols
  MarkerDefineBitmap(
    markerBmGeneric,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm0,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_0,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm1,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_1,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm2,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_2,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm3,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_3,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm4,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_4,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm5,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_5,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm6,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_6,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm7,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_7,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm8,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_8,
      esART_STC_MARGIN
    )
  );
  MarkerDefineBitmap(
    markerBm9,
    wxArtProvider::GetBitmap(
      esART_BOOKMARK_9,
      esART_STC_MARGIN
    )
  );

  // Highlighters
  IndicatorSetStyle(
    highlighter,
    wxSTC_INDIC_ROUNDBOX
  );
  IndicatorSetAlpha(
    highlighter,
    100
  );
  IndicatorSetUnder(
    highlighter,
    true
  );
  IndicatorSetForeground(
    highlighter,
    wxTheColourDatabase->Find("SPRING GREEN")
  );

  // Braces highlighters
  StyleSetSpec(
    wxSTC_STYLE_BRACELIGHT,
    "fore:navy,back:green,bold"
  );
  StyleSetSpec(
    wxSTC_STYLE_BRACEBAD,
    "fore:navy,back:red,bold"
  );

  // Edge
  SetEdgeColumn(80);
  SetEdgeMode(wxSTC_EDGE_LINE);
  SetWrapMode(wxSTC_WRAP_NONE);

  // Whitespace
  SetViewWhiteSpace(wxSTC_WS_VISIBLEALWAYS);

  // Cache
  SetLayoutCache(wxSTC_CACHE_PAGE);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::cmdsInit()
{
  // Allow for custom CTRL-/ and ALT-/ commands
  CmdKeyClear(
    WXK_DIVIDE,
    wxSTC_KEYMOD_CTRL
  );
  CmdKeyClear(
    WXK_DIVIDE,
    wxSTC_KEYMOD_ALT
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::lexerStylesApply(const EsLexDbNode& lexNode)
{
  EsSyntaxHighlighter::lexStylesApply(
    this,
    lexNode
  );

  if(lexNode.isNull())
    return;

  for(int id = EsSyntaxHighlighterId::stcDefault; id < EsSyntaxHighlighterId::stcItemsCount; ++id)
  {
    const EsSyntaxHighlighterNode& node = lexNode.highlighters[id];
    if(node.isNull() && !node.haveWords())
      continue;

    const wxString& wordsStr = node.words;
    const wxArrayString& tokens = wxStringTokenize(
      wordsStr,
      wxT("\t\r\n ")
    );

    std::set<wxString> words;
    for(auto const& tok : tokens)
      words.insert(tok);

    m_categorizedTokens[id] = words;
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::autocompletionInit()
{
  AutoCompSetIgnoreCase(false);         //< Case insensitive autocompletion lookup
  AutoCompSetCaseInsensitiveBehaviour(wxSTC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE); //< Prefer autocompletion items matching case
  AutoCompSetCancelAtStart(true);       //< Cancel autocompletion on backspace
  AutoCompSetDropRestOfWord(true);      //< Erase the rest of the word upon successful autocompletion
  AutoCompSetSeparator(wxT('\\'));      //< Separate items in list with backslash
  AutoCompSetTypeSeparator(wxT('?'));   //< Separate item type with ?
  AutoCompSetMaxWidth(128);             //< Reserve enough for extra-long functions
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::textSet(const EsString& text)
{
  wxWindowUpdateLocker lock(this);

  try
  {
    Unbind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);

    SetText(text.c_str());
    EmptyUndoBuffer();

    // TODO: validate bookmarks in attahced document

    Bind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);
  }
  catch(...)
  {
    Bind(wxEVT_STC_MODIFIED, &EsTextEditorViewBase::onEditorContentChange, this);

    throw;
  }
}
//--------------------------------------------------------------------------------

EsString EsTextEditorViewBase::textGet() const
{
  return GetText().wc_str();
}
//--------------------------------------------------------------------------------

EsString EsTextEditorViewBase::keyGet() const
{
  if( m_doc )
    return m_doc->keyGet().asString();

  return EsString::null();
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::highlightClear()
{
  highlightRemove(-1, -1);
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::canHighlightSelection(int fromPos, int toPos) const
{
  if(-1 >= fromPos || fromPos >= toPos)
    return false;

  while(fromPos < toPos)
  {
    int ch = GetCharAt(fromPos++);
    if(wxIsspace(ch))
      return false;
  }

  return true;
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::fromToFixup(int& from, int& to) const
{
  if( from < 0 )
    from = 0;

  if( to < 0 )
    to = GetLastPosition();

  if( to < from )
  {
    int tmp = to;
    to = from;
    from = tmp;
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::highlight(int fromPos, int toPos)
{
  SetIndicatorCurrent(highlighter);

  fromToFixup(
    fromPos,
    toPos
  );

  IndicatorFillRange(
    fromPos,
    toPos-fromPos
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::highlight(const wxString& txt, int fromPos, int toPos, bool all)
{
  if( txt.IsEmpty() )
    return;

  fromToFixup(
    fromPos,
    toPos
  );

  int len = txt.Length();
  int flags = wxSTC_FIND_MATCHCASE|wxSTC_FIND_WHOLEWORD;
  int found = FindText(
    fromPos,
    toPos,
    txt,
    flags
  );

  if( all )
  {
    std::vector<int> sel;
    while( -1 != found )
    {
      sel.push_back(found);
      fromPos = found + len;

      found = FindText(
        fromPos,
        toPos,
        txt,
        flags
      );
    }

    if( sel.empty() )
      return;

    SetIndicatorCurrent(highlighter);

    for( auto const& pos: sel )
    {
      IndicatorFillRange(
        pos,
        len
      );
    }
  }
  else if( -1 < found )
  {
    SetIndicatorCurrent(highlighter);

    IndicatorFillRange(
      found,
      len
    );
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::highlightRemove(int fromPos, int toPos)
{
  fromToFixup(
    fromPos,
    toPos
  );

  SetIndicatorCurrent(highlighter);

  IndicatorClearRange(
    fromPos,
    toPos
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

wxMenuSharedPtr EsTextEditorViewBase::ctxMenuGet()
{
  if(m_pmnu)
    return m_pmnu;

  m_pmnu = std::make_shared<wxMenu>();
  ES_ASSERT(m_pmnu);

  ctxMenuInit();

  return m_pmnu;
}
//--------------------------------------------------------------------------------

wxMenuSharedPtr EsTextEditorViewBase::customCtxMenuGet()
{
  if(!m_pmnuCtx)
  {
    doCustomCtxMenuInit();
    customCtxMenuStringsUpdate(m_pmnuCtx.get());
  }

  return m_pmnuCtx;
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::customCtxMenuStringsUpdate(wxMenu* pmnu)
{
  if(!pmnu)
    return;

  doCtxMenuStringsUpdate(pmnu);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::customCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set)
{
  if(!subj)
    return;

  doCustomCtxMenuEvtHandlersSet(
    subj,
    set
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::ctxMenuInit()
{
  ES_ASSERT(m_pmnu);

  wxMenu* mnuTpl = wxGetApp().mainWindowGet().menuEditGet();
  ES_ASSERT(mnuTpl);

  // Clone standard edit menu to our pop-up menu part
  EsUtilities::menuClone(
    m_pmnu.get(),
    mnuTpl
  );

  // Remove the last cloned 'advanced' submenu
  m_pmnu->Destroy(
    EsSconsoleCmds::usrID_EDIT_CUSTOM_CTX_MENU
  );

  wxMenuSharedPtr customCtx = customCtxMenuGet();
  if(customCtx)
  {
    m_pmnu->AppendSeparator();
    EsUtilities::menuClone(
      m_pmnu.get(),
      customCtx.get()
    );
    customCtxMenuEvtHandlersSet(
      this,
      true
    );
  }
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::doCustomCtxMenuInit()
{
  ES_ASSERT(!m_pmnuCtx);

  m_pmnuCtx = std::make_shared<wxMenu>();
  ES_ASSERT(m_pmnuCtx);

  // Script context items
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE,
    EsUtilities::wxSpaceString()
  );
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE,
    EsUtilities::wxSpaceString()
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::doCtxMenuStringsUpdate(wxMenu* pmnu)
{
  if(!pmnu)
    return;

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE,
    _("To closing brace\tCTRL-]").as<wxString>()
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE,
    _("Jump to corresponding closing brace").as<wxString>()
  );

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE,
    _("To opening brace\tCTRL-[").as<wxString>()
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE,
    _("Jump to corresponding opening brace").as<wxString>()
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::doCustomCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set)
{
  ES_ASSERT(subj);

  if(set)
  {
    subj->Bind(wxEVT_MENU, &EsTextEditorViewBase::onGotoClosingBrace, this, EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE);
    subj->Bind(wxEVT_MENU, &EsTextEditorViewBase::onGotoOpeningBrace, this, EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE);
    subj->Bind(wxEVT_UPDATE_UI, &EsTextEditorViewBase::onCmdUiUpdate, this, EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE, EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE);
  }
  else
  {
    subj->Unbind(wxEVT_MENU, &EsTextEditorViewBase::onGotoClosingBrace, this, EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE);
    subj->Unbind(wxEVT_MENU, &EsTextEditorViewBase::onGotoOpeningBrace, this, EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE);
    subj->Unbind(wxEVT_UPDATE_UI, &EsTextEditorViewBase::onCmdUiUpdate, this, EsSconsoleCmds::usrID_EDIT_GOTO_CLOSING_BRACE, EsSconsoleCmds::usrID_EDIT_GOTO_OPENING_BRACE);
  }
}
//--------------------------------------------------------------------------------

bool EsTextEditorViewBase::isBrace(const wxString::char_type& ch) const
{
  auto cit = m_categorizedTokens.find(stcBrace);
  if(m_categorizedTokens.end() == cit)
    return '(' == ch || ')' == ch || '{' == ch || '}' == ch || '[' == ch || ']' == ch || '<' == ch || '>' == ch;

  auto const& tokens = (*cit).second;
  return tokens.end() != tokens.find(ch);
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::braceHighlightUpdate(int pos)
{
  if(0 > pos)
  {
    m_braceBeg = -1;
    m_braceEnd = -1;
  }
  else
  {
    int ch = GetCharAt(pos);
    if(!isBrace(ch))
    {
      // Remove any brace highlight
      m_braceBeg = -1;
      m_braceEnd = -1;
    }
    else
    {
      m_braceBeg = pos;
      m_braceEnd = BraceMatch(
        m_braceBeg
      );
    }
  }

  // Highlight brace-bad match
  BraceBadLight(-1);
  if(-1 < m_braceEnd)
  {
    ES_ASSERT(m_braceBeg > -1);

    if(m_braceEnd < m_braceBeg)
      std::swap(
        m_braceBeg,
        m_braceEnd
      );

    BraceHighlight(
      m_braceBeg,
      m_braceEnd
    );
  }
  else
  {
    BraceHighlight(
      -1,
      -1
    );

    if(-1 < m_braceBeg)
      BraceBadLight(m_braceBeg);
  }

  ES_DEBUG_TRACE(
    esT("EsTextEditorViewBase::braceHighlightUpdate(%d) [%d,%d]"),
    pos,
    m_braceBeg,
    m_braceEnd
  );
}
//--------------------------------------------------------------------------------

void EsTextEditorViewBase::selectionEncloseIn(const wxString& left, const wxString& right)
{
  const wxString& block = GetSelectedText();
  if(block.empty())
    return;

  wxString newBlock = left;
  newBlock += block;
  newBlock += right;

  ReplaceSelection(newBlock);
}
//--------------------------------------------------------------------------------
