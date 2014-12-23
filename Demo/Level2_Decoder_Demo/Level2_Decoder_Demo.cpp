#include "Level2_Decoder_Demo.h"
#include "SH_Level2_Tag.h"
#include "SZ_Level2_Tag.h"

Level2_Decoder_Demo::Level2_Decoder_Demo(FAST_TYPE ft,char * lpFile):
m_Recv(NULL),
	m_lock(NULL),
	m_lpFile(NULL),
	m_Decoder(NULL)
{
	m_ft=ft;
	m_lpFile=lpFile;


}
Level2_Decoder_Demo::~Level2_Decoder_Demo()
{

	if (m_Recv!=NULL)
	{
		delete m_Recv;
	}

	if (m_lock!=NULL)
	{
		delete m_lock;
	}
	m_Decoder->Release();
}

#ifdef _WIN32
typedef void* (* PF_FUNC) () ;
#endif
int Level2_Decoder_Demo::Init()
{
	IDecoder_Factory* lpFactory = GetDecoderFactoryInstance();
	//解释工厂
	//从解释工厂得到解释器
	m_Decoder = lpFactory->GetFastDecoder (m_ft) ; 
	if (!m_Decoder)
	{
		return -1;
	}

	m_Recv=new(std::nothrow) L2_Receiver(this);
	if (!m_Recv)
	{
		return -1;
	}
	m_lock=new Lock();

	
	//加载模板
	return m_Decoder->LoadTemplate(m_lpFile);
}
int Level2_Decoder_Demo::ConnectServer(int port,char *ip)
{
	if(m_Recv->Connect(port,ip)!=0)
	{
		return -1;
	}
	return 0;
	
}

#ifdef _WIN32
DWORD WINAPI Level2_Decoder_Demo::Deal(void* lpParamter)
#else
void* Level2_Decoder_Demo::Deal(void* lpParamter)
#endif
{
	Level2_Decoder_Demo *L2Decoder=(Level2_Decoder_Demo*)lpParamter;

	while (1)
	{
		L2_Data_Tag *buff = L2Decoder->Pop();
		if (buff == NULL)
		{
#ifdef _WIN32
			Sleep(10);
#else
			usleep(10*1000);
#endif
			continue;
		}
		if (L2Decoder->m_ft==emFAST_SHLEVEL2)
		{
			L2Decoder->Deal_SH_Level2_Data(buff->buff,buff->lenth);
		}
		else
		{
			L2Decoder->Deal_SZ_Level2_Data(buff->buff,buff->lenth);
		}

		delete buff;
	}

#ifdef _WIN32
	return 0;
#endif
	
}


void Level2_Decoder_Demo::Start()
{
#ifdef _WIN32
	hThread = CreateThread(NULL, 0,Deal, this, 0, NULL);
	CloseHandle(hThread);
	m_Recv->Start();
#else
	int i,ret;
	ret=pthread_create(&hThread,NULL,Deal,this);
	if(ret!=0){
		printf ("Create thread error!\n");
		exit (1);
	}
	m_Recv->Start();
	pthread_join(hThread,NULL);
#endif
}
void Level2_Decoder_Demo::Push(L2_Data_Tag &buff)
{
	AutoLock aulock(m_lock);
	//m_L2Data.push_back(buff);
	this->m_ReadBuff.AddData(buff.buff,buff.lenth);
}

Level2_Decoder_Demo::L2_Data_Tag* Level2_Decoder_Demo::Pop()
{
	AutoLock aulock(m_lock);
	/*if(m_L2Data.size()>0)
	{
		L2_Data_Tag *buff=m_L2Data[0];
		m_L2Data.pop_front();
		return buff;
	}*/
	FastMsgInfo refMsgInfo;
	if (0==GetOneFastMessage(refMsgInfo))
	{
		int length=refMsgInfo.nMsgLen;
		L2_Data_Tag *data=new L2_Data_Tag();
		data->buff=new char[length];
		memcpy(data->buff,refMsgInfo.lpMsgData,length);
		data->lenth=length;
		return data;
	}

	return NULL;
}

int Level2_Decoder_Demo::GetOneFastMessage (FastMsgInfo& refMsgInfo) 
{
	int nRet = this->GetFastMsgInfo (this->m_ReadBuff.GetReadData (), 
		this->m_ReadBuff.GetBuffSize (), 
		refMsgInfo) ;
	if (nRet <= 0)
	{
		return -1;
	}
	this->m_ReadBuff.MoveRead (nRet) ;
	return 0 ;
}

int Level2_Decoder_Demo::GetFastMsgInfo (const char* lpData, int nLen, FastMsgInfo& refMsgInfo) 
{
	if (nLen < MIN_STEP_LEN)
		return 0 ;
	if (memcmp (lpData, STEP_HEADER_FLAG, STEP_HEADER_SIZE) != 0)
		return -1 ;

	// 获取FastMsg长度
	const char* lpStepLen = strstr (lpData, STEP_LEN_FLAG) ;
	if (!lpStepLen)
		return -1 ;
	lpStepLen += STEP_LEN_SIZE ;

	char bufTmp [20] ;
	int nPos = 0 ;
	while ((*lpStepLen) != STEP_FIELD_DELIM)
	{
		bufTmp [nPos] = *lpStepLen ;
		++nPos ;
		++lpStepLen ;

		if (nPos >= 20)
			return -1 ;
	}
	++lpStepLen ;
	bufTmp [nPos] = 0x00 ;
	refMsgInfo.nMsgLen = atoi(bufTmp) + (lpStepLen - lpData) + FAST_TAIL_LENGTH ;
	if (nLen < refMsgInfo.nMsgLen)
		return 0 ;
	refMsgInfo.lpMsgData = lpData ;

	// 获取消息类型
	const char* lpFastType = strstr (lpData, STEP_TYPE_FLAG) ;
	if (lpFastType)
	{
		lpFastType += STEP_TYPE_SIZE ;
		nPos = 0 ;
		while ((*lpFastType) != STEP_FIELD_DELIM)
		{
			bufTmp [nPos] = *lpFastType ;
			++nPos ;
			++lpFastType ;

			if (nPos >= 20)
				return -1 ;
		}
		bufTmp [nPos] = 0x00 ;
		refMsgInfo.strMsgType = bufTmp ;
	}

	// 消息序号
	const char* lpSeqNum = 0 ;

	if (emFAST_SHLEVEL2 ==m_ft)
	{
		lpSeqNum= strstr (lpData,STEP_MSGSEQID_FLAG) ;
		if (lpSeqNum)
		{
			lpSeqNum += STEP_MSGSEQID_SIZE ;
		}
	}
	else if (emFAST_SZLEVEL2==m_ft)
	{
		lpSeqNum= strstr (lpData, STEP_SEQUENCE_FLAG) ;
		if (lpSeqNum)
		{
			lpSeqNum += STEP_SEQUENCE_SIZE ;
		}
	}

	if (lpSeqNum)
	{
		//lpSeqNum += STEP_MSGSEQID_SIZE ;
		nPos = 0 ;
		while ((*lpSeqNum) != STEP_FIELD_DELIM)
		{
			bufTmp [nPos] = *lpSeqNum ;
			++nPos ;
			++lpSeqNum ;

			if (nPos >= 20)
				return -1 ;
		}
		bufTmp [nPos] = 0x00 ;
		refMsgInfo.nSeqNum = atoi (bufTmp) ;
	}

	// 时间戳
	const char* lpSendTime = strstr (lpData, STEP_SENDTIME_FLAG) ;
	if (lpSendTime)
	{
		lpSendTime += STEP_SENDTIME_SIZE ;
		nPos = 0 ;
		while ((*lpSendTime) != STEP_FIELD_DELIM)
		{
			bufTmp [nPos] = *lpSendTime ;
			++nPos ;
			++lpSendTime ;

			if (nPos >= 20)
				return -1 ;
		}
		bufTmp [nPos] = 0x00 ;

		bufTmp [8]  = 0x00 ;
		bufTmp [11] = 0x00 ;
		bufTmp [14] = 0x00 ;
		refMsgInfo.nDate = atoi (bufTmp) ;
		refMsgInfo.nTimeStamp = atoi (bufTmp + 9)*10000 + atoi (bufTmp + 12)*100 + atoi (bufTmp + 15) ;
	}

	return refMsgInfo.nMsgLen ;
}

void Level2_Decoder_Demo::Deal_SH_Level2_Data(char *buff,int length)
{
	//解释FAST数据 得到一个Fast_Message 消息
	IFast_Message *FastMsg=m_Decoder->Decode(buff,length);
	if (!FastMsg)
	{
		printf("出错解释FAST数据\n");
		printf("%s\n",m_Decoder->GetLastError());
		return;
	}
	const char * strType=FastMsg->GetMsgType();

	if( strType==0 )
	{
		FastMsg->Release();
		return;
	}
	else if (!strcmp (strType, "UA3201"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		/*std::cout<<"*************************************"<<std::endl ;
		std::cout<<"MsgType:"<<FastMsg->GetMsgType ()<<" SendTime:"<<FastMsg->GetSendTime ()
			<<" SeqNum:"<<FastMsg->GetSeqNum ()<<"RecordCount:"<<count<<std::endl ;*/
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SH_NGTSTransaction(Recoder);
		}
		//
	}
	else if (!strcmp (strType, "UA3202"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		/*std::cout<<"*************************************"<<std::endl ;
		std::cout<<"MsgType:"<<FastMsg->GetMsgType ()<<" SendTime:"<<FastMsg->GetSendTime ()
			<<" SeqNum:"<<FastMsg->GetSeqNum ()<<"RecordCount:"<<count<<std::endl ;*/
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SH_NGTSMarketData(Recoder);
		}
		//
	}
	else if (!strcmp (strType, "UA3113"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		/*std::cout<<"*************************************"<<std::endl ;
		std::cout<<"MsgType:"<<FastMsg->GetMsgType ()<<" SendTime:"<<FastMsg->GetSendTime ()
			<<" SeqNum:"<<FastMsg->GetSeqNum ()<<"RecordCount:"<<count<<std::endl ;*/
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SH_NGTSIndex(Recoder);
		}
		//
	}
	else if (!strcmp (strType, "UA3115"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SH_NGTSMarketOverview(Recoder);
		}
		//
	}
	else if (!strcmp (strType, "UA3107"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SH_NGTSVirtualAuctionPrice(Recoder);
		}
		//
	}
	FastMsg->Release();
}


void Level2_Decoder_Demo::Deal_SH_NGTSTransaction(IFast_Record *Record)
{
	//将逐笔成交中的每条记录取出来
	string str="";
	char c[25];
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	
	//nTagID 参照SH_Level2_Tag.h 对应的注释模板和宏 
	//SH_DataStatus 为ID 的宏定义

	str+="DataStatus:";
	temp_int32=Record->GetInt32(SH_DataStatus); //获取DataStatus
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  TradeIndex:";
	temp_int32=Record->GetInt32(SH_TradeIndex); //获取TradeIndex
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  TradeChannel:";
	temp_int32=Record->GetInt32(SH_TradeChannel); //获取TradeChannel
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  SecurityID:";
	temp=Record->GetString(SH_SecurityID);  //获取SecurityID
	str+=temp;

	str+="  TradeTime:";
	temp_int32=Record->GetInt32(SH_TradeTime); //获取TradeTime
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  TradePrice:";
	temp_int32=Record->GetInt32(SH_TradePrice); //获取TradePrice
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  TradeQty:";
	temp_int64=Record->GetInt64(SH_TradeQty); //获取TradeQty
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  TradeMoney:";
	temp_int64=Record->GetInt64(SH_TradeMoney); //获取TradeMoney
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	printf("Transaction:%s\n",str.c_str());
}
void Level2_Decoder_Demo::Deal_SH_NGTSMarketData(IFast_Record *Record)
{
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	//nTagID 参照SH_Level2_Tag.h 对应的注释模板和宏 
	//SH_DataTimestamp 为ID 的宏定义
	temp_int32=Record->GetInt32(SH_DataTimestamp); //获取DataTimestamp
	temp_int32=Record->GetInt32(SH_DataStatus); //获取DataStatus
	temp=Record->GetString(SH_SecurityID);  //获取SecurityID

	temp_int32=Record->GetInt32(SH_ImageStatus); //获取ImageStatus
	temp_int32=Record->GetInt32(SH_PreClosePx); //获取PreClosePx
	temp_int32=Record->GetInt32(SH_OpenPx);     //获取OpenPx
	temp_int32=Record->GetInt32(SH_HighPx);     //获取HighPx
	temp_int32=Record->GetInt32(SH_LowPx);      //获取LowPx
	temp_int32=Record->GetInt32(SH_LastPx);     //获取LastPx
	temp_int32=Record->GetInt32(SH_ClosePx);    //获取ClosePx
	temp=Record->GetString(SH_InstrumentStatus);  //获取InstrumentStatus
	temp_int32=Record->GetInt32(SH_NumTrades);    //获取NumTrades

	temp_int64=Record->GetInt64(SH_TotalVolumeTrade); //获取TotalVolumeTrade
	temp_int64=Record->GetInt64(SH_TotalValueTrade);  //获取TotalValueTrade
	temp_int64=Record->GetInt64(SH_TotalBidQty);      //获取TotalBidQty
	temp_int32=Record->GetInt32(SH_WeightedAvgBidPx);    //获取WeightedAvgBidPx
	temp_int32=Record->GetInt32(SH_AltWeightedAvgBidPx);    //获取AltWeightedAvgBidPx
	temp_int64=Record->GetInt64(SH_TotalOfferQty);      //获取TotalOfferQty

	temp_int32=Record->GetInt32(SH_WeightedAvgOfferPx); //获取WeightedAvgOfferPx
	temp_int32=Record->GetInt32(SH_AltWeightedAvgOfferPx); //获取AltWeightedAvgOfferPx
	temp_int32=Record->GetInt32(SH_IOPV);     //获取IOPV
	temp_int32=Record->GetInt32(SH_YieldToMaturity);     //获取YieldToMaturity

	temp_int64=Record->GetInt64(SH_TotalWarrantExecQty); //获取TotalWarrantExecQty
	temp_int64=Record->GetInt64(SH_WarLowerPx);  //获取WarLowerPx
	temp_int64=Record->GetInt64(SH_WarUpperPx);      //获取WarUpperPx

	int subCount1=Record->GetSubCount(SH_NoBidLevel);
	for (int i=0;i<subCount1;i++)
	{
		IFast_Record *subRecord=Record->GetSubRecord(SH_NoBidLevel,i);
		if (!subRecord)
		{
			return;
		}
		temp_int32=subRecord->GetInt32(SH_PriceLeveOperator);     //获取PriceLeveOperator
		temp_int32=subRecord->GetInt32(SH_Price);     //获取Price
		temp_int64=subRecord->GetInt64(SH_OrderQty); //获取OrderQty
		temp_int32=subRecord->GetInt32(SH_NumOrders);     //获取NumOrders

		int tsubCount=subRecord->GetSubCount(SH_Orders);
		for (int j=0;j<tsubCount;j++)
		{
			IFast_Record *tsubRecord=subRecord->GetSubRecord(SH_Orders,j);
			if (!tsubRecord)
			{
				return;
			}
			temp_int32=tsubRecord->GetInt32(SH_OrderQueueOperator);     //获取OrderQueueOperator
			temp_int32=tsubRecord->GetInt32(SH_OrderQueueOperatorEntryID);     //获取OrderQueueOperatorEntryID
			temp_int64=tsubRecord->GetInt64(SH_SubOrderQty); //获取SubOrderQty
		}
	}

	int subCount2=Record->GetSubCount(SH_NoOfferLevel);
	for (int i=0;i<subCount2;i++)
	{
		IFast_Record *subRecord=Record->GetSubRecord(SH_NoBidLevel,i);
		if (!subRecord)
		{
			return;
		}
		temp_int32=subRecord->GetInt32(SH_PriceLeveOperator);     //获取PriceLeveOperator
		temp_int32=subRecord->GetInt32(SH_Price);     //获取Price
		temp_int64=subRecord->GetInt64(SH_OrderQty); //获取OrderQty
		temp_int32=subRecord->GetInt32(SH_NumOrders);     //获取NumOrders

		int tsubCount=subRecord->GetSubCount(SH_Orders);
		for (int j=0;j<tsubCount;j++)
		{
			IFast_Record *tsubRecord=subRecord->GetSubRecord(SH_Orders,j);
			if (!tsubRecord)
			{
				return;
			}
			temp_int32=tsubRecord->GetInt32(SH_OrderQueueOperator);     //获取OrderQueueOperator
			temp_int32=tsubRecord->GetInt32(SH_OrderQueueOperatorEntryID);     //获取OrderQueueOperatorEntryID
			temp_int64=tsubRecord->GetInt64(SH_SubOrderQty); //获取SubOrderQty
		}
	}
	
}
void Level2_Decoder_Demo::Deal_SH_NGTSIndex(IFast_Record *Record)
{
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	//nTagID 参照SH_Level2_Tag.h 对应的注释模板和宏 
	//SH_DataTimestamp 为ID 的宏定义
	temp_int32=Record->GetInt32(SH_DataTimestamp); //获取DataTimestamp
	temp_int32=Record->GetInt32(SH_DataStatus); //获取DataStatus
	temp=Record->GetString(SH_SecurityID);  //获取SecurityID

	temp_int64=Record->GetInt64(SH_PreCloseIndex); //获取PreCloseIndex
	temp_int64=Record->GetInt64(SH_OpenIndex);     //获取OpenIndex
	temp_int64=Record->GetInt64(SH_Turnover);      //获取Turnover
	temp_int64=Record->GetInt64(SH_HighIndex);    //获取HighIndex
	temp_int64=Record->GetInt64(SH_LowIndex);     //获取LowIndex
	temp_int64=Record->GetInt64(SH_LastIndex);      //获取LastIndex
	temp_int32=Record->GetInt32(SH_TradeTime);    //获取TradeTime
	temp_int64=Record->GetInt64(SH_TotalVolumeTrade); //获取TotalVolumeTrade
	temp_int64=Record->GetInt64(SH_CloseIndex);  //获取CloseIndex
}

void Level2_Decoder_Demo::Deal_SH_NGTSMarketOverview(IFast_Record *Record)
{

}
void Level2_Decoder_Demo::Deal_SH_NGTSVirtualAuctionPrice(IFast_Record *Record)
{

}



void Level2_Decoder_Demo::Deal_SZ_Level2_Data(char *buff,int length)
{
	IFast_Message *FastMsg=m_Decoder->Decode(buff,length);
	if (!FastMsg)
	{
		printf("出错解释FAST数据\n");
		return;
	}

	const char * strType=FastMsg->GetMsgType();

	if (strType==0)
	{
		FastMsg->Release();
		return;
	}
	else if (!strcmp(strType, "UA101"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_StockInfo(Recoder);
		}
		//
	}
	else if (!strcmp(strType, "UA102"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_StockStatus(Recoder);
		}
		//
	}
	else if (!strcmp(strType, "UA103"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_Snapshot(Recoder);
		}
		//
	}
	else if (!strcmp(strType, "UA104"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_Index(Recoder);
		}
		//
	}
	else if (!strcmp(strType, "UA201"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_Order(Recoder);
		}
		//
	}
	else if (!strcmp(strType, "UA202"))
	{
		//得到FAST 消息里Record的数量
		int count=FastMsg->GetRecordCount();
		for (int i=0;i<count;i++)
		{
			//得到每一条Record
			IFast_Record *Recoder=FastMsg->GetRecord(i);
			if (!Recoder)
			{
				FastMsg->Release();
				return;
			}
			//处理Record
			Deal_SZ_Trade(Recoder);
		}
		//
	}
	FastMsg->Release();
}

void Level2_Decoder_Demo::Deal_SZ_StockInfo(IFast_Record *Record)
{
	const char * SecurityID=Record->GetString(SZ_SecurityID);                
	const char * Symbol=Record->GetString(SZ_Symbol);    
	const char * SecurityDesc=Record->GetString(SZ_SecurityDesc);            
}
void Level2_Decoder_Demo::Deal_SZ_StockStatus(IFast_Record *Record)
{

}
void Level2_Decoder_Demo::Deal_SZ_Snapshot(IFast_Record *Record)
{
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	//nTagID 参照SZ_Level2_Tag.h 对应的注释模板和宏 
	//SH_DataTimestamp 为ID 的宏定义
	temp_int32=Record->GetInt32(SZ_DataTimeStamp); //获取DataTimestamp
	
	temp=Record->GetString(SZ_SecurityID);  //获取SecurityID

	temp_int32=Record->GetInt32(SZ_PreClosePx); //获取PreClosePx
	temp_int32=Record->GetInt32(SZ_OpenPx);     //获取OpenPx
	temp_int32=Record->GetInt32(SZ_HighPx);     //获取HighPx
	temp_int32=Record->GetInt32(SZ_LowPx);      //获取LowPx
	temp_int32=Record->GetInt32(SZ_LastPx);     //获取LastPx

	temp_int64=Record->GetInt64(SZ_NumTrades);    //获取NumTrades

	temp_int64=Record->GetInt64(SZ_TotalVolumeTrade); //获取TotalVolumeTrade
	temp_int64=Record->GetInt64(SZ_TotalValueTrade);  //获取TotalValueTrade
	temp_int64=Record->GetInt64(SZ_TotalLongPosition);      //获取TotalLongPosition
	
	temp_int32=Record->GetInt32(SZ_PERatio1);    //获取PERatio1
	temp_int32=Record->GetInt32(SZ_PERatio2);    //获取PERatio2

	temp=Record->GetString(SZ_EndOfDayMaker);  //获取EndOfDayMaker

	temp_int64=Record->GetInt64(SZ_TotalOfferQty);      //获取TotalOfferQty
	temp_int64=Record->GetInt64(SZ_WeightedAvgOfferPx);      //获取WeightedAvgOfferPx


	int subCount1=Record->GetSubCount(SZ_OfferPriceLevel);
	for (int i=0;i<subCount1;i++)
	{
		IFast_Record *subRecord=Record->GetSubRecord(SZ_OfferPriceLevel,i);
		if (!subRecord)
		{
			return;
		}
		temp_int32=subRecord->GetInt32(SZ_OfferPx);     //获取Price
		temp_int64=subRecord->GetInt64(SZ_OfferSize); //获取OrderQty
		temp_int32=subRecord->GetInt32(SZ_NumOrders);     //获取NumOrders

		int tsubCount=subRecord->GetSubCount(SZ_Orders);
		for (int j=0;j<tsubCount;j++)
		{
			IFast_Record *tsubRecord=subRecord->GetSubRecord(SZ_Orders,j);
			if (!tsubRecord)
			{
				return;
			}
			temp_int32=tsubRecord->GetInt32(SZ_OrderQty);     //获取
		}
	}

	temp_int64=Record->GetInt64(SZ_TotalBidQty);      //获取TotalBidQty
	temp_int64=Record->GetInt64(SZ_WeightedAvgBidPx);      //获取WeightedAvgBidPx

	int subCount2=Record->GetSubCount(SZ_BidPriceLevel);
	for (int i=0;i<subCount2;i++)
	{
		IFast_Record *subRecord=Record->GetSubRecord(SZ_BidPriceLevel,i);
		if (!subRecord)
		{
			return;
		}
		temp_int32=subRecord->GetInt32(SZ_BidPx);     //获取Price
		temp_int64=subRecord->GetInt64(SZ_BidSize); //获取OrderQty
		temp_int32=subRecord->GetInt32(SZ_NumOrders);     //获取NumOrders

		int tsubCount=subRecord->GetSubCount(SZ_Orders);
		for (int j=0;j<tsubCount;j++)
		{
			IFast_Record *tsubRecord=subRecord->GetSubRecord(SZ_Orders,j);
			if (!tsubRecord)
			{
				return;
			}
			temp_int32=tsubRecord->GetInt32(SZ_OrderQty);     //获取
		}
	}
}

void Level2_Decoder_Demo::Deal_SZ_Index(IFast_Record *Record)
{
	//将逐笔成交中的每条记录取出来
	string str="";
	char c[25];
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	//nTagID 参照SZ_Level2_Tag.h 对应的注释模板和宏 
	str+="DataTimeStamp:";
	temp_int32=Record->GetInt32(SZ_DataTimeStamp); //获取DataTimeStamp
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  SecurityID:";
	temp=Record->GetString(SZ_SecurityID);  //获取SecurityID
	str+=temp;

	str+="  CloseIndex:";
	temp_int64=Record->GetInt64(SZ_CloseIndex); //获取CloseIndex
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  OpenIndex:";
	temp_int64=Record->GetInt64(SZ_OpenIndex); //获取OpenIndex
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  HighIndex:";
	temp_int64=Record->GetInt64(SZ_HighIndex); //获取HighIndex
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  LowIndex:";
	temp_int64=Record->GetInt64(SZ_LowIndex); //获取LowIndex
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  LastIndex:";
	temp_int64=Record->GetInt64(SZ_LastIndex); //获取LastIndex
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  TurnOver:";
	temp_int64=Record->GetInt64(SZ_TurnOver); //获取TurnOver
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  NumTrades:";
	temp_int64=Record->GetInt64(SZ_NumTrades); //获取NumTrades
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  TotalVolumeTrade:";
	temp_int64=Record->GetInt64(SZ_TotalVolumeTrade); //获取TotalVolumeTrade
	sprintf(c, "%llu", temp_int64); 
	str+=c;

	str+="  EndOfDayMaker:";
	temp=Record->GetString(SZ_EndOfDayMaker);  //获取EndOfDayMaker
	str+=temp;

	/*printf("Index:%s\n",str.c_str());*/

}
void Level2_Decoder_Demo::Deal_SZ_Order(IFast_Record *Record)
{
	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	temp_int32=Record->GetInt32(SZ_SetNo); //获取SetNo
	temp_int32=Record->GetInt32(SZ_RecNo); //获取RecNo
	temp=Record->GetString(SZ_SecurityID);  //获取SecurityID
	temp_int32=Record->GetInt32(SZ_Price); //获取Price

	temp_int32=Record->GetInt32(SZ_OrderQty); //获取OrderQty
	temp=Record->GetString(SZ_OrderKind);  //获取OrderKind
	temp=Record->GetString(SZ_FunctionCode);  //获取FunctionCode
	temp_int32=Record->GetInt32(SZ_OrderEntryTime); //获取OrderEntryTime
}
void Level2_Decoder_Demo::Deal_SZ_Trade(IFast_Record *Record)
{
	//将逐笔成交中的每条记录取出来
	string str="";
	char c[25];

	const char* temp;
	uint32 temp_int32=0;
	uint64 temp_int64=0;

	str+="SetNo:";
	temp_int32=Record->GetInt32(SZ_SetNo); //获取SetNo
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  RecNo:";
	temp_int32=Record->GetInt32(SZ_RecNo); //获取RecNo
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  BuyOrderRecNo:";
	temp_int32=Record->GetInt32(SZ_BuyOrderRecNo); //获取BuyOrderRecNo
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  SellOrderRecNo:";
	temp_int32=Record->GetInt32(SZ_SellOrderRecNo); //获取SellOrderRecNo
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  SecurityID:";
	temp=Record->GetString(SZ_SecurityID);  //获取SecurityID
	str+=temp;

	str+="  Price:";
	temp_int32=Record->GetInt32(SZ_Price); //获取Price
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  TradeQty:";
	temp_int32=Record->GetInt32(SZ_TradeQty); //获取TradeQty
	sprintf(c, "%u", temp_int32); 
	str+=c;

	str+="  OrderKind:";
	temp=Record->GetString(SZ_OrderKind);  //获取OrderKind
	str+=temp;

	str+="  FunctionCode:";
	temp=Record->GetString(SZ_FunctionCode);  //获取FunctionCode
	str+=temp;

	str+="  TradeTime:";
	temp_int32=Record->GetInt32(SZ_TradeTime); //获取TradeTime
	sprintf(c, "%u", temp_int32); 
	str+=c;

	printf("Trade:%s\n",str.c_str());
}


