#include "ess_console_pch.h"
#pragma hdrstop

#include "EsPathsListDlg.h"
//--------------------------------------------------------------------------------

const wxSize& EsPathsListDlg::minSizeGet()
{
  static const wxSize c_minSize = { 300, 500 };
  return c_minSize;
}
//--------------------------------------------------------------------------------

EsPathsListDlg::EsPathsListDlg(
  wxWindow* parent, 
  const wxString& title,
  const wxString& dirPickerPrompt,
  const wxString& dirListLabel
) :
EsDlgBase(
  parent, 
  title,
  wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
),
m_dirPickerPrompt(dirPickerPrompt),
m_dirListLabel(dirListLabel),
m_folderOps(nullptr),
m_folderBtns(nullptr),
m_folder(nullptr),
m_btnUp(nullptr),
m_btnDown(nullptr),
m_btnAdd(nullptr),
m_btnReplace(nullptr),
m_btnDelete(nullptr),
m_lblList(nullptr),
m_lstFolders(nullptr),
m_btnOk(nullptr),
m_btnCancel(nullptr)
{
  SetMinSize(
    minSizeGet()
  );

  m_folderOps = new wxBoxSizer(wxVERTICAL);
  ES_ASSERT(m_folderOps);

  m_folder = new wxDirPickerCtrl(
    this,
    wxID_ANY,
    wxEmptyString,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxDIRP_DEFAULT_STYLE|wxDIRP_SMALL
  );
  ES_ASSERT(m_folder);

  wxSize szeDefault = { 16, 16 };
  wxSize szeBtnDefault = {
    -1,
    wxSystemSettings::GetMetric(
       wxSystemMetric::wxSYS_MENU_Y
     ) + 
    4*wxSystemSettings::GetMetric(
      wxSystemMetric::wxSYS_BORDER_Y
    )
  };

  m_btnUp = new wxButton(
    this,
    wxID_UP,
    EsUtilities::wxSpaceString(),
    wxDefaultPosition,
    szeBtnDefault
  );
  ES_ASSERT(m_btnUp);
  m_btnUp->SetBitmap(
    wxArtProvider::GetBitmap(
      wxART_GO_UP,
      wxART_OTHER,
      szeDefault
    )
  );

  m_btnDown = new wxButton(
    this,
    wxID_DOWN,
    EsUtilities::wxSpaceString(),
    wxDefaultPosition,
    szeBtnDefault
  );
  ES_ASSERT(m_btnDown);
  m_btnDown->SetBitmap(
    wxArtProvider::GetBitmap(
      wxART_GO_DOWN,
      wxART_OTHER,
      szeDefault
    )
  );

  m_btnAdd = new wxButton(
    this,
    wxID_ADD,
    EsUtilities::wxSpaceString(),
    wxDefaultPosition,
    szeBtnDefault
  );
  ES_ASSERT(m_btnAdd);
  m_btnAdd->SetBitmap(
    wxArtProvider::GetBitmap(
      wxART_PLUS,
      wxART_OTHER,
      szeDefault
    )
  );

  m_btnReplace = new wxButton(
    this,
    wxID_REPLACE,
    EsUtilities::wxSpaceString(),
    wxDefaultPosition,
    szeBtnDefault
  );
  ES_ASSERT(m_btnReplace);

  m_btnDelete = new wxButton(
    this,
    wxID_DELETE,
    EsUtilities::wxSpaceString(),
    wxDefaultPosition,
    szeBtnDefault
  );
  ES_ASSERT(m_btnDelete);
  m_btnDelete->SetBitmap(
    wxArtProvider::GetBitmap(
      wxART_DELETE,
      wxART_OTHER,
      szeDefault
    )
  );

  m_folderOps->Add(
    m_folder,
    wxSizerFlags(1).Expand()
  );

  m_folderBtns = new wxBoxSizer(wxHORIZONTAL);
  ES_ASSERT(m_folderBtns);

  m_folderBtns->Add(
    m_btnUp,
    wxSizerFlags().Left()
  );
  m_folderBtns->Add(
    m_btnDown,
    wxSizerFlags().Left().Border(wxRIGHT)
  );
  m_folderBtns->Add(
    m_btnAdd,
    wxSizerFlags().Left().Border(wxRIGHT)
  );
  m_folderBtns->Add(
    m_btnReplace,
    wxSizerFlags().Left().Border(wxRIGHT)
  );
  m_folderBtns->Add(
    m_btnDelete,
    wxSizerFlags().Left()
  );

  m_folderOps->Add(
    m_folderBtns,
    wxSizerFlags().Expand()
  );

  m_lstFolders = new wxListBox(
    this,
    wxID_ANY
  );
  ES_ASSERT(m_lstFolders);

  ES_ASSERT(m_contents);

  m_lblList = new wxStaticText(
    this,
    wxID_ANY,
    EsUtilities::wxSpaceString()
  );
  ES_ASSERT(m_lblList);

  m_contents->Add(
    m_folderOps,
    wxSizerFlags().Top().Expand().Border()
  );
  m_contents->Add(
    m_lblList,
    wxSizerFlags().Expand().Top().Border(wxTOP|wxLEFT|wxRIGHT)
  );
  m_contents->Add(
    m_lstFolders,
    wxSizerFlags(1).Expand().Border()
  );

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

  Bind(wxEVT_BUTTON, &EsPathsListDlg::onDirItemUp, this, wxID_UP);
  Bind(wxEVT_BUTTON, &EsPathsListDlg::onDirItemDown, this, wxID_DOWN);
  Bind(wxEVT_BUTTON, &EsPathsListDlg::onDirItemAdd, this, wxID_ADD);
  Bind(wxEVT_BUTTON, &EsPathsListDlg::onDirItemReplace, this, wxID_REPLACE);
  Bind(wxEVT_BUTTON, &EsPathsListDlg::onDirItemDelete, this, wxID_DELETE);
  Bind(wxEVT_LISTBOX, &EsPathsListDlg::onDirListItemChange, this);

  Bind(wxEVT_UPDATE_UI, &EsPathsListDlg::onUpdateUi, this, wxID_UP);
  Bind(wxEVT_UPDATE_UI, &EsPathsListDlg::onUpdateUi, this, wxID_DOWN);
  Bind(wxEVT_UPDATE_UI, &EsPathsListDlg::onUpdateUi, this, wxID_ADD);
  Bind(wxEVT_UPDATE_UI, &EsPathsListDlg::onUpdateUi, this, wxID_REPLACE);
  Bind(wxEVT_UPDATE_UI, &EsPathsListDlg::onUpdateUi, this, wxID_DELETE);
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onI18nLocaleChanged(const EsString& loc)
{
  EsDlgBase::onI18nLocaleChanged(loc);

  wxTextCtrl* txt = m_folder->GetTextCtrl();
  wxString prompt = EsStringI18n::translate(m_dirPickerPrompt.t_str()).c_str();
  if( txt )
    txt->SetToolTip(prompt);
  m_folder->SetToolTip(prompt);

  m_btnUp->SetLabel(_("Up").as<wxString>());
  m_btnUp->SetToolTip(_("Move selected item up one row in the list").as<wxString>());

  m_btnDown->SetLabel(_("Down").as<wxString>());
  m_btnDown->SetToolTip(_("Move selected item dowm one row in the list").as<wxString>());

  m_btnAdd->SetLabel(_("Add").as<wxString>());
  m_btnAdd->SetToolTip(_("Add path, currently selected in folder picker, to the path list").as<wxString>());

  m_btnReplace->SetLabel(_("Replace").as<wxString>());
  m_btnReplace->SetToolTip(_("Replace currently selected item wuth one from the folder picker").as<wxString>());

  m_btnDelete->SetLabel(_("Delete").as<wxString>());
  m_btnReplace->SetToolTip(_("Delete currently selected item from the list").as<wxString>());

  m_lblList->SetLabel(
    EsStringI18n::translate(m_dirListLabel.t_str()).as<wxString>()
  );

  m_contents->Layout();

  m_btnOk->SetLabel(_("OK").as<wxString>());
  m_btnCancel->SetLabel(_("Cancel").as<wxString>());

  m_btns->Layout();
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirItemUp(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(canMoveCurrentUp());
  moveCurrentUp();
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirItemDown(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(canMoveCurrentDown());
  moveCurrentDown();
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirItemAdd(wxCommandEvent& ES_UNUSED(evt))
{
  const wxString& dir = m_folder->GetDirName().GetFullPath();
  ES_ASSERT(!dir.IsEmpty());

  m_lstFolders->AppendString( dir );
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirItemReplace(wxCommandEvent& ES_UNUSED(evt))
{
  int sel = m_lstFolders->GetSelection();
  ES_ASSERT(-1 < sel);

  const wxString& dir = m_folder->GetDirName().GetFullPath();
  ES_ASSERT(!dir.IsEmpty());
  ES_ASSERT(dir != m_lstFolders->GetString(sel));

  m_lstFolders->SetString(
    sel,
    dir
  );
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirItemDelete(wxCommandEvent& evt)
{
  int sel = m_lstFolders->GetSelection();
  ES_ASSERT(-1 < sel);

  m_lstFolders->Delete(
    static_cast<unsigned>(sel)
  );

  if( sel >= static_cast<int>(m_lstFolders->GetCount())-1 )
    sel = static_cast<int>(m_lstFolders->GetCount())-1;

  if( sel > -1 )
    m_lstFolders->SetSelection(sel);
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onDirListItemChange(wxCommandEvent& evt)
{
  int sel = evt.GetSelection();
  if( -1 < sel )
  {
    const wxString& item = m_lstFolders->GetString(sel);
    m_folder->SetDirName(item);
  }
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::onUpdateUi(wxUpdateUIEvent& evt)
{
  switch( evt.GetId() )
  {
  case wxID_UP:
    evt.Enable(
      canMoveCurrentUp()
    );
    break;
  case wxID_DOWN:
    evt.Enable(
      canMoveCurrentDown()
    );
    break;
  case wxID_ADD:
    {
      const wxString& path = m_folder->GetDirName().GetFullPath();
      evt.Enable(
        !path.IsEmpty() &&
        -1 == m_lstFolders->FindString(path)
      );
    }
    break;
  case wxID_REPLACE:
    {
      const wxString& path = m_folder->GetDirName().GetFullPath();
      int sel = m_lstFolders->GetSelection();

      evt.Enable(
        !path.IsEmpty() &&
        -1 == m_lstFolders->FindString(path) &&
        -1 < sel && 
        m_lstFolders->GetString(sel) != path
      );
    }
    break;
  case wxID_DELETE:
    evt.Enable(
      -1 < m_lstFolders->GetSelection()
    );
    break;
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsString::Array EsPathsListDlg::foldersGet() const
{
  if( m_lstFolders->IsEmpty() )
    return EsString::nullArray();

  const wxArrayString& strs = m_lstFolders->GetStrings();

  EsString::Array result;
  EsUtilities::wxArrayStringToEsStringArray(
    result,
    strs
  );

  return result;
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::foldersSet(const EsString::Array& folders)
{
  wxWindowUpdateLocker lock(m_lstFolders);

  m_lstFolders->Clear();

  wxArrayString items;
  EsUtilities::esStringArrayToWxArrayString(
    items, 
    folders
  );

  if( !items.empty() )
    m_lstFolders->InsertItems(
      items,
      0
    );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

bool EsPathsListDlg::canMoveCurrentUp() const ES_NOTHROW
{
  int idx = m_lstFolders->GetSelection();
  return idx > 0;
}
//--------------------------------------------------------------------------------

bool EsPathsListDlg::canMoveCurrentDown() const ES_NOTHROW
{
  int idx = m_lstFolders->GetSelection();
  return idx > -1 && idx < static_cast<int>(m_lstFolders->GetCount())-1;
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::moveCurrentUp() ES_NOTHROW
{
  ES_ASSERT(canMoveCurrentUp());

  wxWindowUpdateLocker lock(m_lstFolders);

  int idx = m_lstFolders->GetSelection();
  ES_ASSERT(-1 < idx);

  wxString tmp = m_lstFolders->GetString(idx);
  m_lstFolders->Delete(
    static_cast<unsigned>(idx)
  );
  m_lstFolders->Insert(
    tmp,
    --idx
  );
  m_lstFolders->SetSelection(idx);
}
//--------------------------------------------------------------------------------

void EsPathsListDlg::moveCurrentDown() ES_NOTHROW
{
  ES_ASSERT(canMoveCurrentDown());

  wxWindowUpdateLocker lock(m_lstFolders);

  int idx = m_lstFolders->GetSelection();
  ES_ASSERT(-1 < idx);

  wxString tmp = m_lstFolders->GetString(idx);
  m_lstFolders->Delete(
    static_cast<unsigned>(idx)
  );
  m_lstFolders->Insert(
    tmp,
    ++idx
  );
  m_lstFolders->SetSelection(idx);
}
//--------------------------------------------------------------------------------
