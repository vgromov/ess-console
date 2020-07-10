#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSyntaxHighlighterPreferences.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsString::const_pointer EsSyntaxHighlighter::specStrGet(EsSyntaxHighlighterId id) ES_NOTHROW
{
# define ES_STYLEMAP_BEGIN static const EsString::const_pointer sc_styleSpecs[EsSyntaxHighlighterId::stcItemsCount + 1] = {
# define ES_STYLEMAP_ENTRY(stcId,specStr) specStr,
# define ES_STYLEMAP_END nullptr };
# include "EsSyntaxHighlighterPreferences.specs.hxx"

  EsString::const_pointer specStr = sc_styleSpecs[id];
  if(nullptr == specStr)
    return sc_styleSpecs[stcDefault];

  return specStr;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Lexer definitions database
//

// Lexer highlighter database generation
static const EsLexDbNode sc_lexNodes[] = {

  // ESS lexer mapping
# define ES_LEXMAP_BEGIN(lexId,extStr) { (lexId), (extStr), {
# define ES_LEXMAP_ENTRY(lexHlId,wordStr) { (lexHlId), (wordStr) },
# define ES_LEXMAP_END {-1, nullptr} } },
# include "EsSyntaxHighlighterPreferences.lex_ess.hxx"

  // CPP lexer mapping
# define ES_LEXMAP_BEGIN(lexId,extStr) { (lexId), (extStr), {
# define ES_LEXMAP_ENTRY(lexHlId,wordStr) { (lexHlId), (wordStr) },
# define ES_LEXMAP_END {-1, nullptr} } },
# include "EsSyntaxHighlighterPreferences.lex_cpp.hxx"

  // Log and Error output lexer
# define ES_LEXMAP_BEGIN(lexId,extStr) { (lexId), (extStr), {
# define ES_LEXMAP_ENTRY(lexHlId,wordStr) { (lexHlId), (wordStr) },
# define ES_LEXMAP_END {-1, nullptr} } },
# include "EsSyntaxHighlighterPreferences.lex_log.hxx"

  // Add more lexer highlighter mappings here...

  // Last DB item is a null one
  {
    -1,
    nullptr,
    {0}
  }
};
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

const EsLexDbNode& EsLexDbNode::null() ES_NOTHROW
{
  return sc_lexNodes[EsSyntaxHighlighterId::stcItemsCount];
}
//--------------------------------------------------------------------------------

const EsLexDbNode& EsSyntaxHighlighter::lexNodeByExtGet(const EsString& ext) ES_NOTHROW
{
  if( ext.empty() )
    return EsLexDbNode::null();

  int cnt = 0;
  while(1)
  {
    const EsLexDbNode& node = sc_lexNodes[cnt++];
    if(node.isNull())
      break;

    ES_ASSERT(  node.extsStr );
    EsStringTokenizer tok(node.extsStr);

    while(tok.get_moreTokens())
    {
      const EsString& item = tok.get_nextToken();
      if(item == ext)
        return node;
    }
  }

  return EsLexDbNode::null();
}
//--------------------------------------------------------------------------------

const EsLexDbNode& EsSyntaxHighlighter::lexNodeByLexIdGet(int lexId) ES_NOTHROW
{
  if(0 > lexId)
    return EsLexDbNode::null();

  int cnt = 0;
  while(1)
  {
    const EsLexDbNode& node = sc_lexNodes[cnt++];
    if(node.isNull())
      break;

    if(node.lexId == lexId)
      return node;
  }

  return EsLexDbNode::null();
}
//--------------------------------------------------------------------------------

void EsSyntaxHighlighter::lexStylesApply(wxStyledTextCtrl* stc, const EsLexDbNode& lexNode)
{
  if(!stc)
    return;

  if(lexNode.isNull())
    return;

  int kwdSet = 0;
  for(int id = EsSyntaxHighlighterId::stcDefault; id < EsSyntaxHighlighterId::stcItemsCount; ++id)
  {
    const EsSyntaxHighlighterNode& node = lexNode.highlighters[id];
    if(node.isNull())
      continue;

    stc->StyleSetSpec(
      node.lexHlId,
      EsSyntaxHighlighter::specStrGet(
        as_<EsSyntaxHighlighterId>(id)
      )
    );

    if(node.haveWords())
      stc->SetKeyWords(
        kwdSet++,
        node.words
      );
  }
}
//--------------------------------------------------------------------------------
