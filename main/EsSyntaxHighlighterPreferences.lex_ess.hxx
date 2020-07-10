// X-Macro file for ess lexer definitions
ES_LEXMAP_BEGIN(wxSTC_LEX_RUST, esT("ess"))
ES_LEXMAP_ENTRY(wxSTC_RUST_DEFAULT /*stcDefault*/, nullptr)
// Special words sets
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD /*stcWords0*/,
    esT("return extern extends if else for foreach while do \
      break continue switch case default label goto throw rethrow \
      try catch"
    )
)
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD2 /*stcWords1*/,
  esT(
    "this null true false __startup __version __value __exception __metaclass __scriptHost"
  )
)
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD3 /*stcWords2*/, 
  esT("require link") 
)
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD4 /*stcWords3*/, 
  esT("esU8 esU16 esU32 esU64 esI8 esI16 esI32 esI64 esDT esF")
)
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD5 /*stcWords4*/, 
  esT("new delete function property read write")
)
ES_LEXMAP_ENTRY(wxSTC_RUST_WORD6 /*stcWords5*/, 
  esT("var const enum object")
)
ES_LEXMAP_ENTRY(-1 /*stcWords6*/, nullptr)
// Comments
ES_LEXMAP_ENTRY(wxSTC_RUST_COMMENTBLOCK /*stcComment*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_COMMENTLINE /*stcCommentLine*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_COMMENTBLOCKDOC /*stcCommentDoc*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_COMMENTLINEDOC /*stcCommentSpec*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcPreprocessorComment*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcPreprocessorCommentDoc*/, nullptr)
// Strings && chars
ES_LEXMAP_ENTRY(wxSTC_RUST_CHARACTER /*stcChar*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcCharEol*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_STRING /*stcString*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcStringEol*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_BYTECHARACTER /*stcCharSpec1*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcCharSpec2*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_BYTESTRING /*stcStringSpec1*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcStringSpec2*/, nullptr)
// Delimiters and punctuation
ES_LEXMAP_ENTRY(-1 /*stcDelimiter*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcPunctuation*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_OPERATOR /*stcOperator*/, esT("$ $$ @ # ## = * + - / % ? : . ~ ^ ! | & > < in"))
ES_LEXMAP_ENTRY(-1 /*stcBrace*/, esT("( ) [ ] { }"))
// Special extras
ES_LEXMAP_ENTRY(-1 /*stcCommand*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_IDENTIFIER /*stcIdentifier*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcLabel*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_RUST_NUMBER /*stcNumber*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberFlt*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberHex*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberBin*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberOct*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcParameter*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcRegex*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcUuid*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcValue*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcPreprocessor*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcScript*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWarning*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcError*/, nullptr)
ES_LEXMAP_END

#undef ES_LEXMAP_BEGIN
#undef ES_LEXMAP_ENTRY
#undef ES_LEXMAP_END