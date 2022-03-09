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

#define	PW_AUTH_SUCCESSED			    0     //�{�Ҧ��\
#define PW_INVALID_ACCOUNT		    1		  //�L�Ī��b��
#define	PW_INVALID_PASSWD			    2     //�L�Ī��K�X
#define	PW_ACCOUNT_INUSE			    3     //�b��b�ϥΤ�
#define PW_ZERO_BALANCE				    4     //0 �l�B
#define PW_ACCOUNT_EXPIRE			    5     //�b���L��
#define	PW_CREDIT_LIMIT				    6	    //�H�έ���,�ھڶO�v�Mbalance�D�̤j���q�ɱ`���Ѯ�
#define	PW_USER_DENIED				    7
#define PW_SERVICE_INAVAILABLE	  8
#define	PW_CEDID_BLOCKED			    9
#define	PW_RETRIES_EXCEED			    10
#define	PW_INVALID_ARGUMENT			  11
#define	PW_INSUFFICIENT_BALANCE	  12  //�b��l�B����
#define PW_UNLIMIT_CALL				    13
#define	PW_INVALID_CARDNO			    14  //�d�����s�b :  prefix exist
#define	PW_DATABASE_FAILED			  15 
#define	PW_NETWORK_UNACCESSABLE	  50
#define	PW_REDIRECT_CALL			    51
#define	PW_REDIRECT_CUSTSERVICE	  52

//acms externd
#define PW_INVALID_RATEGROUP			53      //�L�Ī��O�v��
#define	PW_INVALID_RATESET			  54      //�L�Ī��O�v�M
#define	PW_INVALID_USERNAME			  55      //�L�Ī��Τ�W
#define	PW_INVALID_BUSINESS			  56      //�L�Ī��~��,�~�ȦW�r�֥d�������T�αK�X�����T
                                          // no this prefix

#define	PW_BALANCEUSEOUT			    57	  //�l�B�Q�R��
#define	PW_NOTACTIVE				      58	  //�R�ȥd�����A���O�E����  prohibited
#define	PW_INVALID_TRGTCARDNO			59	  //�Q�R�Ȫ��d�����s�b
#define	PW_TRGTBALANCEUSEOUT			60	  //�Q�R�Ȫ��d�l�B�Χ�,����Q�R ????


#define	PW_TRGTNOTACTIVE			    61	  //�Q�R�Ȫ��d���O�E����,����Q�R
#define	PW_TRGTINSUFFICIENT_BALANCE		62	//�Q�R�Ȫ��d�l�B����

#define	PW_ACCOUNT_PROHIBITED			63	//�b��Q����
#define PW_TRGTACCOUNT_PROHIBITED	64	//�Q�R�ȱb��Q����
#define	PW_TRGTACCOUNT_EXPIRED		65	//�Q�ȱb��L��
#define	PW_TRGTACCOUNT_INUSE			66	//�Q�R�ȱb��ϥΤ�



typedef void (*RadiusNotifier) (int id,RadiusReply context);

//��l��radius
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


