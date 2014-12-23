
/*******************************************************************************

源程序名称:  Fast_Define.h
软件著作权: 恒生电子股份有限公司版权所有
系统名称:   行情服务系统5.0项目
模块名称:   上海Level2适配器
功能说明:   FAST的基本类型定义
相关文档:   
作者:       郑骁玮

*******************************************************************************/

#ifndef  H5DS_FAST_DEFINE_H
#define  H5DS_FAST_DEFINE_H

#include "../Include/Basic_Types.h"
//#include <string>
#include <vector>
#include <map>
using std::vector ;
using std::map ;

// Fast Template
#define FAST_TEMPLATE_NAME "template"
#define FAST_SEQUENCE_NAME "sequence"

#define FFT_STRING "string"
#define FFT_INT32  "int32"
#define FFT_INT64  "int64"
#define FFT_UINT32 "uint32"
#define FFT_UINT64 "uint64"
#define FFT_DOUBLE "double"
#define FFT_SEQUENCE "sequence"
#define FFT_LENGTH "length"
#define FFT_NULL_TYPE "NULL_TYPE"

#define FFOP_CONSTANT  "constant"
#define FFOP_DEFAULT   "default"
#define FFOP_COPY      "copy"
#define FFOP_INCREMENT "increment"
#define FFOP_NOOP      "NoOp"

#define FFPSE_OPTIONAL  "optional"
#define FFPSE_MANDATORY "Mandatory"

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

#define MAX_FAST_TEMPLATE                                  40
#define UA3101_SLOT                                        0
#define UA3102_SLOT                                        1
#define UA3103_SLOT                                        2
#define UA3104_SLOT                                        3
#define UA3105_SLOT                                        4
#define UA3106_SLOT                                        5
#define UA3107_SLOT                                        6
#define UA1115_SLOT                                        7
#define UA3111_SLOT                                        12
#define UA3113_SLOT                                        14
#define UA3115_SLOT                                        16
// FAST2.0
#define UA2102_SLOT                                        21
#define UA2107_SLOT                                        22
#define UA3201_SLOT                                        23
#define UA3202_SLOT                                        24
#define UA5102_SLOT                                        25

// Logon Tag
#define FASTTAG_ENCRYPT_METHOD                             98
#define FASTTAG_HEARTBT_INT                                108
// FAST-Rebuild Request Tag
#define FAST_REQTYPE_REBUILD                               "UA1201"
#define FAST_REQTYPE_LOGON                                 "A"
#define FASTTAG_CATEGORY                                   10142
#define FASTTAG_REBUILD_METHOD                             10075
#define FASTTAG_TRADE_CHANNEL                              10077
#define FASTTAG_BEGIN_ID                                   10073
#define FASTTAG_END_ID                                     10074
#define FASTTAG_REBUILD_STATUS                             10076
#define FASTTAG_TEXT                                       58

// FAST消息类型
enum  Fast_Type
{
  FAST_NONE_TYPE                    = 0    ,
  FAST_LOGON                       = 'A'  ,  //登录
  FAST_LOGOUT                       = 5    ,  //登出
  FAST_REFERENCE_DATA               = 101  ,  //初始化消息·
  FAST_REBUILD                      = 1201 ,  //REBUILD
  FAST_SYSTEM_MESSAGE               = 1202 ,  //SystemMessage
  FAST_ANNOUNCEMENT                 = 1100 ,  //公告消息
  FAST_TRANSACTION                  = 3101 ,  //逐笔消息
  FAST_MARKET_DATA                  = 3102 ,  //市场消息
  FAST_ORDER_RANKING                = 3103 ,  //订单排名
  FAST_TRANSACTION_RANKING_INDUSTRY = 3104 ,  //行业逐笔排名
  FAST_SINGLE_ORDER_CANCEL_RANKING  = 3105 ,  //单笔撤单排名
  FAST_CONSOLIDATED_CANCEL_RANKING  = 3106 ,  //累计撤单排名
  FAST_NGTS_VIRTUAL_ACTION_PRICE    = 3107 ,  //虚拟竞拍
  FAST_NGTS_INDEX                   = 3113 ,  //指数行情消息
  FAST_NGTS_MARKET_OVERVIEW         = 3115 ,  //市场概况消息
  FAST_NGTS_ORDER_QUEUE             = 3111 ,  //委托队列
  // FAST2.0 - NEW
  //FAST2_MARKET_OVERVIEW             = 3115 ,
  FAST2_AH_MARKET_DATA              = 2102 ,
  FAST2_AH_VIRUTAL_AUCTION_PRICE    = 2107 ,
  FAST2_AH_MARKET_OVERVIEW          = 1115 ,
  FAST2_NGTS_TRANSACTION            = 3201 ,
  FAST2_NGTS_MARKET_DATA            = 3202 ,
  FAST2_LEVEL1_DATA                 = 5102 ,

  //国债 个股期权
  FAST_ZQQDBJCJHQ                    =6302,
  FAST_ZQCJMX                        =6301,
  FAST_ISP_DATA                      =8102,
  FAST_OPT_LEVEL1                    =9502,
  //国债 个股期权

  //sz
  FAST_SZ_LOGON                     = 'A'    ,  // SLZ2 登录           (原始类型: A) 使用时会用到 FAST_LOGON
  FAST_SZ_LOGOUT                    = 5      ,  // SLZ2 登出           (原始类型: 5) 使用时会用到 FAST_LOGOUT
  FAST_SZ_REBUILD                   = 2      ,  // SZL2 重建           (原始类型: 2)
  FAST_SZ_HEARTBEAT                 = 1      ,  // SZL2 心跳           (原始类型: UA001)
  FAST_SZ_SYSPARAM                  = 9002   ,  // SZL2 市场运行数据   (原始类型: UA002, 本来此处应定义成2, 但是与FAST_SZ_REBUILD冲突, 故定义成9002)
  FAST_SZ_USERREPORT                = 3      ,  // SLZ2 用户信息报告   (原始类型: UA003)
  FAST_SZ_STOCKINFO                 = 101    ,  // SLZ2 证券信息       (原始类型: UA101) 
  FAST_SZ_STOCKSTATUS               = 102    ,  // SLZ2 证券状态       (原始类型: UA102)
  FAST_SZ_SNAPSHOT                  = 103    ,  // SLZ2 行情快照       (原始类型: UA103)
  FAST_SZ_INDEX                     = 104    ,  // SLZ2 指数快照       (原始类型: UA104)
  FAST_SZ_ORDER                     = 201    ,  // SLZ2 逐笔委托       (原始类型: UA201)
  FAST_SZ_TRADE                     = 202    ,  // SLZ2 逐笔成交       (原始类型: UA202)
  FAST_SZ_BULLETIN                  = 401    ,  // SLZ2 公告及增值信息 (原始类型: UA401)
  //sz

  //未知的消息
  FAST_UNKNOWN_TYPE  = 1000000,


} ;

// FAST最大产品类别
#define MAX_FAST_CATEGORY           20
// FAST产品类别
enum Fast_Category
{
  FAST_CID_REFERENCE                = 1 ,     //参考数据
  FAST_CID_INIT_FILE                = 3 ,     //初始化文件
  FAST_CID_MARKETDATA               = 6 ,     //行情快照
  FAST_CID_TRANSACTION              = 7 ,     //逐笔成交
  FAST_CID_AH_MARKETDATA            = 9 ,     //A+H行情快照
  FAST_CID_STATIC_FILE              = 10 ,    //静态数据: 融资融券文件,重点指数表现文件,开放式基金净值文件
  FAST_CID_LEVEL1                   = 13      //Level1行情快照
} ;

// RebuildMethod
enum RebildMethod
{
  RMETHOD_BY_CATEGORY_SEQUENCE_NUMBER = 1 ,   //根据产品类别及消息序号
  RMETHOD_FULL_IMATE_REBUILD          = 2 ,   //该产品类别下的全量消息
  RMETHOD_TRANSACTION                 = 3     //逐笔成交的回补
} ;

// RebuildStatus
enum RebuildStatus
{
  RSTATUS_OK                          = 1 ,   //成功,所有数据返回
  RSTATUS_PARTIALLY_COMPLETED         = 2 ,   //部分成功
  RSTATUS_REJECTED                    = 3 ,   //拒绝
  RSTATUS_DATA_NOT_AVAILABLE          = 4     //无此数据
} ;

//Fast字段值类型
enum Fast_FieldType
{
  FFT_Null_Type = 0 ,
  FFT_String ,
  FFT_UString,
  FFT_Int8   ,
  FFT_UInt8  ,
  FFT_Int16  ,
  FFT_UInt16 ,
  FFT_Int32  ,
  FFT_UInt32 ,
  FFT_Int64  ,
  FFT_UInt64 ,
  FFT_Sequence ,
  FFT_Length
} ;

//Fast基本的操作类型
enum Fast_OP
{
  OP_NULL = 0 ,
  OP_Constant ,
  OP_Default  ,
  OP_Copy     ,
  OP_Increment,
  OP_Delta
} ;

//Fast字段的存在性
enum Fast_Presence
{
  PRES_Mandatory = 0,
  PRES_Optional
} ;

//Fast字段值
#define FAST_MAXSTRINGLEN 64
struct Fast_Value
{
  Fast_FieldType  field_type ;      //值类型
  uint32          decimal_place ;   //小数位

  union{
    int32   l4 ;
    int64   l8 ;
    double  d8 ;
    char    str[FAST_MAXSTRINGLEN] ;
  } val ;

  Fast_Value(){ memset(this, 0, sizeof(*this)); }

  void Reset()
  {
	  memset(&val, 0xff, sizeof val);
  }

  bool IsAssigned()
  {
	  unsigned char *p = (unsigned char *)&val;
	  for (size_t i = 0; i < sizeof val; i++)
	  {
		  if (p[i] != 0xff)
		  {
			  return true;
		  }
	  }
	  return false;
  }
} ;

//Fast模板字段属性
struct FastMsg_Templ ;
#define FAST_FIELDNAME_LEN 50
struct Fast_TemplField
{
  uint32               field_id ;         //字段的ID
  Fast_OP              field_op ;         //字段的OP
  Fast_FieldType       field_type ;       //字段的类型
  char                 field_name[FAST_FIELDNAME_LEN] ; //字段名称
  Fast_Presence        field_pres ;       //字段的存在性
  int32                field_slot ;       //slot position
  uint32               decimal_place ;    //小数位
  Fast_Value           field_opval ;      //OP Value ,<Constant value=>
  Fast_Value           field_curval ;     //字段的当前值
  FastMsg_Templ        *seq_ptr ;         //若该字段是Sequence类型的,该字段保存其模板

  Fast_TemplField()
  { 
	  memset(this, 0, sizeof(*this)); 
	  field_slot=-1;  
	  ResetCurrentValue();
  }
  void Destory() ;
  ~Fast_TemplField(){ Destory();}

  void ResetCurrentValue()
  {
	  field_curval.Reset();
  }
  bool IsAssignedCurrentValue()
  {
	  return field_curval.IsAssigned();
  }
} ;

//Fast消息模板
#define FAST_TEMPLNAME_LEN 100
typedef vector<Fast_TemplField *> Fast_Field_Array ;
struct FastMsg_Templ
{
  uint32                templ_id ;
  uint32                slot_count  ; //slot count
  uint32                field_count ; //field count
  char                  templ_name[FAST_TEMPLNAME_LEN] ; //template name
  Fast_Field_Array      field_array ; //模板字段的列表
  FastMsg_Templ():templ_id(0), slot_count(0), field_count(0) { }
  ~FastMsg_Templ()
  { 
    for(size_t i=0; i<field_array.size(); i++)
    {
      if( field_array[i]!=0 )
        delete field_array[i] ;
    }
  }
 
  int AddField(Fast_TemplField *pField)
  {
    if( pField==0 ) return -1 ;
    field_array.push_back(pField) ;
    return 0 ;
  }

  void ResetCurrentValue()
  {
	  for (size_t i = 0; i < field_array.size(); i++)
	  {
		  if (field_array[i])
		  {
			  field_array[i]->ResetCurrentValue();
		  }
	  }
  }
} ;

#define FAST_PMAPSIZE 8
typedef unsigned char PMAP[FAST_PMAPSIZE] ;

//Fast模板表
typedef map<uint32, FastMsg_Templ *> FastTempl_Map ;
class FastTempl_Manager
{
protected:
  FastTempl_Map                m_mapTempl ;

public:
  ~FastTempl_Manager()
  {
    this->Clear () ;
  }

  FastMsg_Templ *GetTemplate(uint32 nTemplID)
  {
    FastTempl_Map::iterator iter = m_mapTempl.find (nTemplID) ;
    if( iter!= m_mapTempl.end() )
      return iter->second ;
    else
      return 0 ;
  }

  int  AddTempl(uint32 nTemplID, FastMsg_Templ *lpFastTempl)
  {
    std::pair<FastTempl_Map::iterator, bool> ret = m_mapTempl.insert(FastTempl_Map::value_type(nTemplID, lpFastTempl)) ;
    if( ret.second )
      return  0  ;
    else
      return  -1 ;
  }

  void Clear()
  {
    for(FastTempl_Map::iterator iter = m_mapTempl.begin() ;
        iter != m_mapTempl.end() ;
        ++iter)
    {
      FastMsg_Templ *lpTempl = iter->second ;
      if( lpTempl )
        delete lpTempl ;
      lpTempl = 0 ;
    }
    m_mapTempl.clear() ;
  }

  void Print()
  {
    char  strTemp[256+1] ;
    sprintf(strTemp, "<<<<<<Template Count:%d>>>>>>>\n", m_mapTempl.size()) ;
    printf (strTemp) ;
    for(FastTempl_Map::iterator iter = m_mapTempl.begin() ;
        iter != m_mapTempl.end() ;
        ++iter)
    {
      FastMsg_Templ* lpMsgTempl = iter->second ;
      sprintf (strTemp, "***TNAME:%s TID:%d FieldCount:%d SlotCount:%d\n",
                lpMsgTempl->templ_name,  lpMsgTempl->templ_id,
                lpMsgTempl->field_count, lpMsgTempl->slot_count ) ;
      printf (strTemp) ;
      for (size_t i = 0; i<lpMsgTempl->field_array.size(); ++i)
      {
        Fast_TemplField* lpFieldTempl = lpMsgTempl->field_array[i] ;
        sprintf (strTemp, "  %s %d\n", lpFieldTempl->field_name, lpFieldTempl->field_id) ;
        printf (strTemp) ;
      }
    }
  }
};


class Fast_Method
{
public:
  static Fast_FieldType StrToFieldType(const char *strType)
  {
    if (!strType)  return FFT_Null_Type ;
	//  忽略大小写
	std::string tmp_str(strType);
	strType = tmp_str.c_str();
	for (std::string::size_type i = 0; i < tmp_str.size(); i++)
	{
		tmp_str[i] = tolower(tmp_str[i]);
	}
	// 忽略大小写

    if (!strcmp(strType, "string"))
      return FFT_String ;
    else if (!strcmp(strType, "int32"))
      return FFT_Int32  ;
    else if (!strcmp(strType, "uint32"))
      return FFT_UInt32 ;
    else if (!strcmp(strType, "int64"))
      return FFT_UInt64 ;
    else if (!strcmp(strType, "uint64"))
      return FFT_UInt64 ;
    else if (!strcmp(strType, "sequence"))
      return FFT_Sequence ;
    else if (!strcmp(strType, "length"))
      return FFT_Length ;
    else
      return FFT_Null_Type ;
  }

  static Fast_OP StrToFastOp(const char *strType)
  {
    if (!strType)  return OP_NULL ;
    if (!strcmp(strType, "constant"))
      return OP_Constant ;
    else if (!strcmp(strType, "default"))
      return OP_Default  ;
    else if (!strcmp(strType, "copy"))
      return OP_Copy ;
    else if (!strcmp(strType, "increment"))
      return OP_Increment ;
    else if (!strcmp(strType, "delta"))
		  return OP_Delta ;
    else
      return OP_NULL ;
  }

  static Fast_Presence StrToPres(const char *strPres)
  {
    if (!strPres) return PRES_Mandatory ;
    if (!strcmp(strPres, "optional"))
      return PRES_Optional ;
    else
      return PRES_Mandatory ;
  }

  static int Slot(Fast_OP op, Fast_Presence pres)
  {
    if(  (op==OP_NULL) 
       ||(op==OP_Constant && PRES_Mandatory == pres)
       ||(op==OP_Delta && PRES_Mandatory == pres)
      )
      return 0 ;
    else
      return 1 ;
  }
};

#endif
