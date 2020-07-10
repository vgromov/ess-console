// X-Macro file for cpp lexer definitions
ES_LEXMAP_BEGIN(wxSTC_LEX_CPP, esT("c cpp cxx cc cs h hh hpp hcc hxx sma"))
ES_LEXMAP_ENTRY(wxSTC_C_DEFAULT /*stcDefault*/, nullptr)
// Special words sets
ES_LEXMAP_ENTRY(wxSTC_C_WORD /*stcWords0*/,
    esT(
      "asm auto break case catch class const const_cast \
      continue default delete do dynamic_cast else enum explicit \
      export extern for friend goto if inline \
      mutable namespace new operator private protected public register \
      reinterpret_cast return sizeof static static_cast \
      struct switch template throw try typedef typeid \
      typename union using virtual volatile while"
    ))
ES_LEXMAP_ENTRY(wxSTC_C_WORD2 /*stcWords1*/, 
  esT(
    "this char bool double false float int long short signed true unsigned void wchar_t nullptr NULL"
  ))
ES_LEXMAP_ENTRY(-1 /*stcWords2*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWords3*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWords4*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWords5*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWords6*/, nullptr)
// Comments
ES_LEXMAP_ENTRY(wxSTC_C_COMMENT /*stcComment*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_COMMENTLINE /*stcCommentLine*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_COMMENTDOC /*stcCommentDoc*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_COMMENTLINEDOC /*stcCommentSpec*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_PREPROCESSORCOMMENT /*stcPreprocessorComment*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_PREPROCESSORCOMMENTDOC /*stcPreprocessorCommentDoc*/, nullptr)
// Strings && chars
ES_LEXMAP_ENTRY(wxSTC_C_CHARACTER /*stcChar*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcCharEol*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_STRING /*stcString*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_STRINGEOL /*stcStringEol*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcCharSpec1*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcCharSpec2*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_STRINGRAW /*stcStringSpec1*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcStringSpec2*/, nullptr)
// Delimiters and punctuation
ES_LEXMAP_ENTRY(-1 /*stcDelimiter*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcPunctuation*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_OPERATOR /*stcOperator*/, esT("= * + - / % ? : ... ~ ^ ! | & -> > <"))
ES_LEXMAP_ENTRY(-1 /*stcBrace*/, esT("( ) [ ] { } < >"))
// Special extras
ES_LEXMAP_ENTRY(-1 /*stcCommand*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcIdentifier*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcLabel*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_NUMBER /*stcNumber*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberFlt*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberHex*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberBin*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcNumberOct*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcParameter*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_REGEX /*stcRegex*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcUuid*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcValue*/, nullptr)
ES_LEXMAP_ENTRY(wxSTC_C_PREPROCESSOR /*stcPreprocessor*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcScript*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcWarning*/, nullptr)
ES_LEXMAP_ENTRY(-1 /*stcError*/, nullptr)
ES_LEXMAP_END

#undef ES_LEXMAP_BEGIN
#undef ES_LEXMAP_ENTRY
#undef ES_LEXMAP_END