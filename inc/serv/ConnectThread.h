#define		  Login				        1  //	"Login"	   
#define		  Logout				      2	//"Logout"
#define		  OpenAllLine			    3	//"OpenAllLine"
#define		  CloseAllLineAtOnce	4	//"CloseAllLine5"
#define		  CloseAllLineAftHook	5	//"CloseAllLine3"
#define		  AskAPName			      6	//"AskforApName"
#define		  OpenLine			      7	//"OpenLine"
#define		  CloseLineAtOnce		  8	//"CloseLine5"
#define		  CloseLineAftHook	  9	//"CloseLine3"	
#define		  DebugLine			      10	//"DebugLine"	
#define		  DebugAll			      11	//"DebugAll"
#define		  UpdateLineStatus	  12	//"UpdateLineSta"
#define		  UpdatePassword		  13	//"UpdatePassword"
#define		  AddNewAccount		    14	//"AddNewAccount"
#define		  DeleteAccount		    15	//"DeleteAccount"
#define		  UpdateAccount		    16	//"UpdateAccount"
#define		  UpdateAdminPassword	17	//"UpdateAdminPwd"
#define		  AddLoginIP			    18	//"AddLoginIP"
#define		  DeleteLoginIP		    19	//"DeleteLoginIP"
#define		  TooManyConnection	  20	//"TooManyCon"
#define		  NotLogin			      21	//"NotLogin"
#define		  AlreadyLogin		    22	//"AlreadyLogin"


#define     CONNECTION_TIMEOUT	300
#define     MAX_CONCURRENT_CONNECTION    5

#define     UER_PRIORITY_ROOT	  1
#define     UER_PRIORITY_SUPER	2
#define     UER_PRIORITY_NORMAL	3

#define     KERNEL_NAME         "drint64v.exe"
#define     USER_ACCOUNT_FILE   "UserAcc.txt"
#define 		USER_IP_FILE		    "UserIP.txt"
#define     SERVER_ADDR_FILE	  "ServAddr.txt"
#define	  	DEFAULT_ACCOUNT		  "root"
#define		  CHECK_IP_DISABLE	  "0.0.0.0"
#define		  DEFAULT_PWD		    	"000000"
#define		  MAX_ALLOWED_IP		  30
#define     MAX_ALLOWED_ACCOUNT	30
#define     WAIT_LOCK_TIME      -1
#define     ACC_FILE_MUTEX      "accFileMutex"
#define     IP_FILE_MUTEX       "ipFileMutex"
#define     LOGIN_TABLE_MUTEX   "LoginTable"



UINT ConnectThread(LPVOID pParam);
void CommandParse(HoSocket * mSocket , char * buff);
int  CheckFunction(CString func);
BOOL SendData(HoSocket * mSocket , char * func , char * errcode , char * data , unsigned int datalen);
