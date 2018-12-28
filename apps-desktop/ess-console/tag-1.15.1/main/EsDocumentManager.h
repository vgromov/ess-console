#ifndef _es_document_manager_h_
#define _es_document_manager_h_

/// @file EsDocumentManager.h
/// Reflected implementation of document manager interface.
///

/// Document manager notification events declarations
///
#define ES_EVTC_MDI esT("es_mdi")

enum class EsMdiEvt : ulong
{
  DocumentCreated,              ///< Event Payload: key
  DocumentOpened,               ///< Event Payload: key, parameters (optional, null, if not set)
  DocumentChanged,              ///< Event Payload: key, property name, or emtpy string for unspecified change, optional sender object pointer, to prevent unneeded processing
  DocumentKeyChanged,           ///< Event Payload: old key, new key
  DocumentStateChanged,         ///< Event Payload: key
  DocumentSideloadChanged,      ///< Event Payload: key, sideload property name, or empty string for unspecified sideload. Optional sender object pointer, to prevent unneeded processing
  DocumentClosed,               ///< Event Payload: key, document type
  AllDocumentsClosed            ///< Event Payload: none
};

/// Default implementation of document manager interface
///
class ES_INTF_IMPL2(EsDocumentManager, EsDocumentManagerIntf, EsReflectedClassIntf)

public:
  ES_DECL_REFLECTED_CLASS_BASE(EsDocumentManager)
  ES_DECL_ATTR_HANDLING_STD

  /// Reflected document manager creation
  ///
  ES_DECL_REFLECTED_CLASS_CTOR0(EsBaseIntfPtr);

  /// EsDocumentManagerIntf implementation
  ///
  ES_DECL_REFLECTED_INTF_METHOD2(void, documentRegister, cr_EsString, cr_EsVariant);
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentIsRegistered, cr_EsString) ES_NOTHROW { return m_reg.itemExists(p1); }
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentIsSingleton, cr_EsString);
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsString, documentDefaultExtGet, cr_EsString);
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(EsStringArray, registeredDocumentTypesGet) ES_NOTHROW { return m_reg.namesGet(); }
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentRegistrationPayloadGet, cr_EsString) { return m_reg.valueGet(p1); }
  ES_DECL_REFLECTED_INTF_METHOD1(EsVariant, documentCreate, cr_EsString);
  ES_DECL_REFLECTED_INTF_METHOD2(EsVariant, documentCreate, cr_EsString, cr_EsVariant);
  ES_DECL_REFLECTED_INTF_METHOD2(EsVariant, documentOpen, cr_EsString, cr_EsVariant);
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentsGet,cr_EsString);
  ES_DECL_REFLECTED_INTF_CONST_METHOD0(ulong, documentsCountGet) { return m_docs.countGet(); }
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentFind, cr_EsVariant) ES_NOTHROW;
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsVariant, documentFindFirstByType, cr_EsString) ES_NOTHROW;
  ES_DECL_REFLECTED_INTF_CONST_METHOD1(EsString, documentTypeFindByFileExt, cr_EsString);

  ES_DECL_REFLECTED_INTF_METHOD1(void, documentClose, cr_EsVariant);
  ES_DECL_REFLECTED_INTF_METHOD0(void, documentsCloseAll);

  /// Non-reflected services
  ///

  /// Document registry helper.
  /// Creates default minimal document registration entry, and return 
  /// registry parameter object to allow additional information to be added 
  /// afterwards
  ///
  static EsAssocContainerIntf::Ptr registerIn(
    const EsDocumentManagerIntf::Ptr& mgr, 
    const EsString& docType,
    const EsString& defaultExt,
    const EsString& shortDescr,
    const EsString& filterStr,
    bool isSingleton = false
  );

  /// Semi-private services
  ///
  void documentKeyCheck(const EsVariant& key);
  void keyChange(cr_EsVariant oldKey, cr_EsVariant newKey);

protected:
  EsAssocContainerIntf::Ptr regInfoGetForType(const EsString& type) const;
  ulong newDocumentCounterGet(const EsString& type);
  EsVariant newDocumentKeyCreate(const EsString& type, const EsVariant& regParams);
  void documentAttach(const EsVariant& doc, cr_EsVariant key, cr_EsVariant params);
  void documentReadAndAttach(const EsVariant& doc, cr_EsVariant key, cr_EsVariant params);
  bool documentOfTypeExists(const EsString& type) const;

  static void documentTypeCheck(const EsString& type);

protected:
  EsStringIndexedMap m_reg;
  EsAssocContainer m_docs;
  std::map<EsString, ulong> m_newDocCounter;

private:
  EsDocumentManager();
  EsDocumentManager(const EsDocumentManager&) ES_REMOVEDECL;
  EsDocumentManager& operator=(const EsDocumentManager&) ES_REMOVEDECL;
};
//---------------------------------------------------------------------------------------

#endif // _es_document_manager_h_
