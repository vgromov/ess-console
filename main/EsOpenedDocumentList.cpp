#include "ess_console_pch.h"
#pragma hdrstop

#include "EsOpenedDocumentList.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsOpenedDocumentList::EvtHandler::EvtHandler(EsOpenedDocumentList& owner) ES_NOTHROW :
EsEventSubscriber(
  ES_EVTC_MDI EVTC_AND
  ES_EVTC_I18N
),
m_owner(owner)
{}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  ES_ASSERT(evt);

  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if(ES_EVTC_MDI == cat)
  {
    switch(as_<EsMdiEvt>(id))
    {
    case EsMdiEvt::DocumentCreated:
      m_owner.onDocumentCreated(
        payload[0].asString()
      );
      break;
    case EsMdiEvt::DocumentOpened:
      m_owner.onDocumentOpened(
        payload[0].asString()
      );
      break;
    case EsMdiEvt::DocumentClosed:
      m_owner.onDocumentClosed(
        payload[0].asString()
      );
      break;
    case EsMdiEvt::DocumentKeyChanged:
      m_owner.onDocumentKeyChanged(
        payload[0].asString(),
        payload[1].asString()
      );
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

EsOpenedDocumentList::EsOpenedDocumentList(wxWindow* parent, wxWindowID id /*= wxID_ANY*/) :
  EsListViewBase(parent, id),
  m_evtHandler(*this)
{
  // Set-up model
  EsListViewModel::Ptr model = EsListViewModel::create();
  ES_ASSERT(model);

  model->fieldAdd(
    _i("Name"),
    100
  ).
  fieldAdd(
    _i("Path"),
    300
  ).
  fieldAdd(
    _i("Type"),
    60
  );
  modelSet(model);

  Bind(
    wxEVT_LIST_ITEM_ACTIVATED,
    &EsOpenedDocumentList::onDocumentSelected,
    this
  );
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::ctxMenuInit()
{
  ES_ASSERT(m_pmnu);

  m_pmnu->Append(
    usrID_CLOSE,
    _("Close"),
    _("Clsoe document, selected in list")
  );
  m_pmnu->Append(
    usrID_CLOSE_ALL,
    _("Close all"),
    _("Close all open documents")
  );

  const wxSize& appmnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_pmnu.get(),
    usrID_CLOSE,
    appmnuimgsze,
    wxART_OTHER,
    esART_CLOSE
  );

  EsUtilities::menuItemBitmapSet(
    m_pmnu.get(),
    usrID_CLOSE_ALL,
    appmnuimgsze,
    wxART_OTHER,
    esART_CLOSE_ALL
  );
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::toolBarInit()
{
  wxMenuPtr pmnu = ctxMenuGet();

  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_CLOSE,
    wxART_TOOLBAR,
    esART_CLOSE
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_ptb,
    pmnu.get(),
    usrID_CLOSE_ALL,
    wxART_TOOLBAR,
    esART_CLOSE_ALL
  );
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::evtHandlersSet(wxEvtHandler* subj, bool set)
{
  ES_ASSERT(subj);

  if( set )
  {
    subj->Bind(
      wxEVT_MENU,
      &EsOpenedDocumentList::onCloseRequest,
      this,
      usrID_CLOSE
    );
    subj->Bind(
      wxEVT_MENU,
      &EsOpenedDocumentList::onCloseAllRequest,
      this,
      usrID_CLOSE_ALL
    );
    subj->Bind(
      wxEVT_UPDATE_UI,
      &EsOpenedDocumentList::onUpdateUi,
      this,
      usrID_CLOSE,
      usrID_CLOSE_ALL
    );
  }
  else
  {
    subj->Unbind(
      wxEVT_MENU,
      &EsOpenedDocumentList::onCloseRequest,
      this,
      usrID_CLOSE
    );
    subj->Unbind(
      wxEVT_MENU,
      &EsOpenedDocumentList::onCloseAllRequest,
      this,
      usrID_CLOSE_ALL
    );
    subj->Unbind(
      wxEVT_UPDATE_UI,
      &EsOpenedDocumentList::onUpdateUi,
      this,
      usrID_CLOSE,
      usrID_CLOSE_ALL
    );
  }
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onDocumentCreated(const EsString& key)
{
#ifdef ES_DEBUG
  const EsVariant& found = m_model->recordsFind(1, key); //< Field index 1 contains full document key by design
  ES_ASSERT(found.isEmpty());
#endif

  const EsPath& path = EsPath::createFromFilePath(key);
  const EsVariant::Array& rec = {
    path.fileNameExtGet(),
    key,
    path.fileExtGet()
  };

  m_model->recordAppend(
    rec
  );
  refresh(true);
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onDocumentOpened(const EsString& key)
{
  const EsVariant& found = m_model->recordsFind(1, key); //< Field index 1 contains full document key by design

  if(!found.isEmpty())
    return;

  const EsPath& path = EsPath::createFromFilePath(key);
  const EsVariant::Array& rec = {
    path.fileNameExtGet(),
    key,
    path.fileExtGet()
  };

  m_model->recordAppend(
    rec
  );
  refresh(true);
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onDocumentClosed(const EsString& key)
{
  const EsVariant& found = m_model->recordsFind(1, key); //< Field index 1 contains full document key by design
  if(found.isEmpty())
    return;

  ES_ASSERT(1 == found.countGet());
  m_model->recordDelete(
    found[0].asULong()
  );
  refresh(true);
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onDocumentKeyChanged(const EsString& keyOld, const EsString& keyNew)
{
  const EsVariant& found = m_model->recordsFind(1, keyOld); //< Field index 1 contains full document key by design
  if(found.isEmpty())
    return;

  const EsPath& path = EsPath::createFromFilePath(keyNew);
  const EsVariant::Array& rec = {
    path.fileNameExtGet(),
    keyNew,
    path.fileExtGet()
  };

  ES_ASSERT(1 == found.countGet());
  m_model->recordSet(
    found[0].asULong(),
    rec
  );
  refresh(true);
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onI18nLocaleChanged(const EsString& lang)
{
  // TODO:
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onDocumentSelected(wxListEvent& evt)
{
  long idx = evt.GetIndex();
  if(0 > idx || !m_model)
    return;

  const EsVariant::Array& rec = m_model->recordGet(idx);
  const EsString& key = rec[1].asString(); //< Activated document key

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::DocumentActivate),
    key
  );
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onCloseRequest(wxCommandEvent& ES_UNUSED(evt))
{
  EsString::Array keys;

  long item = -1;
  do
  {
    item = GetNextItem(
      item,
      wxLIST_NEXT_ALL,
      wxLIST_STATE_SELECTED
    );
    
    if( -1 < item )
    {
      const EsString& key = m_model->fieldDataGet(
        item,
        1 //< Document key field index
      ).asString();

      keys.push_back(key);
    }

  } while( -1 < item );

  if( keys.empty() )
    return;

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::DocListCloseRequest),
    keys
  );
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onCloseAllRequest(wxCommandEvent& ES_UNUSED(evt))
{
  wxGetApp().mainWindowGet().documentsCloseAll();
}
//--------------------------------------------------------------------------------

void EsOpenedDocumentList::onUpdateUi(wxUpdateUIEvent& evt)
{
  switch( evt.GetId() )
  {
  case usrID_CLOSE:
    evt.Enable(
      m_model && 
      !m_model->isEmpty() &&
      GetSelectedItemCount() > 0
    );
    break;
  case usrID_CLOSE_ALL:
    evt.Enable(
      m_model &&
      !m_model->isEmpty()
    );
    break;
  }
}
//--------------------------------------------------------------------------------
