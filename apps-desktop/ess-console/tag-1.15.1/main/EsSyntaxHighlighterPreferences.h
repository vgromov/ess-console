#ifndef _es_syn_prefs_h_
#define _es_syn_prefs_h_

// Generate our common style IDs
# define ES_STYLEMAP_BEGIN enum EsSyntaxHighlighterId {
# define ES_STYLEMAP_ENTRY(stcId,specStr) stcId,
# define ES_STYLEMAP_END stcItemsCount };
# include "EsSyntaxHighlighterPreferences.specs.hxx"

struct EsSyntaxHighlighterNode
{
  int lexHlId;
  EsString::const_pointer words;

  inline bool isNull() const ES_NOTHROW { return -1 == lexHlId; }
  inline bool haveWords() const ES_NOTHROW { return nullptr != words; }
};

struct EsLexDbNode
{
  int lexId;
  EsString::const_pointer extsStr;

  EsSyntaxHighlighterNode highlighters[EsSyntaxHighlighterId::stcItemsCount+1];

  inline bool isNull() const ES_NOTHROW { return -1 == lexId; }
  static const EsLexDbNode& null() ES_NOTHROW;
};

namespace EsSyntaxHighlighter
{
  /// Return highlighter spec string by its ID, or default, if spec is not defined
  EsString::const_pointer specStrGet(EsSyntaxHighlighterId id) ES_NOTHROW;

  /// Return LEX DB node by file extension, or null node, if extension is unknown
  const EsLexDbNode& lexNodeByExtGet(const EsString& ext) ES_NOTHROW;

  /// Return the _first_ found LEX DB node by its lexer ID, or null node, if not found in DB
  const EsLexDbNode& lexNodeByLexIdGet(int lexId) ES_NOTHROW;

  /// Apply styles to the current wxStyledTextCtrl lexer
  void lexStylesApply(wxStyledTextCtrl* stc, const EsLexDbNode& lexNode);
}

#endif // _es_syn_prefs_h_
