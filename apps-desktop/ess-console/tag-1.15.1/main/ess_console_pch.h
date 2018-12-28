#ifndef _ess_console_pch_h_
#define _ess_console_pch_h_

#include <escore/escore.h>
#include <esmath/esmath.h>
#include <escomm/escomm.h>
#include <esscript/esscript.h>
#include <escore-gui/escore-gui.h>

#ifndef WX_PRECOMP
# include <wx/wx.h>
#else
# include <wx/wxprec.h>
#endif

#include <wx/cmdline.h>
#include <wx/snglinst.h>
#include <wx/filename.h>
#include <wx/filehistory.h>
#include <wx/fdrepdlg.h>
#include <wx/artprov.h>
#include <wx/stc/stc.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>

#include "product_version.h"
#include "EsSconsoleEvtDefs.h"

#include "EsDocumentManagerIntf.h"
#include "EsDocument.h"
#include "EsDocumentManager.h"

#include "EsTextDocument.h"
#include "EsScriptDocument.h"
#include "EsCompiledScriptDocument.h"

#include "EsSconsoleOutputBase.h"
#include "EsSconsoleCompilerOutput.h"
#include "EsSconsoleScriptOutput.h"
#include "EsOpenedDocumentList.h"

#include "EsSyntaxHighlighterPreferences.h"

#include "EsTextEditorViewBase.h"
#include "EsTextEditorView.h"
#include "EsScriptEditorView.h"
#include "EsCompiledScriptView.h"

#include "EsPathsListDlg.h"

#include "EsSconsoleParams.h"

#include "EsSconsoleApp.h"
#include "EsSconsoleMain.h"

#endif // _ess_console_pch_h_

