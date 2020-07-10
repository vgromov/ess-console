#ifndef _es_sconsole_output_base_h_
#define _es_sconsole_output_base_h_

/// @file EsSconsoleOutputBase.h 
/// Console styled messages read-only view base class
/// 
class EsSconsoleOutputBase : public wxStyledTextCtrl
{
public:
  /// Custom commands
  ///
  enum {
    usrID_SELECT_ALL = EsSconsoleCmds::usrConsoleMainIdMax,
    usrID_COPY,
    usrID_CLEARALL,
    usrID_GOTO,

    // Specific value, must go last
    usrConsoleOutputIdMax
  };

public:
  EsSconsoleOutputBase(wxWindow* parent);
  virtual ~EsSconsoleOutputBase() ES_OVERRIDE;

  wxMenuSharedPtr ctxMenuGet();
  wxToolBar* toolBarGet(wxWindow* parent);

protected:
  // Initialize highlighting styles
  void styleInit(int lexerId);

  // Text read-only modification API
  void textClearAll();
  void textLineAppend(const wxString& txt);

  // Parsing and Positioning API
  void txtParseForFilePositionAndGoto(const wxString& txt, bool isExecMode = false);

  virtual void ctxMenuInit();
  virtual void toolBarInit();
  virtual void evtHandlersSet(wxEvtHandler* subj, bool set);

  // WX event handlers
  void onContextMenu(wxContextMenuEvent& evt);
  void onDoubleClick(wxStyledTextEvent& evt);
  void onSelectAll(wxCommandEvent& evt);
  void onCopy(wxCommandEvent& evt);
  void onClearAll(wxCommandEvent& evt);
  void onGoto(wxCommandEvent& evt);

protected:
  wxMenuSharedPtr m_pmnu;
  wxToolBar* m_ptb;
};

#endif // _es_sconsole_output_base_h_
