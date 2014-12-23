#ifndef HUNDSUN_PUBLIC_FAST_MESSAGE_IMPL_H
#define HUNDSUN_PUBLIC_FAST_MESSAGE_IMPL_H

#include "../Include/Fast_Decoder.h"
//#include <string>
#include <vector>

class Fast_Record_Impl ;
class Fast_Message_Impl : public IFast_Message
{
  friend class Fast_Decoder_Impl;
	   ;
public:
  Fast_Message_Impl () ;

  virtual const char* FUNCTION_CALL_MODE GetMsgType () ;

  virtual const char* FUNCTION_CALL_MODE GetSendTime () ;

  virtual int FUNCTION_CALL_MODE GetSeqNum () ;

  virtual int FUNCTION_CALL_MODE GetRecordCount () ;

  virtual IFast_Record* FUNCTION_CALL_MODE GetRecord (int nSlot) ;

  virtual const char* FUNCTION_CALL_MODE GetLastError () ;

  virtual void FUNCTION_CALL_MODE Release () ;

  Fast_Record_Impl* AddRecord () ;

protected:
  virtual ~Fast_Message_Impl () ;

  // 发送时间
  char                    m_strSendTime [21] ;
  // 消息类型
  char                    m_strMsgType [21] ;
  // 消息序号
  int                            m_nSeqNum ;

  // Records of Message
  std::vector <IFast_Record*>    m_ayRecords ;
} ;

#endif