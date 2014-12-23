#ifndef _H_SZ_LEVEL2_TAG_H_
#define _H_SZ_LEVEL2_TAG_H_

///////////SZ Fast MsgType
#define FAST_SZ_LOGON                      "A"        // SLZ2 登录           
#define FAST_SZ_LOGOUT                     "5"        // SLZ2 登出           
#define FAST_SZ_REBUILD                    "2"        // SZL2 重建           
#define FAST_SZ_HEARTBEAT                  "UA001"    // SZL2 心跳           
#define FAST_SZ_SYSPARAM                   "UA002"    // SZL2 市场运行数据   
#define FAST_SZ_USERREPORT                 "UA003"    // SLZ2 用户信息报告   
#define FAST_SZ_STOCKINFO                  "UA101"    // SLZ2 证券信息       
#define FAST_SZ_STOCKSTATUS                "UA102"    // SLZ2 证券状态     
#define FAST_SZ_SNAPSHOT                   "UA103"    // SLZ2 行情快照       
#define FAST_SZ_INDEX                      "UA104"    // SLZ2 指数快照       
#define FAST_SZ_ORDER                      "UA201"    // SLZ2 逐笔委托       
#define FAST_SZ_TRADE                      "UA202"    // SLZ2 逐笔成交       
#define FAST_SZ_BULLETIN                   "UA401"    // SLZ2 公告及增值信息 
///////////SZ Fast MsgType

#define SZ_RecNo                                8926
#define SZ_SecurityID                           48
#define SZ_Symbol                               55
#define SZ_SecurityDesc                         107
#define SZ_UnderlyingSecurityID                 309
#define SZ_SecurityIDSource                     22
#define SZ_SecurityAltIDs                       454
#define SZ_SecurityAltID                        455
#define SZ_SecurityAltIDSource                  456
#define SZ_IndustryClassification               8507
#define SZ_Currency                             15
#define SZ_ShareFaceValue                       8508
#define SZ_OutstandingShare                     8509
#define SZ_PublicFloatShareQuantity             8510
#define SZ_PreviousYearProfitPerShare           8511
#define SZ_CurrentYearProfitPerShare            8512
#define SZ_NAV                                  8537
#define SZ_MiscFees                             136
#define SZ_MiscFeeType                          139
#define SZ_MiscFeeBasis                         891
#define SZ_MiscFeeAmt                           137
#define SZ_IssueDate                            225
#define SZ_BondType                             10106
#define SZ_CouponRate                           223
#define SZ_ConversionPrice                      10103
#define SZ_American_European                    10107
#define SZ_CallOrPut                            10108
#define SZ_WarrantClearingType                  8536
#define SZ_CVRatio                              10114
#define SZ_ConversionBeginDate                  8902
#define SZ_ConversionEndDate                    8903
#define SZ_InterestAccrualDate                  874
#define SZ_MaturityDate                         541
#define SZ_RoundLot                             561
#define SZ_BidLotSize                           8513
#define SZ_AskLotSize                           8514
#define SZ_MaxFloor                             111
#define SZ_TradeMethod                          8905
#define SZ_PriceTickSize                        8515
#define SZ_PriceLimitType                       8516
#define SZ_AuctionPriceLimit                    8517
#define SZ_ContinuousTradePriceLimit            8518
#define SZ_DailyPriceUpLimit                    8519
#define SZ_DailyPriceLowLimit                   8520
#define SZ_DailyPriceUpLimit2                   8911
#define SZ_DailyPriceLowLimit2                  8912
#define SZ_ContractMultiplier                   231
#define SZ_GageRate                             8913
#define SZ_CrdBuyUnderlying                     8914
#define SZ_CrdSellUnderlying                    8915
#define SZ_IndicesParticipated                  8522
#define SZ_participatingIndexID                 8528
#define SZ_MarketMakerFlag                      8916
#define SZ_SecurityExchange                     207
#define SZ_CFICode                              461
#define SZ_SecuritySubType                      762
#define SZ_SecurityProperties                   8521
#define SZ_SecurityTradingStatus                326
#define SZ_CorporateAction                      292
#define SZ_TradingMechanism                     8906
#define SZ_CrdPriceCheckType                    8925
#define SZ_NetVotingFlag                        8904
#define SZ_ShrstrurefmFlag                      8917
#define SZ_OfferingFlag                         8918
#define SZ_SecurityPreName                      8901
#define SZ_TradingPhaseCode                     8538
#define SZ_CrdBuyStatus                         8919
#define SZ_CrdSellStatus                        8920
#define SZ_SubScribeStatus                      8921
#define SZ_RedemptionStatus                     8922
#define SZ_WarrantCreated                       8923
#define SZ_WarrantDropped                       8924
#define SZ_DataTimeStamp                       10178
#define SZ_PreClosePx                          140
#define SZ_OpenPx                              10018
#define SZ_HighPx                              332
#define SZ_LowPx                               333
#define SZ_LastPx                              31
#define SZ_NumTrades                           8503
#define SZ_TotalVolumeTrade                    387
#define SZ_TotalValueTrade                     8504
#define SZ_TotalLongPosition                   8506
#define SZ_PERatio1                            8524
#define SZ_PERatio2                            8525
#define SZ_EndOfDayMaker                       10004
#define SZ_TotalOfferQty                       10044
#define SZ_WeightedAvgOfferPx                  10040
#define SZ_OfferPriceLevel                     10069
#define SZ_OfferPx                             133
#define SZ_OfferSize                           135
#define SZ_NumOrders                           10067
#define SZ_Orders                              73
#define SZ_OrderQty                            38
#define SZ_TotalBidQty                         10043
#define SZ_WeightedAvgBidPx                    10039
#define SZ_BidPriceLevel                       10068
#define SZ_BidPx                               132
#define SZ_BidSize                             134
#define SZ_CloseIndex                          10007
#define SZ_OpenIndex                           10006
#define SZ_HighIndex                           10009
#define SZ_LowIndex                            10010
#define SZ_LastIndex                           10008
#define SZ_TurnOver                            10118
#define SZ_SetNo                               10115
#define SZ_Price                               44
#define SZ_OrderKind                           8930
#define SZ_FunctionCode                        8931
#define SZ_OrderEntryTime                      8500
#define SZ_BuyOrderRecNo                       10116
#define SZ_SellOrderRecNo                      10117
#define SZ_TradeQty                            10015
#define SZ_TradeTime                           10013


/************************************************************************/
/* 模板ID对应的宏定义， 在level2解包中
/* 通过ID对应的宏定义 来获取对应的值                                
/************************************************************************/

// FAST证券信息模版 <template id="101" name="StockInfo">
/**** 
<uInt32 id="8926"  name="RecNo" />                     SZ_RecNo              
<string id="48"    name="SecurityID" />                SZ_SecurityID
<string id="55"    name="Symbol" />                    SZ_Symbol
<string id="107"   name="SecurityDesc" />              SZ_SecurityDesc
<string id="309"   name="UnderlyingSecurityID" />      SZ_UnderlyingSecurityID
<string id="22"    name="SecurityIDSource">            SZ_SecurityIDSource
<sequence id="454" name="SecurityAltIDs">              SZ_SecurityAltIDs
  <string id="455"  name="SecurityAltID" />              SZ_SecurityAltID
  <string id="456"  name="SecurityAltIDSource"/>　　　　 SZ_SecurityAltIDSource
</sequence>
<string id="8507"  name="IndustryClassification" />    SZ_IndustryClassification
<string id="15"    name="Currency">                    SZ_Currency
<uInt32 id="8508"  name="ShareFaceValue">              SZ_ShareFaceValue
<uInt64 id="8509"  name="OutstandingShare" />          SZ_OutstandingShare
<uInt64 id="8510"  name="PublicFloatShareQuantity" />  SZ_PublicFloatShareQuantity
<int32 id="8511"   name="PreviousYearProfitPerShare"/> SZ_PreviousYearProfitPerShare
<int32 id="8512"   name="CurrentYearProfitPerShare" /> SZ_CurrentYearProfitPerShare
<uInt32 id="8537"  name="NAV"/>                        SZ_NAV
<sequence id="136" name="MiscFees">                    SZ_MiscFees                  
  <string id="139"  name="MiscFeeType" />                SZ_MiscFeeType
  <uInt32 id="891"  name="MiscFeeBasis">                 SZ_MiscFeeBasis
  <uInt32 id="137"  name="MiscFeeAmt"/>                  SZ_MiscFeeAmt
</sequence>
<uInt32 id="225"    name="IssueDate" />                SZ_IssueDate
<string id="10106"  name="BondType">                   SZ_BondType

<uInt32 id="223"    name="CouponRate"/>                SZ_CouponRate
<uInt32 id="10103"  name="ConversionPrice"/>           SZ_ConversionPrice
<string id="10107"  name="American/European" />        SZ_American_European
<string id="10108"  name="CallOrPut" />                SZ_CallOrPut
<string id="8536"   name="WarrantClearingType">        SZ_WarrantClearingType

<uInt32 id="10114"  name="CVRatio"/>                   SZ_CVRatio
<uInt32 id="8902"   name="ConversionBeginDate" />      SZ_ConversionBeginDate
<uInt32 id="8903"   name="ConversionEndDate" />        SZ_ConversionEndDate
<uInt32 id="874"    name="InterestAccrualDate" />      SZ_InterestAccrualDate
<uInt32 id="541"    name="MaturityDate" />             SZ_MaturityDate
<uInt32 id="561"    name="RoundLot">                   SZ_RoundLot

<uInt32 id="8513"   name="BidLotSize">                 SZ_BidLotSize
<uInt32 id="8514"   name="AskLotSize">                 SZ_AskLotSize
<uInt32 id="111"    name="MaxFloor">                   SZ_MaxFloor

<string id="8905"   name="TradeMethod">                SZ_TradeMethod
<uInt32 id="8515"   name="PriceTickSize">              SZ_PriceTickSize
<string id="8516"   name="PriceLimitType">
<uInt32 id="8517"   name="AuctionPriceLimit" >         SZ_AuctionPriceLimit
<uInt32 id="8518"   name="ContinuousTradePriceLimit">  SZ_ContinuousTradePriceLimit

<uInt32 id="8519"  name="DailyPriceUpLimit" />         SZ_DailyPriceUpLimit
<uInt32 id="8520"  name="DailyPriceLowLimit" />        SZ_DailyPriceLowLimit
<uInt32 id="8911"  name="DailyPriceUpLimit2" />        SZ_DailyPriceUpLimit2
<uInt32 id="8912"  name="DailyPriceLowLimit2"/>        SZ_DailyPriceLowLimit2
<uInt32 id="231"   name="ContractMultiplier" />        SZ_ContractMultiplier
<uInt32 id="8913"  name="GageRate"  />                 SZ_GageRate
<string id="8914"  name="CrdBuyUnderlying">            SZ_CrdBuyUnderlying
<string id="8915"  name="CrdSellUnderlying">           SZ_CrdSellUnderlying
<sequence id="8522" name="IndicesParticipated">        SZ_IndicesParticipated  
  <string id="8528"  name="participatingIndexID" />      SZ_participatingIndexID
</sequence>
<string id="8916"  name="MarketMakerFlag">             SZ_MarketMakerFlag
<string id="207"   name="SecurityExchange">            SZ_SecurityExchange

<string id="461"   name="CFICode">                     SZ_CFICode
<string id="762"   name="SecuritySubType">             SZ_SecuritySubType
<string id="8521"  name="SecurityProperties">          SZ_SecurityProperties
<uInt32 id="326"   name="SecurityTradingStatus">       SZ_SecurityTradingStatus
<string id="292"   name="CorporateAction">             SZ_CorporateAction
<string id="8906"  name="TradingMechanism">            SZ_TradingMechanism
<string id="8925"  name="CrdPriceCheckType">           SZ_CrdPriceCheckType

<string id="8904"  name="NetVotingFlag">               SZ_NetVotingFlag
<string id="8917"  name="ShrstrurefmFlag">             SZ_ShrstrurefmFlag

<string id="8918"  name="OfferingFlag">                SZ_OfferingFlag
*******/


//FAST证券状态模版 <template id="102" name="StockStatus">
/*** 
<string id="48"    name="SecurityID" />       SZ_SecurityID
<string id="8901"  name="SecurityPreName" />  SZ_SecurityPreName
<string id="8538"  name="TradingPhaseCode">   SZ_TradingPhaseCode

<string id="8919"  name="CrdBuyStatus">       SZ_CrdBuyStatus
<string id="8920"  name="CrdSellStatus">      SZ_CrdSellStatus
<string id="8921"  name="SubScribeStatus">    SZ_SubScribeStatus
<string id="8922"  name="RedemptionStatus">   SZ_RedemptionStatus
<string id="8923"  name="WarrantCreated">     SZ_WarrantCreated
<string id="8924"  name="WarrantDropped">     SZ_WarrantDropped
***/

//FAST行情模版 <template id="103" name="Snapshot">
/*** 
<int32 id="10178"  name="DataTimeStamp">       SZ_DataTimeStamp
<string id="48"    name="SecurityID" />        SZ_SecurityID
<uInt32 id="140"   name="PreClosePx" />        SZ_PreClosePx
<uInt32 id="10018" name="OpenPx" />            SZ_OpenPx
<uInt32 id="332"   name="HighPx" />            SZ_HighPx
<uInt32 id="333"   name="LowPx" />             SZ_LowPx
<uInt32 id="31"    name="LastPx" />            SZ_LastPx
<uInt64 id="8503"  name="NumTrades" />         SZ_NumTrades
<uInt64 id="387"   name="TotalVolumeTrade" />  SZ_TotalVolumeTrade
<uInt64 id="8504"  name="TotalValueTrade" />   SZ_TotalValueTrade
<uInt64 id="8506"  name="TotalLongPosition" /> SZ_TotalLongPosition
<uInt32 id="8524"  name="PERatio1" />          SZ_PERatio1
<uInt32 id="8525"  name="PERatio2"/>           SZ_PERatio2
<string id="10004" name="EndOfDayMaker">       SZ_EndOfDayMaker
<uInt64 id="10044" name="TotalOfferQty" />     SZ_TotalOfferQty
<uInt64 id="10040" name="WeightedAvgOfferPx"/> SZ_WeightedAvgOfferPx
<sequence id="10069" name="OfferPriceLevel">   SZ_OfferPriceLevel
  <uInt32 id="133"     name="OfferPx" />         SZ_OfferPx
  <uInt64 id="135"     name="OfferSize" />       SZ_OfferSize
  <uInt32 id="10067"   name="NumOrders" />       SZ_NumOrders
  <sequence id="73" name="Orders">               SZ_Orders
    <uInt32 id="38"      name="OrderQty" />        SZ_OrderQty
  </sequence>
</sequence>

<uInt64 id="10043"   name="TotalBidQty" />     SZ_TotalBidQty
<uInt64 id="10039"   name="WeightedAvgBidPx"/> SZ_WeightedAvgBidPx

<sequence id="10068" name="BidPriceLevel">       SZ_BidPriceLevel
  <uInt32 id="132"     name="BidPx" />           SZ_BidPx
  <uInt64 id="134"     name="BidSize" />         SZ_BidSize
  <uInt32 id="10067"   name="NumOrders" />       SZ_NumOrders
  <sequence id="73" name="Orders">               SZ_Orders
    <uInt32 id="38"      name="OrderQty" />        SZ_OrderQty
  </sequence>
</sequence>
***/

//FAST指数模版 <template id="104" name="Index">
/***
<int32 id="10178"  name="DataTimeStamp">       SZ_DataTimeStamp
<string id="48"    name="SecurityID" />        SZ_SecurityID
<uInt64 id="10007" name="CloseIndex" />        SZ_CloseIndex
<uInt64 id="10006" name="OpenIndex" />         SZ_OpenIndex
<uInt64 id="10009" name="HighIndex"/>          SZ_HighIndex
<uInt64 id="10010" name="LowIndex" />          SZ_LowIndex
<uInt64 id="10008" name="LastIndex"/>          SZ_LastIndex
<uInt64 id="10118" name="TurnOver" />          SZ_TurnOver
<uInt64 id="8503"  name="NumTrades" />         SZ_NumTrades
<uInt64 id="387"   name="TotalVolumeTraded"/>  SZ_TotalVolumeTrade
<string id="10004"  name="EndOfDayMaker">      SZ_EndOfDayMaker
 ***/


// FAST委托模版   <template id="201" name="Order">
/*** 
<uInt32 id="10115"  name="SetNo">         SZ_SetNo
<uInt32 id="8926"   name="RecNo">         SZ_RecNo
<string id="48"     name="SecurityID" />  SZ_SecurityID
<uInt32 id="44"     name="Price" />       SZ_Price
<uInt32 id="38"     name="OrderQty" />    SZ_OrderQty
<string id="8930"   name="OrderKind" />   SZ_OrderKind
<string id="8931"   name="FunctionCode"/> SZ_FunctionCode
<int32 id="8500"    name="OrderEntryTime">SZ_OrderEntryTime
***/

// FAST成交模版 <template id="202" name="Trade">
/*** 
<uInt32 id="10115"  name="SetNo">            SZ_SetNo
<uInt32 id="8926"   name="RecNo">            SZ_RecNo
<uInt32 id="10116"  name="BuyOrderRecNo" />  SZ_BuyOrderRecNo
<uInt32 id="10117"  name="SellOrderRecNo" /> SZ_SellOrderRecNo
<string id="48"     name="SecurityID" />     SZ_SecurityID
<uInt32 id="44"     name="Price" />          SZ_Price
<uInt32 id="10015"  name="TradeQty" />       SZ_TradeQty
<string id="8930"   name="OrderKind" />      SZ_OrderKind
<string id="8931"   name="FunctionCode" />   SZ_FunctionCode
<int32 id="10013"   name="TradeTime">        SZ_TradeTime
***/


#endif


