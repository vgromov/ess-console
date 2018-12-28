#include "ess_console_pch.h"
#pragma hdrstop

#include "EsTextDocument.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

// Reflection class info declaration
ES_DECL_CLASS_INFO_DERIVED_BEGIN( EsTextDocument, EsDocument, NO_CLASS_DESCR )
  // Reflected interface services
  //
  ES_DECL_REFLECTED_INTF_METHOD_INFO( EsTextDocument, EsDocumentIntf, sideloadRead, void_Call, NO_METHOD_DESCR )
  ES_DECL_REFLECTED_INTF_METHOD_INFO( EsTextDocument, EsDocumentIntf, sideloadWrite, void_Call, NO_METHOD_DESCR )
  // Reflected services
  //
  ES_DECL_REFLECTED_METHOD_INFO_STD( EsTextDocument, contentSet, void_Call_cr_EsString, NO_METHOD_DESCR )
  ES_DECL_REFLECTED_METHOD_INFO_STD( EsTextDocument, contentGet, EsString_CallConst, NO_METHOD_DESCR )
  ES_DECL_REFLECTED_METHOD_INFO_STD( EsTextDocument, hashGet, EsVariant_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_METHOD_INFO_STD( EsTextDocument, bookmarksGet, cr_EsVariant_CallConst, NO_METHOD_DESCR)
  // Reflected ctors
  //
  ES_DECL_REFLECTED_CTOR_INFO( EsTextDocument, EsVariant_ClassCall_cr_EsVariant, NO_METHOD_DESCR )
ES_DECL_CLASS_INFO_END
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsTextDocument::EsTextDocument() :
  EsDocument()
{
}
//--------------------------------------------------------------------------------

EsVariant EsTextDocument::NEW( cr_EsVariant ES_UNUSED( regInfo ) )
{
  EsDocumentIntf::Ptr obj(
    new EsTextDocument
  );
  ES_ASSERT( obj );

  obj->emptyContentsInit();

  return obj;
}
//--------------------------------------------------------------------------------

void EsTextDocument::emptyContentsInit()
{
  contentSet( EsString::null() );
  bookmarksSet(EsAssocContainer::create());
  
  m_originalHash = EsString::null().hashGet();

  m_modified = false; //< Make sure new document is not modified
}
//--------------------------------------------------------------------------------

void EsTextDocument::valueSet( cr_EsString name, cr_EsVariant val )
{
  EsDocument::valueSet(
    name,
    val
  );

  if(esT("content") == name)
  {
    if( m_originalHash == EsString::null().hashGet() )
    {
      m_originalHash = contentGet().hashGet();
      m_modified = false;
    }
    else
      m_modified =
        m_originalHash != contentGet().hashGet();
  }
}
//--------------------------------------------------------------------------------

void EsTextDocument::contentSet( cr_EsString content )
{
  valueSet(
    esT( "content" ),
    content
  );
}
//--------------------------------------------------------------------------------

EsString EsTextDocument::contentGet() const
{
  return valueGet( esT( "content" ) ).asString();
}
//--------------------------------------------------------------------------------

EsVariant EsTextDocument::hashGet() const
{
  return contentGet().hashGet();
}
//--------------------------------------------------------------------------------

bool EsTextDocument::isEmpty() const ES_NOTHROW
{
  if( !EsDocument::isEmpty() && valueExists( esT( "content" ) ) )
  {
    const EsVariant& content = valueGet( "content" );
    return content.isEmpty() ||
      (content.isString() && EsString::null() == content.doInterpretAsString());
  }

  return EsDocument::isEmpty();
}
//--------------------------------------------------------------------------------

bool EsTextDocument::doRead( cr_EsVariant params )
{
  // Interpret src as script file path
  EsPath fpath = EsPath::createFromFilePath( m_key.asString() );
  const EsString& fpathStr = fpath.pathGet(); //< Absolutize path str

  if( !fpath.fileExists() )
    EsException::Throw(
      esT( "File '%s' does not exist" ),
      fpathStr
    );

  // TODO: Read script binary from file
  EsFile in(
    fpathStr,
    as_<ulong>( EsFileFlag::Read ) |
    as_<ulong>( EsFileFlag::Text )
  );

  if( in.open() )
  {
    emptyContentsInit();

    contentSet(
      in.readAllAsString()
    );

    m_key = fpathStr;
    in.close();

    return true;
  }

  return false;
}
//--------------------------------------------------------------------------------

void EsTextDocument::doWrite( cr_EsVariant target, cr_EsVariant params )
{
  // Interpret src as script file path
  const EsPath& fpath = EsPath::createFromFilePath( target.asString() );
  const EsString& fpathStr = fpath.pathGet(); //< Absolutize path str

  // Write script binary to file
  EsFile out(
    fpathStr,
    as_<ulong>( EsFileFlag::Write ) |
    as_<ulong>( EsFileFlag::Text )
  );

  if( out.open() )
  {
    out.writeAllAsString(
      contentGet()
    );
    m_originalHash = contentGet().hashGet();

    out.close();
  }
}
//--------------------------------------------------------------------------------

const EsVariant& EsTextDocument::bookmarksGet() const
{
  if(valueExists(esT("bookmarks")))
    return valueGet(esT("bookmarks"));

  return EsVariant::null();
}
//--------------------------------------------------------------------------------

void EsTextDocument::bookmarksSet(const EsAssocContainerIntf::Ptr& bm)
{
  ES_ASSERT(bm);

  valueSet(
    esT("bookmarks"),
    bm
  );
}
//--------------------------------------------------------------------------------

void EsTextDocument::sideloadRead()
{
  // Try to find and read sideload data
  const EsString& sideloadPathStr = m_key.asString() + esT(".sl");

  if(!EsPath::fileExists(sideloadPathStr, EsString::null()))
    return;

  EsStreamIntf::Ptr stream = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::File) |
    as_<ulong>(EsStreamFlag::Read),
    sideloadPathStr
  );
  ES_ASSERT(stream);

  valueSet(
    esT("bookmarks"),
    stream->valueRead(
      esT("bookmarks"),
      EsAssocContainer::create()
    )
  );
}
//--------------------------------------------------------------------------------

void EsTextDocument::sideloadWrite()
{
  sideloadFileDelete();

  if(!valueExists(esT("bookmarks")))
    return;

  // Try to write sideload data
  const EsString& sideloadPathStr = m_key.asString() + esT(".sl");
  EsStreamIntf::Ptr stream = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::File) |
    as_<ulong>(EsStreamFlag::Write),
    sideloadPathStr
  );
  ES_ASSERT(stream);

  stream->valueWrite(
    esT("bookmarks"),
    valueGet(esT("bookmarks"))
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsTextDocument::bookmarkToggle(void* initiator, int line, int number)
{
  const EsString& bmsname = esT("bookmarks");
  if(!valueExists(bmsname))
    return;

  EsAssocContainerIntf::Ptr bms = valueGet(bmsname).asExistingObject();
  ES_ASSERT(bms);

  if(-1 == number) //< Simple bookmark case
  {
    if(bms->keyExists(line))
    {
      const EsVariant& val = bms->valueGet(line);

      if(val.isEmpty()) //< Just remove, if not numbered
        bms->valueDelete(line);
      else //< Replace with non-numbered otherwise
        bms->valueSet(
          line, 
          EsVariant::null()
        );
    }
    else    
      bms->newValueSet(
        line,
        EsVariant::null()
      );
  }
  else //< Numbered bookmark case - we have to check if there were any same-numbered bm records
  {
    // If same number, same line - delete it and exit
    // If same line and no number - change no-number to number
    // If same number and another line - change line
    // Otherwise - just add lina and number record
    //
    if(bms->keyExists(line))
    {
      const EsVariant& oldVal = bms->valueGet(line);
      if(oldVal.isEmpty() || (oldVal.isNumeric() && (oldVal.asInt() != number))) //< no-number or other number
        bms->valueSet(line, number); //< change old val to number
      else if(oldVal.isNumeric() && (oldVal.asInt() == number)) //< same number
        bms->valueDelete(line); //< Remove numbered bm
    }
    else
    {
      // Lookup same number anywhere else
      const EsVariant::Array& keys = bms->allKeysGet().asVariantCollection();
      for(const EsVariant& key : keys)
      {
        const EsVariant& oldVal = bms->valueGet(key);
        if( oldVal.isNumeric() && (number == oldVal.asInt()) )
        {
          // Remove same-number bm from other line
          bms->valueDelete(key);
          break;
        }
      }

      // Add numbered bm
      bms->newValueSet(
        line,
        number
      );
    }
  }

  // Notify with optional initiator
  documentSideloadChangedNotify(
    bmsname,
    initiator
  );

  // Update sideload
  if( !isNew() )
    sideloadWrite();
}
//--------------------------------------------------------------------------------

void EsTextDocument::bookmarksClear(void* initiator)
{
  const EsString& bmsname = esT("bookmarks");
  if (!valueExists(bmsname))
    return;

  EsAssocContainerIntf::Ptr bms = valueGet(bmsname).asExistingObject();
  ES_ASSERT(bms);

  bms->clear();

  // Notify with optional initiator
  documentSideloadChangedNotify(
    bmsname,
    initiator
  );

  // Update sideload
  if (!isNew())
    sideloadWrite();
}
//--------------------------------------------------------------------------------

bool EsTextDocument::isSideloadName(const EsString& name) const
{
  if( esT("bookmarks") == name )
    return true;
  
  return false;
}
//---------------------------------------------------------------------------
