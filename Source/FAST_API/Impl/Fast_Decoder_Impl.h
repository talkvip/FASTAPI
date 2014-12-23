/*
 * =====================================================================================
 *
 *   Filename: Fast_Decoder_Impl
 *   Company:   hundsun
 *   Copyrigth: hundsun
 *   
 *   Version:  
 *   Date: 20140214
 *   Compiler:  
 *
 *   Author:  唐模超
 *        
 *   Describ： 解释上海、深圳Fast消息
 *
 *  @tangmc 20140704 
 *  1、增加 DecodeFastData              直接输入FAST数据的解析接口
 *          
 *			DecodeFastForNotMsgType         解析Fast数据没有传入消息类型
 *          DecodeFastRecordForNotMsgType    解析Fast数据没有传入消息类型
 *  @tangmc 20141126 
 *   1、解析UStringLength增加 Fast_Presence pres 操作符处理
 * =====================================================================================
 */
#ifndef HUNDSUN_FAST_DECODER_SH_H
#define HUNDSUN_FAST_DECODER_SH_H

#include "../Include/Fast_Decoder.h"
#include "Fast_Define.h"
#include "TinyXML/tinyxml.h"
#include "Fast_Record_Impl.h"
#include "Fast_Message_Impl.h"
#include <map>

class Fast_Decoder_Impl : public IFast_Decoder
{
public:
  Fast_Decoder_Impl (FAST_TYPE makettype) ;

  virtual int FUNCTION_CALL_MODE LoadTemplate (const char* lpFile) ;

  virtual int FUNCTION_CALL_MODE LoadTemplateForSZG5HQ (const char* lpFile);

  virtual int FUNCTION_CALL_MODE GetFastMsgLen (const char* lpData, int nLen) ;

  virtual IFast_Message* FUNCTION_CALL_MODE Decode (const char* lpData, int nLen) ;

  virtual IFast_Message* FUNCTION_CALL_MODE DecodeFastData (const char* lpFastData, int nFastDataLen,int nMsgType);

  virtual IFast_Message* FUNCTION_CALL_MODE DecodeFastData (const char* lpFastData, int nFastDataLen);

  virtual const FastField_Info* FUNCTION_CALL_MODE GetFieldInfo (int nTagID) ;

  virtual const char* FUNCTION_CALL_MODE GetLastError () ;

  virtual void FUNCTION_CALL_MODE Release () ;

protected:
  FastTempl_Manager                 m_FastTempls ;
  std::map<int, Fast_TemplField *>  m_mapFieldInfo ;

  char                              m_strError [256] ;
  bool                              m_bHasError ;
  FAST_TYPE m_makettype;

  virtual FastMsg_Templ* LoadTemplate (TiXmlElement *pXmlElement) ;

  virtual Fast_TemplField* LoadFieldTempl (TiXmlElement *pXmlElement) ;

  // 解析FAST-Data
  virtual int DecodeFast (const char* lpData, 
                          int nLen, 
                          Fast_Message_Impl* lpFastMsg,
                          FastMsg_Templ* lpMsgTempl) ;
  virtual int DecodeFastRecord (const char* lpData, 
                                int nLen, 
                                Fast_Record_Impl* lpRecord,
                                FastMsg_Templ* lpMsgTempl) ;

  //解析Fast数据没有传入消息类型
  int DecodeFastForNotMsgType (const char* lpData, 
	  int nLen, 
	  Fast_Message_Impl* lpFastMsg) ;

  //解析Fast数据没有传入消息类型
  virtual FastMsg_Templ* DecodeFastRecordForNotMsgType (const char* lpFastData, 
	  int nDataLen, 
	  Fast_Record_Impl* lpRecord,int &nOffset) ;

  //解析Sequence的个数
  size_t DecodeSequenceCount(const char* lpfast_data, uint32& nCount, const Fast_Presence& pres) ;
 
  //2013-02-18 tangmc 将上海深圳分开
  //解析一个sequence
  size_t DecodeSequenceSH (FastGroup *lpGroup, const char *lpFastData, size_t nDataLen, FastMsg_Templ *lpMsgTempl) ;
  //解析一个sequence到 IGroup
  size_t DecodeSequenceSZ (FastGroup *lpGroup, const char *lpFastData, size_t nDataLen, Fast_TemplField *lpField/*FastMsg_Templ *lpMsgTempl*/) ;
  //2013-02-18 tangmc 将上海深圳分开

  //设置一个Fast_Value到IRecord中
  int SetFastValRecord (Fast_Record_Impl *lpRecord, uint32& nID, const Fast_Value& fast_val) ;

  //解析PMAP
  size_t DecodePMAP (const char* lpData, size_t nDataLen, PMAP pmap) ;
  //解析FAST消息类型
  size_t DecodeFastType (const char* lpData, uint32& nMsgType) ;
  //解析FAST字节获得一个字段	
  size_t DecodeBytes (const char* lpData, char* lpBuf, size_t nDataLen) ;
  //解析int32类型
  size_t DecodeInt32 (const char* lpData, Fast_Presence pres, Fast_Value& fast_val) ;
  //解析int64类型
  size_t DecodeInt64 (const char* lpData, Fast_Presence pres, Fast_Value& fast_val) ;
  //解析string类型
  size_t DecodeString (const char* lpData, Fast_Presence pres, Fast_Value& fast_val) ;
  // 解析unicode string
  size_t DecodeUString(const char *lpData, Fast_Presence pres, Fast_Value &fast_val);
  // 解析unicode string的长度 //20141126 tangmc 增加操作符
  size_t DecodeUStringLength(const char *lpData, uint32 &nLen, Fast_Presence pres);

  //获取pmap的第loc个bit
  int GetPMAPBit(const PMAP pmap, uint32 loc) ;
  //判断字段的值是否出现在流中
  bool IsExistField (const FastMsg_Templ* lpMsgTempl, const  PMAP pmap, uint32 pos) ;
  bool IsExistInSeq (const FastMsg_Templ* lpMsgTempl, const  PMAP pmap, uint32 pos) ;
  //解析NORMAL字段
  size_t DecodeNormalField (const char* lpData, const FastMsg_Templ* lpMsgTempl, 
                                   const PMAP pmap, uint32 pos, Fast_Value &fast_val) ;
  //解析字段值
  size_t DecodeFieldValue (const char* lpData, Fast_Value& fast_val, Fast_Presence pres) ;

  //得到某一STEP字段值
  std::string get_step_field_value(const char *buf, int len, const std::string &field_name);

  std::string UTF8_To_GBK(const std::string& utf8_str);

} ;

#endif