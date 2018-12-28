#ifndef _es_script_document_h_
#define _es_script_document_h_

class ES_INTF_IMPL_DERIVED(EsScriptDocument, EsTextDocument)

protected:
  EsScriptDocument();

public:
  ES_DECL_REFLECTED_CLASS(EsScriptDocument, EsTextDocument)

  // EsBaseIntf implementation
  ES_DECL_INTF_METHOD(EsString, typeNameGet)() const ES_NOTHROW { return classNameGetStatic(); }

  /// Reflected  services
  ///
  
  /// Document constructor always get registry parameters as an argument,
  /// even if these are not used in specific implementation
  ES_DECL_REFLECTED_CLASS_CTOR1(EsVariant, cr_EsVariant);

private:
  EsScriptDocument(const EsScriptDocument&) ES_REMOVEDECL;
  EsScriptDocument& operator=(const EsScriptDocument&) ES_REMOVEDECL;
};

#endif // _es_script_document_h_
