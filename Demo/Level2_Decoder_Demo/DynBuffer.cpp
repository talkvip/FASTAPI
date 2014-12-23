#include "DynBuffer.h"

DynBuffer::DynBuffer(void)
	: m_lpBuff (0)
	, m_nCapacity (0)
	, m_nRead (0)
	, m_nWrite (0)
{
	this->ExpandFreeTo (1024*1024) ;
}

DynBuffer::~DynBuffer(void)
{
	if (this->m_lpBuff)
		delete [] this->m_lpBuff ;
}

unsigned int DynBuffer::GetBuffSize ()
{
	return (this->m_nWrite - this->m_nRead) ;
}

unsigned int DynBuffer::GetCapacity ()
{
	return this->m_nCapacity ;
}

unsigned int DynBuffer::GetFreeSize ()
{
	return (this->m_nCapacity - this->m_nWrite) ;
}

const char* DynBuffer::GetReadData ()
{
	return this->m_lpBuff + this->m_nRead ;
}

char* DynBuffer::GetWriteData ()
{
	return this->m_lpBuff + this->m_nWrite ;
}

void DynBuffer::MoveRead (int nOffset)
{
	if (this->m_nRead + nOffset > this->m_nWrite)
		this->m_nRead = this->m_nWrite ;
	else
		this->m_nRead += nOffset ;
}

void DynBuffer::AddData (const char* lpData, int nLen)
{
	ExpandFreeTo (nLen) ;
	memcpy (this->GetWriteData (), lpData, nLen) ;
	this->m_nWrite += nLen ;
}

void 
	DynBuffer::Clear ()
{
	this->m_nRead = this->m_nWrite = 0 ;
}

int DynBuffer::ExpandFreeTo (unsigned int nSize)
{
	if (this->GetFreeSize () >= nSize)
		return 0 ;
	if (this->m_nRead + this->GetFreeSize () >= nSize)
	{
		int nDataLen = this->GetBuffSize () ;
		memmove (this->m_lpBuff, this->GetReadData (), nDataLen) ;
		this->m_nRead  = 0 ;
		this->m_nWrite = nDataLen ;
	}
	else
	{
		int nNewSize = this->GetBuffSize () + nSize ;
		int nDataLen = this->GetBuffSize () ;
		char* lpNewData = new char [nNewSize] ;
		memcpy (lpNewData, this->GetReadData (), nDataLen) ;
		this->m_nRead  = 0 ;
		this->m_nWrite = nDataLen ;
		if (this->m_lpBuff)
			delete [] this->m_lpBuff ;
		this->m_lpBuff    = lpNewData ;
		this->m_nCapacity = nNewSize ;
	}

	return 0 ;
}

