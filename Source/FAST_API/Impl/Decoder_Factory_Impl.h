#ifndef HUNDSUN_DECODER_FACTORY_IMPL_H
#define HUNDSUN_DECODER_FACTORY_IMPL_H

#include "../Include/Decoder_Factory.h"


class Decoder_Factory_Impl : public IDecoder_Factory
{ 
  friend class IDecoder_Factory ;
public:
  Decoder_Factory_Impl () ;

  virtual IFast_Decoder* FUNCTION_CALL_MODE GetFastDecoder (FAST_TYPE ft) ;

  virtual const char* FUNCTION_CALL_MODE GetLastError () ;

protected:
  // Last Error.
  bool                               m_bHasError ;
  char                               m_strError [256] ;

  static IDecoder_Factory*           ms_lpFactory ;

  //virtual ~Decoder_Factory_Impl () ;
} ;

#endif