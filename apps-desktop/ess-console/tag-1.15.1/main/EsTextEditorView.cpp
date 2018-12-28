#include "ess_console_pch.h"
#pragma hdrstop

#include "EsTextEditorView.h"
//--------------------------------------------------------------------------------

EsTextEditorView::EsTextEditorView(wxWindow *parent, wxWindowID id, long style) :
EsTextEditorViewBase(
  parent,
  id,
  style,
  esT("EsTextEditorView")
)
{
}
//--------------------------------------------------------------------------------

EsTextEditorView* EsTextEditorView::create(wxWindow *parent, wxWindowID id /*= wxID_ANY*/, long style /*= 0*/)
{
  std::unique_ptr<EsTextEditorView> ptr(
    new EsTextEditorView(
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
