#include "ess_console_pch.h"
#pragma hdrstop

#include "EsTextDocument.h"
#include "EsScriptDocument.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

// Reflection class info declaration
ES_DECL_CLASS_INFO_DERIVED_BEGIN( EsScriptDocument, EsTextDocument, NO_CLASS_DESCR )
  
  // Reflected ctors
  //
  ES_DECL_REFLECTED_CTOR_INFO(        EsScriptDocument, EsVariant_ClassCall_cr_EsVariant, NO_METHOD_DESCR )
ES_DECL_CLASS_INFO_END
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsScriptDocument::EsScriptDocument(const EsAssocContainerIntf::Ptr& regInfo) :
EsTextDocument(regInfo)
{}
//--------------------------------------------------------------------------------

EsVariant EsScriptDocument::NEW(cr_EsVariant regInfo)
{
  std::unique_ptr<EsScriptDocument> obj = ES_MAKE_UNIQUE(
    EsScriptDocument,
    regInfo.asObject()
  );
  ES_ASSERT(obj);

  return obj.release()->asBaseIntfPtr();
}
//--------------------------------------------------------------------------------