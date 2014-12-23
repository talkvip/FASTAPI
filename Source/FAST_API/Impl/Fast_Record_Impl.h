#ifndef HUNDSUN_PUBLIC_FAST_RECORD_IMPL_H
#define HUNDSUN_PUBLIC_FAST_RECORD_IMPL_H

#include "../Include/Fast_Decoder.h"
#include "../Include/Basic_Types.h"
#include "Fast_Define.h"
#include <map>
#include <vector>

class Fast_Record_Impl ;

class FastGroup
{
public:
  FastGroup () ;

  virtual ~FastGroup () ;

  Fast_Record_Impl* AddRecord () ;

  Fast_Record_Impl* GetRecord (int nSlot) ;

  uint32 GetRecordCount () ;

protected:
  std::vector <Fast_Record_Impl *>    m_ayRecords ; 
} ;


struct Field_Value
{
  Fast_FieldType         ff_type ;
  union
  {
    uint8   u8 ;
    uint16  u16 ;
    uint32  u32 ;
    uint64  u64 ;
    char    str [256] ;
  } ff_value ;
  
  FastGroup              ff_group ;

  Field_Value () ;

  ~Field_Value () ;
} ;

class Fast_Record_Impl : public IFast_Record
{
protected:
  typedef std::map<uint32, Field_Value> FIELD_MAP ;

public:
  Fast_Record_Impl () ;

  virtual ~Fast_Record_Impl () ;

  virtual uint8 FUNCTION_CALL_MODE GetInt8 (int nTagID) ;
  
  virtual uint16 FUNCTION_CALL_MODE GetInt16 (int nTagID) ;
  
  virtual uint32 FUNCTION_CALL_MODE GetInt32 (int nTagID) ;
  
  virtual uint64 FUNCTION_CALL_MODE GetInt64 (int nTagID) ;

  virtual const char* FUNCTION_CALL_MODE GetString (int nTagID) ;

  virtual bool FUNCTION_CALL_MODE IsExist (int nTagID) ;

  virtual int FUNCTION_CALL_MODE GetSubCount (int nTagID) ;

  virtual IFast_Record* FUNCTION_CALL_MODE GetSubRecord (int nTagID, int nSlot) ;

public:
  virtual int FUNCTION_CALL_MODE SetInt8 (int nTagID, uint8 u8) ;
  
  virtual int FUNCTION_CALL_MODE SetInt16 (int nTagID, uint16 u16) ;
  
  virtual int FUNCTION_CALL_MODE SetInt32 (int nTagID, uint32 u32) ;
  
  virtual int FUNCTION_CALL_MODE SetInt64 (int nTagID, uint64 u64) ;

  virtual int FUNCTION_CALL_MODE SetString (int nTagID, const char* str) ;

  FastGroup* SetGroup (int nTagID) ;

  FastGroup* GetGroup (int nTagID) ;

protected:
  FIELD_MAP                            m_mapFields ;
} ;

#endif