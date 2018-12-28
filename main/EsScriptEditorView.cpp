#include "ess_console_pch.h"
#pragma hdrstop

#include "EsScriptEditorView.h"
#include "EsCompiledScriptView.h"
//--------------------------------------------------------------------------------

EsScriptEditorView::EvtHandler::EvtHandler(EsScriptEditorView& owner) ES_NOTHROW :
EsEventSubscriber(
  ES_EVTC_APPLICATION EVTC_AND
  ES_EVTC_SCRIPT_DEBUG_RSP
),
m_owner(owner)
{}
//--------------------------------------------------------------------------------

void EsScriptEditorView::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  ES_ASSERT(evt);

  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();

  if( ES_EVTC_APPLICATION == cat )
  {
    switch(as_<EsSconsoleEvt>(id))
    {
    case EsSconsoleEvt::CompiledScriptChanged:
      m_owner.onCompiledScriptChanged(
        evt->payloadGet()
      );
      break;
    case EsSconsoleEvt::CompiledScriptClosed:
      m_owner.onCompiledScriptClosed();
      break;
    default:
      // Do nothing
      break;
    }
  }
  else if( ES_EVTC_SCRIPT_DEBUG_RSP == cat )
  {
    const EsVariant& payload = evt->payloadGet();

    switch( as_<EsScriptDebugEvt>(id) )
    {
    case EsScriptDebugEvt::BreakpointChanged:
      // Skip other file names
      if( payload[1].asString() == m_owner.keyGet() )
        m_owner.onBreakpointChanged(
          payload[0].asExistingObject(), //< script
          payload[2],                    //< old state
          payload[3]                     //< new state
        );
      break;
    case EsScriptDebugEvt::Paused:
      if(payload[0].asString() == m_owner.keyGet())
        m_owner.onDebuggerPaused(
          payload[1].asULong(),
          payload[2].asBool()
        );
      break;
    case EsScriptDebugEvt::Continued:
      m_owner.onExecContinued();
      break;
    case EsScriptDebugEvt::Finished:
      m_owner.onExecFinished();
      break;
    default:
      break;
    }
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsScriptEditorView::EsScriptEditorView(wxWindow *parent, wxWindowID id, long style) :
EsTextEditorViewBase(
  parent,
  id,
  style,
  esT("EsScriptEditorView")
),
m_handler(*this),
m_tmrParser(
  this,
  EsSconsoleCmds::usrID_TMR_EVT_PARSE
),
m_tmrAutoComplete(
  this,
  EsSconsoleCmds::usrID_TMR_EVT_AUTOCOMP
),
m_topCtx(nullptr),
m_curlinePrev(-1),
m_ctxAtPos(EsScriptParser::noneId),
m_parserStop(0),
m_ctxParsed(false)
{
  Bind(wxEVT_STC_MARGINCLICK, &EsScriptEditorView::onMarginClick, this);
  Bind(wxEVT_TIMER, &EsScriptEditorView::onTimer, this);
}
//--------------------------------------------------------------------------------

EsScriptEditorView* EsScriptEditorView::create(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, long style /*= 0*/)
{
  std::unique_ptr<EsScriptEditorView> ptr(
    new EsScriptEditorView(
      parent,
      id,
      style
    )
  );
  ES_ASSERT(ptr);

  ptr->stylesInit();
  ptr->autocompletionInit();

  return ptr.release();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::doCustomCtxMenuInit()
{
  EsTextEditorViewBase::doCustomCtxMenuInit();

  ES_ASSERT(m_pmnuCtx);

  m_pmnuCtx->AppendSeparator();

  // Script context items
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR
  );
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR
  );
  m_pmnuCtx->AppendSeparator();
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE
  );
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE
  );
  m_pmnuCtx->AppendSeparator();
  m_pmnuCtx->Append(
    EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::stylesSetCommon()
{
  EsTextEditorViewBase::stylesSetCommon();

  // Breakpoints margin set-up
  SetMarginType(
    0,
    wxSTC_MARGIN_SYMBOL
  );

  SetMarginWidth(
    0,
    16
  );

  // Set-up bookmark symbols
  MarkerDefineBitmap(
    EsCompiledScriptView::markerBrkLine,
    wxArtProvider::GetBitmap(
      esART_EXECLINE,
      esART_STC_MARGIN
    )
  );

  MarkerDefineBitmap(
    EsCompiledScriptView::markerBrk,
    wxArtProvider::GetBitmap(
      esART_BRK_ACTIVE,
      esART_STC_MARGIN
    )
  );

  MarkerDefineBitmap(
    EsCompiledScriptView::markerBrkInactive,
    wxArtProvider::GetBitmap(
      esART_BRK_INACTIVE,
      esART_STC_MARGIN
    )
  );

  MarkerDefineBitmap(
    EsCompiledScriptView::markerBrkInvalid,
    wxArtProvider::GetBitmap(
      esART_BRK_INVALID,
      esART_STC_MARGIN
    )
  );

  MarkerDefine(
    EsCompiledScriptView::markerBrkCurrent,
    wxSTC_MARK_BACKGROUND,
    wxNullColour,
    wxTheColourDatabase->Find("ORANGE RED")
  );

  SetMarginMask(
    0,
    EsCompiledScriptView::markerBrkMaskAll
  );

  SetMarginSensitive(
    0,
    true
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::autocompletionInit()
{
  RegisterImage(
    acIdKeyword,
    wxArtProvider::GetBitmap(
      esART_AC_KEYWORDS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdConst,
    wxArtProvider::GetBitmap(
      esART_AC_CONSTS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdAttr,
    wxArtProvider::GetBitmap(
      esART_AC_ATTRS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdVarGlobal,
    wxArtProvider::GetBitmap(
      esART_AC_GLOBVARS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdEnum,
    wxArtProvider::GetBitmap(
      esART_AC_ENUMS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdEnumItem,
    wxArtProvider::GetBitmap(
      esART_AC_ENUM_ITEMS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdFunc,
    wxArtProvider::GetBitmap(
      esART_AC_GLOBFUNCS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdVarsvc,
    wxArtProvider::GetBitmap(
      esART_AC_VARSVCS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClass,
    wxArtProvider::GetBitmap(
      esART_AC_OBJECTS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClassVar,
    wxArtProvider::GetBitmap(
      esART_AC_OBJVARS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClassFld,
    wxArtProvider::GetBitmap(
      esART_AC_OBJFIELDS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClassProp,
    wxArtProvider::GetBitmap(
      esART_AC_OBJPROPS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClassMemberFunc,
    wxArtProvider::GetBitmap(
      esART_AC_OBJFUNCS,
      esART_STC_AUTOCOMPL
    )
  );
  RegisterImage(
    acIdClassFunc,
    wxArtProvider::GetBitmap(
      esART_AC_SERVICES,
      esART_STC_AUTOCOMPL
    )
  );

  EsTextEditorViewBase::autocompletionInit();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onEditorLinesChanged()
{
  EsTextEditorViewBase::onEditorLinesChanged();

  breakableLineMarkersClear();

  EsAssocContainerIntf::Ptr ctr = EsAssocContainer::create();
  ES_ASSERT(ctr);

  markersEnumerate(
    EsCompiledScriptView::markerBrkPointMask,
    [this, ctr](int line, int mask, int maskFound) {
        ctr->newValueSet(
          line,
          true
        );
    }
  );

  ES_ASSERT(m_doc);
  const EsVariant::Array& payload = {
    keyGet(),
    ctr,
    EsVariant(
      this,
      EsVariant::ACCEPT_POINTER
    )
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_SCRIPT_DEBUG_REQ,
    as_<ulong>(EsScriptDebugEvt::BreakpointsSet),
    payload
  );

  // Mark all existing breakpoints invalid
  breakpointsInvalidSet();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onI18nLocaleChanged(const EsString& loc)
{
  EsTextEditorViewBase::onI18nLocaleChanged(loc);

  customCtxMenuStringsUpdate(
    m_pmnuCtx.get()
  );
}
//--------------------------------------------------------------------------------

static EsString autocompletionItemFormat(const EsString& item, int id)
{
  if( EsScriptEditorView::acIdFunc == id || EsScriptEditorView::acIdClassFunc == id || EsScriptEditorView::acIdClassMemberFunc == id || EsScriptEditorView::acIdVarsvc == id )
  {
    EsString svc = item;

    if( EsScriptEditorView::acIdVarsvc == id ) //< Correct parameters list for variant services - remove the first one, it's implied lhs
    {
      size_t posSkipFrom = svc.find(esT('('));
      ES_ASSERT(EsString::npos != posSkipFrom);
      ++posSkipFrom;

      size_t posSkipTo = svc.find(
        esT(", "), 
        posSkipFrom
      );

      if( EsString::npos == posSkipTo )
        posSkipTo = svc.find(
          esT(')'), 
          posSkipFrom
        );
      else
        posSkipTo += 2; //< Skip ', ' part

      ES_ASSERT(EsString::npos != posSkipTo);
      svc = svc.substr(
        0, 
        posSkipFrom
      ) + 
      svc.substr(
        posSkipTo
      );
    }

    // Reposition return type to the end of the service autocompletion string, separate it with colon
    size_t pos = svc.find(esT(' '));
    svc = svc.substr(
      pos+1
    ) + esT(": ") +
    svc.substr(
      0,
      pos
    );

    // Remove namespace part, if any
    pos = svc.find(esT("::"));
    if( EsString::npos != pos )
      svc = svc.substr(
        pos + 2
      );

    return svc + 
      esT("?") + 
      EsString::fromULong(id);
  }
  else
    return item + 
      esT("?") + 
      EsString::fromULong(id);
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::autocompletionItemsAppend(EsString::Array& dest, const EsString::Array& src, int id)
{
  if(src.empty())
    return;

  dest.reserve(
    dest.size()+src.size()
  );
  
  for(size_t idx = 0; idx < src.size(); ++idx)
  {
    dest.push_back(
      autocompletionItemFormat(
        src[idx], 
        id
      )
    );
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::autocompletionItemsAppend(EsString::Array& dest, const EsScriptParser::Node::PtrArrayT& parserNodes, const EsString& filter, int id)
{
  if(parserNodes.empty())
    return;

  dest.reserve(
    dest.size()+parserNodes.size()
  );
  const EsString& txt = textGet();
  for(size_t idx = 0; idx < parserNodes.size(); ++idx)
  {
    EsScriptParser::Node::PtrT node = parserNodes[idx];
    const EsScriptParser::Node* identNode = node->firstChildGetById(
      EsScriptParser::identId, 
      false
    );
    ES_ASSERT(identNode);

    const EsString& ident = identNode->stringExtract(txt);
    ES_ASSERT(!ident.empty());

    if(
      !filter.empty() && 
      EsString::npos == ident.find(filter)
    )
      continue;

    dest.push_back(
      autocompletionItemFormat(
        ident,
        id
      )
    );
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::operatorAndSubjGetLeftOfPos(int curPos, wxString& subj, wxString& op, bool searchSubj /*= true*/)
{
  subj = wxEmptyString;
  op = wxEmptyString;

  enum {
    searchStateIdle       = -1,
    searchStateSubjIdle   = -2,
    searchStateOP         = 0,
    searchStateSubj
  };

  // Lookup operator to the left of pos
  int state = searchStateIdle;
  for(int pos = curPos; pos >= 0; --pos)
  {
    wxUniChar uc = GetCharAt(pos);
    
    if(0 == static_cast<int>(uc))
      continue;

    if( uc == wxT(';') || !uc.IsAscii() )
      return;

    if(wxIsspace(uc) || wxIscntrl(uc))
    {
      if(searchStateSubj == state) //< We're collecting subj, break immediately
        return;
      else if(searchStateOP == state) //< We were collecting op, switch to subj-idle
      {
        if( !searchSubj )
          return;

        state = searchStateSubjIdle;
      }
      else
        continue; //< Skip space
    }
   
    if( !(wxIsalnum(uc) || wxT('_') == uc) ) //< We were idle, and it's non-word start collecting operator sequence
    {
      if(searchStateIdle == state)
        state = searchStateOP; //< Collecting operator
      else if(searchStateSubj == state) //< We were collecting subj. exit immediately
        return;
      
      if(searchStateOP == state)
      {
        if(op.IsEmpty())
          op = uc;
        else
          op = uc + op;
      }
    }
    else if( searchStateSubjIdle == state || searchStateOP == state || searchStateSubj == state ) //< We were still collecting op, in idle subj, or in collecting subj
    {
      if( !searchSubj )
        return;

      if( searchStateOP == state )
        state = searchStateSubj; //< Collecting subj

      if( subj.IsEmpty() )
        subj = uc;
      else
        subj = uc + subj;
    } 
  }
}
//--------------------------------------------------------------------------------

wxString EsScriptEditorView::autocompletionListPrepare(int curPos, const EsString& filter)
{
  EsVariant metaLookup;
  bool scriptedMetaInfo = false;

  // 1. If this script source file is a module of existing compiled script - get meta info from there
  if(m_doc)
  {
    EsDocumentManagerIntf::Ptr mgr = m_doc->managerGet();
    ES_ASSERT(mgr);

    const EsVariant& bin = mgr->documentFindFirstByType(
      EsCompiledScriptDocument::classNameGetStatic()
    );

    if(!bin.isEmpty())
    {
      EsCompiledScriptDocument* docBin = ES_VARIANT_TO_OBJECTPTR<EsCompiledScriptDocument>(bin);
      ES_ASSERT(docBin);

      EsScriptIntf::Ptr script = docBin->valueGet(esT("content")).asExistingObject();
      ES_ASSERT(script);

      if(script->hasSourceModule(m_doc->keyGet().asString()))
      {
        metaLookup = EsScriptMetainfoLookup::NEW(
          script->vm().metaGet()
        );
        scriptedMetaInfo = true;
      }
    }
  }

  // 2. If not - use reserved words and meta info from reflected engine only
  if(metaLookup.isEmpty())
    metaLookup = EsScriptMetainfoLookup::NEW(
      EsMetaclass::instance()
    );

  ES_ASSERT(!metaLookup.isEmpty());
  EsScriptMetainfoLookup* lookup = ES_VARIANT_TO_OBJECTPTR<EsScriptMetainfoLookup>(metaLookup);
  ES_ASSERT(lookup);

  EsString::Array acItems;
  bool processed = true; //< Autocompletion was processed

  // Try to get local context, if any
  //
  wxString subj;
  wxString op;
  operatorAndSubjGetLeftOfPos(
    curPos, 
    subj, 
    op
  );

  ES_DEBUG_TRACE(
    esT("operatorAndSubjGetLeftOfPos(from: %d, subj: %s, op: %s)"),
    curPos,
    EsVariant(
      subj.wc_str(),
      EsVariant::ACCEPT_STRING
    ),
    EsVariant(
      op.wc_str(),
      EsVariant::ACCEPT_STRING
    )
  );
  
  if(0 == op.Cmp(wxT("#"))) //< Get variant services
  {
    autocompletionItemsAppend(
      acItems,
      lookup->variantServicesFind(
        filter
      ),
      acIdVarsvc
    );
  }
  else if(0 == op.Cmp(wxT("::")))
  {
    if( !subj.IsEmpty() )
      autocompletionItemsAppend(
        acItems,
        lookup->objectStaticMethodsFind(
          subj.wc_str(),
          filter
        ),
        acIdClassFunc
      );
    else if(scriptedMetaInfo)
      autocompletionItemsAppend(
        acItems,
        lookup->globalFunctionsFind(
          filter
        ),
        acIdFunc
      );
  }
  else if(0 == op.Cmp(wxT(".")))
  {
    // TODO: get expected object type from subj string
    //if(scriptedMetaInfo)
    // get variable
    // get field
    // get method
    //else
    // get method
    //autocompletionItemsAppend(
    //  acItems,
    //  lookup->object(
    //    subj.wc_str(),
    //    filter
    //  ),
    //  acIdClassProp
    //);
  }
  else if(0 == op.Cmp(wxT("$")))
  {
    // TODO: get expected object type from subj string
    //autocompletionItemsAppend(
    //  acItems,
    //  lookup->objectPropertiesFind(
    //    subj.wc_str(),
    //    filter
    //  ),
    //  acIdClassProp
    //);
  }
  else if(0 == op.Cmp(wxT("$$")) && !subj.IsEmpty())
  {
    processed = false;

    // Try parsed context first
    if(
      m_ctxParsed &&
      m_topCtx && 
      EsScriptParser::enumValId == m_topCtx->idGet()
    )
    {
      // Top ctx would be the parsed enum name in identifier child node
      const EsScriptParser::Node* enumDecl =
        m_ctxParser.rootNodeFind(
          EsScriptParser::stmtEnumDeclId,
          EsString::HashCalcT(subj.wc_str()).get()
        );
      
      if(enumDecl)
      {
        EsScriptParser::Node::PtrArrayT items = enumDecl->childrenGet(EsScriptParser::stmtEnumItemDeclId);
        autocompletionItemsAppend(
          acItems,
          items,
          filter,
          acIdEnumItem
        );
        processed = true;
      }
    }
    
    if( 
      !processed &&
      !lookup->enumNamesFind(subj.wc_str()).empty() 
    )
    {
      autocompletionItemsAppend(
        acItems,
        lookup->enumSymbolsFind(
          subj.wc_str(),
          filter
        ),
        acIdEnumItem
      );
      processed = true;
    }
  }
  else if(0 == op.Cmp(wxT("@")))
  {
    // TODO:
  }
  else if(0 == op.Cmp(wxT("##")))
  {
    // Get specific preprocessor keywords
    autocompletionItemsAppend(
      acItems,
      lookup->keywordsFind(
        esT("3"),
        filter
      ),
      acIdKeyword
    );
  }
  else
  {
    // Get keywords
    autocompletionItemsAppend(
      acItems,
      lookup->keywordsFind(
        EsString::null(),
        filter
      ),
      acIdKeyword
    );

    if( scriptedMetaInfo )
    {
      // Get global constants
      autocompletionItemsAppend(
        acItems,
        lookup->constantsFind(
          filter
        ),
        acIdConst
      );

      // Get global variables
      autocompletionItemsAppend(
        acItems,
        lookup->globalVarsFind(
          filter
        ),
        acIdVarGlobal
      );

      // Get global functions
      autocompletionItemsAppend(
        acItems,
        lookup->globalFunctionsFind(
          filter
        ),
        acIdFunc
      );
    }

    autocompletionItemsAppend(
      acItems,
      lookup->enumNamesFind(
        filter
      ),
      acIdEnum
    );

    autocompletionItemsAppend(
      acItems,
      lookup->objectNamesFind(
        filter
      ),
      acIdClass
    );
  }

  // Finally, sort all acItems
  std::sort(
    acItems.begin(),
    acItems.end()
  );

  // Finally, concatenate autocompletion items
  wxString autoCompletionItems;
  wxUniChar uc = AutoCompGetSeparator();
  for (size_t idx = 0; idx < acItems.size(); ++idx)
  {
    if (!autoCompletionItems.IsEmpty())
      autoCompletionItems += uc;

    autoCompletionItems += acItems[idx].c_str();
  }

  return autoCompletionItems;
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::autocompletionShow(bool force /*= false*/)
{
  int currentPos = GetCurrentPos();

  // Display the autocompletion list, emulating entered count of chars
  int enteredTotal = currentPos - WordStartPosition( //< Count even non word chars on left to get entered chars
    currentPos,
    false
  );

  int wordStart = WordStartPosition( //< Get only word chars as filter
    currentPos,
    true
  );
  int enteredWord = currentPos - wordStart;
  if(enteredWord < 0)
    enteredWord = 0;

  EsString filter;
  if(enteredTotal < 0)
    enteredTotal = 0;
  else
    filter = GetTextRange(
      wordStart,
      currentPos
    ).wc_str();

  ES_DEBUG_TRACE(
    esT("EsScriptEditorView::autocompletionShow(force=%d), curPos=%d, enteredTotal=%d enteredWord=%d, filter=%s"),
    (int)force,
    currentPos,
    enteredTotal,
    enteredWord,
    filter
  );

  if(
    force || 
    enteredTotal >= autoCompletionShowAfterCnt
  )
  {
    m_acList = autocompletionListPrepare(
      currentPos,
      filter
    );

    if(!m_acList.IsEmpty())
      AutoCompShow(
        enteredWord,
        m_acList
      );
    else
      AutoCompCancel();
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::breakpointDelete(int line)
{
  // Remove any breakpoint marker at line
  MarkerDelete(
    line,
    EsCompiledScriptView::markerBrk
  );
  MarkerDelete(
    line,
    EsCompiledScriptView::markerBrkInactive
  );
  MarkerDelete(
    line,
    EsCompiledScriptView::markerBrkInvalid
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::breakpointSet(int line, bool state, bool valid)
{
  breakpointDelete(line);

  if( valid )
  {
    if( state )
      MarkerAdd(
        line,
        EsCompiledScriptView::markerBrk
      );
    else
      MarkerAdd(
        line,
        EsCompiledScriptView::markerBrkInactive
      );
  }
  else
    MarkerAdd(
      line,
      EsCompiledScriptView::markerBrkInvalid
    );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::currentExecutionLineSet(int line, bool set)
{
  if(set)
  {
    if(m_curlinePrev != line)
    {
      m_curlinePrev = line;

      if( -1 < line )
      {
        MarkerAdd(
          line,
          EsCompiledScriptView::markerBrkCurrent
        );

        GotoLine(line);
      }
    }
  }
  else if(-1 < m_curlinePrev)
  {
    MarkerDelete(
      m_curlinePrev,
      EsCompiledScriptView::markerBrkCurrent
    );

    m_curlinePrev = -1;
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::textSet(const EsString& text)
{
  m_tmrParser.Stop();
  m_tmrAutoComplete.Stop();
  EsTextEditorViewBase::textSet(text);
  Refresh();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onMarginClick(wxStyledTextEvent& evt)
{
  int mrg = evt.GetMargin();
  if(0 != mrg)
    return;

  if(!m_doc)
    return;

  int line = LineFromPosition(
    evt.GetPosition()
  );
  ES_ASSERT(-1 < line);

  int mmask = MarkerGet(line);
  bool bkrSet = (mmask & EsCompiledScriptView::markerBrkPointMask); //< One of our BRK markers

  EsScriptDocument* doc = ES_INTFPTR_TO_OBJECTPTR<EsScriptDocument>(m_doc);
  ES_ASSERT(doc);

  // Breakpoint state change requested by Script source view. Payload - [script key, source hash, source line, set/reset, desired state (active/inactive)]
  const EsVariant::Array& payload = {
    doc->keyGet(),
    doc->hashGet(),
    line,
    !bkrSet,
    true
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::ScriptBrkChangeRequested),
    payload
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onTimer(wxTimerEvent& evt)
{
  int id = evt.GetId();
  if(EsSconsoleCmds::usrID_TMR_EVT_PARSE == id)
  {
    const EsString& in = textGet();
    m_ctxParsed = m_ctxParser.parse(
      in
    );

    m_parserStop = m_ctxParser.stopGet();

    ES_DEBUG_TRACE(
      esT("Current script source parsed: %d, stopped at %d"),
      m_ctxParsed,
      m_parserStop
    );
  }
  else if(EsSconsoleCmds::usrID_TMR_EVT_AUTOCOMP == id)
    autocompletionShow();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onFileOpenAtCursor(wxCommandEvent& ES_UNUSED(evt))
{
  if(!m_topCtx || EsScriptParser::stmtRequireId != m_topCtx->idGet())
    return;

  const EsScriptParser::Node* strNode = m_topCtx->firstChildGetById(
    EsScriptParser::strValId
  );
  if(!strNode)
    return;

  ulong start, end;
  strNode->rangeGet(
    start,
    end
  );

  const EsString& file = strNode->stringValExtract(
    GetTextRange(
      start,
      end
    ).t_str()
  );

  const EsString& fileNameAbs = EsScript::absoluteFileNameGet(
    file,
    wxGetApp().settingsAccess().m_includes,
    false,
    keyGet()
  );

  if(fileNameAbs.empty())
    return;

  ES_DEBUG_TRACE(
    esT("EsScriptEditorView::onFileOpenAtCursor '%s'"),
    fileNameAbs
  );

  const EsVariant::Array& payload = {
    fileNameAbs,          //< file
    EsVariant::null(),    //< line
    EsVariant::null(),    //< col
    false                 //< isInExecMode
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::ScriptOpenAndSetPosition),
    payload
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onFileLocationOpenAtCursor(wxCommandEvent& ES_UNUSED(evt))
{
  if(
    !m_topCtx || 
    (
      EsScriptParser::stmtRequireId != m_topCtx->idGet() && 
      EsScriptParser::stmtLinkId != m_topCtx->idGet()
    )
  )
    return;

  const EsScriptParser::Node* strNode = m_topCtx->firstChildGetById(
    EsScriptParser::strValId
  );
  if(!strNode)
    return;

  ulong start, end;
  strNode->rangeGet(
    start,
    end
  );

  const EsString& file = strNode->stringValExtract(
    GetTextRange(
      start,
      end
    ).t_str()
  );

  EsString fileNameAbs = EsScript::absoluteFileNameGet(
    file,
    wxGetApp().settingsAccess().m_includes,
    false,
    keyGet()
  );

  if(fileNameAbs.empty()) //< Try links instead
    fileNameAbs = EsScript::absoluteFileNameGet(
      file,
      wxGetApp().settingsAccess().m_linkPaths,
      false,
      keyGet()
    );

  if(fileNameAbs.empty())
    return;

  const EsPath& path = EsPath::createFromFilePath(fileNameAbs);
  const EsString& location = path.pathGet(
    as_<ulong>(EsPathFlag::Default) |
    as_<ulong>(EsPathFlag::ExcludeFile)
  );

  ES_DEBUG_TRACE(
    esT("EsScriptEditorView::onFileLocationOpenAtCursor '%s'"),
    location
  );

  // Open location
#ifdef __WXMSW__
  wxExecute(
    EsString::format(
      esT("explorer \"%s\""),
      location
    ).c_str(),
    wxEXEC_ASYNC
  );
#endif
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onLineCommentToggle(wxCommandEvent& evt)
{
  int from;
  int to;
  GetSelection(
    &from,
    &to
  );

  if(from > to)
    std::swap(
      from,
      to
    );

  from = LineFromPosition(
    from
  );
  to = LineFromPosition(
    to
  );

  wxString newLines;
  for(int line = from; line <= to; ++line)
  {
    const wxString& lineStr = GetLine(line);
    wxString rest;

    if(lineStr.StartsWith("//", &rest))
      newLines += rest;
    else
    {
      newLines += esT("//");
      newLines += lineStr;
    }
  }

  from = PositionFromLine(from);
  // Include last line's EOL into selection
  to = PositionAfter(
    GetLineEndPosition(to)
  );

  SetSelection(
    from,
    to
  );

  ReplaceSelection(newLines);
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onBlockCommentToggle(wxCommandEvent& evt)
{
  wxString block = GetSelectedText();
  if(block.empty())
    return;

  const wxString& left = esT("/*");
  const wxString& right = esT("*/");

  size_t from = block.find(left);
  size_t to = block.rfind(right);
  if(wxString::npos != from && wxString::npos != to && from < to)
  {
    block = block.replace(
      from,
      left.length(),
      wxEmptyString
    );

    to = block.rfind(right);
    block = block.replace(
      to,
      right.length(),
      wxEmptyString
    );

    ReplaceSelection(block);
  }
  else
    selectionEncloseIn(
      esT("/*"),
      esT("*/")
    );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onCodeInsight(wxCommandEvent& evt)
{
  m_tmrAutoComplete.Stop();
  autocompletionShow(true); //< Show auto completion list despite the number of chars entered
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onCmdUiUpdate(wxUpdateUIEvent& evt)
{
  EsTextEditorViewBase::onCmdUiUpdate(evt);

  switch(evt.GetId())
  {
  case EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR:
    evt.Enable(
      nullptr != m_topCtx &&
      EsScriptParser::stmtRequireId == m_topCtx->idGet()
    );
    break;
  case EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR:
    evt.Enable(
      nullptr != m_topCtx &&
      (
        EsScriptParser::stmtRequireId == m_topCtx->idGet() ||
        EsScriptParser::stmtLinkId == m_topCtx->idGet()
      )
    );
    break;
  case EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE:
    evt.Enable(
      -1 < GetCurrentPos()
    );
    break;
  case EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE:
    evt.Enable(
      !GetSelectionEmpty()
    );
    break;
  default:
    break;
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onStcUiUpdate(wxStyledTextEvent& evt)
{
  EsTextEditorViewBase::onStcUiUpdate(evt);

  if(wxGetApp().mainWindowGet().isExecutingBatch())
    return;

  int flags = evt.GetUpdated();
  ES_DEBUG_TRACE(
    esT("EsScriptEditorView::onStcUiUpdate flags=0x%08X"),
    flags
  );

  if(flags & wxSTC_UPDATE_CONTENT)
  {
    m_tmrAutoComplete.Stop();
    m_tmrParser.Stop();
    
    m_tmrAutoComplete.StartOnce(autoCompTmo);
    m_tmrParser.StartOnce(reparseDelay);
  }

  if(flags & (wxSTC_UPDATE_SELECTION|wxSTC_UPDATE_CONTENT))
  {
    m_ctxAtPos = scriptCtxAtPosGet(
      GetCurrentPos()
    );

    ES_DEBUG_TRACE(
      esT("m_ctxAtPos=%d, topCtx=%d"),
      m_ctxAtPos,
      m_topCtx ?
        m_topCtx->idGet() :
        EsScriptParser::noneId
    );
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onAutoCompleting(wxStyledTextEvent& evt)
{
  const wxString& acItem = evt.GetString();

  size_t pos = acItem.find(wxT(')')); //< Remove rettype from function autocompletion string when inserting selected result
  if( wxString::npos != pos )
  {
    // Cancel automatic insertion, do it manually
    int txtpos = evt.GetPosition();
    AutoCompCancel();
    int start = WordStartPosition(txtpos, true);
    int end = WordEndPosition(txtpos, true);

    wxString svc = acItem.substr(
      0, 
      pos+1
    );
    pos = svc.find(wxT('('));
    ES_ASSERT(wxString::npos != pos);
    ++pos;

    Replace(
      start,
      end,
      svc
    );
    GotoPos(start+pos); //< Move caret after the opening bracket
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onCompiledScriptChanged(const EsVariant& compiledScript)
{
  ES_ASSERT(compiledScript.isKindOf(EsCompiledScriptDocument::classNameGetStatic()));

  EsCompiledScriptDocument* doc = ES_VARIANT_TO_OBJECTPTR<EsCompiledScriptDocument>(compiledScript);
  ES_ASSERT(doc);

  EsScriptIntf::Ptr script = doc->valueGet(esT("content")).asExistingObject();

  wxWindowUpdateLocker lock(this);
  allBrkMarkersClean();

  if(!script->hasSourceModulesInfo())
    return;

  if(!m_doc)
    return;

  const EsString& key = keyGet();
  if(!script->hasSourceModule(key))
    return;

  const EsVariant& hash = script->sourceModuleHashGet(key);
  EsScriptDocument* srcdoc = ES_INTFPTR_TO_OBJECTPTR<EsScriptDocument>(m_doc);
  ES_ASSERT(srcdoc);

  bool hashValid = hash == srcdoc->hashGet();

  // Set-up breakable lines
  if(hashValid)
  {
    const EsVariant::Array& lines = script->sourceModuleExecutableLinesGet(key).asVariantCollection();
    for(size_t idx = 0; idx < lines.size(); ++idx)
    {
      const EsVariant& range = lines[idx];
      int min = range.propertyGet("min").asInt();
      int max = range.propertyGet("max").asInt();

      for(int line = min; line <= max; ++line)
      {
        MarkerAdd(
          line,
          EsCompiledScriptView::markerBrkLine
        );
      }
    }
  }

  // Set-up breakpoints
  EsAssocContainerIntf::Ptr brks = doc->breakpointsGet().asExistingObject();
  ES_ASSERT(brks);

  if(!brks->keyExists(key))
    return;

  brks = brks->valueGet(key).asExistingObject();
  ES_ASSERT(brks);

  const EsVariant::Array& brkLines = brks->allKeysGet().asVariantCollection();
  for(auto const& brkLine : brkLines)
  {
    int line = brkLine.asInt();
    bool state = brks->valueGet(
      brkLine
    ).asBool();

    breakpointSet(
      line,
      state,
      hashValid
    );
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onCompiledScriptClosed()
{
  wxWindowUpdateLocker lock(this);
  allBrkMarkersClean();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onBreakpointChanged(const EsScriptIntf::Ptr& script, const EsVariant& oldState, const EsVariant& newState)
{
  ES_ASSERT(script);

  int line = oldState[0].asInt();
  // Delete breakpoint at old line
  breakpointDelete(line);

  ES_ASSERT(m_doc);

  const EsString& path = keyGet();
  if( !script->hasSourceModule(path) )
    return;

  // Set breakpoint at new line
  if( !newState[1].isEmpty() )
  {
    EsScriptDocument* pdoc = ES_INTFPTR_TO_OBJECTPTR<EsScriptDocument>(m_doc);
    ES_ASSERT(pdoc);

    bool valid = pdoc->hashGet() == script->sourceModuleHashGet(path);
    line = newState[0].asInt();

    breakpointSet(
      line,
      newState[1].asBool(),
      valid
    );
  }
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onDebuggerPaused(ulong line, bool isBreakpoint)
{
  currentExecutionLineSet(
    line,
    true
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onExecContinued()
{
  currentExecutionLineSet(
    -1,
    false
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::onExecFinished()
{
  currentExecutionLineSet(
    -1,
    false
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsScriptEditorView::breakpointMarkersClean()
{
  MarkerDeleteAll(EsCompiledScriptView::markerBrk);
  MarkerDeleteAll(EsCompiledScriptView::markerBrkInactive);
  MarkerDeleteAll(EsCompiledScriptView::markerBrkInvalid);
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::breakableLineMarkersClear()
{
  MarkerDeleteAll(EsCompiledScriptView::markerBrkLine);
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::allBrkMarkersClean()
{
  // Remove existing brekpoints, and breakable lines for this view
  breakableLineMarkersClear();
  MarkerDeleteAll(EsCompiledScriptView::markerBrkCurrent);
  m_curlinePrev = -1;
  breakpointMarkersClean();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::breakpointsInvalidSet()
{
  int line = 0;

  while( 1 )
  {
    line = MarkerNext(
      line,
      EsCompiledScriptView::markerBrkMask|
      EsCompiledScriptView::markerBrkInactiveMask
    );

    if( -1 < line )
    {
      MarkerDelete(
        line,
        EsCompiledScriptView::markerBrk
      );
      MarkerDelete(
        line,
        EsCompiledScriptView::markerBrkInactive
      );

      MarkerAdd(
        line,
        EsCompiledScriptView::markerBrkInvalid
      );

      ++line;
    }
    else
      break;
  }
}
//--------------------------------------------------------------------------------

int EsScriptEditorView::scriptCtxAtPosGet(int pos)
{
  const EsScriptParser::Node* node = m_ctxParser.deepestNodeFindByPos(pos);
  if(!node)
  {
    m_topCtx = nullptr;
    return EsScriptParser::noneId;
  }

  static const EsScriptParser::IdsT s_topIds = {
    EsScriptParser::idxAccId,
    EsScriptParser::fieldOrMemberVarAccId,
    EsScriptParser::propAccId,
    EsScriptParser::attrAccId,
    EsScriptParser::objMethodCallId,
    EsScriptParser::varSvcCallId,
    EsScriptParser::enumValId,
    EsScriptParser::enumValLblId,
    EsScriptParser::exprFuncCallId,
    EsScriptParser::exprObjCtrCallId,
    EsScriptParser::exprStaticOrBaseCallId,
    EsScriptParser::exprCallId,
    EsScriptParser::stmtRequireId,
    EsScriptParser::stmtLinkId
  };

  const EsScriptParser::Node* _node = node;
  while(!_node->isRoot() && !_node->isIdOneOf(s_topIds))
    _node = &_node->parentGet();

  ES_ASSERT(_node);
  m_topCtx = _node;

  return node->idGet();
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::doCtxMenuStringsUpdate(wxMenu* pmnu)
{
  EsTextEditorViewBase::doCtxMenuStringsUpdate(pmnu);

  if(!pmnu)
    return;

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR,
    _("Open file\tCTRL-Enter")
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR,
    _("Open script file at cursor")
  );

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR,
    _("Open location\tALT-Enter")
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR,
    _("Open location of file at cursor")
  );

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE,
    _("Toggle Line comment\tCTRL-/")
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE,
    _("Toggle line comment for current line or selection")
  );

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE,
    _("Toggle Block comment\tALT-/")
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE,
    _("Toggle block comment for selection")
  );

  pmnu->SetLabel(
    EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT,
    _("Code Insight\tCTRL-Space")
  );
  pmnu->SetHelpString(
    EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT,
    _("Open Code Insight browser console")
  );
}
//--------------------------------------------------------------------------------

void EsScriptEditorView::doCustomCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set)
{
  ES_ASSERT(subj);

  EsTextEditorViewBase::doCustomCtxMenuEvtHandlersSet(
    subj,
    set
  );

  if(set)
  {
    subj->Bind(wxEVT_MENU, &EsScriptEditorView::onFileOpenAtCursor, this, EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR);
    subj->Bind(wxEVT_MENU, &EsScriptEditorView::onFileLocationOpenAtCursor, this, EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR);
    subj->Bind(wxEVT_MENU, &EsScriptEditorView::onLineCommentToggle, this, EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE);
    subj->Bind(wxEVT_MENU, &EsScriptEditorView::onBlockCommentToggle, this, EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE);
    subj->Bind(wxEVT_MENU, &EsScriptEditorView::onCodeInsight, this, EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT);
    subj->Bind(wxEVT_UPDATE_UI, &EsScriptEditorView::onCmdUiUpdate, this, EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR, EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT);
  }
  else
  {
    subj->Unbind(wxEVT_MENU, &EsScriptEditorView::onFileOpenAtCursor, this, EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR);
    subj->Unbind(wxEVT_MENU, &EsScriptEditorView::onFileLocationOpenAtCursor, this, EsSconsoleCmds::usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR);
    subj->Unbind(wxEVT_MENU, &EsScriptEditorView::onLineCommentToggle, this, EsSconsoleCmds::usrID_SEDIT_LINE_COMMENT_TOGGLE);
    subj->Unbind(wxEVT_MENU, &EsScriptEditorView::onBlockCommentToggle, this, EsSconsoleCmds::usrID_SEDIT_BLOCK_COMMENT_TOGGLE);
    subj->Unbind(wxEVT_MENU, &EsScriptEditorView::onCodeInsight, this, EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT);
    subj->Unbind(wxEVT_UPDATE_UI, &EsScriptEditorView::onCmdUiUpdate, this, EsSconsoleCmds::usrID_SEDIT_FILE_OPEN_AT_CURSOR, EsSconsoleCmds::usrID_SEDIT_CODE_INSIGHT);
  }
}
//--------------------------------------------------------------------------------
