#ifndef _es_code_insight_view_h_
#define _es_code_insight_view_h_

/// @file EsCompiledScriptView.h
/// Compiled script binary view form ess console MDI workspace
///

class EsCodeInsightView : public wxPanel
{
public:
  EsCodeInsightView(wxWindow* parent);

private:
  EsCodeInsightView() ES_REMOVEDECL;
  EsCodeInsightView(const EsCodeInsightView&) ES_REMOVEDECL;
  EsCodeInsightView& operator=(const EsCodeInsightView&) ES_REMOVEDECL;
};

#endif // _es_code_insight_view_h_

