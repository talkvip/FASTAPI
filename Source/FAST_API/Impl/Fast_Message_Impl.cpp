#include "Fast_Message_Impl.h"
#include "Fast_Record_Impl.h"

Fast_Message_Impl::Fast_Message_Impl ()
: m_nSeqNum (-1)
{}

Fast_Message_Impl::~Fast_Message_Impl ()
{
  for (size_t i = 0; i<m_ayRecords.size (); ++i)
    if (this->m_ayRecords [i])
      delete this->m_ayRecords [i] ;

  this->m_ayRecords.clear () ;
}

const char* FUNCTION_CALL_MODE 
Fast_Message_Impl::GetMsgType ()
{
  return this->m_strMsgType ;
}

const char* FUNCTION_CALL_MODE 
Fast_Message_Impl::GetSendTime ()
{
  return this->m_strSendTime ;
}

int FUNCTION_CALL_MODE 
Fast_Message_Impl::GetSeqNum ()
{
  return this->m_nSeqNum ;
}

int FUNCTION_CALL_MODE 
Fast_Message_Impl::GetRecordCount ()
{
  return static_cast<int> (this->m_ayRecords.size ()) ;
}

IFast_Record* FUNCTION_CALL_MODE 
Fast_Message_Impl::GetRecord (int nSlot)
{
  if (nSlot >= 0 && static_cast<size_t> (nSlot) < this->m_ayRecords.size ()) 
    return this->m_ayRecords [nSlot] ;
  return 0 ;
}

const char* FUNCTION_CALL_MODE 
Fast_Message_Impl::GetLastError ()
{
  return 0 ;
}

void FUNCTION_CALL_MODE 
Fast_Message_Impl::Release ()
{
  delete this ;
}

Fast_Record_Impl* 
Fast_Message_Impl::AddRecord ()
{
  Fast_Record_Impl* lpRecord = new Fast_Record_Impl ;
  this->m_ayRecords.push_back (lpRecord) ;
  return lpRecord ;
}