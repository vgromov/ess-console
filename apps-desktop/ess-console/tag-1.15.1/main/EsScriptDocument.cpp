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

EsScriptDocument::EsScriptDocument() :
  EsTextDocument()
{
}
//--------------------------------------------------------------------------------

EsVariant EsScriptDocument::NEW(cr_EsVariant ES_UNUSED(regInfo))
{
  EsDocumentIntf::Ptr obj(
    new EsScriptDocument
  );
  ES_ASSERT(obj);

  obj->emptyContentsInit();

  return obj;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
