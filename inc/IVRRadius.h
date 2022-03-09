typedef struct AuthInfo
{
	unsigned char authID;
	char username[128];
	char passwd[32];
	char callingID[64];
	char calledID[64];
  char trunkID[64];
  char confid[128];
  bool callbacktag;
}AuthInfo;

typedef struct RefillInfo
{
	unsigned char reqID;
	char username[128];
	char passwd[32];
	char tousername[128];
}RefillInfo;

typedef struct ChgPwdInfo
{
	unsigned char reqID;
	char username[128];
	char oripasswd[32];
	char confirmpwd[32];
}ChgPwdInfo;

typedef struct AdjustTimeInfo
{
	char confid[64];
	char gatewayid[64];
	int creditamount;
	int credittime;
}AdjustTimeInfo;
    		
typedef struct RadAcctInfo
{
	int  status;
	char username[64];
	unsigned char ID;	  	    
	char sessionid[64];
	char confid[64];
	char CallerNumber[64];
	char CalledNumber[64];
	char ServiceType[64];
	char venderinfo[64];
	char gatewayid[64];
	char rmgatewayid[64];
	char connectid[64];
	char remoteaddr[64];
	char CallOrigin[64];	  			
	int  inputoctet;
	int  outputoctet;
	int  packets_in;
	int  packets_out;
	int  delay_time;
	int  session_time;
	int  DisconnectCause;
	char CallSetupTime[64];
	char ConnectTime[64];
	char DisconnectTime[64];
}RadAcctInfo;


//Data structure definitions 
typedef struct RadiusReply
{
	int  reply_tag;			    ///   
	double credit_amount;
	int  credit_time;
	int  prompt_id;			    /// 
	int  timeandday; 			  /// 
	char redirect_number[64]; /// 
	char preferedlang[64];  /// 
	char redirect_address[64]; /// 
	int  billingmodel;        /// 
 	char currency[64];        /// 
}RadiusReply;

#define    MIN_BALANCE              0
#define    LocalNum                 "8862168"
#define    CardNoLen                12

#define	PW_AUTH_SUCCESSED			    0     //認證成功
#define PW_INVALID_ACCOUNT		    1		  //無效的帳號
#define	PW_INVALID_PASSWD			    2     //無效的密碼
#define	PW_ACCOUNT_INUSE			    3     //帳戶在使用中
#define PW_ZERO_BALANCE				    4     //0 餘額
#define PW_ACCOUNT_EXPIRE			    5     //帳號過期
#define	PW_CREDIT_LIMIT				    6	    //信用限制,根據費率和balance求最大接通時常失敗時
#define	PW_USER_DENIED				    7
#define PW_SERVICE_INAVAILABLE	  8
#define	PW_CEDID_BLOCKED			    9
#define	PW_RETRIES_EXCEED			    10
#define	PW_INVALID_ARGUMENT			  11
#define	PW_INSUFFICIENT_BALANCE	  12  //帳戶餘額不足
#define PW_UNLIMIT_CALL				    13
#define	PW_INVALID_CARDNO			    14  //卡號不存在 :  prefix exist
#define	PW_DATABASE_FAILED			  15 
#define	PW_NETWORK_UNACCESSABLE	  50
#define	PW_REDIRECT_CALL			    51
#define	PW_REDIRECT_CUSTSERVICE	  52

//acms externd
#define PW_INVALID_RATEGROUP			53      //無效的費率組
#define	PW_INVALID_RATESET			  54      //無效的費率套
#define	PW_INVALID_USERNAME			  55      //無效的用戶名
#define	PW_INVALID_BUSINESS			  56      //無效的業務,業務名字核卡號不正確或密碼不正確
                                          // no this prefix

#define	PW_BALANCEUSEOUT			    57	  //餘額被充完
#define	PW_NOTACTIVE				      58	  //充值卡的狀態不是激活的  prohibited
#define	PW_INVALID_TRGTCARDNO			59	  //被充值的卡號不存在
#define	PW_TRGTBALANCEUSEOUT			60	  //被充值的卡餘額用完,不能被充 ????


#define	PW_TRGTNOTACTIVE			    61	  //被充值的卡不是激活的,不能被充
#define	PW_TRGTINSUFFICIENT_BALANCE		62	//被充值的卡餘額不足

#define	PW_ACCOUNT_PROHIBITED			63	//帳戶被停用
#define PW_TRGTACCOUNT_PROHIBITED	64	//被充值帳戶被停用
#define	PW_TRGTACCOUNT_EXPIRED		65	//被值帳戶過期
#define	PW_TRGTACCOUNT_INUSE			66	//被充值帳戶使用中



typedef void (*RadiusNotifier) (int id,RadiusReply context);

//初始化radius
int initRadius(char *localaddr,int authport,int acctport);
int setServer(char *server,int authport,int acctport,char *key); 
int clearRadius();

int RadiusQuery(int callid,AuthInfo & Auth,RadiusReply &replymsg);
int RadiusAuth(int callid,AuthInfo & Auth,RadiusReply &replymsg);
int RadiusRefill(int callid,RefillInfo & Refill,RadiusReply &replymsg);
int RadiusChgPwd(int callid,ChgPwdInfo &ChgPwd,RadiusReply &replymsg);
int RadiusAcctStart(int callid,RadAcctInfo &Acct,RadiusReply &replymsg);
int RadiusAcctStop(int callid,RadAcctInfo &Acct,RadiusReply &replymsg);

//#endif


