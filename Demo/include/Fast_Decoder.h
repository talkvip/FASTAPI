#ifndef HUNDSUN_PUBLIC_FAST_DECODER_H
#define HUNDSUN_PUBLIC_FAST_DECODER_H

#include "Basic_Types.h"

//ValueType
enum ValueType
{
  emInt8   ,
  emUInt8  ,
  emInt16  ,
  emUInt16 ,
  emInt32  ,
  emUInt32 ,
  emInt64  ,
  emUInt64 ,
  emString ,
  emSequence
} ;

/***
 *@struct FastField_Info
 *描述了FAST字段的属性
 **/
struct FastField_Info
{
  ValueType      emType ;            // 值类型
  int            nDecimalPlaces ;    // 小数位
  char           strDesc [32] ;      // 字段描述
} ;


/***
 * @class IFast_Record
 */
class IFast_Record
{
public:

  virtual ~IFast_Record () {}
  /***
   *@method GetInt8
   *@func   获取8-bits的字段值
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   value of a 8-bit int field.
   *   0: field may be not exist. Call IsExist() to confirm.
   */
  virtual uint8 FUNCTION_CALL_MODE GetInt8 (int nTagID) = 0 ;
  
  /***
   *@method GetInt8
   *@func   获取16-bits的字段值
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   value of a 16-bit int field.
   *   0: field may be not exist. Call IsExist() to confirm.
   */
  virtual uint16 FUNCTION_CALL_MODE GetInt16 (int nTagID)  = 0 ;
  
  /***
   *@method GetInt32
   *@func   获取16-bits的字段值
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   value of a 32-bit int field.
   *   0: field may be not exist. Call IsExist() to confirm.
   */
  virtual uint32 FUNCTION_CALL_MODE GetInt32 (int nTagID) = 0 ;
  
  /***
   *@method GetInt64
   *@func   获取64-bits的字段值
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   value of a 64-bit int field.
   *   0: field may be not exist. Call IsExist() to confirm.
   */
  virtual uint64 FUNCTION_CALL_MODE GetInt64 (int nTagID) = 0 ;

  /***
   *@method GetString
   *@func   获取String的字段值
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   value of a string field.
   *   0: field may be not exist. Call IsExist() to confirm.
   */
  virtual const char* FUNCTION_CALL_MODE GetString (int nTagID) = 0 ;

  /***
   *@method IsExist
   *@func   判断某个字段是否存在
   *@param
   *   nTagID: Fast Field TagID
   *@return
   *   false: not exist.
   *   true : exist.
   */
  virtual bool FUNCTION_CALL_MODE IsExist (int nTagID)   = 0 ;

   /***
   *@method GetSubCount
   *@func   当某个字段为Sequence时,调用此方法获取其下的记录数
   *@param
   *   nTagID: TagID of A Sequence Field.
   *@return
   *   0: field not exist.
   *  >0: record count. 
   */
  virtual int FUNCTION_CALL_MODE GetSubCount (int nTagID) = 0 ;

  /***
   *@method GetSubRecord
   *@func   获取某个Sequence字段下的某个FAST记录
   *@param
   *   nTagID: TagID of A Sequence Field.
   *   nSlot: 0...GetSeqCount ()-1
   *@return
   *   Nonzero: succ
   *   0: error. 
   */
  virtual IFast_Record* FUNCTION_CALL_MODE GetSubRecord (int nTagID, int nSlot) = 0 ;
} ;


/***
 * @class IFast_Message
 */
class IFast_Message
{
public:
  virtual ~IFast_Message () {}
  /***
   *@method GetMsgType
   *@func   获取消息类型.
   *@return
   *   0: null message.
   */
  virtual const char* FUNCTION_CALL_MODE GetMsgType () = 0 ;

  /***
   *@method GetSendTime
   *@func   获取发送时间.
   *@return
   *   0: null message.
   */
  virtual const char* FUNCTION_CALL_MODE GetSendTime () = 0 ;

  /***
   *@method GetSeqNum
   *@func   获取消息序号.
   *@return
   *   -1: null message.
   */
  virtual int FUNCTION_CALL_MODE GetSeqNum () = 0 ;

  /***
   *@method GetRecordCount
   *@func   获取FAST记录的个数
   *@return
   *   >0: record count
   *   -1: error. Call GetLastError() to get error info.
   */
  virtual int FUNCTION_CALL_MODE GetRecordCount () = 0 ;

  /***
   *@method GetRecord
   *@func   获取FAST记录
   *@param
   *   nSlot: 0...GetRecordCount ()
   *@return
   *   Nonzero: succ
   *   0: error. Call GetLastError() to get error info.
   */
  virtual IFast_Record* FUNCTION_CALL_MODE GetRecord (int nSlot) = 0 ;

  /***
   *@method GetLastError
   *@func   获取最后的错误信息
   *@return
   *     0: no error.
   * other: error info.
   */
  virtual const char* FUNCTION_CALL_MODE GetLastError () = 0 ;

  /***
   *@method Release
   *@func   释放消息.
   */
  virtual void FUNCTION_CALL_MODE Release () = 0 ;
} ;


/***
 * @class IFast_Decorder
 * @func  Interface for decoding fast message.
 */
class IFast_Decoder
{
public:
  virtual ~IFast_Decoder () {}
  /***
   *@method LoadTemplate
   *@func   载入FAST模板文件
   *@param
   *   lpFile: template file name
   *@return
   *   0: succ
   */
  virtual int FUNCTION_CALL_MODE LoadTemplate (const char* lpFile) = 0 ;

  /***
   *@method LoadTemplate
   *@func   载入FAST模板文件（深圳五代行情模板）
   *@param
   *   lpFile: template file name
   *@return
   *   0: succ
   */
  virtual int FUNCTION_CALL_MODE LoadTemplateForSZG5HQ (const char* lpFile) = 0 ;

  /***
   *@method GetFastMsgLen
   *@func   获取一条完整FAST消息的长度
   *@param
   *   lpData: Received buffer
   *   nLen  : Received size
   *@return
   *   -1: error. Call LastErr() to get error info.
   *    0: buffer is not enough.
   *   >0: size of a complete fast message.
   */
  virtual int FUNCTION_CALL_MODE GetFastMsgLen (const char* lpData, int nLen) = 0 ;

  /***
   *@method Decode
   *@func   解析一条完整的FAST消息.一整条Step消息输入
   *@param
   *   lpData: fast data of a complete fast message. 
   *   nLen:   length of fast message.
   *@return
   *   0: error. Call GetLastError() for detailed error.
   * !=0: succ. Call Release() after used.
   */
  virtual IFast_Message* FUNCTION_CALL_MODE Decode (const char* lpData, int nLen) = 0 ;

  /***
   *@method DecodeFastData
   *@func   解析一条完整的FAST消息.Fast的数据输入
   *@param
   *   lpData: fast data of a complete fast message. 
   *   nLen:   length of fast message.
   *   nMsgType  message type (template id)
   *@return
   *   0: error. Call GetLastError() for detailed error.
   * !=0: succ. Call Release() after used.
   */
  virtual IFast_Message* FUNCTION_CALL_MODE DecodeFastData (const char* lpFastData, int nFastDataLen,int nMsgType) = 0 ;


  /***
   *@method DecodeFastData
   *@func   解析一条完整的FAST消息.Fast的数据输入 (深圳第五代行情)
   *@param
   *   lpData: fast data of a complete fast message. 
   *   nLen:   length of fast message.
   *@return
   *   0: error. Call GetLastError() for detailed error.
   * !=0: succ. Call Release() after used.
   */
  virtual IFast_Message* FUNCTION_CALL_MODE DecodeFastData (const char* lpFastData, int nFastDataLen) = 0 ;



  /***
   *@method GetFieldInfo
   *@func   获取某个FAST字段的信息
   *@param
   *   nTagID: tagid of a fast field.
   *@return
   *     0: no [nTagID]field.
   */
  virtual const FastField_Info* FUNCTION_CALL_MODE GetFieldInfo (int nTagID) = 0 ;

  /***
   *@method GetLastError
   *@func   获取最后的错误信息
   *@return
   *     0: no error.
   * other: error info.
   */
  virtual const char* FUNCTION_CALL_MODE GetLastError () = 0 ;

  /***
   *@method Release
   *@func   释放解析器.
   */
  virtual void FUNCTION_CALL_MODE Release () = 0 ;
} ;

#endif