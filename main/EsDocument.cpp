#include "ess_console_pch.h"
#pragma hdrstop

#include "EsDocument.h"
//--------------------------------------------------------------------------------

// Reflection class info declaration
ES_DECL_BASE_CLASS_INFO_BEGIN(EsDocument, NO_CLASS_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, isManaged, bool_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, isEmpty, bool_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, isNew, bool_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, isModified, bool_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, keyGet, cr_EsVariant_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, valueExists, bool_CallConst_cr_EsString, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, valueNamesGet, EsStringArray_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, valueGet, cr_EsVariant_CallConst_cr_EsString, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, valueSet, void_Call_cr_EsString_cr_EsVariant, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, valueDelete, void_Call_cr_EsString, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, managerGet, EsBaseIntfPtr_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, read, void_Call_cr_EsVariant, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsDocument, EsDocumentIntf, write, void_Call_cr_EsVariant_cr_EsVariant, NO_METHOD_DESCR)
ES_DECL_CLASS_INFO_END
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsDocument::EsDocument() :
m_vals(
  EsStringIndexedMap::ContainerWithoutInterlock,
  esT("EsDocument")
),
m_new(true),
m_modified(false)
{
  m_dynamic = true; //< Allow only dunamic creation, through derived classes
}
//--------------------------------------------------------------------------------

void EsDocument::keySet(const EsVariant& key)
{
  if(m_key != key)
  {
    if(isManaged())
    {
      EsDocumentManager* mgr = ES_INTFPTR_TO_OBJECTPTR<EsDocumentManager, EsDocumentManagerIntf::Ptr>(m_mgr);
      ES_ASSERT(mgr);

      mgr->documentKeyCheck(key);

      EsVariant oldKey = m_key;
      m_key = key;

      mgr->keyChange(
        oldKey,
        m_key
      );
    }
    else
      m_key = key;
  }
}
//--------------------------------------------------------------------------------

void EsDocument::managerSet(const EsDocumentManagerIntf::Ptr& mgr)
{
  if(mgr)
    m_mgr.reset(
      mgr.get(),
      false
    );
  else
    m_mgr.reset();
}
//--------------------------------------------------------------------------------

void EsDocument::valueSet(cr_EsString name, cr_EsVariant val)
{
  if( !isSideloadName(name) )
  {
    if( m_vals.itemExists(name) )
    {
      const EsVariant& oldval = m_vals.valueGet(name);
      m_modified = oldval != val;
    }
    else
      m_modified = true;
  }

  m_vals.itemAdd(
    name,
    val,
    false
  );
}
//--------------------------------------------------------------------------------

void EsDocument::valueDelete(cr_EsString name)
{
  m_vals.itemDelete(name);
  m_modified = true;
}
//--------------------------------------------------------------------------------

void EsDocument::read(cr_EsVariant& params)
{
  if( doRead(params) )
  {
    m_modified = false;
    m_new = false;

    sideloadRead();

    if( isManaged() )
    {
      documentChangedNotify(
        EsString::null(),
        nullptr
      );

      documentSideloadChangedNotify(
        EsString::null(),
        nullptr
      );
    }
  }
}
//--------------------------------------------------------------------------------

void EsDocument::write(cr_EsVariant& key, cr_EsVariant& params)
{
  ES_ASSERT(isManaged());

  EsDocumentManager* mgr = ES_INTFPTR_TO_OBJECTPTR<EsDocumentManager, EsDocumentManagerIntf::Ptr>(m_mgr);
  ES_ASSERT(mgr);

  bool keyChange = keyGet() != key;
  if(keyChange)
    mgr->documentKeyCheck(key);
  
  bool stateChange = false;
  if(isModified() || isNew())
  {
    doWrite(
      key, 
      params
    );

    m_modified = false;
    m_new = false;

    stateChange = true;
  }

  if(keyChange)
  {
    sideloadFileDelete(); //< Remove sideload for an old key

    keySet(key);
  }

  if(stateChange)
    EsEventDispatcher::eventPost(
      ES_EVTC_MDI,
      as_<ulong>(EsMdiEvt::DocumentStateChanged),
      m_key
    );
      
  ES_ASSERT(!isNew());
  sideloadWrite();
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsDocument::sideloadFileDelete() ES_NOTHROW
{
  const EsString& sideloadPathStr = m_key.asString() + esT(".sl");
  if(EsPath::fileExists(sideloadPathStr, EsString::null()))
  {
    try
    {
      EsPath::fileRemove(sideloadPathStr);
    }
    catch(...)
    {
    }
  }
}
//--------------------------------------------------------------------------------

void EsDocument::documentChangedNotify(const EsString& subject, void* sender) const
{
  if(!isManaged())
    return;

  // Post document changed event with existing key
  const EsVariant::Array& payload = {
    m_key,
    subject,
    EsVariant(sender, EsVariant::ACCEPT_POINTER)
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_MDI,
    as_<ulong>(EsMdiEvt::DocumentChanged),
    payload
  );
}
//--------------------------------------------------------------------------------

void EsDocument::documentSideloadChangedNotify(const EsString& subject, void* sender) const
{
  if(!isManaged())
    return;

  // Post document changed event with existing key
  const EsVariant::Array& payload = {
    m_key,
    subject,
    EsVariant(sender, EsVariant::ACCEPT_POINTER)
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_MDI,
    as_<ulong>(EsMdiEvt::DocumentSideloadChanged),
    payload
  );
}
//--------------------------------------------------------------------------------
