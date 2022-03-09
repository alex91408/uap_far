typedef struct 
{ 
	  char  account[16];
      char  password[32];
      char  priority[4];
}Account_Desp;

typedef struct 
{ 
	  char  ip[16];
}IP_Desp;

bool chkIP(CString ipaddr);
bool chkIPExit(CString ipaddr);
bool chkAcc(CString acc);
int  getAccPriority(CString acc);
int  addItemInAccFile(CString acc,CString pwd,CString pri);
int  updItemInAccFile(CString acc,CString pwd,CString pri,int flag);//flag 3:update 2:delete
int  getAccFile(char *buf);
int  updPwdInAccFile(CString acc,CString oldpwd,CString newpwd);
int  addItemInIPFile(CString buf);
int  delItemInIPFile(CString ip);
int  getIPFile(char * buf);
int  CallUpdateIPFile(HoSocket * mSocket , char * buff,int flag);  //1 :add 2:delete
int  CallUpdateAccountFile(HoSocket * mSocket , char * buff,int flag);
int  CallLogin(HoSocket * mSocket , char * buff);
int  CallUpdatePassword(HoSocket * mSocket , char * buff ,int flag);



