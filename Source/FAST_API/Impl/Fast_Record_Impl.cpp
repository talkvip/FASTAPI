#include "Fast_Record_Impl.h"

FastGroup::FastGroup ()
{
}
 
FastGroup::~FastGroup ()
{
  for (size_t i = 0; i<this->m_ayRecords.size (); ++i)
    if (this->m_ayRecords [i])
      delete this->m_ayRecords [i] ;
  this->m_ayRecords.clear () ;
}

Fast_Record_Impl* 
FastGroup::AddRecord ()
{
  Fast_Record_Impl* lpRecord = new Fast_Record_Impl ;
  this->m_ayRecords.push_back (lpRecord) ;
  return lpRecord ;
}

Fast_Record_Impl* 
FastGroup::GetRecord (int nSlot)
{
  if ((size_t)nSlot < this->m_ayRecords.size () && nSlot >= 0)
    return this->m_ayRecords [nSlot] ;
  return 0 ;
}

uint32 
FastGroup::GetRecordCount ()
{
  return this->m_ayRecords.size () ;
}


Field_Value::Field_Value ()
: ff_type (FFT_Null_Type)
{}

Field_Value::~Field_Value ()
{}

//
Fast_Record_Impl::Fast_Record_Impl ()
{}

Fast_Record_Impl::~Fast_Record_Impl ()
{}

uint8 FUNCTION_CALL_MODE 
Fast_Record_Impl::GetInt8 (int nTagID)
{
  if (this->IsExist (nTagID))
    return m_mapFields [nTagID].ff_value.u8 ;
  return 0 ;
}
  
uint16 FUNCTION_CALL_MODE 
Fast_Record_Impl::GetInt16 (int nTagID)
{
  if (this->IsExist (nTagID))
    return m_mapFields [nTagID].ff_value.u16 ;
  return 0 ;
}
  
uint32 FUNCTION_CALL_MODE 
Fast_Record_Impl::GetInt32 (int nTagID)
{
  if (this->IsExist (nTagID))
    return m_mapFields [nTagID].ff_value.u32 ;
  return 0 ;
}
  
uint64 FUNCTION_CALL_MODE 
Fast_Record_Impl::GetInt64 (int nTagID)
{
  if (this->IsExist (nTagID))
    return m_mapFields [nTagID].ff_value.u64 ;
  return 0 ;
}

const char* FUNCTION_CALL_MODE 
Fast_Record_Impl::GetString (int nTagID)
{
  if (this->IsExist (nTagID))
    return m_mapFields [nTagID].ff_value.str ;
  return 0 ;
}

bool FUNCTION_CALL_MODE 
Fast_Record_Impl::IsExist (int nTagID)
{
  return this->m_mapFields.find (nTagID) != this->m_mapFields.end () ;
}

int FUNCTION_CALL_MODE 
Fast_Record_Impl::GetSubCount (int nTagID)
{
  if (this->IsExist (nTagID))
    return this->m_mapFields[nTagID].ff_group.GetRecordCount () ;
  return 0 ;
}

IFast_Record* FUNCTION_CALL_MODE 
Fast_Record_Impl::GetSubRecord (int nTagID, int nSlot)
{
  if (this->IsExist (nTagID))
    return this->m_mapFields [nTagID].ff_group.GetRecord (nSlot) ;
  return 0 ;
}

int FUNCTION_CALL_MODE 
Fast_Record_Impl::SetInt8 (int nTagID, uint8 u8)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_UInt8 ;
  lpValue->ff_value.u8 = u8 ;
  return 0 ;
}
  
int FUNCTION_CALL_MODE 
Fast_Record_Impl::SetInt16 (int nTagID, uint16 u16)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_UInt16 ;
  lpValue->ff_value.u16 = u16 ;
  return 0 ;
}

int FUNCTION_CALL_MODE 
Fast_Record_Impl::SetInt32 (int nTagID, uint32 u32)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_UInt32 ;
  lpValue->ff_value.u32 = u32 ;
  return 0 ;
}
  
int FUNCTION_CALL_MODE 
Fast_Record_Impl::SetInt64 (int nTagID, uint64 u64)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_UInt64 ;
  lpValue->ff_value.u64 = u64 ;
  return 0 ;
}

int FUNCTION_CALL_MODE 
Fast_Record_Impl::SetString (int nTagID, const char* str)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_String ;
  memset (lpValue->ff_value.str, 0, sizeof (lpValue->ff_value.str)) ;
  strncpy (lpValue->ff_value.str, str, sizeof (lpValue->ff_value.str)-1) ;
  return 0 ;
}

FastGroup* 
Fast_Record_Impl::SetGroup (int nTagID)
{
  Field_Value* lpValue = &this->m_mapFields [nTagID] ;
  lpValue->ff_type = FFT_Sequence ;
  return &lpValue->ff_group ;
}

FastGroup* 
Fast_Record_Impl::GetGroup (int nTagID)
{
  if (this->IsExist (nTagID))
    return &this->m_mapFields [nTagID].ff_group ;
  return 0 ;
}