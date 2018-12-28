#ifndef _es_document_h_
#define _es_document_h_

/// @file EsDocument.h
/// Minimal reflected implementation for building MDI-aware frameworks
///

/// Common base implementation for EsDocumentIntf 
///
class ES_INTF_IMPL2(EsDocument, EsDocumentIntf, EsReflectedClassIntf)

protected:
  EsDocument();

public:
  ES_DECL_REFLECTED_CLASS_BASE(EsDocument)
  ES_DECL_ATTR_HANDLING_STD

  /// EsDocumentIntf reflected implementation
  ///
  
  /// Return true if document is managed (attached to manager)
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(bool, isManaged) ES_NOTHROW { return m_mgr; }

  /// Document emptiness check
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(bool, isEmpty) ES_NOTHROW { return m_vals.isEmpty(); }
  /// New document check (never saved)
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(bool, isNew) ES_NOTHROW { return m_new; }
  /// Document have unsaved changes
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(bool, isModified) ES_NOTHROW { return m_modified; }

  /// Document identification
  ///

  /// Document key access - unique key for unambiguous document identification 
  /// in document manager collection
  ///
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(cr_EsVariant, keyGet) ES_NOTHROW { return m_key; }

  /// Document properties access
  ///

  /// Return true if document property with 'name' exists, false otherwise
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(bool, valueExists, cr_EsString) ES_NOTHROW { return m_vals.itemExists(p1); }

  /// Return all assigned property names
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(EsStringArray, valueNamesGet) ES_NOTHROW { return m_vals.namesGet(); }

  /// Return named property value. Throw, if value does not exist.
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(cr_EsVariant, valueGet, cr_EsString) { return m_vals.valueGet(p1); }

  /// Assign named property value. If value with such name does not exist in document - create it
  ES_DECL_REFLECTED_INTF_METHOD2(void, valueSet, cr_EsString, cr_EsVariant);

  /// Remove value from the document
  ES_DECL_REFLECTED_INTF_METHOD1(void, valueDelete, cr_EsString);

  /// Document manager object access
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(EsBaseIntfPtr, managerGet) ES_NOTHROW { return m_mgr; }

  /// Document serialization basic implementation
  ES_DECL_REFLECTED_INTF_METHOD1(void, read, cr_EsVariant);
  ES_DECL_REFLECTED_INTF_METHOD2(void, write, cr_EsVariant, cr_EsVariant);

  /// Document change notification
  ES_DECL_INTF_METHOD(void, documentChangedNotify)(const EsString& subject, void* sender) const ES_OVERRIDE;

  /// Document sideload change notification
  ES_DECL_INTF_METHOD(void, documentSideloadChangedNotify)(const EsString& subject, void* sender) const ES_OVERRIDE;

  // Non-reflected services
  //
  virtual bool doRead(cr_EsVariant params) = 0;
  virtual void doWrite(cr_EsVariant key, cr_EsVariant params) = 0;

  void keySet(const EsVariant& key);
  void managerSet(const EsDocumentManagerIntf::Ptr& mgr);

protected:
  void sideloadFileDelete() ES_NOTHROW;
  virtual bool isSideloadName(const EsString& name) const = 0;

protected:
  // Manager weak reference
  EsDocumentManagerIntf::Ptr m_mgr;
  // Document key
  EsVariant m_key;
  // Document named values container
  EsStringIndexedMap m_vals;
  // Document flags
  bool m_new;
  bool m_modified;
  
  EsDocument(const EsDocument&) ES_REMOVEDECL;
  EsDocument& operator=(const EsDocument&) ES_REMOVEDECL;
};
//---------------------------------------------------------------------------------------

#endif // _es_document_h_
