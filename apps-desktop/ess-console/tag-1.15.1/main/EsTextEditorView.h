#ifndef _es_text_editor_view_h_
#define _es_text_editor_view_h_

class EsTextEditorView : public EsTextEditorViewBase
{
protected:
  EsTextEditorView(wxWindow *parent, wxWindowID id, long style);

public:
  static EsTextEditorView* create(wxWindow *parent, wxWindowID id = wxID_ANY, long style = 0);

private:
  EsTextEditorView() ES_REMOVEDECL;
  EsTextEditorView(const EsTextEditorView&) ES_REMOVEDECL;
  EsTextEditorView& operator=(const EsTextEditorView&) ES_REMOVEDECL;
};

#endif // _es_text_editor_view_h_
