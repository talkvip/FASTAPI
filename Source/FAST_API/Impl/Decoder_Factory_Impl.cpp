
#include "Decoder_Factory_Impl.h"
#include "Fast_Decoder_Impl.h"
//#include <string>
#include "Public.h"

IDecoder_Factory * FUNCTION_CALL_MODE GetDecoderFactoryInstance()
{
	return IDecoder_Factory::GetInstance();
}

IDecoder_Factory* FUNCTION_CALL_MODE
IDecoder_Factory::GetInstance ()
{
  return Decoder_Factory_Impl::ms_lpFactory ;
}

//
IDecoder_Factory* Decoder_Factory_Impl::ms_lpFactory = new Decoder_Factory_Impl ;

Decoder_Factory_Impl::Decoder_Factory_Impl ()
: m_bHasError (false)
{}

IFast_Decoder* FUNCTION_CALL_MODE 
Decoder_Factory_Impl::GetFastDecoder (FAST_TYPE ft)
{
  this->m_bHasError = false ;
  switch (ft)
  {
  case emFAST_SHLEVEL2:
    return new Fast_Decoder_Impl(emFAST_SHLEVEL2) ;
  case emFAST_SZLEVEL2:
    // Set error.
   /* this->m_bHasError = true ;
    snprintf (this->m_strError, sizeof(this->m_strError)-1, "Permission denied [FAST-SZL2].") ;
    return 0 ;*/
	return new Fast_Decoder_Impl(emFAST_SZLEVEL2) ;
  default:
    // errno
    this->m_bHasError = true ;
    snprintf (this->m_strError, sizeof(this->m_strError)-1, "Param[%d] invalid.", ft) ;
    return 0 ;
  } ;
  return 0 ;
}

const char* FUNCTION_CALL_MODE 
Decoder_Factory_Impl::GetLastError ()
{
  if (this->m_bHasError)
    return this->m_strError ;
  return "No Error." ;
}