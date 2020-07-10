#ifndef _es_opened_document_list_h_
#define _es_opened_document_list_h_

class EsOpenedDocumentList : public EsListViewBase
{
private:
  // Local Event IDs
  enum {
    usrID_CLOSE      = EsSconsoleCmds::usrConsoleMainIdMax,
    usrID_CLOSE_ALL
  };

  // ES Event subscriber
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsOpenedDocumentList& owner) ES_NOTHROW;

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  protected:
    EsOpenedDocumentList& m_owner;
  };
  friend class EvtHandler;

public:
  EsOpenedDocumentList(wxWindow* parent, wxWindowID id = wxID_ANY);

protected:
  /// Base class API implkementation
  virtual int keyFromItemGet(long item) const ES_OVERRIDE { return item; }

  virtual void ctxMenuInit() ES_OVERRIDE;
  virtual void toolBarInit() ES_OVERRIDE;
  virtual void evtHandlersSet(wxEvtHandler* subj, bool set) ES_OVERRIDE;

  // ES event handlers
  void onDocumentCreated(const EsString& key);
  void onDocumentOpened(const EsString& key);
  void onDocumentClosed(const EsString& key);
  void onDocumentKeyChanged(const EsString& keyOld, const EsString& keyNew);
  void onI18nLocaleChanged(const EsString& lang);

  // WX event handlers
  void onDocumentSelected(wxListEvent& evt);
  void onCloseRequest(wxCommandEvent& evt);
  void onCloseAllRequest(wxCommandEvent& evt);
  void onUpdateUi(wxUpdateUIEvent& evt);

protected:
  EvtHandler m_evtHandler;
};

#endif // _es_opened_document_list_h_
