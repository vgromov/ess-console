#ifndef _es_text_document_h_
#define _es_text_document_h_

class ES_INTF_IMPL_DERIVED(EsTextDocument, EsDocument)

protected:
  EsTextDocument(const EsAssocContainerIntf::Ptr& regInfo);

public:
  ES_DECL_REFLECTED_CLASS(EsTextDocument, EsDocument)

  // EsBaseIntf implementation
  ES_DECL_INTF_METHOD( EsString, typeNameGet )() const ES_NOTHROW { return classNameGetStatic(); }

  /// Document content initialization
  ES_DECL_INTF_METHOD(void, emptyContentsInit)(const EsVariant& params) ES_OVERRIDE;

  /// Reflected  services
  ///

  /// Document constructor always get registry parameters as an argument,
  /// even if these are not used in specific implementation
  ES_DECL_REFLECTED_CLASS_CTOR1( EsVariant, cr_EsVariant );

  /// Script document-specific reflected services
  ///

  /// Content
  ES_DECL_REFLECTED_METHOD1( void, contentSet, cr_EsString );
  ES_DECL_REFLECTED_CONST_METHOD0( EsString, contentGet );

  /// Content hash
  ES_DECL_REFLECTED_CONST_METHOD0(EsVariant, hashGet);

  /// Bookmark data
  ES_DECL_REFLECTED_CONST_METHOD0(cr_EsVariant, bookmarksGet);

  /// EsDocumentIntf overrides
  ///
  ES_DECL_INTF_METHOD( bool, isEmpty )() const ES_NOTHROW;
  ES_DECL_INTF_METHOD( void, valueSet )(cr_EsString name, cr_EsVariant val);

  /// The rest of EsDocumentIntf reflected implementation
  ///
  ES_DECL_REFLECTED_INTF_METHOD0(void, sideloadRead);
  ES_DECL_REFLECTED_INTF_METHOD0(void, sideloadWrite);

  /// Non-reflected services
  ///
  virtual bool doRead(cr_EsVariant params) ES_OVERRIDE;
  virtual void doWrite(cr_EsVariant key, cr_EsVariant params, bool asCopy) ES_OVERRIDE;

  void bookmarkToggle(void* initiator, int line, int number);
  
  void bookmarksClear(void* initiator);
  
protected:
  void bookmarksSet(const EsAssocContainerIntf::Ptr& bm);
  virtual bool isSideloadName(const EsString& name) const ES_OVERRIDE;

protected:
  EsVariant m_originalHash;

  ES_NON_COPYABLE(EsTextDocument);
};

#endif // _es_text_document_h_
