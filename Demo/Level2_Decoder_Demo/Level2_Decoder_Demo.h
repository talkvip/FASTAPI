/******************************************************************
@源程序名称: Level2_Decoder_Demo.h
@软件著作权: 恒生电子股份有限公司 版权所有
@系统名称: 
@模块名称: 
@功能说明: Level2数据的转换示例
@相关文档: 
@作者:     
@审核: (可选的)

@修改记录
@修改日期: 2013-02-25
@修改人员: 唐模超
@修改说明: 创建
@版本：   1.0

*******************************************************************/
#ifndef _H_LEVEL2_DECODER_DEMO_H_
#define _H_LEVEL2_DECODER_DEMO_H_

#define  STEP_HEADER_FLAG                                  "8=STEP.1.0.0"
#define  STEP_HEADER_SIZE                                  12
#define  STEP_LEN_FLAG                                     "9="
#define  STEP_LEN_SIZE                                     2
#define  STEP_MSGSEQID_FLAG                                "10072="
#define  STEP_MSGSEQID_SIZE                                6
#define  STEP_TYPE_FLAG                                    "35="
#define  STEP_TYPE_SIZE                                    3
#define  STEP_SENDTIME_FLAG                                "52="
#define  STEP_SENDTIME_SIZE                                3
#define  STEP_SEQUENCE_FLAG                                "34="
#define  STEP_SEQUENCE_SIZE                                3
#define  FASTDATA_LEN_FLAG                                 "95="
#define  FASTDATA_LEN_SIZE                                 3
#define  FASTDATA_FLAG                                     "96="
#define  FASTDATA_SIZE                                     3
#define  FAST_TAIL_LENGTH                                  7

#define  MIN_STEP_LEN                                      30
#define  STEP_FIELD_DELIM                                  0x01

#include <iostream>
#include <fstream>
#include "L2_Receiver.h"
#include <vector>
#include <deque>
#include "Lock.h"
#include <Decoder_Factory.h>
#include <Basic_Types.h>
#include "DynBuffer.h"
#ifdef _WIN32 
#include <Windows.h>
typedef HANDLE L2_THREAD_HANDLE;
#else
#include <unistd.h> 
#include <pthread.h>
typedef     pthread_t L2_THREAD_HANDLE;
#endif

using namespace std;

class L2_Receiver;
class Level2_Decoder_Demo
{
public:
	struct L2_Data_Tag
	{
		char *buff;
		int lenth;
		~L2_Data_Tag()
		{
			if (buff)
			{
				delete[] buff;
			}
		}
	};
public:
	Level2_Decoder_Demo(FAST_TYPE ft,char * lpFile);
	~Level2_Decoder_Demo();
	int Init();
	int ConnectServer(int port,char *ip);
	void Start();
	void Push(L2_Data_Tag &buff);
	L2_Data_Tag * Pop();
	int GetOneFastMessage (FastMsgInfo& refMsgInfo) ;

#ifdef _WIN32
	static DWORD WINAPI Deal(void* lpParamter);
#else
	static void*Deal(void* lpParamter);
#endif

	/***************************************************
	@处理上海level2   FAST数据
	@
	****************************************************/
	void Deal_SH_Level2_Data(char *buff,int length);

	/***************************************************
	@处理上海level2  数据        (实现，当作DEMO)
	@逐笔成交
	****************************************************/
	void Deal_SH_NGTSTransaction(IFast_Record *Record);
	/***************************************************
	@处理上海level2  数据        (实现，当作DEMO)
	@行情快照
	****************************************************/
	void Deal_SH_NGTSMarketData(IFast_Record *Record);
	/***************************************************
	@处理上海level2  数据        (实现，当作DEMO)
	@指数行情消息
	****************************************************/
	void Deal_SH_NGTSIndex(IFast_Record *Record);

	/***************************************************
	@处理上海level2  数据        
	@市场概况消息
	****************************************************/
	void Deal_SH_NGTSMarketOverview(IFast_Record *Record);
	/***************************************************
	@处理上海level2  数据        
	@虚拟竞拍
	****************************************************/
	void Deal_SH_NGTSVirtualAuctionPrice(IFast_Record *Record);
	


	/***************************************************
	@处理深圳level2  FAST数据       
	@
	****************************************************/
	void Deal_SZ_Level2_Data(char *buff,int length);

	/***************************************************
	@处理深圳level2  数据       
	@FAST证券信息
	****************************************************/
	void Deal_SZ_StockInfo(IFast_Record *Record);
	/***************************************************
	@处理深圳level2  数据       
	@FAST证券状态
	****************************************************/
	void Deal_SZ_StockStatus(IFast_Record *Record);
	/***************************************************
	@处理深圳level2  数据       
	@FAST行情
	****************************************************/
	void Deal_SZ_Snapshot(IFast_Record *Record);

	/***************************************************
	@处理深圳level2  数据       
	@FAST指数行情
	****************************************************/
	void Deal_SZ_Index(IFast_Record *Record);
	/***************************************************
	@处理深圳level2  数据       
	@FAST逐筆委托
	****************************************************/
	void Deal_SZ_Order(IFast_Record *Record);
	/***************************************************
	@处理深圳level2  数据       
	@ FAST逐筆成交
	****************************************************/
	void Deal_SZ_Trade(IFast_Record *Record);

protected:
    int GetFastMsgInfo (const char* lpData, int nLen, FastMsgInfo& refMsgInfo) ;
private:
	//std::deque<char *> m_L2Data;
	L2_Receiver *m_Recv;
	Lock *m_lock;
	L2_THREAD_HANDLE  hThread;

	FAST_TYPE m_ft;
	char *m_lpFile;
	
	DynBuffer         m_ReadBuff ;
	//定义一个解释器
	IFast_Decoder* m_Decoder;

};


#endif
