#include "ess_console_pch.h"
#pragma hdrstop

#include "EsDbgLogRulesDlg.h"
//--------------------------------------------------------------------------------

EsDbgLogRulesDlg::EsDbgLogRulesDlg(wxWindow* parent) :
  EsDlgBase(
    parent,
    wxEmptyString,
    wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
  ),
  m_szrTest(nullptr),
  m_edTest(nullptr),
  m_btnTestEval(nullptr),
  m_bmEvalStat(nullptr),
  m_chkInclFirst(nullptr),
  m_szrIncl(nullptr),
  m_edIncl(nullptr),
  m_szrInclBtns(nullptr),
  m_btnInclUp(nullptr),
  m_btnInclDown(nullptr),
  m_btnAddIncl(nullptr),
  m_btnReplaceIncl(nullptr),
  m_btnDeleteIncl(nullptr),
  m_lblListIncl(nullptr),
  m_lstIncl(nullptr),
  m_szrExcl(nullptr),
  m_edExcl(nullptr),
  m_szrExclBtns(nullptr),
  m_btnExclUp(nullptr),
  m_btnExclDown(nullptr),
  m_btnAddExcl(nullptr),
  m_btnReplaceExcl(nullptr),
  m_btnDeleteExcl(nullptr),
  m_lblListExcl(nullptr),
  m_lstExcl(nullptr),
  m_btnOk(nullptr),
  m_btnCancel(nullptr)
{
  // Rule Evaluation test controls
  // 
  m_szrTest = new wxStaticBoxSizer(
    wxHORIZONTAL,
    this,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_szrTest);

  m_edTest = new wxTextCtrl(
    m_szrTest->GetStaticBox(),
    wxID_ANY
  );
  ES_ASSERT(m_edTest);

  m_szrTest->Add(
    m_edTest,
    wxSizerFlags(1).Expand().Border()
  );

  m_btnTestEval = new wxButton(
    m_szrTest->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnTestEval);

  m_szrTest->Add(
    m_btnTestEval,
    wxSizerFlags().Border()
  );

  m_bmEvalStat = new wxStaticBitmap(
    m_szrTest->GetStaticBox(),
    wxID_ANY,
    wxNullBitmap
  );
  ES_ASSERT(m_bmEvalStat);

  m_szrTest->Add(
    m_bmEvalStat,
    wxSizerFlags().Border()
  );

  m_contents->Add(
    m_szrTest,
    wxSizerFlags().Expand().Border()
  );
  //
  // Eval test controls end

  // Rules order 
  //
  m_chkInclFirst = new wxCheckBox(
    this,
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_chkInclFirst);

  m_contents->Add(
    m_chkInclFirst,
    wxSizerFlags().Expand().Border()
  );
  // 
  // Rules order end

  // Inclusion rules editor
  //
  m_szrIncl = new wxStaticBoxSizer(
    wxVERTICAL,
    this,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_szrIncl);

  m_edIncl = new wxTextCtrl(
    m_szrIncl->GetStaticBox(),
    wxID_ANY
  );
  ES_ASSERT(m_edIncl);
  m_szrIncl->Add(
    m_edIncl,
    wxSizerFlags().Expand().Border()
  );

  m_szrInclBtns = new wxBoxSizer(wxHORIZONTAL);
  ES_ASSERT(m_szrInclBtns);

  m_btnInclUp = new wxButton(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnInclUp);

  m_szrInclBtns->Add(
    m_btnInclUp,
    wxSizerFlags().Border()
  );

  m_btnInclDown = new wxButton(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnInclDown);

  m_szrInclBtns->Add(
    m_btnInclDown,
    wxSizerFlags().Border()
  );

  m_btnAddIncl = new wxButton(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnAddIncl);

  m_szrInclBtns->Add(
    m_btnAddIncl,
    wxSizerFlags().Border()
  );

  m_btnReplaceIncl = new wxButton(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnReplaceIncl);

  m_szrInclBtns->Add(
    m_btnReplaceIncl,
    wxSizerFlags().Border()
  );

  m_btnDeleteIncl = new wxButton(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnDeleteIncl);

  m_szrInclBtns->Add(
    m_btnDeleteIncl,
    wxSizerFlags().Border()
  );

  m_szrIncl->Add(
    m_szrInclBtns,
    wxSizerFlags().Expand().Border()
  );

  m_lblListIncl = new wxStaticText(
    m_szrIncl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_lblListIncl);

  m_szrIncl->Add(
    m_lblListIncl,
    wxSizerFlags().Expand().Border()
  );

  m_lstIncl = new wxListBox(
    m_szrIncl->GetStaticBox(),
    wxID_ANY
  );
  ES_ASSERT(m_lstIncl);

  m_szrIncl->Add(
    m_lstIncl,
    wxSizerFlags(1).Expand().Border()
  );

  m_contents->Add(
    m_szrIncl,
    wxSizerFlags(1).Expand().Border()
  );
  //
  // Inclusion rules editor end

  // Exclusion rules editor
  // 
  m_szrExcl = new wxStaticBoxSizer(
    wxVERTICAL,
    this,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_szrExcl);

  m_edExcl = new wxTextCtrl(
    m_szrExcl->GetStaticBox(),
    wxID_ANY
  );
  ES_ASSERT(m_edExcl);
  m_szrExcl->Add(
    m_edExcl,
    wxSizerFlags().Expand().Border()
  );

  m_szrExclBtns = new wxBoxSizer(wxHORIZONTAL);
  ES_ASSERT(m_szrExclBtns);

  m_btnExclUp = new wxButton(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnExclUp);

  m_szrExclBtns->Add(
    m_btnExclUp,
    wxSizerFlags().Border()
  );

  m_btnExclDown = new wxButton(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnExclDown);

  m_szrExclBtns->Add(
    m_btnExclDown,
    wxSizerFlags().Border()
  );

  m_btnAddExcl = new wxButton(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnAddExcl);

  m_szrExclBtns->Add(
    m_btnAddExcl,
    wxSizerFlags().Border()
  );

  m_btnReplaceExcl = new wxButton(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnReplaceExcl);

  m_szrExclBtns->Add(
    m_btnReplaceExcl,
    wxSizerFlags().Border()
  );

  m_btnDeleteExcl = new wxButton(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnDeleteExcl);

  m_szrExclBtns->Add(
    m_btnDeleteExcl,
    wxSizerFlags().Border()
  );

  m_szrExcl->Add(
    m_szrExclBtns,
    wxSizerFlags().Expand().Border()
  );

  m_lblListExcl = new wxStaticText(
    m_szrExcl->GetStaticBox(),
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_lblListExcl);

  m_szrExcl->Add(
    m_lblListExcl,
    wxSizerFlags().Expand().Border()
  );

  m_lstExcl = new wxListBox(
    m_szrExcl->GetStaticBox(),
    wxID_ANY
  );
  ES_ASSERT(m_lstExcl);

  m_szrExcl->Add(
    m_lstExcl,
    wxSizerFlags(1).Expand().Border()
  );

  m_contents->Add(
    m_szrExcl,
    wxSizerFlags(1).Expand().Border()
  );
  //
  // Exclusion rules editor end

  // Dialog Buttons
  //
  ES_ASSERT(m_btns);

  m_btnOk = new wxButton(
    this,
    wxID_OK,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnOk);

  m_btnCancel = new wxButton(
    this,
    wxID_CANCEL,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_btnCancel);

  m_btns->AddButton(m_btnOk);
  m_btns->AddButton(m_btnCancel);
  m_btns->SetAffirmativeButton(m_btnOk);
  m_btns->SetCancelButton(m_btnCancel);

  // Setup event handlers
  //
  m_edTest->Bind(
    wxEVT_TEXT,
    &EsDbgLogRulesDlg::onTestSubjChanged,
    this
  );
  m_btnTestEval->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onTestEval,
    this
  );
  m_btnInclUp->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onInclItemUp,
    this
  );
  m_btnInclDown->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onInclItemDown,
    this
  );
  m_btnAddIncl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onInclItemAdd,
    this
  );
  m_btnReplaceIncl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onInclItemReplace,
    this
  );
  m_btnDeleteIncl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onInclItemDelete,
    this
  );
  m_lstIncl->Bind(
    wxEVT_LISTBOX,
    &EsDbgLogRulesDlg::onInclListItemChange,
    this
  );

  m_btnExclUp->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onExclItemUp,
    this
  );
  m_btnExclDown->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onExclItemDown,
    this
  );
  m_btnAddExcl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onExclItemAdd,
    this
  );
  m_btnReplaceExcl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onExclItemReplace,
    this
  );
  m_btnDeleteExcl->Bind(
    wxEVT_BUTTON,
    &EsDbgLogRulesDlg::onExclItemDelete,
    this
  );
  m_lstExcl->Bind(
    wxEVT_LISTBOX,
    &EsDbgLogRulesDlg::onExclListItemChange,
    this
  );

  // Bind UI updaters for all buttons and edit boxes
  //
  m_edTest->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnTestEval->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_edIncl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnInclUp->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnInclDown->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnAddIncl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnReplaceIncl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnDeleteIncl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_lstIncl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_edExcl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnExclUp->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnExclDown->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnAddExcl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnReplaceExcl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_btnDeleteExcl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
  m_lstExcl->Bind(
    wxEVT_UPDATE_UI,
    &EsDbgLogRulesDlg::onUpdateUi,
    this
  );
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::inclIsFirstGet() const
{
  ES_ASSERT(m_chkInclFirst);
  return m_chkInclFirst->GetValue();
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::inclIsFirstSet(bool inclFirst)
{
  ES_ASSERT(m_chkInclFirst);
  m_chkInclFirst->SetValue(inclFirst);
}
//--------------------------------------------------------------------------------

EsString::Array EsDbgLogRulesDlg::rulesInclGet() const
{
  ES_ASSERT(m_lstIncl);

  return EsUtilities::wxArrayStringToEsStringArray(
    m_lstIncl->GetStrings()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::rulesInclSet(const EsString::Array& rules)
{
  ES_ASSERT(m_lstIncl);

  wxWindowUpdateLocker lock(m_lstIncl);
  m_lstIncl->Clear();
  m_lstIncl->Append(
    EsUtilities::esStringArrayToWxArrayString(rules)
  );
}
//--------------------------------------------------------------------------------

EsString::Array EsDbgLogRulesDlg::rulesExclGet() const
{
  ES_ASSERT(m_lstExcl);

  return EsUtilities::wxArrayStringToEsStringArray(
    m_lstExcl->GetStrings()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::rulesExclSet(const EsString::Array& rules)
{
  ES_ASSERT(m_lstExcl);

  wxWindowUpdateLocker lock(m_lstExcl);
  m_lstExcl->Clear();
  m_lstExcl->Append(
    EsUtilities::esStringArrayToWxArrayString(rules)
  );
}
//--------------------------------------------------------------------------------

const wxSize& EsDbgLogRulesDlg::minSizeGet()
{
  static const wxSize c_minSize = { 320, 680 };
  return c_minSize;
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onI18nLocaleChanged(const EsString& ES_UNUSED(loc))
{
  SetTitle(
    _("Debug Log suppressing rules editor").as<wxString>()
  );

  ES_ASSERT(m_szrTest);
  m_szrTest->GetStaticBox()->SetLabel(
    _("Rules evaluation test").as<wxString>()
  );

  ES_ASSERT(m_edTest);
  m_edTest->SetHint(
    _("Enter the test subject").as<wxString>()
  );
  m_edTest->SetHelpText(
    _("Enter the text to test ruleset on").as<wxString>()
  );

  ES_ASSERT(m_btnTestEval);
  m_btnTestEval->SetLabel(
    _("Evaluate").as<wxString>()
  );
  m_btnTestEval->SetHelpText(
    _("Evaluate rules set on test subject").as<wxString>()
  );

  ES_ASSERT(m_chkInclFirst);
  m_chkInclFirst->SetLabel(
    _("Inclusion rules first").as<wxString>()
  );
  m_chkInclFirst->SetHelpText(
    _("Execute inclusion ruleset before an exclusion one").as<wxString>()
  );

  ES_ASSERT(m_szrIncl);
  m_szrIncl->GetStaticBox()->SetLabel(
    _("Inclusion rules").as<wxString>()
  );

  ES_ASSERT(m_edIncl);
  m_edIncl->SetHint(
    _("Include rule").as<wxString>()
  );
  m_edIncl->SetHelpText(
    _("Edit Include rule's regular expression").as<wxString>()
  );

  ES_ASSERT(m_lblListIncl);
  m_lblListIncl->SetLabel(
    _("Inclusion rules list").as<wxString>()
  );

  ES_ASSERT(m_szrExcl);
  m_szrExcl->GetStaticBox()->SetLabel(
    _("Exclusion rules").as<wxString>()
  );

  ES_ASSERT(m_edExcl);
  m_edExcl->SetHint(
    _("Exclude rule").as<wxString>()
  );
  m_edExcl->SetHelpText(
    _("Edit Exclude rule's regular expression").as<wxString>()
  );
  
  ES_ASSERT(m_lblListExcl);
  m_lblListExcl->SetLabel(
    _("Exclusion rules list").as<wxString>()
  );

  ES_ASSERT(m_btnInclUp);
  ES_ASSERT(m_btnExclUp);
  m_btnInclUp->SetLabel(
    _("Up").as<wxString>()
  );
  m_btnExclUp->SetLabel(
    m_btnInclUp->GetLabel()
  );
  m_btnInclUp->SetHelpText(
    _("Move rule up in ruleset").as<wxString>()
  );
  m_btnExclUp->SetHelpText(
    m_btnInclUp->GetHelpText()
  );

  ES_ASSERT(m_btnInclDown);
  ES_ASSERT(m_btnExclDown);
  m_btnInclDown->SetLabel(
    _("Down").as<wxString>()
  );
  m_btnExclDown->SetLabel(
    m_btnInclDown->GetLabel()
  );
  m_btnInclDown->SetHelpText(
    _("Move rule down in ruleset").as<wxString>()
  );
  m_btnExclDown->SetHelpText(
    m_btnInclDown->GetHelpText()
  );

  ES_ASSERT(m_btnAddIncl);
  ES_ASSERT(m_btnAddExcl);
  m_btnAddIncl->SetLabel(
    _("Add").as<wxString>()
  );
  m_btnAddExcl->SetLabel(
    m_btnAddIncl->GetLabel()
  );
  m_btnAddIncl->SetHelpText(
    _("Add rule to an Inclusion ruleset").as<wxString>()
  );
  m_btnAddExcl->SetHelpText(
    _("Add rule to an Exclusion ruleset").as<wxString>()
  );

  ES_ASSERT(m_btnReplaceIncl);
  ES_ASSERT(m_btnReplaceExcl);
  m_btnReplaceIncl->SetLabel(
    _("Replace").as<wxString>()
  );
  m_btnReplaceExcl->SetLabel(
    m_btnReplaceIncl->GetLabel()
  );
  m_btnReplaceIncl->SetHelpText(
    _("Replace rule in an Inclusion ruleset").as<wxString>()
  );
  m_btnReplaceExcl->SetHelpText(
    _("Replace rule in an Exclusion ruleset").as<wxString>()
  );

  ES_ASSERT(m_btnDeleteIncl);
  ES_ASSERT(m_btnDeleteExcl);
  m_btnDeleteIncl->SetLabel(
    _("Delete").as<wxString>()
  );
  m_btnDeleteExcl->SetLabel(
    m_btnDeleteIncl->GetLabel()
  );
  m_btnDeleteIncl->SetHelpText(
    _("Delete rule from an Inclusion ruleset").as<wxString>()
  );
  m_btnDeleteExcl->SetHelpText(
    _("Replace rule from an Exclusion ruleset").as<wxString>()
  );

  m_contents->Layout();

  m_btnOk->SetLabel(_("OK").as<wxString>());
  m_btnCancel->SetLabel(_("Cancel").as<wxString>());

  m_btns->Layout();
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::rulesEvaluate(const EsString& fname) const
{
  return EsScript::shouldSuppressDbgLog(
    fname,
    inclIsFirstGet(),
    rulesInclGet(),
    rulesExclGet()
  );
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::hasCurrent(wxListBox* list) const ES_NOTHROW
{
  return wxNOT_FOUND != list->GetSelection();
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::canAdd(wxListBox* list, wxTextCtrl* ed) const ES_NOTHROW
{
  return !ed->IsEmpty() &&
    wxNOT_FOUND == list->FindString(ed->GetValue());
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::canReplace(wxListBox* list, wxTextCtrl* ed) const ES_NOTHROW
{
  if(ed->IsEmpty())
    return false;

  int sel = list->GetSelection();
  if(wxNOT_FOUND == sel)
    return false;

  return wxNOT_FOUND == list->FindString(ed->GetValue());
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::canMoveCurrentUp(wxListBox* list) const ES_NOTHROW
{
  return 0 < list->GetSelection();
}
//--------------------------------------------------------------------------------

bool EsDbgLogRulesDlg::canMoveCurrentDown(wxListBox* list) const ES_NOTHROW
{
  int sel = list->GetSelection();
  return (sel > wxNOT_FOUND) && (sel < static_cast<int>(list->GetCount()) - 1);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::moveCurrentUp(wxListBox* list) ES_NOTHROW
{
  int sel = list->GetSelection();
  ES_ASSERT(sel > 0);
  wxWindowUpdateLocker lock(list);

  wxString str = list->GetStringSelection();
  list->Delete(sel);
  list->Insert(
    str,
    sel - 1
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::moveCurrentDown(wxListBox* list) ES_NOTHROW
{
  int sel = list->GetSelection();
  ES_ASSERT(sel < static_cast<int>(list->GetCount()) - 1);
  wxWindowUpdateLocker lock(list);

  wxString str = list->GetStringSelection();
  list->Delete(sel);
  list->Insert(
    str,
    sel + 1
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::itemInsert(wxListBox* list, wxTextCtrl* ed) ES_NOTHROW
{
  int sel = list->GetSelection();
  if(
    wxNOT_FOUND == sel ||
    sel == list->GetCount() - 1
  )
    list->Append(
      ed->GetValue()
    );
  else
    list->Insert(
      ed->GetValue(),
      sel
    );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::itemReplace(wxListBox* list, wxTextCtrl* ed) ES_NOTHROW
{
  list->SetString(
    list->GetSelection(),
    ed->GetValue()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::itemDelete(wxListBox* list) ES_NOTHROW
{
  list->Delete(
    list->GetSelection()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onTestSubjChanged(wxCommandEvent& evt)
{
  if(!m_bmEvalStat->GetBitmap().IsNull())
    m_bmEvalStat->SetBitmap(wxNullBitmap);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclItemUp(wxCommandEvent& ES_UNUSED(evt))
{
  moveCurrentUp(m_lstIncl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclItemDown(wxCommandEvent& ES_UNUSED(evt))
{
  moveCurrentDown(m_lstIncl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclItemAdd(wxCommandEvent& ES_UNUSED(evt))
{
  itemInsert(
    m_lstIncl,
    m_edIncl
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclItemReplace(wxCommandEvent& ES_UNUSED(evt))
{
  itemReplace(
    m_lstIncl,
    m_edIncl
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclItemDelete(wxCommandEvent& ES_UNUSED(evt))
{
  itemDelete(m_lstIncl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onInclListItemChange(wxCommandEvent& ES_UNUSED(evt))
{
  m_edIncl->SetValue(
    m_lstIncl->GetStringSelection()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclItemUp(wxCommandEvent& ES_UNUSED(evt))
{
  moveCurrentUp(m_lstExcl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclItemDown(wxCommandEvent& ES_UNUSED(evt))
{
  moveCurrentDown(m_lstExcl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclItemAdd(wxCommandEvent& ES_UNUSED(evt))
{
  itemInsert(
    m_lstExcl,
    m_edExcl
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclItemReplace(wxCommandEvent& ES_UNUSED(evt))
{
  itemReplace(
    m_lstExcl,
    m_edExcl
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclItemDelete(wxCommandEvent& ES_UNUSED(evt))
{
  itemDelete(m_lstExcl);
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onExclListItemChange(wxCommandEvent& ES_UNUSED(evt))
{
  m_edExcl->SetValue(
    m_lstExcl->GetStringSelection()
  );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onTestEval(wxCommandEvent& ES_UNUSED(evt))
{
  bool ok = rulesEvaluate(
    m_edTest->GetValue().t_str()
  );

  if(ok)
    m_bmEvalStat->SetBitmap(
      wxArtProvider::GetBitmap(wxART_PLUS)
    );
  else
    m_bmEvalStat->SetBitmap(
      wxArtProvider::GetBitmap(wxART_MINUS)
    );
}
//--------------------------------------------------------------------------------

void EsDbgLogRulesDlg::onUpdateUi(wxUpdateUIEvent& evt)
{
  wxObject* obj = evt.GetEventObject();
  if(obj == m_btnTestEval)
  {
    evt.Enable(
      !m_edTest->IsEmpty()
    );
    return;
  }

  if(obj == m_btnInclUp)
  {
    evt.Enable(
      canMoveCurrentUp(m_lstIncl)
    );
    return;
  }

  if(obj == m_btnInclDown)
  {
    evt.Enable(
      canMoveCurrentDown(m_lstIncl)
    );
    return;
  }

  if(obj == m_btnAddIncl)
  {
    evt.Enable(
      canAdd(
      m_lstIncl,
      m_edIncl
    )
    );
    return;
  }

  if(obj == m_btnReplaceIncl)
  {
    evt.Enable(
      canReplace(
      m_lstIncl,
      m_edIncl
    )
    );
    return;
  }

  if(obj == m_btnDeleteIncl)
  {
    evt.Enable(
      wxNOT_FOUND != m_lstIncl->GetSelection()
    );
    return;
  }

  if(obj == m_btnExclUp)
  {
    evt.Enable(
      canMoveCurrentUp(m_lstExcl)
    );
    return;
  }

  if(obj == m_btnExclDown)
  {
    evt.Enable(
      canMoveCurrentDown(m_lstExcl)
    );
    return;
  }

  if(obj == m_btnAddExcl)
  {
    evt.Enable(
      canAdd(
      m_lstExcl,
      m_edExcl
    )
    );
    return;
  }

  if(obj == m_btnReplaceExcl)
  {
    evt.Enable(
      canReplace(
      m_lstExcl,
      m_edExcl
    )
    );
    return;
  }

  if(obj == m_btnDeleteExcl)
  {
    evt.Enable(
      wxNOT_FOUND != m_lstExcl->GetSelection()
    );
    return;
  }
}
//--------------------------------------------------------------------------------
