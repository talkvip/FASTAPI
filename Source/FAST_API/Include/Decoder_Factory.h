#ifndef HUNDSUN_PUBLIC_DECODER_FACTORY_H
#define HUNDSUN_PUBLIC_DECODER_FACTORY_H

#include "Basic_Types.h"
#include "Fast_Decoder.h"

/***
 * @class IDecoder_Factory
 * @func 数据解析器工厂
 */
class IDecoder_Factory
{
public:
  

  /***
   *@method GetFastDecoder
   *@func   获取FAST解析器
   *@param
   *    ft:  FAST解析器的类型
   *@return
   *        0:   failed.
   *  Nonzero:   succ. Call Release() after used.
   */
  virtual IFast_Decoder* FUNCTION_CALL_MODE GetFastDecoder (FAST_TYPE ft) = 0 ;

  /***
   *@method GetLastError
   *@func   获取最后的错误信息
   *@return
   *     0: no error.
   * other: error info. 
   */
  virtual const char* FUNCTION_CALL_MODE GetLastError () = 0 ;

  /***
   *@method GetInstance
   *@func   获取Decoder工厂实例
   */
  static IDecoder_Factory* FUNCTION_CALL_MODE GetInstance () ;
} ;

#ifdef __cplusplus
extern "C" {
#endif

	IDecoder_Factory * FUNCTION_CALL_MODE GetDecoderFactoryInstance();

#ifdef __cplusplus
}
#endif

#endif