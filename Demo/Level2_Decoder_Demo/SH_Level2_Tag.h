
#ifndef _H_SH_LEVEL2_TAG_H_
#define _H_SH_LEVEL2_TAG_H_

///////////SH Fast MsgType
#define FAST_SH_LOGON                         "A"         //LOGON
#define FAST_SH_LOGOUT                        "5"         //LOGOUT
#define FAST_SH_REBUILD                       "UA1201"    //REBUILD
#define FAST_SH_SYSTEM_MESSAGE                "UA1202"    //Heartbeat
#define FAST_SH_NGTS_VIRTUAL_ACTION_PRICE     "UA3107"    //虚拟竞拍
#define FAST_SH_NGTS_INDEX                    "UA3113"    //指数行情消息
#define FAST_SH_NGTS_MARKET_OVERVIEW          "UA3115"    //市场概况消息
#define FAST_SH_AH_MARKET_DATA                "UA2102"    //个股行情
#define FAST_SH_AH_VIRUTAL_AUCTION_PRICE      "UA2107"    //个股集合竞价
#define FAST_SH_MARKET_OVERVIEW               "UA1115"     //市场状态
#define FAST_SH_NGTS_TRANSACTION              "UA3201"     //逐笔成交
#define FAST_SH_NGTS_MARKET_DATA              "UA3202"     //行情快照
#define FAST_SH_LEVEL1_DATA                   "UA5102"     //Level-1 实时数据
#define FAST_SH_STATIC_DATA                   "UA2001"     //静态数据
///////////SH Fast MsgType


#define SH_MessageType                 35
#define SH_DataTimestamp               10178
#define SH_DataStatus                  10121
#define SH_SecurityID                  48
#define SH_AShareIndex                 10001
#define SH_BShareIndex                 10002
#define SH_SSEIndex                    10005
#define SH_OrigTime                    42
#define SH_OrigDate                    10003
#define SH_EndOfDayMarker              10004
#define SH_Symbol                      55
#define SH_PreClosePx                  140
#define SH_HighPx                      332
#define SH_LowPx                       333
#define SH_LastPx                      31
#define SH_NorminalPx                  10078
#define SH_BidPx                       132
#define SH_OfferPx                     133
#define SH_TotalVolumeTrade            387
#define SH_TotalValueTrade             8504
#define SH_Price                       44
#define SH_VirtualAuctionQty           10127
#define SH_TradeIndex                  10011
#define SH_TradeChannel                10115
#define SH_TradeTime                   10013
#define SH_TradePrice                  10014
#define SH_TradeQty                    10015
#define SH_TradeMoney                  10016
#define SH_ImageStatus                 10146
#define SH_OpenPx                      10018
#define SH_ClosePx                     10204
#define SH_InstrumentStatus            10135
#define SH_NumTrades                   8503
#define SH_TotalBidQty                 10043
#define SH_WeightedAvgBidPx            10039
#define SH_AltWeightedAvgBidPx         10116
#define SH_TotalOfferQty               10044
#define SH_WeightedAvgOfferPx          10040
#define SH_AltWeightedAvgOfferPx       10117
#define SH_IOPV                        10057
#define SH_YieldToMaturity             10060
#define SH_TotalWarrantExecQty         10138
#define SH_WarLowerPx                  10139
#define SH_WarUpperPx                  10140
#define SH_NoBidLevel                  10068
#define SH_PriceLeveOperator           10147
#define SH_OrderQty                    39
#define SH_NumOrders                   10067
#define SH_Orders                      73
#define SH_OrderQueueOperator          10148
#define SH_OrderQueueOperatorEntryID   10149
#define SH_SubOrderQty                 38
#define SH_NoOfferLevel                10069
#define SH_PreCloseIndex               10007
#define SH_OpenIndex                   10006
#define SH_Turnover                    10118
#define SH_HighIndex                   10009
#define SH_LowIndex                    10010
#define SH_LastIndex                   10008
#define SH_CloseIndex                  10205
#define SH_LeavesQty                   151
#define SH_Side                        54
#define SH_BidSize                     134
#define SH_OfferSize                   135
#define SH_PE                          10128
#define SH_DeletionIndicator           10130

/************************************************************************/
/* 模板对应的宏定义                          
/************************************************************************/


//   市场状态   <template name="MarketOverview" id="1115">
/*** 
<string name="MessageType" id="35"                   SH_MessageType
<int32 name="DataTimestamp" id="10178"               SH_DataTimestamp
<int32 name="DataStatus" id="10121"                  SH_DataStatus
<string name="SecurityID" id="48"                    SH_SecurityID
<int32 name="AShareIndex" id="10001"                 SH_AShareIndex
<int32 name="BShareIndex" id="10002"                 SH_BShareIndex
<int32 name="SSEIndex" id="10005"                    SH_SSEIndex
<int32 name="OrigTime" id="42"                       SH_OrigTime
<int32 name="OrigDate" id="10003"                    SH_OrigDate
<string name="EndOfDayMarker" id="10004"             SH_EndOfDayMarker
***/

//个股行情  <template name="A+HMarketData" id="2102">
/*** 
<string name="MessageType" id="35"      SH_MessageType
<int32 name="DataTimestamp" id="10178"  SH_DataTimestamp 
<int32 name="DataStatus" id="10121"     SH_DataStatus
<string name="SecurityID" id="48"       SH_SecurityID
<string name="Symbol" id="55"           SH_Symbol
<int32 name="PreClosePx" id="140"       SH_PreClosePx
<int32 name="HighPx" id="332"           SH_HighPx
<int32 name="LowPx" id="333"            SH_LowPx
<int32 name="LastPx" id="31"            SH_LastPx
<int32 name="NorminalPx" id="10078"     SH_NorminalPx
<int32 name="BidPx" id="132"            SH_BidPx
<int32 name="OfferPx" id="133"          SH_OfferPx
<int64 name="TotalVolumeTrade" id="387" SH_TotalVolumeTrade
<int64 name="TotalValueTrade" id="8504" SH_TotalValueTrade
***/

//个股集合竞价 <template name="A+HVirtualAuctionPrice" id="2107">
/*** 
<string name="MessageType" id="35"          SH_MessageType
<int32 name="DataTimestamp" id="10178"      SH_DataTimestamp 
<int32 name="DataStatus" id="10121"         SH_DataStatus
<string name="SecurityID" id="48"           SH_SecurityID
<string name="Symbol" id="55"               SH_Symbol
<int32 name="ClosePrice" id="140"           SH_PreClosePx
<int32 name="Price" id="44"                 SH_Price  
<int64 name="VirtualAuctionQty"id="10127"   SH_VirtualAuctionQty
***/


//逐笔成交 <template name="NGTSTransaction" id="3201">
/*** 
<string name="MessageType" id="35"        SH_MessageType
<int32 name="DataStatus" id="10121"       SH_DataStatus
<int32 name="TradeIndex" id="10011"       SH_TradeIndex
<int32 name="TradeChannel" id="10115"     SH_TradeChannel
<string name="SecurityID" id="48"         SH_SecurityID
<int32 name="TradeTime" id="10013"        SH_TradeTime
<int32 name="TradePrice" id="10014"       SH_TradePrice
<int64 name="TradeQty" id="10015"         SH_TradeQty
<int64 name="TradeMoney" id="10016"       SH_TradeMoney
***/


//行情快照  <template name="NGTSMarketData" id="3202">
/*** 
<string name="MessageType" id="35"          SH_MessageType
<int32 name="DataTimeStamp" id="10178"      SH_DataTimestamp
<int32 name="DataStatus" id="10121"         SH_DataStatus
<string name="SecurityID" id="48"           SH_SecurityID
<int32 name="ImageStatus" id="10146"        SH_ImageStatus
<int32 name="PreClosePx" id="140"           SH_PreClosePx
<int32 name="OpenPx" id="10018"             SH_OpenPx
<int32 name="HighPx" id="332"               SH_HighPx
<int32 name="LowPx" id="333"                SH_LowPx
<int32 name="LastPx" id="31"                SH_LastPx
<int32 name="ClosePx" id="10204"            SH_ClosePx
<string name="InstrumentStatus" id="10135"       SH_InstrumentStatus
<int32 name="NumTrades" id="8503"                SH_NumTrades
<int64 name="TotalVolumeTrade" id="387"          SH_TotalVolumeTrade
<int64 name="TotalValueTrade" id="8504"          SH_TotalValueTrade
<int64 name="TotalBidQty" id="10043"             SH_TotalBidQty
<int32 name="WeightedAvgBidPx" id="10039"        SH_WeightedAvgBidPx
<int32 name="AltWeightedAvgBidPx" id="10116"     SH_AltWeightedAvgBidPx
<int64 name="TotalOfferQty" id="10044"           SH_TotalOfferQty
<int32 name="WeightedAvgOfferPx" id="10040"      SH_WeightedAvgOfferPx
<int32 name="AltWeightedAvgOfferPx" id="10117"      SH_AltWeightedAvgOfferPx
<int32 name="IOPV" id="10057"                       SH_IOPV
<int32 name="YieldToMaturity" id="10060"            SH_YieldToMaturity
<int64 name="TotalWarrantExecQty" id="10138"        SH_TotalWarrantExecQty
<int64 name="WarLowerPx" id="10139"                 SH_WarLowerPx
<int64 name="WarUpperPx" id="10140"                 SH_WarUpperPx
<sequence   name="BidLevels" id="10068">            SH_NoBidLevel
  <int32 name="PriceLeveOperator" id="10147"          SH_PriceLeveOperator
  <int32 name="Price" id="44"                         SH_Price
  <int64 name="OrderQty" id="39"                      SH_OrderQty
  <int32 name="NumOrders" id="10067"                  SH_NumOrders
  <sequence  name="Orders" id="73">                    SH_Orders
    <int32 name="OrderQueueOperator" id="10148"         SH_OrderQueueOperator
    <int32 name="OrderQueueOperatorEntryID" id="10149"  SH_OrderQueueOperatorEntryID
    <int64 name="OrderQty" id="38"                      SH_SubOrderQty
  </sequence>
</sequence>
<sequence name="OfferLevel" id="10069">               SH_NoOfferLevel
  <int32 name="PriceLeveOperator" id="10147"          SH_PriceLeveOperator
  <int32 name="Price" id="44"                         SH_Price
  <int64 name="OrderQty" id="39"                      SH_OrderQty
  <int32 name="NumOrders" id="10067"                  SH_NumOrders
  <sequence name="Orders" id="73">                      SH_Orders
    <int32 name="OrderQueueOperator" id="10148"         SH_OrderQueueOperator
    <int32 name="OrderQueueOperatorEntryID" id="10149"  SH_OrderQueueOperatorEntryID
    <int64 name="OrderQty" id="38"                      SH_SubOrderQty
  </sequence>
</sequence>
***/


	

//指数行情消息  <template name="NGTSIndex" id="3113">
/***
<string name="MessageType" id="35"         SH_MessageType
<int32 name="DataTimestamp" id="10178"     SH_DataTimestamp
<int32 name="DataStatus" id="10121"        SH_DataStatus
<string name="SecurityID" id="48"          SH_SecurityID
<int64 name="PreCloseIndex" id="10007"     SH_PreCloseIndex
<int64 name="OpenIndex" id="10006"         SH_OpenIndex
<int64 name="Turnover" id="10118"          SH_Turnover
<int64 name="HighIndex" id="10009"         SH_HighIndex
<int64 name="LowIndex" id="10010"          SH_LowIndex
<int64 name="LastIndex" id="10008"         SH_LastIndex
<int32 name="TradeTime" id="10013"         SH_TradeTime
<int64 name="TotalVolumeTraded" id="387"   SH_TotalVolumeTrade
<int64 name="CloseIndex" id="10205"        SH_CloseIndex
***/

//市场概况消息 <template name="NGTSMarketOverview" id="3115">
/***
<string name="MessageType" id="35"          SH_MessageType
<int32 name="DataTimestamp" id="10178"      SH_DataTimestamp
<int32 name="DataStatus" id="10121"         SH_DataStatus
<string name="SecurityID" id="48"           SH_SecurityID
<int32 name="OrigTime" id="42"              SH_OrigTime
<int32 name="OrigDate" id="10003"           SH_OrigDate
***/


//虚拟竞拍  <template name="NGTSVirtualAuctionPrice" id="3107">
/***
<string name="MessageType" id="35"           SH_MessageType
<int32 name="DataTimestamp" id="10178"       SH_DataTimestamp
<int32 name="DataStatus" id="10121"          SH_DataStatus
<string name="SecurityID" id="48"            SH_SecurityID
<int32 name="Price" id="44"                  SH_Price
<int64 name="VirtualAuctionQty" id="10127"   SH_VirtualAuctionQty
<int64 name="LeavesQty" id="151"             SH_LeavesQty
<string name="Side" id="54"                  SH_Side
***/

//Level-1 实时数据  <template name="Level1Data" id="5102">
/*** 
<string name="MessageType" id="35"         SH_MessageType
<int32 name="DataTimestamp" id="10178"     SH_DataTimestamp
<int32 name="DataStatus" id="10121"        SH_DataStatus
<string name="SecurityID" id="48"          SH_SecurityID
<string name="Symbol" id="55"              SH_Symbol
<int32 name="PreClosePx" id="140"          SH_PreClosePx
<int32 name="OpenPx" id="10018"            SH_OpenPx
<int32 name="HighPx" id="332"              SH_HighPx
<int32 name="LowPx" id="333"               SH_LowPx
<int32 name="LastPx" id="31"               SH_LastPx
<sequence name="BidPriceLevel" id="10068"> SH_NoBidLevel
  <int64 name="BidSize" id="134"             SH_BidSize
  <int32 name="BidPx" id="132"               SH_BidPx
</sequence>
<sequence name="OfferPriceLevel" id="10069"> SH_NoOfferLevel
  <int64 name="OfferSize" id="135"           SH_OfferSize
  <int32 name="OfferPx" id="133"             SH_OfferPx
</sequence>
<int64 name="TotalVolumeTrade" id="387"    SH_TotalVolumeTrade
<int64 name="TotalValueTrade" id="8504"    SH_TotalValueTrade
<int32 name="PE" id="10128"                SH_PE
<int32 name="DeletionIndicator" id="10130" SH_DeletionIndicator
***/



#endif

