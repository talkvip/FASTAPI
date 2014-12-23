#include "Fast_Decoder_Impl.h"
#include "Public.h"
#ifdef _WIN32
#include <Windows.h>
#endif

Fast_Decoder_Impl::Fast_Decoder_Impl (FAST_TYPE makettype)
: m_bHasError (false)
,m_makettype(makettype)
{
}

int FUNCTION_CALL_MODE 
Fast_Decoder_Impl::LoadTemplate (const char* lpFile)
{
  this->m_bHasError = false ;
  this->m_FastTempls.Clear () ;
  this->m_mapFieldInfo.clear () ;
  TiXmlDocument *pXmlDoc = new TiXmlDocument() ;
  Delete_Guard<TiXmlDocument> guard (pXmlDoc) ;
  if (pXmlDoc == 0)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "No memory.") ;
      return -1 ;
    }
  if (!pXmlDoc->LoadFile (lpFile))
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Load XML-File[%s] Failed, Error[%s].",
                  lpFile, pXmlDoc->Error ()?pXmlDoc->ErrorDesc ():"") ;
      return -1 ;
    }

  TiXmlElement *pRootElement = pXmlDoc->RootElement() ;
  if (!pRootElement)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Load XML-File[%s] Failed,Error[%s].",
                  lpFile, pXmlDoc->Error ()?pXmlDoc->ErrorDesc ():"no root element") ;
      return -1 ;
    }

	TiXmlElement *lpTempl = pRootElement->FirstChildElement("template") ;
  while (lpTempl)
    {
       FastMsg_Templ* lpMsgTempl = this->LoadTemplate (lpTempl) ;
       if (lpMsgTempl)
         this->m_FastTempls.AddTempl (lpMsgTempl->templ_id, lpMsgTempl) ;
       lpTempl = lpTempl->NextSiblingElement () ;
    }
  //this->m_FastTempls.Print () ;
  return 0 ;
}

int FUNCTION_CALL_MODE 
Fast_Decoder_Impl::LoadTemplateForSZG5HQ (const char* lpFile)
{
	this->m_bHasError = false ;
	this->m_FastTempls.Clear () ;
	this->m_mapFieldInfo.clear () ;
	TiXmlDocument *pXmlDoc = new TiXmlDocument() ;
	Delete_Guard<TiXmlDocument> guard (pXmlDoc) ;
	if (pXmlDoc == 0)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"No memory.") ;
		return -1 ;
	}
	if (!pXmlDoc->LoadFile (lpFile))
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"Load XML-File[%s] Failed, Error[%s].",
			lpFile, pXmlDoc->Error ()?pXmlDoc->ErrorDesc ():"") ;
		return -1 ;
	}

	TiXmlElement *pRootElement = pXmlDoc->RootElement() ;
	if (!pRootElement)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"Load XML-File[%s] Failed,Error[%s].",
			lpFile, pXmlDoc->Error ()?pXmlDoc->ErrorDesc ():"no root element") ;
		return -1 ;
	}

	TiXmlElement *lpTemplates = pRootElement->FirstChildElement();
	if (!lpTemplates)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"Load XML-File[%s] Failed,templates.",
			lpFile) ;
		return -1 ;
	}

	TiXmlElement *lpTempl = lpTemplates->FirstChildElement("template") ;
	while (lpTempl)
	{
		FastMsg_Templ* lpMsgTempl = this->LoadTemplate (lpTempl) ;
		if (lpMsgTempl)
			this->m_FastTempls.AddTempl (lpMsgTempl->templ_id, lpMsgTempl) ;
		lpTempl = lpTempl->NextSiblingElement () ;
	}
	//this->m_FastTempls.Print () ;
	return 0 ;
}

int FUNCTION_CALL_MODE 
Fast_Decoder_Impl::GetFastMsgLen (const char* lpData, int nLen)
{
  this->m_bHasError = false ;
  if (nLen < MIN_STEP_LEN)
    return 0 ;

  if (strncmp (lpData, STEP_HEADER_FLAG, STEP_HEADER_SIZE) != 0)
    {
      this->m_bHasError = true ;
      char temp [STEP_HEADER_SIZE + 1] ;
      memcpy (temp, lpData, STEP_HEADER_SIZE) ;
      temp [STEP_HEADER_SIZE] = 0x00 ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Illegal Fast Data[%s].", temp) ;
      return -1 ;
    }
  const char* lpStepLen = strstr (lpData, STEP_LEN_FLAG) ;
  if (!lpStepLen)
    return 0 ;
  lpStepLen += STEP_LEN_SIZE ;

  char tmp_buf[20] ;
  int  nPos = 0 ;
  while ((*lpStepLen) != STEP_FIELD_DELIM)
    {
      tmp_buf[nPos] = *lpStepLen ;
      ++nPos ;
      ++lpStepLen ;

      if (nPos >= 20)
        break ;
    }

  if (nPos < 20)
    {
      ++lpStepLen ;
      tmp_buf[nPos] = '\0' ;
      return static_cast<int>(atoi(tmp_buf)+(lpStepLen - lpData) + FAST_TAIL_LENGTH)  ;
    }
  else
    return 0 ;
}

IFast_Message* FUNCTION_CALL_MODE 
Fast_Decoder_Impl::Decode (const char* lpData, int nLen)
{
  this->m_bHasError = false ;
  // 判断消息的合法性-头部
  if (strncmp (lpData, STEP_HEADER_FLAG, STEP_HEADER_SIZE) != 0)
    {
      this->m_bHasError = true ;
      char strTmp [STEP_HEADER_SIZE + 1] ;
      strncpy (strTmp, lpData, STEP_HEADER_SIZE) ;
      strTmp [STEP_HEADER_SIZE] = 0x00 ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Not a fast message: prefixion[%s] is dismatched.", strTmp) ;
      return 0 ;
    }

  char strMsgType [21], strSendTime [21] ;
  int  nSeqNum = -1 ;

  // 消息类型
  std::string lpMsgType = get_step_field_value(lpData,nLen, STEP_TYPE_FLAG) ;
  if (0==lpMsgType.size())
  {
	  this->m_bHasError = true ;
	  ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
		  "Not a valid fast message: can't find message type[%s].", STEP_TYPE_FLAG) ;
	  return 0 ;
  }
  else
  {
	  int nPos = lpMsgType.length()<20?lpMsgType.length():20;

	  memset(strMsgType,0,21);
	  memcpy(strMsgType,lpMsgType.c_str(),nPos);
	  strMsgType [nPos] = '\0' ;
	 
  }

  // 权限控制  tangmc 20140703 去除功能号的限制
  //if (! (strcmp (strMsgType, "UA1202") == 0 ||         // HeartBeat 
  //       strcmp (strMsgType, "UA3201") == 0 ||         // Transaction
  //       strcmp (strMsgType, "UA3202") == 0 ||         // MarketData
  //       strcmp (strMsgType, "UA3113") == 0 ||         // Index
  //       strcmp (strMsgType, "UA3115") == 0 ||         // MarketOverView
  //       strcmp (strMsgType, "UA3107") == 0 ||           // VirtualAction

		// //2014-02-18 增加深圳 
		// strcmp (strMsgType, "UA101") == 0 ||  // SLZ2 证券信息       (原始类型: UA101) 
		// strcmp (strMsgType, "UA102") == 0 ||  // SLZ2 证券状态       (原始类型: UA102)
		// strcmp (strMsgType, "UA103") == 0 ||  // SLZ2 行情快照       (原始类型: UA103)
		// strcmp (strMsgType, "UA104") == 0 ||  // SLZ2 指数快照       (原始类型: UA104)
		// strcmp (strMsgType, "UA201") == 0 ||  // SLZ2 逐笔委托       (原始类型: UA201)
		// strcmp (strMsgType, "UA202") == 0   // SLZ2 逐笔成交       (原始类型: UA202)
  //      )
  //    )          
  //{
  //  this->m_bHasError = true ;
  //    ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
  //                "Permission denied: MsgType[%s].",
  //                strMsgType) ;
  //  return 0 ;
  //}

  // 发送时间
 std::string lpSendTime = get_step_field_value(lpData,nLen, STEP_SENDTIME_FLAG) ;
  if (0 == lpSendTime.size())
  {
	  this->m_bHasError = true ;
	  ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
		  "Not a valid fast message: can't find sendtime[%s].", STEP_SENDTIME_FLAG) ;
	  return 0 ;
  }
  else
  {
	  int  nPos = lpSendTime.length()<20? lpSendTime.length():20;
	 
	  memset(strSendTime,0,21);
	  memcpy(strSendTime,lpSendTime.c_str(),nPos);
	  strSendTime [nPos] = '\0' ;
  }

  char tmp_buf [21] ;
  // 消息序号

  std::string lpSeqNum;
  if (emFAST_SHLEVEL2 ==m_makettype)
  {
	  lpSeqNum= get_step_field_value(lpData,nLen, STEP_MSGSEQID_FLAG) ;
  }
  else if (emFAST_SZLEVEL2==m_makettype)
  {
	   lpSeqNum= get_step_field_value(lpData,nLen, STEP_SEQUENCE_FLAG) ;
  }
  if (0==lpSeqNum.size())
  {
	  this->m_bHasError = true ;
	  ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
		  "Not a valid fast message: can't find seqnum[%s].", STEP_MSGSEQID_FLAG) ;
	  return 0 ;
  }
  else
  {
	  int  nPos = lpSeqNum.length()<20?lpSeqNum.length():20;
	  
	  memset(tmp_buf,0,21);
	  memcpy(tmp_buf,lpSeqNum.c_str(),nPos);
	  tmp_buf [nPos] = '\0' ;
	  nSeqNum = atoi (tmp_buf) ;
  }

  Fast_Message_Impl* lpFastMsg = new Fast_Message_Impl ;
  strcpy (lpFastMsg->m_strMsgType, strMsgType) ;
  strcpy (lpFastMsg->m_strSendTime, strSendTime) ;
  lpFastMsg->m_nSeqNum     = nSeqNum ;
  
  int nFastDataLen = 0 ;
  // FASTDATA Length
  const char *lpFastLen = strstr(lpData, FASTDATA_LEN_FLAG) ;
  if (!lpFastLen)
    {
			return lpFastMsg ;
		}
	else
		{
      lpFastLen += FASTDATA_LEN_SIZE ;
			int  nPos = 0 ;
      while ((*lpFastLen) != STEP_FIELD_DELIM)
        {
          tmp_buf [nPos] = *lpFastLen ;
          ++nPos ;
          ++lpFastLen ;

          if (nPos >= 20)
            break ;
        }

      if (nPos < 20)
        {
          ++lpFastLen ;
          tmp_buf [nPos] = '\0' ;
          nFastDataLen = atoi (tmp_buf) ;
        }
	  }

  const char *lpFastData = strstr (lpFastLen, FASTDATA_FLAG) ;
  if (!lpFastData)
    {
      lpFastMsg->Release () ;
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Not a valid fast message: fast data can't find[%s], fast len[%d].", 
                  FASTDATA_FLAG, nFastDataLen) ;
			return 0 ;
    }
  lpFastData += FASTDATA_SIZE ;

  if (lpFastData + nFastDataLen + FAST_TAIL_LENGTH > lpData + nLen)
    {
      lpFastMsg->Release () ;
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Not a complete fast message:Fast Data not enough, Need[%d], Real[%d].",
                  nFastDataLen, nLen - (lpFastData - lpData) - FAST_TAIL_LENGTH) ;
			return 0 ;
    }

  // 解析Fast-Data
  int nMsgType = atoi (strMsgType + 2) ;
  FastMsg_Templ* lpFastTempl = this->m_FastTempls.GetTemplate (nMsgType) ;
  if (!lpFastTempl)
    {
		this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1, "FAST type[%s:%d] template not found.",
                  strMsgType, nMsgType) ;
      lpFastMsg->Release () ;
      return 0 ;
    }
  if (-1 == this->DecodeFast (lpFastData, nFastDataLen, lpFastMsg, lpFastTempl))
    {
      lpFastMsg->Release () ;
			return 0 ;
    }
  return lpFastMsg ;
}


IFast_Message* FUNCTION_CALL_MODE 
Fast_Decoder_Impl::DecodeFastData (const char* lpFastData, int nFastDataLen,int nMsgType)
{
	Fast_Message_Impl* lpFastMsg = new Fast_Message_Impl ;
	lpFastMsg->m_nSeqNum     = 0 ;

	// 解析Fast-Data
	FastMsg_Templ* lpFastTempl = this->m_FastTempls.GetTemplate (nMsgType) ;
	if (!lpFastTempl)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1, "FAST type[%d] template not found.",
			 nMsgType) ;
		lpFastMsg->Release () ;
		return 0 ;
	}
	if (-1 == this->DecodeFast (lpFastData, nFastDataLen, lpFastMsg, lpFastTempl))
	{
		lpFastMsg->Release () ;
		return 0 ;
	}
	return lpFastMsg ;

}

IFast_Message* FUNCTION_CALL_MODE 
Fast_Decoder_Impl::DecodeFastData (const char* lpFastData, int nFastDataLen)
{
	Fast_Message_Impl* lpFastMsg = new Fast_Message_Impl ;
	lpFastMsg->m_nSeqNum     = 0 ;

	// 解析Fast-Data	
	if (-1 == this->DecodeFastForNotMsgType (lpFastData, nFastDataLen, lpFastMsg))
	{
		lpFastMsg->Release () ;
		return 0 ;
	}
	return lpFastMsg ;
}

const FastField_Info* FUNCTION_CALL_MODE 
Fast_Decoder_Impl::GetFieldInfo (int nTagID)
{
  static FastField_Info s_FieldInfo ;
  if (m_mapFieldInfo.find (nTagID) != m_mapFieldInfo.end ())
   {
     Fast_TemplField* lpField = m_mapFieldInfo [nTagID]  ;
     switch (lpField->field_type)
     {
     case FFT_Int8:
       s_FieldInfo.emType = emInt8 ;
       break ;
     case FFT_UInt8:
       s_FieldInfo.emType = emUInt8 ;
       break ;
     case FFT_Int16:
       s_FieldInfo.emType = emInt16 ;
       break ;
     case FFT_UInt16:
       s_FieldInfo.emType = emUInt16 ;
       break ;
     case FFT_Int32:
       s_FieldInfo.emType = emInt32 ;
       break ;
     case FFT_UInt32:
       s_FieldInfo.emType = emUInt32 ;
       break ;
     case FFT_Int64:
       s_FieldInfo.emType = emInt64 ;
       break ;
     case FFT_String:
       s_FieldInfo.emType = emString ;
       break ;
     case FFT_Sequence:
     case FFT_Length:
       s_FieldInfo.emType = emSequence ;
       break ;
     default:
       return 0 ;
     } ;
     s_FieldInfo.nDecimalPlaces = lpField->decimal_place ;
     strcpy (s_FieldInfo.strDesc, lpField->field_name) ;
     return &s_FieldInfo ;
   }
  return 0 ;
}

const char* FUNCTION_CALL_MODE 
Fast_Decoder_Impl::GetLastError ()
{
  if (this->m_bHasError)
    return this->m_strError ;
  else
    return "No error." ;
}

void FUNCTION_CALL_MODE 
Fast_Decoder_Impl::Release ()
{
  delete this ;
}

FastMsg_Templ* 
Fast_Decoder_Impl::LoadTemplate (TiXmlElement *pXmlElement)
{
  if (pXmlElement == 0)
    return 0 ;

  FastMsg_Templ* lpMsgTempl = new FastMsg_Templ ;
	//const char *lpNameStr = pXmlElement->Value() ;
  const char *lpTName   = pXmlElement->Attribute("name") ;
	const char *lpTID     = pXmlElement->Attribute("id") ;

  // 模板名称
  if (lpTName)
    strcpy (lpMsgTempl->templ_name, lpTName) ;
  // 模板ID
  if (lpTID)
    lpMsgTempl->templ_id = atoi (lpTID) ;

  // 载入模板字段
  TiXmlElement *pChild = pXmlElement->FirstChildElement() ;
  while (pChild)
    {
      Fast_TemplField* lpFieldTempl = this->LoadFieldTempl (pChild) ;
      if (lpFieldTempl)
        {
          if (m_mapFieldInfo.find (lpFieldTempl->field_id) == m_mapFieldInfo.end ())
            {
              m_mapFieldInfo [lpFieldTempl->field_id] = lpFieldTempl ;
            }
          if (lpFieldTempl->field_slot == 1)
            {
              lpFieldTempl->field_slot = lpMsgTempl->slot_count ;
              ++lpMsgTempl->slot_count ;
            }
          else
            lpFieldTempl->field_slot = -1 ;

          lpMsgTempl->field_array.push_back (lpFieldTempl) ;
          ++lpMsgTempl->field_count ;
        }
      pChild = pChild->NextSiblingElement () ;
    }
  return lpMsgTempl ;
}

Fast_TemplField* 
Fast_Decoder_Impl::LoadFieldTempl (TiXmlElement *pXmlElement)
{
  const char *lpValue  = pXmlElement->Value() ;
  const char *lpName   = pXmlElement->Attribute("name") ;
	const char *lpID     = pXmlElement->Attribute("id") ;
  const char *lpPres   = pXmlElement->Attribute("presence") ;
  const char *lpDecimal= pXmlElement->Attribute("decimalPlaces") ;

  Fast_FieldType field_type = Fast_Method::StrToFieldType (lpValue) ;
  if (FFT_Null_Type == field_type)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Template Field[%s] Unkown Type.", lpValue) ;
      return 0 ;
    }

  ///2014-02-19 tangmc 增加市场判断
 /* if (emFAST_SZLEVEL2 ==m_makettype)*/
  {
	  /// 2014-02-19 unicode string
	  if (field_type == FFT_String)
	  {
		  lpValue = pXmlElement->Attribute("charset");
		  if (lpValue && !strcmp(lpValue, "unicode"))
		  {
			  field_type = FFT_UString;
		  }
	  }
  }

  Fast_TemplField* lpTemplField = new Fast_TemplField ;
  // 字段类型
  lpTemplField->field_type = field_type ;
  lpTemplField->field_curval.field_type = lpTemplField->field_opval.field_type = field_type ;
  // 字段名称
  if (lpName)
    strcpy(lpTemplField->field_name, lpName) ;
  //
  if (FFT_Sequence == field_type)
    {
      lpTemplField->seq_ptr = this->LoadTemplate (pXmlElement) ;
      
	  ///2014-02-18 tangmc 增加市场判断
	  if (emFAST_SZLEVEL2==m_makettype)
	  {
		  if (lpID)
			  lpTemplField->field_id = atoi (lpID) ;

		  if (lpPres)
			  lpTemplField->field_pres = Fast_Method::StrToPres (lpPres) ;
		  else
			  lpTemplField->field_pres = PRES_Mandatory ;

		  lpTemplField->field_slot = Fast_Method::Slot(lpTemplField->field_op, lpTemplField->field_pres) ;

	  }
	   ///2014-02-18 tangmc 增加市场判断
  }
  else
    {
      if (lpID)
        lpTemplField->field_id = atoi (lpID) ;
      if (lpPres)
        lpTemplField->field_pres = Fast_Method::StrToPres (lpPres) ;
      else
        lpTemplField->field_pres = PRES_Mandatory ;

	   ///2014-02-18  tangmc 增加市场判断  
	   // 2014-02-18  深圳L2用precision表示小数位数
	   if (!lpDecimal && emFAST_SZLEVEL2==m_makettype)
	   {
		   lpDecimal = pXmlElement->Attribute("precision") ;
	   }
	   // 2014-02-18  深圳L2用precision表示小数位数

      if (lpDecimal)
        {
          lpTemplField->decimal_place = atoi (lpDecimal) ;
          lpTemplField->field_curval.decimal_place = lpTemplField->field_opval.decimal_place = 
                                                                          lpTemplField->decimal_place ;
        }

      // Op
      TiXmlElement *lpChild = pXmlElement->FirstChildElement() ;
      if (lpChild)
        {
          const char* lpOp = lpChild->Value () ;
          if (lpOp)
            lpTemplField->field_op = Fast_Method::StrToFastOp (lpOp) ;
          const char* lpValue = lpChild->Attribute ("value") ;
          if (lpValue && OP_Constant == lpTemplField->field_op)
            {
              lpTemplField->field_opval.field_type = lpTemplField->field_type ;
              strcpy(lpTemplField->field_opval.val.str, lpValue) ;
            }

		  ///2014-02-18 tangmc 增加深圳市场判断 

		  // 2014-02-18 为深圳L2增加
		  else if (lpValue  &&  lpTemplField->field_op == OP_Default && emFAST_SZLEVEL2==m_makettype)
		  {
			  if (lpTemplField->field_type == FFT_Int32  ||  lpTemplField->field_type == FFT_UInt32)
			  {
				  lpTemplField->field_opval.val.l4 = atol(lpValue);
			  }
			  else
			  {
				  strcpy(lpTemplField->field_opval.val.str, lpValue);
			  }
		  }
		  else if (lpValue  &&  lpTemplField->field_op == OP_Copy && emFAST_SZLEVEL2==m_makettype)
		  {
			  // copy 且有 value, 目前深圳L2 FAST只有string类型
			  strcpy(lpTemplField->field_opval.val.str, lpValue);
			  lpTemplField->ResetCurrentValue();
		  }
		  // 2014-02-18 为深圳L2增加
        }

      lpTemplField->field_slot = Fast_Method::Slot(lpTemplField->field_op, lpTemplField->field_pres) ;
    }

  return lpTemplField ;
}

int 
Fast_Decoder_Impl::DecodeFastRecord (const char* lpFastData, 
                                   int nDataLen, 
                                   Fast_Record_Impl* lpRecord,
                                   FastMsg_Templ* lpMsgTempl)
{
  size_t curr_size  = 0 ;
  size_t ret_size   = 0 ;

  //解析PMAP
  PMAP pmap ;
  memset(pmap, 0, sizeof(PMAP)) ;
  ret_size = DecodePMAP (lpFastData, FAST_PMAPSIZE, pmap) ;
  if (ret_size == 0)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Decode FastData Error: PMAP Excp.") ;
      return -1 ;
     }
  curr_size += ret_size ;
  //解析消息类型
  uint32  fast_msgtype = 0 ;
  ret_size = DecodeFastType (lpFastData + curr_size, fast_msgtype) ;
  if (ret_size == 0)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Decode FastData Error: fasttype Excp.") ;
      return -1 ;
    }

  if (fast_msgtype != lpMsgTempl->templ_id)
    {
      this->m_bHasError = true ;
      ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                  "Decode FastData Error: fast_msgtype[%d != %d].",
                  fast_msgtype, lpMsgTempl->templ_id) ;
      return -1 ;
    }
     
  curr_size += ret_size ;
  Fast_Value fast_val ;
  //解析各个字段
  for(uint32 i=0; i<lpMsgTempl->field_count; ++i)
    {
      Fast_TemplField* lpFieldTempl = lpMsgTempl->field_array[i] ;
      if (FFT_Sequence == lpFieldTempl->field_type)
        {
          //decode sequence field
			///2014-02-18 tangmc 增加市场判断 
			uint32 nTagID = 0;
			if (emFAST_SHLEVEL2 ==m_makettype)
			{
				if (lpFieldTempl->seq_ptr->field_array[0]->field_type != FFT_Length)
				{
					this->m_bHasError = true ;
					::snprintf (this->m_strError, sizeof (this->m_strError)-1,
						"Decode FastData Error: template[%s-%d] has error field_id[%d].",
						lpMsgTempl->templ_name, lpMsgTempl->templ_id, lpFieldTempl->field_id) ;
					return -1 ;
				}
				nTagID = lpFieldTempl->seq_ptr->field_array[0]->field_id ;
			}
			else if (emFAST_SZLEVEL2==m_makettype)
			{
				nTagID = lpFieldTempl->field_id;
			}
			if( 0 == nTagID )
			{
				return -1;
			}
          FastGroup* lpGroup = lpRecord->SetGroup (nTagID) ;
		  
		  ///2014-02-18 tangmc 增加市场判断
		  if (emFAST_SHLEVEL2 ==m_makettype)
		  {
			  ret_size = DecodeSequenceSH (lpGroup, lpFastData + curr_size, nDataLen - curr_size, lpFieldTempl->seq_ptr) ;
		  }
		  else if (emFAST_SZLEVEL2 ==m_makettype)
		  {
			  ret_size = DecodeSequenceSZ (lpGroup, lpFastData + curr_size, nDataLen - curr_size, lpFieldTempl) ;
		  }
		  curr_size += ret_size ;
        }
      else
        {
          //decode normal field
          ret_size = DecodeNormalField (lpFastData + curr_size, lpMsgTempl, pmap, i, fast_val) ;
          if (fast_val.field_type != FFT_Null_Type
              && lpFieldTempl->field_id!=35
              && SetFastValRecord (lpRecord, lpFieldTempl->field_id, fast_val) == -1)
            {  
              this->m_bHasError = true ;
              ::snprintf (this->m_strError, sizeof (this->m_strError)-1,
                          "Decode FastData Error: set fast_value error, template[%s-%d] field_id[%d].",
                          lpMsgTempl->templ_name, lpMsgTempl->templ_id, lpFieldTempl->field_id) ;
              return -1 ;
            }
           curr_size += ret_size ;
         }
    }
  return curr_size ;
}

int 
Fast_Decoder_Impl::DecodeFast (const char* lpData, 
                             int nLen, 
                             Fast_Message_Impl* lpFastMsg,
                             FastMsg_Templ* lpMsgTempl)
{
  int nCurr = 0 ;
  while (nCurr < nLen)
  {
    Fast_Record_Impl* lpRecord = lpFastMsg->AddRecord () ;

    int nOffset = this->DecodeFastRecord (lpData + nCurr,
                                          nLen - nCurr,
                                          lpRecord,
                                          lpMsgTempl) ;
    if (nOffset <= 0)
      return -1 ;
    nCurr += nOffset ;
  } ;

  //2014-02-19 增加深圳值的释放
  if (emFAST_SZLEVEL2==m_makettype)
  {
	  lpMsgTempl->ResetCurrentValue();
  }
   //2014-02-19 增加深圳值的释放

  return 0 ;
}


int Fast_Decoder_Impl::DecodeFastForNotMsgType (const char* lpData, 
	int nLen, 
	Fast_Message_Impl* lpFastMsg) 
{
	FastMsg_Templ* lpMsgTempl = NULL;
	int nCurr = 0 ;
	while (nCurr < nLen)
	{
		Fast_Record_Impl* lpRecord = lpFastMsg->AddRecord () ;

		int nOffset =0;
		lpMsgTempl = this->DecodeFastRecordForNotMsgType (lpData + nCurr,
			nLen - nCurr,
			lpRecord,
			nOffset) ;
		if (nOffset <= 0)
			return -1 ;
		nCurr += nOffset ;
	} ;

	// 增加深圳值的释放
	if (emFAST_SZLEVEL2==m_makettype && lpMsgTempl)
	{
		lpMsgTempl->ResetCurrentValue();
	}
	// 增加深圳值的释放

	return 0 ;
}

FastMsg_Templ*  Fast_Decoder_Impl::DecodeFastRecordForNotMsgType (const char* lpFastData, 
	int nDataLen,
	Fast_Record_Impl* lpRecord,int &nOffset) 
{
	nOffset = -1;
	size_t curr_size  = 0 ;
	size_t ret_size   = 0 ;

	//解析PMAP
	PMAP pmap ;
	memset(pmap, 0, sizeof(PMAP)) ;
	ret_size = DecodePMAP (lpFastData, FAST_PMAPSIZE, pmap) ;
	if (ret_size == 0)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"Decode FastData Error: PMAP Excp.") ;
		return 0 ;
	}
	curr_size += ret_size ;
	//解析消息类型
	uint32  fast_msgtype = 0 ;
	ret_size = DecodeFastType (lpFastData + curr_size, fast_msgtype) ;
	if (ret_size == 0)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1,
			"Decode FastData Error: fasttype Excp.") ;
		return 0 ;
	}

	FastMsg_Templ* lpMsgTempl  = this->m_FastTempls.GetTemplate (fast_msgtype) ;
	if (!lpMsgTempl)
	{
		this->m_bHasError = true ;
		::snprintf (this->m_strError, sizeof (this->m_strError)-1, "FAST type[%d] template not found.",
			fast_msgtype) ;
		return 0 ;
	}

	curr_size += ret_size ;
	Fast_Value fast_val ;
	//解析各个字段
	for(uint32 i=0; i<lpMsgTempl->field_count; ++i)
	{
		Fast_TemplField* lpFieldTempl = lpMsgTempl->field_array[i] ;
		if (FFT_Sequence == lpFieldTempl->field_type)
		{
			//decode sequence field
			uint32 nTagID = 0;
			if (emFAST_SHLEVEL2 ==m_makettype)
			{
				if (lpFieldTempl->seq_ptr->field_array[0]->field_type != FFT_Length)
				{
					this->m_bHasError = true ;
					::snprintf (this->m_strError, sizeof (this->m_strError)-1,
						"Decode FastData Error: template[%s-%d] has error field_id[%d].",
						lpMsgTempl->templ_name, lpMsgTempl->templ_id, lpFieldTempl->field_id) ;
					return 0 ;
				}
				nTagID = lpFieldTempl->seq_ptr->field_array[0]->field_id ;
			}
			else if (emFAST_SZLEVEL2==m_makettype)
			{
				nTagID = lpFieldTempl->field_id;
			}
			if( 0 == nTagID )
			{
				return 0;
			}
			FastGroup* lpGroup = lpRecord->SetGroup (nTagID) ;

			///增加市场判断
			if (emFAST_SHLEVEL2 ==m_makettype)
			{
				ret_size = DecodeSequenceSH (lpGroup, lpFastData + curr_size, nDataLen - curr_size, lpFieldTempl->seq_ptr) ;
			}
			else if (emFAST_SZLEVEL2 ==m_makettype)
			{
				ret_size = DecodeSequenceSZ (lpGroup, lpFastData + curr_size, nDataLen - curr_size, lpFieldTempl) ;
			}
			curr_size += ret_size ;
		}
		else
		{
			//decode normal field
			ret_size = DecodeNormalField (lpFastData + curr_size, lpMsgTempl, pmap, i, fast_val) ;
			if (fast_val.field_type != FFT_Null_Type
				&& lpFieldTempl->field_id!=35
				&& SetFastValRecord (lpRecord, lpFieldTempl->field_id, fast_val) == -1)
			{  
				this->m_bHasError = true ;
				::snprintf (this->m_strError, sizeof (this->m_strError)-1,
					"Decode FastData Error: set fast_value error, template[%s-%d] field_id[%d].",
					lpMsgTempl->templ_name, lpMsgTempl->templ_id, lpFieldTempl->field_id) ;
				return 0 ;
			}
			curr_size += ret_size ;
		}
	}
	nOffset = curr_size;
	return lpMsgTempl ;
}

// 

size_t 
Fast_Decoder_Impl::DecodeSequenceCount (const char* lpFastData, uint32& nCount, const Fast_Presence& pres)
{
  Fast_Value fast_val ;
  nCount = 0 ;
  size_t size = DecodeInt32 (lpFastData, pres, fast_val) ;
  if( size>0 )
    nCount = fast_val.val.l4 ;
  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeSequenceSH (FastGroup *lpGroup, const char* lpFastData, size_t nDataLen, FastMsg_Templ* lpMsgTempl)
{
  PMAP seq_pmap ;
  size_t curr_size = 0 ;
  uint32 seq_count = 0 ;
  memset (seq_pmap, 0, sizeof(PMAP)) ;
  curr_size += DecodeSequenceCount (lpFastData, seq_count, lpMsgTempl->field_array[0]->field_pres) ;

  Fast_Value  fast_val ;
  for (size_t i=0; i<seq_count; ++i)
  {
    Fast_Record_Impl* lpRecord = lpGroup->AddRecord () ;
    if (lpMsgTempl->slot_count > 0)
      curr_size += DecodePMAP (lpFastData + curr_size, nDataLen - curr_size, seq_pmap) ;
    for (uint32 j=1; j<lpMsgTempl->field_count; ++j)
    {
      Fast_TemplField *lpFieldTempl = lpMsgTempl->field_array[j] ;
      if (FFT_Sequence == lpFieldTempl->field_type)
      {
        int nTagID = lpFieldTempl->seq_ptr->field_array[0]->field_id ;
        FastGroup* lpGroup = lpRecord->SetGroup (nTagID) ;
        curr_size += DecodeSequenceSH (lpGroup, 
	                                   lpFastData + curr_size, 
                                     nDataLen - curr_size, 
                                     lpFieldTempl->seq_ptr) ;
      }
      else
      {
        if( IsExistInSeq (lpMsgTempl, seq_pmap, j) )
        {
          fast_val.field_type = lpFieldTempl->field_type ;
          fast_val.decimal_place = lpFieldTempl->decimal_place ;
          curr_size += DecodeFieldValue (lpFastData + curr_size, fast_val, lpFieldTempl->field_pres) ;
          if( fast_val.field_type==lpFieldTempl->field_type )
          {
            SetFastValRecord (lpRecord, lpFieldTempl->field_id, fast_val) ;
            memcpy(&lpFieldTempl->field_curval, &fast_val, sizeof(Fast_Value)) ;
          }
        }
      }
    } // for
  } // for
  return curr_size ;
}

//2013-01-04 tangmc 将上海深圳分开
size_t 
	Fast_Decoder_Impl::DecodeSequenceSZ (FastGroup* lpGroup, const char* lpFastData, size_t nDataLen, Fast_TemplField *lpField/*FastMsg_Templ* lpMsgTempl*/)
{
	FastMsg_Templ* lpMsgTempl = lpField->seq_ptr;
	PMAP seq_pmap ;
	size_t curr_size = 0 ;
	uint32 seq_count = 0 ;
	memset (seq_pmap, 0, sizeof(PMAP)) ;
	
	curr_size += DecodeSequenceCount(lpFastData, seq_count, lpField->field_pres) ;

	Fast_Value  fast_val ;
	for (size_t i=0; i<seq_count; ++i)
	{
		Fast_Record_Impl* lpRecord = NULL;
		if (lpGroup)
		{
			lpRecord = lpGroup->AddRecord() ;
		}
		if (lpMsgTempl->slot_count > 0)
			curr_size += DecodePMAP (lpFastData + curr_size, nDataLen - curr_size, seq_pmap) ;
		for (uint32 j=0; j<lpMsgTempl->field_count; ++j)
		{
			Fast_TemplField *lpFieldTempl = lpMsgTempl->field_array[j] ;
			if (FFT_Sequence == lpFieldTempl->field_type)
			{
				uint32 nTagID = lpFieldTempl->field_id ;
				if( nTagID==0 )
				{
					printf("转换Sequence错误,SequenceID无法获得,模板:%s-%d NAME:%s-%d\n",
						lpMsgTempl->templ_name, lpMsgTempl->templ_id ,
						lpFieldTempl->field_name, 
						lpFieldTempl->seq_ptr->field_array[0]->field_id) ;
				}
				FastGroup* lpSecGroup = NULL;
				if (lpRecord)
				{
					lpSecGroup = lpRecord->SetGroup (nTagID) ;
				}
				curr_size += DecodeSequenceSZ (lpSecGroup, 
					lpFastData + curr_size, nDataLen - curr_size, lpFieldTempl) ;
			}
			else
			{
				if( IsExistInSeq (lpMsgTempl, seq_pmap, j) )
				{
					fast_val.field_type = lpFieldTempl->field_type ;
					fast_val.decimal_place = lpFieldTempl->decimal_place ;
					curr_size += DecodeFieldValue (lpFastData + curr_size, fast_val, lpFieldTempl->field_pres) ;
					if( fast_val.field_type==lpFieldTempl->field_type )
					{
						if (lpRecord)
						{
							SetFastValRecord (lpRecord, lpFieldTempl->field_id, fast_val) ;
						}
						memcpy(&lpFieldTempl->field_curval, &fast_val, sizeof(Fast_Value)) ;
					}
				}
			
				/// 如果pmap表示不存在
				else if (lpFieldTempl->field_op == OP_Copy) // 目前只处理
				{
					memcpy(&fast_val, &lpFieldTempl->field_curval, sizeof(Fast_Value));
				}
				else // 其它情况记日志
				{
					//			PUB_WRITE_LOG(PUB_LOG_FATAL, "未处理的分支: pmap表示该字段在数据流中不存在, 也无其它处理. 字段名称 = %s, 字段编号 = %d, 操作类型 = %d", lpFieldTempl->field_name, lpFieldTempl->field_id, lpFieldTempl->field_op);
				}
				
				// 		printf("%20s = %s\n", lpFieldTempl->field_name, fast_val.toString().c_str());
			}
		} // for
	} // for
	return curr_size ;
}


int 
Fast_Decoder_Impl::SetFastValRecord (Fast_Record_Impl* lpRecord, uint32& nID, const Fast_Value& fast_val)
{
  switch( fast_val.field_type )
  {
  case FFT_Int32:
  case FFT_UInt32:
    lpRecord->SetInt32 (nID, fast_val.val.l4) ;
    return 0 ;
    break ;
  case FFT_Int64:
  case FFT_UInt64:
    lpRecord->SetInt64 (nID, fast_val.val.l8) ;
    return 0 ;
    break ;
  case FFT_String:
    lpRecord->SetString (nID, fast_val.val.str) ;
    return 0 ;
    break ;
  case FFT_UString:
	  lpRecord->SetString (nID, fast_val.val.str) ;
	  return 0 ;
	  break ;
  default:
    return 0 ;
    break ;
  }
}

size_t 
Fast_Decoder_Impl::DecodePMAP (const char* lpData, size_t nDataLen, PMAP pmap)
{
  size_t size = 0 ;
  size = DecodeBytes (lpData, (char *)pmap, (FAST_PMAPSIZE > nDataLen)?nDataLen:FAST_PMAPSIZE) ;
  char tmp_byte ;

  for(size_t i=0; i<size; ++i)
  {
    if( size==(i+1) )
    {
      pmap[i] = static_cast<char>(pmap[i]<<(i+1)) ;
      break ;
    }
    pmap[i]  = static_cast<char>(pmap[i]<<(i+1)) ;
    tmp_byte = pmap[i+1] ;
    tmp_byte = static_cast<char>(tmp_byte>>(6-i)) ;
    pmap[i]  = pmap[i] | tmp_byte ;
  }
  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeFastType (const char* lpData, uint32& nMsgType)
{
  Fast_Value fast_value ;
  ///2014-02-18 tangmc 增加市场判断
  if (emFAST_SHLEVEL2 ==m_makettype)
  {
	  fast_value.field_type = FFT_Int32 ;
  }
  else if (emFAST_SZLEVEL2 ==m_makettype)
  {
	  // 2014-02-18 tangmc
	  //   fast_value.field_type = FFT_Int32 ;
	  fast_value.field_type = FFT_UInt32 ;
	  // 2014-02-18 tangmc
  }
  
  size_t size = DecodeInt32 (lpData, PRES_Mandatory, fast_value) ;
  nMsgType = static_cast<uint32> (fast_value.val.l4) ;
  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeBytes (const char* lpData, char* lpBuf, size_t nDataLen)
{
  for(size_t i=0; i<nDataLen; ++i)
  {
    if (static_cast<unsigned char>(lpData[i]) >= 0x80)
    {
      lpBuf[i] = lpData[i] & 0x7F ;
      return i+1 ;
    }
    else
      lpBuf[i] = lpData[i] ;
  }
  return 0 ;
}

size_t 
Fast_Decoder_Impl::DecodeInt32 (const char* lpData, Fast_Presence pres, Fast_Value& fast_val)
{
  char b[5] ;
  char sign_mask = 0x00 ;
  if (fast_val.field_type == FFT_Int32)
    sign_mask = 0x40 ;
  size_t size = DecodeBytes (lpData, b, 5) ;
  if( size>0 )
  {
    if (b[0] & sign_mask)
      fast_val.val.l4 = -1 ;
    else
      fast_val.val.l4 = 0  ;

    for (size_t i=0; i<size; ++i)
      fast_val.val.l4 = (fast_val.val.l4<<7) | b[i] ;

    if( PRES_Optional==pres )
    {
      if (fast_val.val.l4 > 0)
        --fast_val.val.l4 ;
      else if (fast_val.val.l4 == 0)
        fast_val.field_type = FFT_Null_Type ;
    }
  }

  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeInt64 (const char* lpData, Fast_Presence pres, Fast_Value& fast_val)
{
  char b[12] ;
  char sign_mask = 0x00 ;
  if (fast_val.field_type == FFT_Int64)
    sign_mask = 0x04 ;
  size_t size = DecodeBytes(lpData, b, 10) ;
  if (size > 0)
  {
    if (b[0] & sign_mask)
      fast_val.val.l8 = -1 ;
    else
      fast_val.val.l8 = 0  ;

    for (size_t i=0; i<size; ++i)
      fast_val.val.l8 = (fast_val.val.l8<<7) | b[i] ;

    if (PRES_Optional == pres)
    {
      if (fast_val.val.l8 > 0)
        --fast_val.val.l8 ;
      else if (fast_val.val.l8 == 0)
        fast_val.field_type = FFT_Null_Type ;
    }
  }

  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeString (const char* lpData, Fast_Presence pres, Fast_Value& fast_val)
{
  char b[FAST_MAXSTRINGLEN] ;
  size_t size = DecodeBytes (lpData, b, FAST_MAXSTRINGLEN) ;
  if (size > 0)
  {
    memcpy(fast_val.val.str, b, size) ;
    fast_val.val.str[size] = 0 ;
    if (PRES_Optional == pres)
    {
      if ( 1==size 
        && fast_val.val.str[0]==0 )
	fast_val.field_type = FFT_Null_Type ;
    }
  }

  return size ;
}

size_t Fast_Decoder_Impl::DecodeUString(const char *lpData, Fast_Presence pres, Fast_Value &fast_val)
{
	uint32 nLen = 0;
	size_t nRead = DecodeUStringLength(lpData, nLen,pres);
	memcpy(fast_val.val.str, lpData + nRead, nLen);
	fast_val.val.str[nLen] = 0;
	return nRead + nLen;
}

size_t Fast_Decoder_Impl::DecodeUStringLength(const char *lpData, uint32 &nLen, Fast_Presence pres)
{
	/// 这2个函数毫无关系, 只是借用它的实现
	//return DecodeFastType(lpData, nLen); //会导致如果是可选的就会出错 tangmc 20141126 

	Fast_Value fast_value ;
	if (emFAST_SHLEVEL2 ==m_makettype)
	{
		fast_value.field_type = FFT_Int32 ;
	}
	else if (emFAST_SZLEVEL2 ==m_makettype)
	{
		fast_value.field_type = FFT_UInt32 ;
	}

	size_t size = DecodeInt32 (lpData, pres, fast_value) ;
	nLen = static_cast<uint32> (fast_value.val.l4) ;
	return size ;
}


int 
Fast_Decoder_Impl::GetPMAPBit (const PMAP pmap, uint32 loc)
{
  int byte_loc = loc/8 ;
  int bit_loc  = loc%8 ;
  if (byte_loc > FAST_PMAPSIZE || byte_loc < 0)
    return -1 ;
  char b = pmap[byte_loc] ;
  if (b>>(7-bit_loc) & 1)
    return 1 ;
  else
    return 0 ;
}

bool 
Fast_Decoder_Impl::IsExistField (const FastMsg_Templ* lpMsgTempl, const  PMAP pmap, uint32 pos)
{
  if (OP_Constant == lpMsgTempl->field_array[pos]->field_op)
    return false ;
  if (-1 == lpMsgTempl->field_array[pos]->field_slot)
    return true  ;
  int bit_val = GetPMAPBit (pmap, lpMsgTempl->field_array[pos]->field_slot + 1) ;
  return (bit_val == 1)?true:false ;
}

bool 
Fast_Decoder_Impl::IsExistInSeq (const FastMsg_Templ* lpMsgTempl, const  PMAP pmap, uint32 pos)
{
  if (OP_Constant == lpMsgTempl->field_array[pos]->field_op)
    return false ;
  if (-1 == lpMsgTempl->field_array[pos]->field_slot)
    return true  ;
  int bit_val = GetPMAPBit (pmap, lpMsgTempl->field_array[pos]->field_slot) ;
  return (bit_val == 1)?true:false ;
}

size_t 
Fast_Decoder_Impl::DecodeNormalField (const char* lpData, const FastMsg_Templ* lpMsgTempl, 
                                   const PMAP pmap, uint32 pos, Fast_Value &fast_val)
{
  Fast_TemplField* lpFieldTempl = lpMsgTempl->field_array[pos] ;
  fast_val.field_type = lpFieldTempl->field_type ;
  bool bIsExist = IsExistField (lpMsgTempl, pmap, pos) ;
  size_t size = 0 ;
  if (bIsExist)
  {
    fast_val.decimal_place = lpFieldTempl->decimal_place ;
    size = DecodeFieldValue (lpData, fast_val, lpFieldTempl->field_pres) ;
    if (size == 0)
      printf("无法解析字段:TEMPL_NAME:%s [%s %d] slot:%d\n",
             lpMsgTempl->templ_name ,
             lpFieldTempl->field_name, lpFieldTempl->field_id, lpFieldTempl->field_slot) ;

	else if (fast_val.field_type == lpFieldTempl->field_type)
	{
		///2014-02-18 tangmc 增加市场判断
		if (emFAST_SHLEVEL2 ==m_makettype)
		{
			memcpy(&lpFieldTempl->field_curval, &fast_val, sizeof(Fast_Value)) ;
		}
		else if (emFAST_SZLEVEL2 ==m_makettype)
		{
			// 2014-02-18 tangmc 修改
			if (lpFieldTempl->IsAssignedCurrentValue()  &&  lpFieldTempl->field_op == OP_Delta  &&  (lpFieldTempl->field_type==FFT_Int32 || lpFieldTempl->field_type==FFT_UInt32 || lpFieldTempl->field_type==FFT_Int64 || lpFieldTempl->field_type==FFT_UInt64))
			{
				if (lpFieldTempl->field_type==FFT_Int32 || lpFieldTempl->field_type==FFT_UInt32)
				{
					lpFieldTempl->field_curval.val.l4 += fast_val.val.l4;
				}
				else if (lpFieldTempl->field_type==FFT_Int64 || lpFieldTempl->field_type==FFT_UInt64)
				{
					lpFieldTempl->field_curval.val.l8 += fast_val.val.l8;
				}
				memcpy(&fast_val, &lpFieldTempl->field_curval, sizeof(Fast_Value));
			}
			else
			{
				memcpy(&lpFieldTempl->field_curval, &fast_val, sizeof(Fast_Value)) ;
			}
			//2014-02-18 tangmc 修改
		}
	}
	else if (fast_val.field_type == FFT_Null_Type && emFAST_SZLEVEL2 ==m_makettype)//2014-02-18 tangmc 增加判断条件
	{
		if (lpFieldTempl->field_op == OP_Copy  &&  lpFieldTempl->IsAssignedCurrentValue())
		{
			lpFieldTempl->ResetCurrentValue();
		}
	}
  }
	
  if (!bIsExist 
    || fast_val.field_type==FFT_Null_Type )
  {
    switch (lpFieldTempl->field_op)
    {
    case OP_Constant:
    {
      if (lpFieldTempl->field_slot > 0)
        fast_val.field_type = FFT_Null_Type ;
      else
        memcpy(&fast_val, &lpFieldTempl->field_opval, sizeof(Fast_Value)) ;
      break ;
    }
    case OP_Copy:
    {
		///2014-02-18 tangmc 增加市场判断
		if (emFAST_SHLEVEL2 ==m_makettype)
		{
			memcpy(&fast_val, &lpFieldTempl->field_curval, sizeof(Fast_Value)) ;
		}
		else if (emFAST_SZLEVEL2 ==m_makettype)
		{
			if (!bIsExist)
			{
				if (lpFieldTempl->IsAssignedCurrentValue())
				{
					memcpy(&fast_val, &lpFieldTempl->field_curval, sizeof(Fast_Value));
				}
				else if (lpFieldTempl->field_opval.IsAssigned())
				{
					memcpy(&fast_val, &lpFieldTempl->field_opval, sizeof(Fast_Value));
				}
				else
				{
					fast_val.field_type = FFT_Null_Type;
				}
			}
		}
      break ;
    }
    case OP_Increment:
    {
      if (FFT_Int32 == lpFieldTempl->field_curval.field_type
       || lpFieldTempl->field_curval.field_type == FFT_UInt32)
       ++lpFieldTempl->field_curval.val.l4 ;
      else if (FFT_Int64 == lpFieldTempl->field_curval.field_type
       || lpFieldTempl->field_curval.field_type == FFT_UInt64)
       ++lpFieldTempl->field_curval.val.l8 ;
      else
      {
        fast_val.field_type = FFT_Null_Type ;
        break ;
      }
      memcpy(&fast_val, &lpFieldTempl->field_curval, sizeof(Fast_Value)) ;
      break ;
    }
    case OP_Default:
    {
	  ///2014-02-18 tangmc 增加市场判断
	  if (emFAST_SHLEVEL2 ==m_makettype)
	  {
		  fast_val.field_type = FFT_Null_Type ;
		  //memcpy(&fast_val, &lpFieldTempl->field_opval, sizeof(Fast_Value)) ;
	  }
	  else if (emFAST_SZLEVEL2 ==m_makettype)
	  {
		  // 2014-02-18 注释上面2句, 改成如下形式
		  //fast_val.field_type = FFT_Null_Type ;
		  if (lpFieldTempl->field_type == FFT_Int32  ||  lpFieldTempl->field_type == FFT_UInt32)
		  {
			  fast_val.val.l4 = lpFieldTempl->field_opval.val.l4;
		  }
		  else
		  {
			  memcpy(&fast_val, &lpFieldTempl->field_opval, sizeof(Fast_Value)) ;
		  }
	  }
      break ;
    }
    default:
      fast_val.field_type = FFT_Null_Type ;
      break ;
    }
  }
  return size ;
}

size_t 
Fast_Decoder_Impl::DecodeFieldValue (const char* lpData, Fast_Value& fast_val, Fast_Presence pres)
{
  size_t size = 0 ;
  switch (fast_val.field_type)
  {
  case FFT_Int32:
  case FFT_UInt32:
    size = DecodeInt32(lpData, pres, fast_val) ;
    break ;
  case FFT_Int64:
  case FFT_UInt64:
    size = DecodeInt64(lpData, pres, fast_val) ;
    break ;
  case FFT_String:
    size = DecodeString(lpData, pres, fast_val) ;
    break ;
  case FFT_UString:
	  size = DecodeUString(lpData, pres, fast_val);
	  {
		  // 目前只在股票名称中用到, 因此转换编码 utf-8 ---> gbk
		  std::string strGBK = UTF8_To_GBK(fast_val.val.str);
		  strncpy(fast_val.val.str, strGBK.c_str(), sizeof fast_val.val.str);
	  }
	  break;
  default:
    printf("DecodeFieldValue错误:类型不可知") ;
    break ;
  }
  return size ;
}

std::string Fast_Decoder_Impl::get_step_field_value(const char *buf, int len, const std::string &field_name)
{
	const char *begin = strstr(buf, field_name.c_str());
	if (!begin)
	{
		return "";
	}

	begin += field_name.size();
	if (begin  >=  (buf + len))
	{
		return "";
	}

	const char *end = begin;
	for (; end  <  (buf + len); end++)
	{
		if (*end == STEP_FIELD_DELIM)
		{
			break;
		}
	}
	if (*end == STEP_FIELD_DELIM)
	{
		return std::string (begin, end - begin);
	}
	else
	{
		return "";
	}
}

std::string Fast_Decoder_Impl::UTF8_To_GBK(const std::string& utf8_str)
{
#ifdef _WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)utf8_str.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP,0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
#else
	iconv_t  cd ;

	cd = iconv_open("GBK", "UTF-8") ;
	if( cd==0 )
	{
		printf("iconv_open失败 UTF8->GBK\n") ;
		return "" ;
	}

	size_t in_size = utf8_str.size() ;
	char  *utf8_buf = new char[in_size+1] ;
	memset(utf8_buf, 0, in_size+1) ;
	memcpy(utf8_buf, utf8_str.c_str(), in_size) ;

	size_t out_size = in_size*2 ;
	char  *gbk_buf = new char[out_size] ;
	memset(gbk_buf, 0, out_size) ;

	char  *in_p    = utf8_buf ;
	char *out_p    = gbk_buf  ;
	char **in_buf  = &in_p    ;
	char **out_buf = &out_p   ;

	if( (size_t)-1 == iconv(cd, in_buf, &in_size, out_buf, &out_size) )
	{
		printf("iconv失败\n") ;
		delete [] utf8_buf ;
		delete [] gbk_buf  ;
		iconv_close( cd ) ;
		return "" ;
	}

	std::string gbk_ret(gbk_buf) ;
	delete [] utf8_buf ;
	delete [] gbk_buf  ;
	iconv_close( cd ) ;
	return gbk_ret ;
#endif
}
