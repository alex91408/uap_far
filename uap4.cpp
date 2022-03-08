
//----------------------------------------------------------------------------------------------
// 每次更改請在此區註解    最新放最上面 CHING2  p400()  
// ver 要改   #define VERSION XXXX   每次異動版本需要修改
//
//----------------------------------------------------------------------------------------------

//#define VERSION   "20220210  V6.00 vs2019 "


//20220210 V6.0 ching2  modify uap for VS2019  及弱掃

// 20220210 要加項目
//#include "uapVar.h"
//extern ex myExp;

//exp 改  myExp  



// uap(Kerinter.lib) 中 exp 已改為 exVar
// 如果要在 uap*.cpp 中使用 exp 時, 可用以下的方法
//  A :
//   1. 在任一 uapX.cpp 中加
//      ex exp;
//      在 init_uap() 中加
//      exp = exVar;
//   2. 在其他 uap*.cpp 中加
//      extern ex exp;
//  B :
//    UAP 專案加 preprocessor definition(_GINN_UAP_USE_EXP_)
//      /D "_GINN_UAP_USE_EXP_"




//1090211 以下為弱掃參考

//1.  sprintf_s()  --> sprintf_s(A , sizeof(A), );
//2.  sscanf()   --> sscanf_s( , "%s " ,A , sizeof(A) )
//3.  strcat()   --> strcat_s(A , sizeof(A), );
//4.  memcpy()   --> memcpy_s(A , sizeof(A), );
//5.  _sopen()   --> _sopen_s(&

//  //fh = _sopen("D:\\otsfax\\URL_LOG_API\\000_API_Lock.txt", _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
//  errno_t myErrNoT = _sopen_s(&fh, "D:\\otsfax\\URL_LOG_API\\000_API_Lock.txt", _O_RDONLY, _SH_DENYNO, _S_IREAD | _S_IWRITE);
//  //fdbprintf("myErrNoT=[%d]", myErrNoT);
//
//  if (myErrNoT != 0)
//  {  err

//6.  fopen()    --> errno_t myErrNoT = fopen_s(

//    if ((fd = fopen(tmp, "r")) == NULL) {
// 改
//    errno_t myErrNoT = fopen_s(&fd, "./conf/hotchk.txt", "r");     //1060211 原 hotchk 改讀 hotchk.txt
//    if (myErrNoT != 0)

//1090121 show_dbg有執行LOG，會咬住log檔無法寫檔，改
//    //1090106 old 
//    //if ((fp = fopen(sFile, "a")) == NULL)
//    //1090121 old 讀取檔案失敗bug
//    //errno_t myErrNoT = fopen_s(&fp, sFile, "a");
//    if ((fp = _fsopen(sFile, "a", _SH_DENYWR)) == NULL)

//7.  strcpy_s()   --> strcpy_s(A , sizeof(A), );
//8.  strncpy()   --> strncpy_s(A , sizeof(A), );

//9.  ctime      --> 改成下面
//
//OLD
//
//  struct   tm *tm;
//  long     lt;
//  time(&lt);
//  tm = localtime(&lt);
//  tm->tm_year - 11, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec

//1060211 new
//  time_t now;
//  struct tm newTime;
//  time(&now);
//    errno_t errNoT = localtime_s(&newTime, &now);

//  newTime.tm_year - 11, newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, newTime.tm_sec
//

//  now += (-60 * 60 * 24);    //bofore day      //開前一天 只有這裏不同  1060217 by ching2
//  errno_t errNoT1 = localtime_s(&now_tm, &now);
//  now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday, now_tm.tm_hour, now_tm.tm_min


// 1060211 new
// time_t now;
// struct tm now_tm;
// time(&now);
// errno_t errNoT = localtime_s(&now_tm, &now);
// //now_tm.tm_year - 11, now_tm.tm_mon + 1, now_tm.tm_mday, now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec


//10.strlen(fax_v25) --> strnlen_s(fax_v25, sizeof(fax_v25)

//11._itoa(iTemp, d, 10) --> _itoa_s(iTemp, d, sizeof(d), 10);


//12.system() --> system_new(scmd)

//int  system_new(char *scmd)
//{
//	FILE *pPipe = NULL;
//
//	if ((pPipe = _popen(scmd, "rt")) == NULL)
//	{
//		printf("執行失敗. %s-%s(%d)\r\n", __FILE__, __FUNCTION__, __LINE__);
//		return(-1);
//	}
//	else
//	{
//		printf("執行成功. %s-%s(%d)\r\n", __FILE__, __FUNCTION__, __LINE__);
//		_pclose(pPipe);
//		return(0);
//	}
//}

//13.fscanf() --> fscanf_s( , "%s " ,A , sizeof(A) )
//14.strtok() --> strtok_s()

// //1081230 new 
// char* next_token;

// //1081230 old 
// //token = strtok(temp1, seps); 
// token = strtok_s(temp1, seps, &next_token);  

// fdbprintf("[token]=[%s] \r\n", token );
// //1081230 old
// //token = strtok(NULL, seps);   
// token = strtok_s(NULL, seps, &next_token);  





//20220210 OLD ---------------------------------------------------------------------------------------





//   ver 3.4  1090423  ching2 v1090423_001 ching2   錄音檔名加民國年

//   ver 3.3  1051017  ching2 v1051017_001 ching2   錄音最後會有雜音出現 , Caller NoIVR Delete --> Caller Delete NoIVR


//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
  //FAR01b3
	//old sprintf_s(myExp->var[17], "T/C=%03d%s Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss,  myExp->var[18]);     //add 	sv17_hhmmss
	//NEW sprintf_s(myExp->var[17], "T/C=%03d%s No Add NOIVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss,  myExp->var[18]);     //add 	sv17_hhmmss


//   ver 3.1  1050120  ching2  解決WAV檔一直寫BUG , T/C=%03d  --> T/C=%03d%s

//  FAR01q()	sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR Record=e:\\rec\\%s", vxp->voie, myExp->var[18]);
//  FAR01r1()	sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR Delete", vxp->voie);	
//  FAR01r2()	sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, myExp->var[18]);


//   ver 3.0  1041027  ching2  add   FAR01n1  4.FAR01a1 *1  4.FAR01a2 *2

//   ver 2.9  1040728  ching2  add   FAR01n1  press 按7: play 7700    ,  FAR01n1  press 按6: play 7600

//   ver 2.8  1040420  SKY     add  setTermDig2

//   ver 2.7  1030815  ching2  add drfar01 L4445  不接1-0 按鍵中斷

//   ver 2.6  1030807  ching2  add FAR01n1  press 按8: play 7800

//   ver 2.5  1030321  ching2  modify  ACO5 -> 6






//   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00

//   ver 2.3  1010831  ching2  add FAR01n1  press 按9:專業投資人 play 7900

//   ver 2.2  1010810  ching2  add FAR01n1  press '3' 結構型商品 play 7400

//   ver 2.1  1010529  ching2  adjust  id_no  12->14 for acc

//   ver 2.0  1010323   sven    交易錄音流程修改
//                              加入外國人銀行帳號輸入


//   ver 1.9  1000607   sven    1.ap要連"您的理財密碼確認無誤..."這句一起錄進去(drFAR01-4320)
//                              2."您的理財密碼確認無誤..." 跟 "您的流水編號為...." 最後要加嗶聲 mess9906 (FAR01p,FAR01n)
//
//                              3.FAR01c2 

//
//劉副理您好：
//
//煩請於錄音系統交易功能流程中新增一功能，
//在「交易錄音請按2.」選2.後新增時間判斷，若入線時間於15:30-24:00(依該台錄音主機時間即可)，
//系統播放「因錄音時間已超過三點半，交易將於次營業日下單，繼續錄音請按1，中止錄音請按2.」
//按1繼續以下流程，按2結束與主機通話(與客戶通話繼續)如附檔
// 
//另關於15:30分請評估若以參數化讓本行可依政策修自行修改時間,或是由 貴公司依本行指示修改兩者之報價


//
//   ver 1.8  1000531   sven    加far01b2,L01處理延遲3秒
//
//   ver 1.7  1000512   sven    客戶id檢核修改
//                              Errcode E215(密碼錯誤)時 重新輸入密碼
//
//   ver 1.6  1000408   sven    解決錄音結束後下停止指令無法立刻結束錄音bug
//                              將far01r拆成far01r1,far01r2,far01r3
//                              同步更新apstart,本檔案為正式機版本,音檔路徑為e:  
//
//   ver 1.5  1000407   sven    新增far01s. 
//                              修改email log,filename log, filesize log跟轉檔
//                              apstart也修改過
//   
//   ver 1.4  1000329   sven    0328已先上一版,此版為d:\\改為e:\\
//
//   ver 1.3  1000303   sven    產生流水編號,流水編號重置在hot做
//                              身份證字號認證
//                              分行理專錄音交易流程2&6
//   ver 1.2  1000302   sven    review code, 修改E:\\rec --> D:\\rec 存放錄音 
//   ver 1.1   980525   ching2  ok
//   ver 1.0   980525   ching2  init
//

// 980611  v1.2 ching2  add log for file_size

//
//myExp->var[1]  = ACO5      
//myExp->var[2]  = PWD8          
//myExp->var[3]  = ID4           
//myExp->var[4]  = 依產品項目錄音請按1，直接錄音請按2，變更密碼請按3 ,結束請按0
//myExp->var[5]  = 基金請按1,海外ETF請按2,海外公司債請按3,結構型商品請按4,多元外幣投資請按5
//myExp->var[6]  = V6=V5+1100    
//myExp->var[7]  = PWD8 new1         
//myExp->var[8]  = PWD8 new2     
//myExp->var[9]  = v9 請輸入2位產品代碼

//myExp->var[10] = V10編號=80** 
//               sprintf_s(myExp->var[10], ".\\mess_far1\\mess%04d.wav", 8000 + vxp->voie);

//myExp->var[11] = 流水編號
//myExp->var[12] = 身份證英文字母

//myExp->var[17] = 錄音外撥 T/C=%d Caller Add IVR Record=.\\path


//   ver 3.4  1090423  ching2 v1090423_001 ching2   錄音檔名加民國年
//1090423 OLD
//myExp->var[18] = 錄音外撥檔名 %s\\%02d%02d_%02d%02d_%s_%s.wav
//myExp->var[19] = 錄音外撥檔名 %s\\%02d%02d_%02d%02d_%s_%s.mp3

//1090423 NEW
//myExp->var[18] = 錄音外撥檔名 %s\\%03d%02d%02d_%02d%02d_%s_%s.wav
//myExp->var[19] = 錄音外撥檔名 %s\\%03d%02d%02d_%02d%02d_%s_%s.mp3



//myExp->var[21] = ID9
//myExp->var[22] = 使用者語音密碼

//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
//myExp->var[23] = rec
//myExp->var[24] = close1  close2

//myExp->cnt[1]  = ACO5 3times 
//myExp->cnt[2]  = PWD8 3times
//myExp->cnt[3]  =
//myExp->cnt[4]  =
//myExp->cnt[5]  =
//myExp->cnt[6]  =
//myExp->cnt[7]  =






#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <time.h>
//#include "wrtLog.h"
//#include "hotLOG.h"      

#include "uapVar.h"

//end---------------------------------------------------------------
extern ex myExp;


#include "md5_ching2.h"            // for md5  md5_ching2.dll      ..\inc
#include <ctime>



#include <sys/types.h>            //O_RDWR ...
#include <sys/stat.h>             //O_RDWR ...
#include <fcntl.h>                //O_RDWR ...



//1030815
int termPlay = 0;
//1040330
int pound_effect = 0;
char sv17_hhmmss[10];


//char  sCaller[100];   //主叫號
//char  sCalled[100];   //被叫號
//char  sPwd[1000];

//密碼加密
int desPass(char* passwd, char* outStr)
{
	int i, lastRem = 1;
	int factV[4] = { 3, 7, 7, 3 };

	for (i = 0; i < 4; i++) {
		lastRem = ((int)passwd[i] - 0X30 + lastRem) * factV[i] % 10;
		outStr[i] = (char)(0X30 + lastRem);
		//printf("%d, lastRem=%d\n", i, lastRem);
	}

	return strlen(outStr);
}

//show v1~v25
int showvar(int line)
{
	int i = 1;
	fdbprintf("Line= %d \r\n", line);

	for (i; i <= 24; i++)
	{
		fdbprintf("v%d = [%s]\r\n", i, myExp->var[i]);
	}
	return 0;
}



//-----------------------------------------------------------------------------
// 970630 add thread 
//-----------------------------------------------------------------------------
// for _beginthredex
typedef unsigned (WINAPI* THREADFUNC)(LPVOID lpRhread);
typedef unsigned* THREADID;

HANDLE hThread_all_far;     //hThread     //include winnt
int    retCode_all_flag_far;
DWORD  hThread_id_far;
char   sIN1_far[1000];



char  sstime_in[50];
char  smessageFile1_far[100];

int  cnt0 = 0;

//    -- 0000:帳號密碼驗證成功   
char BRA01[100];         //BRA01(分行代碼)  
char BRA05[100];         //BRA05(區別名稱)  
char SAL08[200];         //SAL08(AO_email)  
char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 



//-----------------------------------------------------------------------------
// FAR LOG 使用
//-----------------------------------------------------------------------------

typedef struct {

	char    line_no[2 + 1];            // 1.線路別 1 2 
	char    is1;                     // '/' 

	char    line_hour[3 + 1];          // 2.線路時段
	char    is2;                     // '/'

	char    stime_in[20 + 1];          // 3.進線起始時間 YYYY/MM/DD hh:mm:ss 
	char    is3;                     // '/' 

	char    etime_out[20 + 1];         // 4.出線起始時間 YYYY/MM/DD hh:mm:ss 
	char    is4;                     // '/' 

	char    lang[1 + 1];               // 5.語言 1:國語 2:台語
	char    is5;                     // '/' 

	char    trid[4 + 1];               // 6.交易 1:直接錄音 2:依產品
	char    is6;                     // '/' 

	char    error[4 + 1];              // 7.錯誤代碼   0000: 成功  E****
	char    is7;                     // '/' 

	char    bra01[3 + 1];              // 8.分行代碼   001   //BRA01(分行代碼)  
	char    is8;                     // '/' 

	char    bra05[20 + 1];              // 9.區別名稱   01   //BRA05(區別名稱)  3+1-> 20+1 for DB
	char    is9;                     // '/' 

	char    ao_code[20 + 1];           // 10.理專代碼
	char    is10;                    // '/' 

	//   ver 2.1  1010529  ching2  adjust  id_no  12->14 for acc
	//1010529 old
	//char    id_no[12+1];             // 11.客戶ID   1000310 10->12 for id T222547163
	char    id_no[14 + 1];             // 11.客戶ID   1000310 10->12 for id T222547163
	char    is11;                    // '/' 

	char    file_name[50 + 1];         // 12.錄音檔案     //30 to samll ->50 for db  \rec\99110\0504_2159_99110_2222.wav
	char    is12;                    // '/' 

	char    email[100 + 1];            // 13.email
	char    is13;                    // '/' 

	char    email_cc[100 + 1];         // 14.email_cc
	char    is14;                    // '/' 

	char    sno[15 + 1];               // 15.sno
	char    is15;                    // '/' 

	char    file_size[10 + 1];         // 16.file_size
	char    is16;                    // '/' 


} v25_1;


typedef struct _number {
	char shead[10];	                   // LOG END
	char totalnum[10];		             // 共幾筆
	v25_1 v25[5];
} number;

number num;
number* num1;



//------------------------------------------------------------------------------
//  show_time() 顯示時間函數  
//------------------------------------------------------------------------------
int show_time()
{
	char sTemp[30] = { 0 };

	//20220210 OLD
	//struct tm* tm;
	//long lt;
	//time(&lt);
	//tm = localtime(&lt);

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);

	sprintf_s(sTemp, "%04d/%02d/%02d %02d:%02d:%02d", newTime.tm_year + 1900, newTime.tm_mon + 1,
		newTime.tm_mday, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);

	fdbprintf("\r\nShow Time = [%s] \r\n", sTemp);
	return 0;
}



//1080523    V2.40  ching2  1080523 弱掃 
//-----------------------------------------------------------------------------
//  NO:3-6 system_new()
//  IN :  char *scmd
//  OUT:  0: 成功 , -1: 失敗
//-----------------------------------------------------------------------------

int  system_new(char* scmd)
{
	FILE* pPipe = NULL;

	if ((pPipe = _popen(scmd, "rt")) == NULL)
	{
		fdbprintf("執行失敗. %s-%s(%d)\r\n", __FILE__, __FUNCTION__, __LINE__);
		return(-1);
	}
	else
	{
		fdbprintf("執行成功. %s-%s(%d)\r\n", __FILE__, __FUNCTION__, __LINE__);
		_pclose(pPipe);
		return(0);
	}
}




//
//
///*
//
////------------------------------------------------------------------------------
//11111111111111111111111111111
//OTS 
////------------------------------------------------------------------------------
//
//  要先INSTALL 一次
//
//E:\utility\blat262\blat262\full>blat - -subject "測試 blat" -to
//iris@ots.com.tw,voip@ots.com.tw -cc vincent@ots.com.tw -bcc ginn@ots.com.tw -server
//email.ots.com.tw -i voip@ots.com.tw -attach
//E:\utility\blat262\blat262\docs\ChangeLog.txt,E:\utility\blat262\blat262\docs\readme.txt
//-f vincent@ots.com.tw -charset big5 -body "Blat 測試本文"
//
//1) Copy the file "Blat.exe" to your "\WINNT\SYSTEM32" directory, or to
//   any other directory in your path.
//
//blat.dll
//blat.exe
//blat.lib
//
//2) Optionaly, run "Blat -install smtp.yoursite.tld youruserid@yoursite.tld"
//
//blat -install msa.hinet.net emal33.email@msa.hinet.net
//
//
//Blat -body "您好! 有一通留言 時間:[20090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留言" -charset big5 -to tchsu@email.ots.com.tw -attach d:\winonesys\run\mess\92750662\0986720662-20090111-2018.wav
//
//
//
//
//  Blat <filename> -to <recipient> [optional switches (see below)]
//
//  Blat -SaveSettings -f <sender email addy> -server <server addr>
//       [-port <port>] [-try <try>] [-profile <profile>]
//       [-u <login id>] [-pwd <password>]
//  or
//  Blat -install <server addr> <sender's addr> [<try>[<port>[<profile>]]] [-q]
//
//  Blat -profile [-delete | "<default>"] [profile1] [profileN] [-q]
//  Blat -h
//
//
//
//
////------------------------------------------------------------------------------
//22222222222222222222222222222
//FAR  980430 先設定 DNS 及 EMAIL SMTP SERVER 
//copy  至  C:\WINDOWS.0\system32      C:\WINDOWS\system32  不行
//   blat.dll
//   blat.exe
//   blat.lib
////------------------------------------------------------------------------------
// 
//
//        IP Address. . . . . . . . . . . . : 10.50.1.201
//        Subnet Mask . . . . . . . . . . . : 255.255.255.0
//        Default Gateway . . . . . . . . . : 10.50.1.254
//        DNS Servers . . . . . . . . . . . : 10.48.12.35
//                                            10.48.12.39
//
//
//blat -install msa.hinet.net emal33.email@msa.hinet.net
//
//Blat -install <server addr> <sender's addr> [<try>[<port>[<profile>]]] [-q]
//
//
//test1 : error error error error error 
//
//
//blat -install feib.com.tw  lisahuang@feib.com.tw       feib.com.tw 第一次給錯的都不通
//
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to lisahuang@feib.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to lisahuang@feib.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//The SMTP server does not like the name lisahuang@feib.com.tw.
//Have you set the 'To:' field correctly, or do you need authorization (-u/-pw) ?
//The SMTP server response was -> 550 5.7.1 Unable to relay for lisahuang@feib.com
//.tw
//
//celinechang@feib.com.tw
//
//
//
//  C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to ching2@email.ots.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to ching2@email.ots.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//The SMTP server does not like the name ching2@email.ots.com.tw.
//Have you set the 'To:' field correctly, or do you need authorization (-u/-pw) ?
//The SMTP server response was -> 550 5.7.1 Unable to relay for ching2@email.ots.c
//om.tw
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to celinechang@feib.com.tw -u celinechang@feib.com.tw -pw 111
//11
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to celinechang@feib.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//The SMTP server does not require AUTH LOGIN.
//Are you sure server supports AUTH?
//The SMTP server does not like the name celinechang@feib.com.tw.
//Have you set the 'To:' field correctly, or do you need authorization (-u/-pw) ?
//The SMTP server response was -> 550 5.7.1 Unable to relay for celinechang@feib.c
//om.tw
//
//C:\Documents and Settings\Administrator.FAR>blat -install feib.com.tw lisahuang@
//feib.com.tw -pw 11111
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//SMTP server set to feib.com.tw on port 25 with user lisahuang@feib.com.tw, retry
// 1 time(s)
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to celinechang@feib.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to celinechang@feib.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//The SMTP server does not like the name celinechang@feib.com.tw.
//Have you set the 'To:' field correctly, or do you need authorization (-u/-pw) ?
//The SMTP server response was -> 550 5.7.1 Unable to relay for celinechang@feib.c
//om.tw
//
//
////------------------------------------------------------------------------------
//
//test2 : OK OK OK OK OK OK OK OK OK OK OK OK OK OK      
//
//          feib.com.tw -->  webmail.feib.com.tw   第二次給對的OK
////------------------------------------------------------------------------------
//
//
//C:\Documents and Settings\Administrator.FAR>blat -install webmail.feib.com.tw li
//sahuang@feib.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//SMTP server set to webmail.feib.com.tw on port 25 with user lisahuang@feib.com.t
//w, retry 1 time(s)
//
//
////別人OK------------------------------------------------------------------------
//
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to celinechang@feib.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to celinechang@feib.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//
//
////自己OK------------------------------------------------------------------------
//
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to ching2@email.ots.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to ching2@email.ots.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//
//
////外部OK------------------------------------------------------------------------
//
//C:\Documents and Settings\Administrator.FAR>Blat -body "您好! 有一通留言 時間:[2
//0090111-2018], 檔名為:[0986720662-20090111-2018.wav]  " -subject "您好! 有一通留
//言" -charset big5 -to lisahuang@feib.com.tw
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//Sending stdin.txt to lisahuang@feib.com.tw
//Subject: 您好! 有一通留言
//Login name is lisahuang@feib.com.tw
//
//
//
//
//
//Microsoft Windows XP [版本 5.1.2600]
//(C) Copyright 1985-2001 Microsoft Corp.
//
//C:\Documents and Settings\admin>blat
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//
//Win32 console utility to send mail via SMTP or post to usenet via NNTP
//by P.Mendes,M.Neal,G.Vollant,T.Charron,T.Musson,H.Pesonen,A.Donchey,C.Hyde
//  http://www.blat.net
//syntax:
//  Blat <filename> -to <recipient> [optional switches (see below)]
//
//  Blat -SaveSettings -f <sender email addy> -server <server addr>
//       [-port <port>] [-try <try>] [-profile <profile>]
//       [-u <login id>] [-pwd <password>]
//  or
//  Blat -install <server addr> <sender's addr> [<try>[<port>[<profile>]]] [-q]
//
//  Blat -profile [-delete | "<default>"] [profile1] [profileN] [-q]
//  Blat -h
//
//
//C:\Documents and Settings\admin>blat -h
//Blat v2.6.2 w/GSS encryption (build : Feb 25 2007 12:06:19)
//
//
//Win32 console utility to send mail via SMTP or post to usenet via NNTP
//by P.Mendes,M.Neal,G.Vollant,T.Charron,T.Musson,H.Pesonen,A.Donchey,C.Hyde
//  http://www.blat.net
//syntax:
//  Blat <filename> -to <recipient> [optional switches (see below)]
//
//  Blat -SaveSettings -f <sender email addy> -server <server addr>
//       [-port <port>] [-try <try>] [-profile <profile>]
//       [-u <login id>] [-pwd <password>]
//  or
//  Blat -install <server addr> <sender's addr> [<try>[<port>[<profile>]]] [-q]
//
//  Blat -profile [-delete | "<default>"] [profile1] [profileN] [-q]
//  Blat -h
//
//-------------------------------- Installation ---------------------------------
//-SaveSettings   : store common settings to the Windows Registry.  Takes the
//                  same parameters as -install, and is only for SMTP settings.
//-install[SMTP|NNTP|POP3|IMAP] <server addr> <sender email addr> [<try n times>
//                [<port> [<profile> [<username> [<password>]]]]]
//                : set server, sender, number of tries and port for profile
//                  (<try n times> and <port> may be replaced by '-')
//                  port defaults are SMTP=25, NNTP=119, POP3=110, IMAP=143
//                  default profile can be specified with a '-'
//                  username and/or password may be stored to the registry
//                  order of options is specific
//                  use -installNNTP for storing NNTP information
//                  use -installPOP3 for storing POP3 information
//                      (sender and try are ignored, use '-' in place of these)
//                  use -installIMAP for storing IMAP information
//                      (sender and try are ignored, use '-' in place of these)
//
//--------------------------------- The Basics ----------------------------------
//<filename>      : file with the message body to be sent
//                  if your message body is on the command line, use a hyphen (-)
//                  as your first argument, and -body followed by your message
//                  if your message will come from the console/keyboard, use the
//                  hyphen as your first argument, but do not use -body option.
//-of <file>      : text file containing more options (also -optionfile)
//-to <recipient> : recipient list (also -t) (comma separated)
//-tf <file>      : recipient list filename
//-cc <recipient> : carbon copy recipient list (also -c) (comma separated)
//-cf <file>      : cc recipient list filename
//-bcc <recipient>: blind carbon copy recipient list (also -b)
//                  (comma separated)
//-bf <file>      : bcc recipient list filename
//-maxNames <x>   : send to groups of <x> number of recipients
//-ur             : set To: header to Undisclosed Recipients if not using the
//                  -to and -cc options
//-subject <subj> : subject line, surround with quotes to include spaces(also -s)
//-ss             : suppress subject line if not defined
//-sf <file>      : file containing subject line
//-bodyF <file>   : file containing the message body
//-body <text>    : message body, surround with quotes (") to include spaces
//-sig <file>     : text file containing your email signature
//-tag <file>     : text file containing taglines, to be randomly chosen
//-ps <file>      : final message text, possibly for unsubscribe instructions
//
//----------------------------- Registry overrides ------------------------------
//-p <profile>    : send with server, user, and port defined in <profile>
//                : use username and password if defined in <profile>
//-profile        : list all profiles in the Registry
//-server <addr>  : specify SMTP server to be used (optionally, addr:port)
//-serverSMTP <addr>
//                : same as -server
//-serverNNTP <addr>
//                : specify NNTP server to be used (optionally, addr:port)
//-serverPOP3 <addr>
//                : specify POP3 server to be used (optionally, addr:port)
//                  when POP3 access is required before sending email
//-serverIMAP <addr>
//                : specify IMAP server to be used (optionally, addr:port)
//                  when IMAP access is required before sending email
//-f <sender>     : override the default sender address (must be known to server)
//-i <addr>       : a 'From:' address, not necessarily known to the server
//-port <port>    : port to be used on the SMTP server, defaults to SMTP (25)
//-portSMTP <port>: same as -port
//-portNNTP <port>: port to be used on the NNTP server, defaults to NNTP (119)
//-portPOP3 <port>: port to be used on the POP3 server, defaults to POP3 (110)
//-portIMAP <port>: port to be used on the IMAP server, defaults to IMAP (110)
//-u <username>   : username for AUTH LOGIN (use with -pw)
//-pw <password>  : password for AUTH LOGIN (use with -u)
//-pu <username>  : username for POP3 LOGIN (use with -ppw)
//-ppw <password> : password for POP3 LOGIN (use with -pu)
//-iu <username>  : username for IMAP LOGIN (use with -ppw)
//-ipw <password> : password for IMAP LOGIN (use with -pu)
//
//---------------------- Miscellaneous RFC header switches ----------------------
//-organization <organization>
//                : Organization field (also -o and -org)
//-ua             : include User-Agent header line instead of X-Mailer
//-x <X-Header: detail>
//                : custom 'X-' header.  eg: -x "X-INFO: Blat is Great!"
//-noh            : prevent X-Mailer/User-Agent header from showing Blat homepage
//-noh2           : prevent X-Mailer header entirely
//-d              : request disposition notification
//-r              : request return receipt
//-charset <cs>   : user defined charset.  The default is ISO-8859-1
//-a1 <header>    : add custom header line at the end of the regular headers
//-a2 <header>    : same as -a1, for a second custom header line
//-dsn <nsfd>     : use Delivery Status Notifications (RFC 3461)
//                  n = never, s = successful, f = failure, d = delayed
//                  can be used together, however N takes precedence
//-hdrencb        : use base64 for encoding headers, if necessary
//-hdrencq        : use quoted-printable for encoding headers, if necessary
//-priority <pr>  : set message priority 0 for low, 1 for high
//-sensitivity <s>   : set message sensitity 0 for personal, 1 for private,
//                  2 for company-confidential
//
//----------------------- Attachment and encoding options -----------------------
//-attach <file>  : attach binary file(s) to message (filenames comma separated)
//-attacht <file> : attach text file(s) to message (filenames comma separated)
//-attachi <file> : attach text file(s) as INLINE (filenames comma separated)
//-embed <file>   : embed file(s) in HTML.  Object tag in HTML must specify
//                  content-id using cid: tag.  eg: <img src="cid:image.jpg">
//-af <file>      : file containing list of binary file(s) to attach (comma
//                  separated)
//-atf <file>     : file containing list of text file(s) to attach (comma
//                  separated)
//-aef <file>     : file containing list of embed file(s) to attach (comma
//                  separated)
//-base64         : send binary files using base64 (binary MIME)
//-uuencode       : send binary files UUEncoded
//-enriched       : send an enriched text message (Content-Type=text/enriched)
//-unicode        : message body is in 16- or 32-bit Unicode format
//-html           : send an HTML message (Content-Type=text/html)
//-alttext <text> : plain text for use as alternate text
//-alttextf <file>: plain text file for use as alternate text
//-mime           : MIME Quoted-Printable Content-Transfer-Encoding
//-8bitmime       : ask for 8bit data support when sending MIME
//-multipart <size>
//                : send multipart messages, breaking attachments on <size>
//                  KB boundaries, where <size> is per 1000 bytes
//-nomps                : do not allow multipart messages
//
//---------------------------- NNTP specific options ----------------------------
//-groups <usenet groups>
//                : list of newsgroups (comma separated)
//
//-------------------------------- Other options --------------------------------
//-xtndxmit       : Attempt to use POP3 to transmit when accessing POP3 first
//-h              : displays this help (also -?, /?, -help or /help)
//-q              : suppresses all output to the screen
//-debug          : echoes server communications to a log file or screen
//                  (overrides -q if echoes to the screen)
//-log <file>     : log everything but usage to <file>
//-timestamp      : when -log is used, a timestamp is added to each log line
//-overwritelog   : when -log is used, overwrite the log file
//-ti <n>         : set timeout to 'n' seconds.  Blat will wait 'n' seconds for
//                  server responses
//-try <n times>  : how many times blat should try to send (1 to 'INFINITE')
//-binary         : do not convert ASCII | (pipe, 0x7c) to CrLf in the message
//                  body
//-hostname <hst> : select the hostname used to send the message via SMTP
//                  this is typically your local machine name
//-raw            : do not add CR/LF after headers
//-delay <x>      : wait x seconds between messages being sent when used with
//                  -maxnames or -multipart
//-comment <char> : use this character to mark the start of commments in
//                  options files and recipient list files.  The default is ;
//-superdebug     : hex/ascii dump the data between Blat and the server
//-superdebugT    : ascii dump the data between Blat and the server
//-------------------------------------------------------------------------------
//
//Note that if the '-i' option is used, <sender> is included in 'Reply-to:'
//and 'Sender:' fields in the header of the message.
//
//Optionally, the following options can be used instead of the -f and -i
//options:
//
//-mailfrom <addr>   The RFC 821 MAIL From: statement
//-from <addr>       The RFC 822 From: statement
//-replyto <addr>    The RFC 822 Reply-To: statement
//-returnpath <addr> The RFC 822 Return-Path: statement
//-sender <addr>     The RFC 822 Sender: statement
//
//For backward consistency, the -f and -i options have precedence over these
//RFC 822 defined options.  If both -f and -i options are omitted then the
//RFC 821 MAIL FROM statement will be defaulted to use the installation-defined
//default sender address.
//
//C:\Documents and Settings\admin>
//
//
//
//
//
//
//
//
//
//
//遠東商銀電話錄音郵件通知內容及規則
//
//郵件主旨
//主旨：遠東商銀電話錄音確認完成通知！(AO 12345)
//
//郵件內容
//主旨：電話錄音確認完成通知！(AO 12345)
//內容：您好！有一通電話錄音確認完成！
//時間：2009/04/29 20:25:00 
//檔名：\rec\12345\0429 2025 12345 3333.wav
//
//郵件通知規則
//1.郵件正本 ?錄音確認人員(理財業務人員)(AO 12345)
//2.郵件副本 ?錄音確認人員之單位主管(營業單位主管)
//
//
//
//
//*/
//

//------------------------------------------------------------------------------
//  發EMAIL
//------------------------------------------------------------------------------
DWORD WINAPI Thread_funCall_email_FAR(LPVOID lpparam)

{   //20220210 OLD
	//long lt;
	//struct tm* nowtm;

	char sbody_file[500];
	FILE* fd1;

	char sSys[2000], sAO[20], sRec_file[200], sAO_email[200], sAO_email_cc[200];


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.Thread_funCall_email_FAR() satart    ----------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	fdbprintf("Thread_funCall_email_FAR: SAL08(AO_email)=%s \r\n", SAL08);
	fdbprintf("Thread_funCall_email_FAR: SAL08_BRA03(分行經理_email)=%s \r\n", SAL08_BRA03);

	strcpy_s(sAO, myExp->var[1]);
	strcpy_s(sRec_file, smessageFile1_far);
	strcpy_s(sAO_email, SAL08);
	strcpy_s(sAO_email_cc, SAL08_BRA03);


	//20220210 OLD
	//time(&lt);
	//nowtm = localtime(&lt);


	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);



	//1.寫BODY 檔---------------------------------------------------------------

	sprintf_s(sbody_file, ".\\log_FAR\\body_%02d.txt", vxp->voie);
	//sprintf_s( sSys, "del %s", sbody_file);
	//fdbprintf( "Thread_funCall_email_FAR: system=[%s] \r\n", sSys);
	//system(sSys);
	//Sleep(1000);
	// ching2 980506 如果沒有檔案可 DEL THREAD 似乎會停止 不會往

	//內容：您好！有一通電話錄音確認完成！(AO 12345)
	//時間：2009/04/29 20:25:00 
	//檔名：\rec\12345\0429_2025_12345_3333.wav

	//20220210 OLD
	//fd1 = fopen(sbody_file, "w");

	//20220210 new
	errno_t myErrNoT22 = fopen_s(&fd1, sbody_file, "w");
	if (myErrNoT22 != 0) {
		fdbprintf( "\r\nsOpen [%s] error!!! ", sbody_file);
		//return;
	}
	else
	{
		fprintf(fd1, "內容：您好！有一通電話錄音確認完成！(AO %s) \r\n", sAO);

		fdbprintf("Thread_funCall_email_FAR: 內容：您好！有一通電話錄音確認完成！(AO %s) \r\n", sAO);

		fprintf(fd1, "時間：%04d/%02d/%02d %02d:%02d:%02d \r\n",
			newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);
		fdbprintf("Thread_funCall_email_FAR: 時間：%04d/%02d/%02d %02d:%02d:%02d \r\n",
			newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);

		fprintf(fd1, "檔名：%s \r\n", sRec_file);
		fdbprintf("Thread_funCall_email_FAR: 檔名：%s \r\n", sRec_file);

		fclose(fd1);

	}



	//2.叫BLAT---------------------------------------------------------------

	//sprintf_s(stemp, "Blat -body \"您好! 有一通留言 時間:[%s], 檔名為:[%s]  \" -subject \"您好! 有一通留言\" -charset big5 -to %s ", date ,smessageFile1_far ,semailAddress_far );

	if (strcmp(sAO_email, "\"\"") == 0 && strcmp(sAO_email_cc, "\"\"") == 0)
	{
		fdbprintf("Thread_funCall_email_FAR: 無sAO_email  無sAO_email_cc  Blat \r\n");
		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- 4.Thread_funCall_email_FAR() end   --------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		return(1);
	}
	if (strcmp(sAO_email, "\"\"") != 0 && strcmp(sAO_email_cc, "\"\"") == 0)
	{
		fdbprintf("Thread_funCall_email_FAR: 有sAO_email  無sAO_email_cc  \r\n");
		sprintf_s(sSys, "Blat -bodyf %s -subject \"遠東商銀電話錄音確認完成通知！(AO %s)\" -charset big5 -to %s  ", sbody_file, sAO, sAO_email);
	}
	if (strcmp(sAO_email, "\"\"") == 0 && strcmp(sAO_email_cc, "\"\"") != 0)
	{
		fdbprintf("Thread_funCall_email_FAR: 無sAO_email  有sAO_email_cc  \r\n");
		sprintf_s(sSys, "Blat -bodyf %s -subject \"遠東商銀電話錄音確認完成通知！(AO %s)\" -charset big5 -cc %s ", sbody_file, sAO, sAO_email_cc);
	}
	if (strcmp(sAO_email, "\"\"") != 0 && strcmp(sAO_email_cc, "\"\"") != 0)
	{
		fdbprintf("Thread_funCall_email_FAR: 有sAO_email  有sAO_email_cc  \r\n");
		sprintf_s(sSys, "Blat -bodyf %s -subject \"遠東商銀電話錄音確認完成通知！(AO %s)\" -charset big5 -to %s -cc %s ", sbody_file, sAO, sAO_email, sAO_email_cc);
	}

	fdbprintf("Thread_funCall_email_FAR: system=[%s] \r\n", sSys);
	
	
	//20220210 old system(sSys);
	system_new(sSys);

	Sleep(1000);


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.Thread_funCall_email_FAR() end   --------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");


	return(1);

}



// FAR FAR FAR


int cbDtmf(int c); // 收到按鍵時的 callback function (_uap_receive_dtmf), c 為 dtmf 按鍵

//------------------------------------------------------------------------------
// FrecA() 4.FrecA v11=0000 to 20
//------------------------------------------------------------------------------
int FrecA()
{

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FrecA() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("myExp->var[11]=[%s]  \r\n", myExp->var[11]);

	if (strcmp(myExp->var[11], "0000") == 0)
	{
		fdbprintf("vxp->branch = 20  錄音請按1,聽錄音請按2  \r\n");
		vxp->branch = 20;
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FrecA() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");

	return 0;


}
int funERR_EFS2CHT(char* sIn_error, char* sOut_mess)
{
	char  str_in[400];        // 取最大長度
	char  sFile_error[20] = { 0 };

	FILE* fp_error;


	//20220210 OLD 
	//fp_error = fopen(".\\conf\\uap_errcode.txt", "r");

	errno_t myErrNoT22 = fopen_s(&fp_error, ".\\conf\\uap_errcode.txt", "r");
	if (myErrNoT22 != 0) {
		//sprintf_s(sTemp, sizeof(sTemp), "\r\nsOpen [%s] error!!! ",  ".\\conf\\uap_errcode.txt" );
		//return;
	}

	if (fp_error == NULL)
	{
		fdbprintf("Open  .\\conf\\uap_errcode.txt  Error! \r\n ");
		return (-1);
	}

	fdbprintf("sIn_error=[%s],  ", sIn_error);
	fseek(fp_error, 0, 0);                             /* move head */

	while (fgets(str_in, 400, fp_error) != NULL)
	{
		//wrtLog("str_in=[%s] %s(%i)\n", str_in, __FILE__, __LINE__);
		if (str_in[0] != 'L')   continue;                // 非 L 跳開
		//wrtLog("str_in=[%s] %s(%i)\n", str_in, __FILE__, __LINE__);

		//strncpy(sFile_error, &str_in[9], 10);   sFile_error[10]=0;    // 取10-13 中心CODE

		/*
		#音檔檔名(mess) 錯誤代碼(errcode)   音檔內容

	L8765           E302                ;
		*/

		sscanf_s(str_in, "%*s %s", sFile_error, sizeof(sFile_error) ); //990121 add
		//wrtLog("sFile_error=[%s] %s(%i)\n", sFile_error, __FILE__, __LINE__);

		if (sFile_error[9] == 0x20) sFile_error[9] = 0;
		if (sFile_error[8] == 0x20) sFile_error[8] = 0;
		if (sFile_error[7] == 0x20) sFile_error[7] = 0;
		if (sFile_error[6] == 0x20) sFile_error[6] = 0;
		if (sFile_error[5] == 0x20) sFile_error[5] = 0;
		if (sFile_error[4] == 0x20) sFile_error[4] = 0;
		if (sFile_error[3] == 0x20) sFile_error[3] = 0;
		if (sFile_error[2] == 0x20) sFile_error[2] = 0;
		if (sFile_error[1] == 0x20) sFile_error[1] = 0;


		if (strcmp(sIn_error, sFile_error) == 0)
		{
			//sscanf(str_in,"%*s %s %*s %s", eflag, eflag); //990121 add 
			//sscanf(str_in,"%*s %s %*s *%s", eflag);
			//wrtLog("eflag=[%s] eflag=[%s] %s(%i)\n", eflag, eflag, __FILE__, __LINE__);

			fdbprintf("sFile_error=[%s] \r\n", sFile_error); //990121 add              
			strncpy_s(sOut_mess, 4, &str_in[1], 4);   sOut_mess[4] = 0;   // 取1-4 mess code
			//wrtLog("sOut_mess=[%s] %s(%i)\n", sOut_mess, __FILE__, __LINE__);

			if (strcmp(sOut_mess, "    ") == 0)
			{
				//wrtLog("return 00000000 %s(%i)\n", __FILE__, __LINE__);
				strcpy_s(sOut_mess, 2, "");
				//wrtLog("return 00000000 %s(%i)\n", __FILE__, __LINE__);
				fdbprintf("轉換 IPIVR Error=[%s] ==> [%s] \r\n", sIn_error, sOut_mess);
				fclose(fp_error);
				//wrtLog("return 00000000 %s(%i)\n", __FILE__, __LINE__);
				return(0);
			}
			else
			{
				//wrtLog("return 444444444444 %s(%i)\n", __FILE__, __LINE__);
				fdbprintf("轉換 IPIVR Error=[%s] ==> [%s] \r\n", sIn_error, sOut_mess);
				fclose(fp_error);
				//wrtLog("return 444444444444 %s(%i)\n", __FILE__, __LINE__);
				return(4);
			}
		}
	} /* while */


	strcpy_s(sOut_mess, 2, "");

	fdbprintf(" << 找不到對照表 >> ==> 轉換 IPIVR Error=[%s] ==> [%s] \r\n", sIn_error, sOut_mess);

	//wrtLog(" << 找不到對照表 >> ==> 轉換 IPIVR Error=[%s] ==> [%s] %s(%i)\n", sIn_error, sOut_mess, __FILE__, __LINE__);

	fclose(fp_error);
	return(0);
}



//------------------------------------------------------------------------------
// 4.FAR01a() init 
//------------------------------------------------------------------------------
int FAR01a()
{

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01a() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	//--------------------------------------------------------------------------------------
	// 0.設定按鍵時的 callback function
	//--------------------------------------------------------------------------------------
	pound_effect = 0;
	fdbprintf("pound_effect = 0 \r\n");

	termPlay = 0;
	fdbprintf("termPlay = 0 \r\n");

	setFuncPointToKer("_uap_receive_dtmf", (NFUNCPTR)cbDtmf);

	//--------------------------------------------------------------------------------------
	// 1.接通函數 START
	//--------------------------------------------------------------------------------------
	setFuncPointToKer("_uap_check_play", NULL);
	ginn_answercall();					// Answer the call

	//inFrom = FXO;					  		// default from FXO  // for *1(Transfer), *2(Hold), *3(Conference)
	//fdbprintf("inFrom=FXO\r\n");
	//--------------------------------------------------------------------------------------
	// 1.接通函數 END
	//--------------------------------------------------------------------------------------


	//    -- 0000:帳號密碼驗證成功   
	memset(BRA01, 0x00, sizeof(BRA01));      // char BRA01[100];         //BRA01(分行代碼)  
	memset(BRA05, 0x00, sizeof(BRA05));      // char BRA05[100];         //BRA05(區別名稱)  
	memset(SAL08, 0x00, sizeof(SAL08));      // char SAL08[200];         //SAL08(AO_email)  
	memset(SAL08_BRA03, 0x00, sizeof(SAL08_BRA03));      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 



	int b = 1;
	for (b = 1;b <= 25;b++)
	{
		memset(myExp->var[b], 0x0, sizeof(myExp->var[b]));
	}

	cnt0 = 0;

	int a = 0;
	for (a = 0;a <= 4;a++)
	{
		memset(num.v25[a].line_no, 0x0, sizeof(num.v25[a].line_no));
		memset(num.v25[a].line_hour, 0x0, sizeof(num.v25[a].line_hour));
		memset(num.v25[a].stime_in, 0x0, sizeof(num.v25[a].stime_in));
		memset(num.v25[a].etime_out, 0x0, sizeof(num.v25[a].etime_out));
		memset(num.v25[a].lang, 0x0, sizeof(num.v25[a].lang));
		memset(num.v25[a].error, 0x0, sizeof(num.v25[a].error));
		memset(num.v25[a].trid, 0x0, sizeof(num.v25[a].trid));

		memset(num.v25[a].ao_code, 0x0, sizeof(num.v25[a].ao_code));
		memset(num.v25[a].id_no, 0x0, sizeof(num.v25[a].id_no));
		memset(num.v25[a].file_name, 0x0, sizeof(num.v25[a].file_name));
		memset(num.v25[a].sno, 0x0, sizeof(num.v25[a].sno));
		memset(num.v25[a].file_size, 0x0, sizeof(num.v25[a].file_size));

	}


	char    sTemp[2000];

	//20220210 OLD 
	//long    lt;
	//struct  tm* newtm;
	//time(&lt);
	//newtm = localtime(&lt);

	//20220210 OLD 
	//CTime now(time(NULL));

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	sprintf_s(sTemp, "%4d/%02d/%02d %02d:%02d:%02d", newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday
		, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);
	sprintf_s(sstime_in, "%4d%02d%02d_%02d%02d%02d", newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday
		, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);
	int c = 0;
	for (c = 0;c <= 4;c++)
	{
		//---------------------write log 進線時間 --------------------------
		strcpy_s(num.v25[c].stime_in, sTemp);
		//---------------------write log 離線時間 --------------------------
		strcpy_s(num.v25[c].etime_out, sTemp);
	}



	//------------線路時段 line_hour  以半小時為準的-----------------------
	int iTemp = 0;
	char d[4 + 5] = { 0 };

	//20220210 OLD
	//iTemp = now.GetHour() * 2 + 1;          //48個半小時時段
	//if (now.GetMinute() > 30) iTemp = iTemp + 1;

	//20220210 new
	/* ********** 填入時段 **************** */
	iTemp = newTime.tm_hour * 2 + 1;     //48個半小時時段
	if (newTime.tm_min > 30) iTemp = iTemp + 1;


	fdbprintf(" line_hour 進線時段 (半小時) =[%d]  \r\n", iTemp);
	
	//20220210 OLD 
	//itoa(iTemp, d, 10);                    // itoa  把iTemp的 int值  轉換成字串給 d，以十進位為底
	//20220210 new
	_itoa_s(iTemp, d, 10);                    // itoa  把iTemp的 int值  轉換成字串給 d，以十進位為底


	memcpy(num.v25[0].line_hour, d, sizeof(num.v25[0].line_hour) - 1);
	memcpy(num.v25[1].line_hour, d, sizeof(num.v25[1].line_hour) - 1);
	memcpy(num.v25[2].line_hour, d, sizeof(num.v25[2].line_hour) - 1);
	memcpy(num.v25[3].line_hour, d, sizeof(num.v25[3].line_hour) - 1);
	memcpy(num.v25[4].line_hour, d, sizeof(num.v25[4].line_hour) - 1);
	//fdbprintf(" ***  \r\r num.v25[cnt0].line_hour = %s ",num.v25[cnt0].line_hour );


	//--------------------write log ------------------------------------------
	strcpy_s(num.v25[0].error, "E997");    //E997 未輸入按鍵
	strcpy_s(num.v25[1].error, "E997");    //E997 未輸入按鍵
	strcpy_s(num.v25[2].error, "E997");    //E997 未輸入按鍵
	strcpy_s(num.v25[3].error, "E997");    //E997 未輸入按鍵
	strcpy_s(num.v25[4].error, "E997");    //E997 未輸入按鍵

  //--------------------write log ------------------------------------------
	strcpy_s(num.v25[0].trid, "0");    //0.主選單
	strcpy_s(num.v25[1].trid, "0");    //0.主選單
	strcpy_s(num.v25[2].trid, "0");    //0.主選單
	strcpy_s(num.v25[3].trid, "0");    //0.主選單
	strcpy_s(num.v25[4].trid, "0");    //0.主選單





	// 2.設定線路------------------------------------------------------
	sprintf_s(num.v25[0].line_no, "%d", vxp->voie);
	sprintf_s(num.v25[1].line_no, "%d", vxp->voie);
	sprintf_s(num.v25[2].line_no, "%d", vxp->voie);
	sprintf_s(num.v25[3].line_no, "%d", vxp->voie);
	sprintf_s(num.v25[4].line_no, "%d", vxp->voie);
	fdbprintf(" \r\n\r\n  線路別 = [%d]  \r\n", vxp->voie);

	// 3.設定語言------------------------------------------------------
	strcpy_s(num.v25[0].lang, "1");
	strcpy_s(num.v25[1].lang, "1");
	strcpy_s(num.v25[2].lang, "1");
	strcpy_s(num.v25[3].lang, "1");
	strcpy_s(num.v25[4].lang, "1");
	fdbprintf(" \r\n\r\n  語言 = 1  \r\n");

	//filename
	strcpy_s(num.v25[0].file_name, "-");
	strcpy_s(num.v25[1].file_name, "-");
	strcpy_s(num.v25[2].file_name, "-");
	strcpy_s(num.v25[3].file_name, "-");
	strcpy_s(num.v25[4].file_name, "-");

	//file_size
	strcpy_s(num.v25[0].file_size, "0");
	strcpy_s(num.v25[1].file_size, "0");
	strcpy_s(num.v25[2].file_size, "0");
	strcpy_s(num.v25[3].file_size, "0");
	strcpy_s(num.v25[4].file_size, "0");


	//-------------把  is  全部訂好  '/' ------------------
	num.v25[0].is1 = '/'; num.v25[1].is1 = '/';	num.v25[2].is1 = '/'; num.v25[3].is1 = '/'; 	num.v25[4].is1 = '/';
	num.v25[0].is2 = '/'; num.v25[1].is2 = '/';	num.v25[2].is2 = '/'; num.v25[3].is2 = '/'; 	num.v25[4].is2 = '/';
	num.v25[0].is3 = '/'; num.v25[1].is3 = '/';	num.v25[2].is3 = '/'; num.v25[3].is3 = '/'; 	num.v25[4].is3 = '/';
	num.v25[0].is4 = '/'; num.v25[1].is4 = '/';	num.v25[2].is4 = '/'; num.v25[3].is4 = '/'; 	num.v25[4].is4 = '/';
	num.v25[0].is5 = '/'; num.v25[1].is5 = '/';	num.v25[2].is5 = '/'; num.v25[3].is5 = '/'; 	num.v25[4].is5 = '/';
	num.v25[0].is6 = '/'; num.v25[1].is6 = '/';	num.v25[2].is6 = '/'; num.v25[3].is6 = '/'; 	num.v25[4].is6 = '/';
	num.v25[0].is7 = '/'; num.v25[1].is7 = '/';	num.v25[2].is7 = '/'; num.v25[3].is7 = '/'; 	num.v25[4].is7 = '/';
	num.v25[0].is8 = '/'; num.v25[1].is8 = '/';	num.v25[2].is8 = '/'; num.v25[3].is8 = '/'; 	num.v25[4].is8 = '/';
	num.v25[0].is9 = '/'; num.v25[1].is9 = '/';	num.v25[2].is9 = '/'; num.v25[3].is9 = '/'; 	num.v25[4].is9 = '/';
	num.v25[0].is10 = '/'; num.v25[1].is10 = '/';	num.v25[2].is10 = '/'; num.v25[3].is10 = '/'; 	num.v25[4].is10 = '/';
	num.v25[0].is11 = '/'; num.v25[1].is11 = '/';	num.v25[2].is11 = '/'; num.v25[3].is11 = '/'; 	num.v25[4].is11 = '/';
	num.v25[0].is12 = '/'; num.v25[1].is12 = '/';	num.v25[2].is12 = '/'; num.v25[3].is12 = '/'; 	num.v25[4].is12 = '/';
	//1000310
	num.v25[0].is13 = '/'; num.v25[1].is13 = '/';	num.v25[2].is13 = '/'; num.v25[3].is13 = '/'; 	num.v25[4].is13 = '/';
	num.v25[0].is14 = '/'; num.v25[1].is14 = '/';	num.v25[2].is14 = '/'; num.v25[3].is14 = '/'; 	num.v25[4].is14 = '/';
	num.v25[0].is15 = '/'; num.v25[1].is15 = '/';	num.v25[2].is15 = '/'; num.v25[3].is15 = '/'; 	num.v25[4].is15 = '/';
	num.v25[0].is16 = '/'; num.v25[1].is16 = '/';	num.v25[2].is16 = '/'; num.v25[3].is16 = '/'; 	num.v25[4].is16 = '/';


	// V10=8000+線路
	sprintf_s(myExp->var[10], ".\\mess_far1\\mess%04d.wav", 8000 + vxp->voie);
	fdbprintf("myExp->var[10]=[%s]  路徑 !!! \r\n", myExp->var[10]);

	sprintf_s(sTemp, "del %s ", myExp->var[10]);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);



	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01a() end     -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;

}




//------------------------------------------------------------------------------
// FAR01b() 組L01上行: huang
//------------------------------------------------------------------------------
int FAR01b()
{
    //20220210 OLD
	//long    lt;
	//struct  tm* newtm;


	char    sTemp[2000];
	int     times;
	char    sLog_file[500];
	FILE*   fd1;


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01b() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("cnt0 = [%d]\r\n", cnt0);
	times = cnt0 + 1;  // 總交易筆數

	if (strcmp(myExp->var[4], "0") == 0 && strcmp(num.v25[cnt0].error, "E997") == 0)  //980610  去除按0多的一筆LOG
		times = times - 1;  // 總交易筆數

	fdbprintf("times = [%d]", times);

	//20220210 OLD
	//time(&lt);
	//newtm = localtime(&lt);
	//CTime now(time(NULL));     //這是系統內的時間呼叫

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);



	sprintf_s(sTemp, "%4d/%02d/%02d %02d:%02d:%02d", newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday
		, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);

	//--------------write log 交易的結束時間 = 離線時間 -------------
	strcpy_s(num.v25[0].etime_out, sTemp);
	strcpy_s(num.v25[1].etime_out, sTemp);
	strcpy_s(num.v25[2].etime_out, sTemp);
	strcpy_s(num.v25[3].etime_out, sTemp);
	strcpy_s(num.v25[4].etime_out, sTemp);


	strcpy_s(num.v25[0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[1].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[2].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[3].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[4].bra01, BRA01);   //分行代碼

	strcpy_s(num.v25[0].bra05, BRA05);   //區別名稱
	strcpy_s(num.v25[1].bra05, BRA05);   //區別名稱
	strcpy_s(num.v25[2].bra05, BRA05);   //區別名稱
	strcpy_s(num.v25[3].bra05, BRA05);   //區別名稱
	strcpy_s(num.v25[4].bra05, BRA05);   //區別名稱


	/* ************************************ */
	// write log  num.totalnum    總交易筆數
	sprintf_s(num.totalnum, "%d", times);
	fdbprintf("times == [%d]\n", times);

	//961026 write --------------------------------------------------------
	fdbprintf("num.v25[1].idx\n");
	sprintf_s(sLog_file, ".//log_far//log%02d.txt", vxp->voie);
	fdbprintf("sLog_file = [%s]\n", sLog_file);
	
	//20220210 OLD 
	//fd1 = fopen(sLog_file, "w");                                // 利用開檔讀檔的方式儲存 LOG
	
	//20220210 new
	//errno_t myErrNoT22 = fopen_s(&fd1, sLog_file, "w");
	//if (myErrNoT22 != 0) {
	//	//sprintf_s(sTemp, sizeof(sTemp), "\r\nsOpen [%s] error!!! ", sLog_file);
	//	//return 1;
	//	//open error 
	//}
	//else
	//{
	//	int ierr = 0;
	//	if(	fseek(fd1, 0, SEEK_SET) <0 )
	//		fdbprintf("fseek() error \r\n\r\n");
	//		

	//	//fread(&num.shead ,sizeof(char),sizeof(num),fd1);
	//	fwrite(&num.shead, sizeof(char), sizeof(num), fd1);
	//	fclose(fd1);
	//}


	errno_t myErr = fopen_s(&fd1, sLog_file, "w");
	fdbprintf("fd1 = [%d] \n ", myErr);
	// 利用開檔讀檔的方式儲存 LOG
   //fseek(fd1, 0, SEEK_SET );
   //fread(&num.shead ,sizeof(char),sizeof(num),fd1);
	fwrite(&num.shead, sizeof(char), sizeof(num), fd1);
	fclose(fd1);



	// 由於LOG筆數多改為寫檔 V25 = 筆數
	sprintf_s(myExp->var[25], "%d", times);                        // 把交易筆數丟給變數25   



	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01b() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");

	return 0;


}


//------------------------------------------------------------------------------
// FAR01b2() 外撥錄音結束-步驟2
// delay 3 sec 處理L01
// "T/C=%03d%s Caller NoIVR Delete"
//------------------------------------------------------------------------------
int FAR01b2()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01b2() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("\r\nSleep 3 sec \r\n");
	Sleep(3000);

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
	fdbprintf("var[23]=[%s] , var[24]=[%s] \r\n", myExp->var[23], myExp->var[24]);

	if (strncmp(myExp->var[23], "rec", 3) == 0)
	{

		//   ver 3.1  1050120  ching2  解決WAV檔一直寫BUG , T/C=%03d  --> T/C=%03d%s
		//  FAR01r1()	sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR Delete", vxp->voie);	
		//  FAR01r2()	sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, myExp->var[18]);

			//sv17_hhmmss
		//  FAR01r1()	sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR Delete", vxp->voie);	

				//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
		if (strcmp(myExp->var[24], "") == 0)
		{
			//   ver 3.3  1051017  ching2 v1051017_001 ching2   錄音最後會有雜音出現 , Caller NoIVR Delete --> Caller Delete NoIVR 
			//old sprintf_s(myExp->var[17], "T/C=%03d%s Caller NoIVR Delete", vxp->voie, sv17_hhmmss);    //add 	sv17_hhmmss
			sprintf_s(myExp->var[17], "T/C=%03d%s Caller Delete NoIVR", vxp->voie, sv17_hhmmss);    //add 	sv17_hhmmss
			fdbprintf("v17=[%s]\r\n", myExp->var[17]);
		}
		else
		{
			fdbprintf("vxp->branch = 9038   close2  \r\n");
			vxp->branch = 9038;
		}

	}
	else
	{
		fdbprintf("vxp->branch = 10  結束  \r\n");
		vxp->branch = 10;
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01b2() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//------------------------------------------------------------------------------
// FAR01b3() 外撥錄音結束-步驟3
// "T/C=%03d%s Caller Add IVR NoRecord=e:\\rec\\%s"
//------------------------------------------------------------------------------
int FAR01b3()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01b3() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
	fdbprintf("var[23]=[%s] , var[24]=[%s] \r\n", myExp->var[23], myExp->var[24]);

	if (strncmp(myExp->var[23], "rec", 3) == 0)
	{

		//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
		if (strncmp(myExp->var[24], "close1", 6) == 0)
		{


			//   ver 3.1  1050120  ching2  解決WAV檔一直寫BUG , T/C=%03d  --> T/C=%03d%s 
			//  FAR01r1()	sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR Delete", vxp->voie);	
	  //  FAR01r2()	sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, myExp->var[18]);

	  //sv17_hhmmss
	  //  FAR01r2()	sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, myExp->var[18]);

	  //   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
		//OLD
		//sprintf_s(myExp->var[17], "T/C=%03d%s Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss,  myExp->var[18]);     //add 	sv17_hhmmss
			sprintf_s(myExp->var[17], "T/C=%03d%s No Add NOIVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss, myExp->var[18]);     //add 	sv17_hhmmss
			fdbprintf("v17=[%s]\r\n", myExp->var[17]);
		}
		else
		{
			fdbprintf("vxp->branch = 10  結束  \r\n");
			vxp->branch = 10;
		}

	}
	else
	{
		fdbprintf("vxp->branch = 10  結束  \r\n");
		vxp->branch = 10;
	}
	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題



	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01b3() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}







//   ver 3.0  1041027  ching2  add   FAR01n1  4.FAR01a1 *1  4.FAR01a2 *2

//------------------------------------------------------------------------------
// 4.FAR01a1() *1 
//------------------------------------------------------------------------------
int FAR01a1()
{

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01a1() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("new myExp->var[1]=[%s]  \r\n", myExp->var[1]);
	//log
	strcpy_s(num.v25[0].ao_code, myExp->var[1]);
	strcpy_s(num.v25[1].ao_code, myExp->var[1]);
	strcpy_s(num.v25[2].ao_code, myExp->var[1]);
	strcpy_s(num.v25[3].ao_code, myExp->var[1]);
	strcpy_s(num.v25[4].ao_code, myExp->var[1]);

	//log
	strcpy_s(num.v25[cnt0].error, "0000");

	//    -- 0000:帳號密碼驗證成功   
	memset(BRA01, 0x00, sizeof(BRA01));      // char BRA01[100];         //BRA01(分行代碼)  
	memset(BRA05, 0x00, sizeof(BRA05));      // char BRA05[100];         //BRA05(區別名稱)  
	memset(SAL08, 0x00, sizeof(SAL08));      // char SAL08[200];         //SAL08(AO_email)  
	memset(SAL08_BRA03, 0x00, sizeof(SAL08_BRA03));      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 

	//ching2 980504
	//sscanf(myExp->var[25] , "%*s %*s %s %s %s %s %s ", error ,BRA01, BRA05, SAL08, SAL08_BRA03 );   

	strcpy_s(BRA01, "888");          // char BRA01[100];         //BRA01(分行代碼)  
	strcpy_s(BRA05, "區域888");      // char BRA05[100];         //BRA05(區別名稱)  
	strcpy_s(SAL08, "");      // char SAL08[200];         //SAL08(AO_email)  
	strcpy_s(SAL08_BRA03, "");      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 


	fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
	fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
	fdbprintf("SAL08(AO_email)=%s \r\n", SAL08);
	fdbprintf("SAL08_BRA03(分行經理_email)=%s \r\n", SAL08_BRA03);
	//log
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱




	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01a1() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//   ver 3.0  1041027  ching2  add   FAR01n1  4.FAR01a1 *1  4.FAR01a2 *2

//------------------------------------------------------------------------------
// 4.FAR01a1() *2 
//------------------------------------------------------------------------------
int FAR01a2()
{

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01a2() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("new myExp->var[1]=[%s]  \r\n", myExp->var[1]);
	//log
	strcpy_s(num.v25[0].ao_code, myExp->var[1]);
	strcpy_s(num.v25[1].ao_code, myExp->var[1]);
	strcpy_s(num.v25[2].ao_code, myExp->var[1]);
	strcpy_s(num.v25[3].ao_code, myExp->var[1]);
	strcpy_s(num.v25[4].ao_code, myExp->var[1]);

	//log
	strcpy_s(num.v25[cnt0].error, "0000");

	//    -- 0000:帳號密碼驗證成功   
	memset(BRA01, 0x00, sizeof(BRA01));      // char BRA01[100];         //BRA01(分行代碼)  
	memset(BRA05, 0x00, sizeof(BRA05));      // char BRA05[100];         //BRA05(區別名稱)  
	memset(SAL08, 0x00, sizeof(SAL08));      // char SAL08[200];         //SAL08(AO_email)  
	memset(SAL08_BRA03, 0x00, sizeof(SAL08_BRA03));      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 

	//ching2 980504
	//sscanf(myExp->var[25] , "%*s %*s %s %s %s %s %s ", error ,BRA01, BRA05, SAL08, SAL08_BRA03 );   

	strcpy_s(BRA01, "888");          // char BRA01[100];         //BRA01(分行代碼)  
	strcpy_s(BRA05, "區域888");      // char BRA05[100];         //BRA05(區別名稱)  
	strcpy_s(SAL08, "");      // char SAL08[200];         //SAL08(AO_email)  
	strcpy_s(SAL08_BRA03, "");      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 


	fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
	fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
	fdbprintf("SAL08(AO_email)=%s \r\n", SAL08);
	fdbprintf("SAL08_BRA03(分行經理_email)=%s \r\n", SAL08_BRA03);
	//log
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱




	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01a2() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}




//------------------------------------------------------------------------------
// FAR01c() S01上行: 組檢查ao_code 
//------------------------------------------------------------------------------
int FAR01c()
{

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01c() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	//test md5
	//void md5(char* lMessage,char *md5_str);    //lMessage為待加密字符串，md5_str為得到的md5
	//  6789000000000 -->  86f60893d3c7918b3c4265560872fdda
	//char md5_str[40];
	//char s[100];
	//strcpy_s(s,"6789000000000");
	//md5( s, md5_str);
	//fdbprintf("md5_str=[%s]  \r\n", md5_str);

	fdbprintf("old myExp->var[1]=[%s]  \r\n", myExp->var[1]);
	//fdbprintf("myExp->var[2]=[%s]  \r\n", myExp->var[2]);

  //   ver 2.5  1030321  ching2  modify  ACO5 -> 6

	if (strlen(myExp->var[1]) == 6 && myExp->var[1][0] == '0')
	{
		char v1[10];
		fdbprintf("myExp->var[1]= 6碼且第一碼為 0 去除0  \r\n");
		sprintf_s(v1, myExp->var[1] + 1);
		strcpy_s(myExp->var[1], v1);
	}

	fdbprintf("new myExp->var[1]=[%s]  \r\n", myExp->var[1]);


	//log
	strcpy_s(num.v25[0].ao_code, myExp->var[1]);
	strcpy_s(num.v25[1].ao_code, myExp->var[1]);
	strcpy_s(num.v25[2].ao_code, myExp->var[1]);
	strcpy_s(num.v25[3].ao_code, myExp->var[1]);
	strcpy_s(num.v25[4].ao_code, myExp->var[1]);



	char sID_PWD[100];
	char spwd[100];

	sprintf_s(sID_PWD, "%s%s", myExp->var[1], myExp->var[2]);
	md5(sID_PWD, spwd);

	fdbprintf("spwd=[%s]  \r\n", spwd);


	//myExp->var[1]  = ACO5      
	//myExp->var[2]  = PWD8          
	sprintf_s(myExp->var[25], "INQ 00 %s %s END", myExp->var[1], spwd);

	strcpy_s(num.v25[cnt0].error, "E999");  //連線程式暫停服務,稍後再撥


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01c() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");

	return 0;


}

//------------------------------------------------------------------------------
// FAR01c2() 讀取時間參數檔; 比對時間區間 
//------------------------------------------------------------------------------
int FAR01c2()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01c2() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	//read hotFAR.txt

	FILE* fd;
	char tmp[2048] = { 0 };

	//char temp[2048] = { 0 };2

	char data[2048] = { 0 };
	char s1[2048] = { 0 };
	char time_s[20] = { 0 }, hh_s[20] = { 0 }, mm_s[20] = { 0 };
	char time_e[20] = { 0 }, hh_e[20] = { 0 }, mm_e[20] = { 0 };
	int iTime_s, iTime_e;
	int idx = 1;

	fdbprintf("start read hotFAR.txt for time_s and time_e \r\n");
	
	
	strcpy_s(tmp, "./conf/hotFAR.txt");   // 971021 FAR 的路徑為 conf


	//20220210 OLD
	//if ((f = fopen(temp, "r")) == NULL)
	//{
	//	fdbprintf("error: can not open hotFAR.txt\r\n");
	//	return(-1);
	//}
	// 
	//20220210 new
	errno_t myErrNoT = fopen_s(&fd, tmp, "r");
	if (myErrNoT != 0){
		fdbprintf("error: can not open hotFAR.txt\r\n");
		return(-1);;
	}

	memset(tmp, 0x20, sizeof(tmp));

	while (fgets(tmp, sizeof(tmp), fd) != 0)
	{
		//memset(func, 0x20, sizeof(func));
		memset(data, 0x20, sizeof(data));


		sprintf_s(s1, "temp=[%s] \r\n", tmp);
		//fdbprintf(s1);

			//1
		if (strncmp(tmp, "time_s", strlen("time_s")) == 0)
		{
			sscanf_s(tmp, "%*s %s", data, sizeof(data) );
			strcpy_s(time_s, data);
			fdbprintf("time_s=[%s]", time_s);
			fdbprintf(data);
			fdbprintf("\r\n");
			continue;
		}
		//2
		if (strncmp(tmp, "time_e", strlen("time_e")) == 0)
		{
			sscanf_s(tmp, "%*s %s", data, sizeof(data));
			strcpy_s(time_e, data);
			fdbprintf("time_e=[%s]", time_e);
			fdbprintf(data);
			fdbprintf("\r\n");
			continue;
		}
	}
	Sleep(1000);

	//拆解time_s, time_e
	memcpy(hh_s, time_s, 2);  memcpy(mm_s, time_s + 3, 2);
	iTime_s = atoi(hh_s) * 100 + atoi(mm_s);
	fdbprintf("iTime_s= [%d]", iTime_s);
	memcpy(hh_e, time_e, 2);  memcpy(mm_e, time_e + 3, 2);
	iTime_e = atoi(hh_e) * 100 + atoi(mm_e);
	fdbprintf("iTime_e= [%d]", iTime_e);

	//取得時間
	//20220210 OLD 
	//struct   tm* tm;
	//long     lt;

	//time(&lt);
	//tm = localtime(&lt);
	
	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	//fdbprintf("[%02d/%02d/%02d]-[%02d:%02d:%02d] \r\n",newTime.tm_year-11,newTime.tm_mon+1,newTime.tm_mday ,newTime.tm_hour,newTime.tm_min,newTime.tm_sec);

	int timenow = newTime.tm_hour * 100 + newTime.tm_min;
	fdbprintf("timenow = [%d]\r\n", timenow);

	//判斷時間
	//ex:
	//          timenow=1600
	//  ----*---------#--------------------*------>
	//    1530                            2400
	//
	if ((iTime_s - timenow <= 0) && (iTime_e - timenow >= 0))
	{
		//在規定時間區間內
		myExp->v[idx++] = 1301;        //因錄音時間已超過
		myExp->v[idx++] = 600 + atoi(hh_s);    //X點
		myExp->v[idx++] = 700 + atoi(mm_s);    //Y分
		vxp->branch = 3985;
	}
	else
	{
		vxp->branch = 183;
	}


	myExp->v[idx++] = -1;
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01c2() end  vxp->branch=[%d] ---------------------------------------\r\n", vxp->branch);
	fdbprintf("---------------------------------------------------------------------------\r\n");

	return 0;
}




//------------------------------------------------------------------------------
// FAR01d() S01 00 下行:  拆解
//
//--Send  rec  host交易代號 S01
//--INQ  00: 帳號 密碼驗證
//
//--上行 V25= INQ  00  acc  pwd  END      acc:帳號 , pwd:密碼
//
//--下行 V25= RES  0000  BRA01 BRA05 SAL08 SAL08_BRA03 END              
//--                                      0000:帳號密碼驗證成功   BRA01(分行代碼)  BRA05(區別名稱)  SAL08(AO_email)  SAL08_BRA03(分行經理_email) 
//
//--     V25= RES  E001  END              E001:帳號不存在
//--     V25= RES  E002  BRA01 BRA05 END              E002:首次變更密碼
//--     V25= RES  E003  BRA01 BRA05 END              E003:密碼被鎖定
//--     V25= RES  E004  BRA01 BRA05 END              E004:密碼逾時需變更
//--     V25= RES  E005  BRA01 BRA05 END              E005:密碼錯誤
//--     V25= RES  E998  END              E998:無法連接資料庫 
//
//------------------------------------------------------------------------------
int FAR01d()
{
	char error[50] = { 0x00 };


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01d() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	//1000310
	//sprintf_s(myExp->var[25], "RES 0000 BRA01 BRA05 SAL08 SAL08_BRA03 END");
	fdbprintf("myExp->var[25]=[%s]  \r\n", myExp->var[25]);

	sscanf_s(myExp->var[25], "%*s %s", error, sizeof(error));
	fdbprintf("error=%s \r\n", error);

	//log
	strcpy_s(num.v25[cnt0].error, error);


	if (strcmp(error, "0000") == 0)       //0000:帳號 密碼驗證成功
	{

		//    -- RES 0000:帳號密碼驗證成功   BRA01(分行代碼)  BRA05(區別名稱)  SAL08(AO_email)  SAL08_BRA03(分行經理_email) 

		//    -- 0000:帳號密碼驗證成功   
		memset(BRA01, 0x00, sizeof(BRA01));      // char BRA01[100];         //BRA01(分行代碼)  
		memset(BRA05, 0x00, sizeof(BRA05));      // char BRA05[100];         //BRA05(區別名稱)  
		memset(SAL08, 0x00, sizeof(SAL08));      // char SAL08[200];         //SAL08(AO_email)  
		memset(SAL08_BRA03, 0x00, sizeof(SAL08_BRA03));      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 

		//ching2 980504
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05), SAL08, sizeof(SAL08), SAL08_BRA03, sizeof(SAL08_BRA03));

		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		fdbprintf("SAL08(AO_email)=%s \r\n", SAL08);
		fdbprintf("SAL08_BRA03(分行經理_email)=%s \r\n", SAL08_BRA03);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱


		//vxp->branch = 180; 

		if (strcmp(myExp->var[1], "88888") == 0)  //myExp->var[1]  = ACO5  
		{
			vxp->branch = 179;  //169 行  drFrec  錄音流程
		}

	}
	else if (strcmp(error, "E001") == 0)  //E001:帳號不存在
	{
		vxp->branch = 171;
		cnt0 = cnt0 + 1;
	}
	else if (strcmp(error, "E002") == 0)  //E002:首次變更密碼
	{
		//ching2 980504
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05));      //RES E002 首次變更密碼 *** ***  
		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱

		vxp->branch = 172;
		cnt0 = cnt0 + 1;

	}
	else if (strcmp(error, "E003") == 0)  //E003:密碼被鎖定
	{
		//ching2 980504
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05));
		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱
		vxp->branch = 173;
		//cnt0= cnt0 +1;

	}
	else if (strcmp(error, "E004") == 0)  //E004:密碼逾時需變更
	{
		//ching2 980504
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05));
		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱
		vxp->branch = 174;
		cnt0 = cnt0 + 1;
	}
	else if (strcmp(error, "E005") == 0)  //E005:密碼錯誤
	{
		//ching2 980504
		//RES E005 密碼錯誤  999  區別名 END
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05));
		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱
		vxp->branch = 175;
		cnt0 = cnt0 + 1;

	}
	else                                   //E998:無法連接資料庫 
	{
		vxp->branch = 178;
		strcpy_s(num.v25[cnt0].error, "E998");
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01d() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}



//------------------------------------------------------------------------------
// FAR01e() 組  依產品項目錄音請按1  之細項播報內容 V6=7000+V5+V9
//------------------------------------------------------------------------------
int FAR01e()
{
	char error[50];


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01e() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	sscanf_s(myExp->var[25], "%*s %s ", error, sizeof(error));
	fdbprintf("error=%s \r\n", error);

	//log
	//myExp->var[3]  = ID4 
	strcpy_s(num.v25[cnt0].id_no, myExp->var[3]);
	//myExp->var[4]  = 1產品2直接*改密碼 
	//myExp->var[5]  = 1基金2金融
	//myExp->var[9]  = v9 請輸入2位產品代碼
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱


	fdbprintf("myExp->var[4]=[%s] \r\n", myExp->var[4]);
	fdbprintf("myExp->var[5]=[%s] \r\n", myExp->var[5]);
	fdbprintf("myExp->var[9]=[%s] \r\n", myExp->var[9]);


	sprintf_s(num.v25[cnt0].trid, "%s%s%s", myExp->var[4], myExp->var[5], myExp->var[9]);
	fdbprintf("num.v25[cnt0].trid=[%s] \r\n", num.v25[cnt0].trid);

	sprintf_s(myExp->var[6], "%04d", 7000 + (atoi(myExp->var[5]) * 100) + atoi(myExp->var[9]));   //V6=7000+V5+V9
	fdbprintf("myExp->var[6]=[%s] \r\n", myExp->var[6]);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01e() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//------------------------------------------------------------------------------
// FAR01f() 依產品項目錄音請按1  拷貝檔案
//------------------------------------------------------------------------------
int FAR01f()
{
	char oldname[1000], newname[1000];
	char sTemp[1000];

	//20220210 OLD
	//long    lt;
	//struct  tm* newtm;


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01f() satart -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	//把新錄好的 招呼語 rename至該user目錄下
	//myExp->var[10] = V10編號=80**
	//  sprintf_s(myExp->var[10], ".\\mess_far1\\mess%04d.wav", 8000 + vxp->voie);

	strcpy_s(oldname, myExp->var[10]);
	fdbprintf("oldname=[%s]\r\n", oldname);

	//20220210 OLD
	//time(&lt);
	//newtm = localtime(&lt);

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);




	//CTime now(time(NULL));     //這是系統內的時間呼叫


  //sprintf_s(sTemp,"%4d/%02d/%02d %02d:%02d:%02d" ,newtm->tm_year+1900   ,newtm->tm_mon+1   ,newtm->tm_mday
	//		                                         ,newtm->tm_hour        ,newtm->tm_min     ,newtm->tm_sec); 

  //一.錄音檔名
  //   1.規則：月+日+AO Code+客戶ID後四碼 (12~13碼，最長13碼)
  //   2.例如：320117563109.wav
  //           3/20 , AO Code：11756, 客戶ID後四碼 3109 

  //myExp->var[1]  = ACO5     //myExp->var[3]  = ID4

  //1000329 d:-->e:
  //sprintf_s(newname, "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
	sprintf_s(newname, "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);

	fdbprintf("newname=[%s]\r\n", newname);

	//1000329 d:-->e:
	//sprintf_s( sTemp, "mkdir d:\\rec\\%s\\", myExp->var[1] );
	sprintf_s(sTemp, "mkdir e:\\rec\\%s\\", myExp->var[1]);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(100);

	//log
	sprintf_s(num.v25[cnt0].file_name, "/rec/%s/%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	strcpy_s(num.v25[cnt0].error, "0000");    //0000
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱


	sprintf_s(sTemp, "copy %s %s", oldname, newname);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(200);

	fdbprintf("5 \r\n");


	//lame --quiet -V 2 input.wav output.mp3
	char newname_mp3[200];
	//1000329 d:-->e:
	//sprintf_s(newname_mp3, "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
	sprintf_s(newname_mp3, "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	fdbprintf("newname=[%s]\r\n", newname);

	sprintf_s(sTemp, "lame --quiet -V 2 %s %s", newname, newname_mp3);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(200);


	//980611 chinb2 add file_size   // 980611  v1.2 ching2  add log for file_size
	int hd;
	
	//20220210 old 
	//hd = open(newname_mp3, O_RDWR | O_BINARY);
	//20220210 new 
	errno_t myErrNoT = _sopen_s(&hd, newname_mp3, O_RDWR | O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE);

	fdbprintf("\r\nnewname_mp3=[%s], sizeof=[%ld] \r\n", newname_mp3, _filelength(hd));
	sprintf_s(num.v25[cnt0].file_size, "%ld", _filelength(hd));
	_close(hd);



	//log
	sprintf_s(num.v25[cnt0].file_name, "/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	strcpy_s(num.v25[cnt0].error, "0000");    //0000

	sprintf_s(num.v25[cnt0].email, "%s", SAL08);     //SAL08(AO_email)
	sprintf_s(num.v25[cnt0].email_cc, "%s", SAL08_BRA03);     //SAL08_BRA03(分行經理_email)


	sprintf_s(smessageFile1_far, "/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	if ((hThread_all_far = CreateThread(NULL, 0, Thread_funCall_email_FAR, (LPVOID)sIN1_far, 0, &hThread_id_far)) == NULL)
	{
		fdbprintf("[Error]  CreateThread() error error error !!!!!!!!!!!!! \r\n");
		Sleep(1000);
	}
	else
	{
		Sleep(200);
	}
	//CloseHandle( hThread_all );
	Sleep(50);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01f() end    -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return(0);

}




//------------------------------------------------------------------------------
// FAR01g()   直接錄音按2 拷貝檔案
//------------------------------------------------------------------------------
int FAR01g()
{
	char oldname[1000], newname[1000];
	char sTemp[1000];
	
	//20220210 OLD
	//long    lt;
	//struct  tm* newtm;


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01g() satart -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	//把新錄好的 招呼語 rename至該user目錄下
	//myExp->var[10] = V10編號=80**
	//  sprintf_s(myExp->var[10], ".\\mess_far1\\mess%04d.wav", 8000 + vxp->voie);

	strcpy_s(oldname, myExp->var[10]);
	fdbprintf("oldname=[%s]\r\n", oldname);

	//20220210 OLD
	//time(&lt);
	//newtm = localtime(&lt);

    //20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	//20220210 OLD CTime now(time(NULL));     //這是系統內的時間呼叫


  //sprintf_s(sTemp,"%4d/%02d/%02d %02d:%02d:%02d" ,newtm->tm_year+1900   ,newtm->tm_mon+1   ,newtm->tm_mday
	//		                                         ,newtm->tm_hour        ,newtm->tm_min     ,newtm->tm_sec); 

  //一.錄音檔名
  //   1.規則：月+日+AO Code+客戶ID後四碼 (12~13碼，最長13碼)
  //   2.例如：320117563109.wav
  //           3/20 , AO Code：11756, 客戶ID後四碼 3109 

  //myExp->var[1]  = ACO5     //myExp->var[3]  = ID4

  //1000329 d:-->e:
  //sprintf_s(newname, "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
	sprintf_s(newname, "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	fdbprintf("newname=[%s]\r\n", newname);

	//1000329 d:-->e:
	//sprintf_s( sTemp, "mkdir d:\\rec\\%s\\", myExp->var[1] );
	sprintf_s(sTemp, "mkdir e:\\rec\\%s\\", myExp->var[1]);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	
	//20220210 old
	//system(sTemp);
	//20220210 new
	system_new(sTemp);

	Sleep(100);

	//log
	//myExp->var[3]  = ID4 
	strcpy_s(num.v25[cnt0].id_no, myExp->var[3]);
	//myExp->var[4]  = 1產品2直接*改密碼 
	sprintf_s(num.v25[cnt0].trid, "%s", myExp->var[4]);   //2
	sprintf_s(num.v25[cnt0].file_name, "/rec/%s/%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	strcpy_s(num.v25[cnt0].error, "0000");    //0000
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱


	sprintf_s(sTemp, "copy %s %s", oldname, newname);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	
	//20220210 old
	//system(sTemp);
	//20220210 new
	system_new(sTemp);

	Sleep(200);

	fdbprintf("5 \r\n");


	//lame --quiet -V 2 input.wav output.mp3
	char newname_mp3[200];

	//1000329 d:-->e:
	//sprintf_s(newname_mp3, "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
	sprintf_s(newname_mp3, "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	fdbprintf("newname=[%s]\r\n", newname);


	//lame = ?
	sprintf_s(sTemp, "lame --quiet -V 2 %s %s", newname, newname_mp3);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(200);


	//980611 chinb2 add file_size   // 980611  v1.2 ching2  add log for file_size
	int hd;
	
	//20220210 old 
	//hd = open(newname_mp3, O_RDWR | O_BINARY);
	//20220210 new
	errno_t myErrNoT = _sopen_s(&hd, newname_mp3, O_RDWR | O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE);


	fdbprintf("\r\nnewname_mp3=[%s], sizeof=[%ld] \r\n", newname_mp3, _filelength(hd));
	sprintf_s(num.v25[cnt0].file_size, "%ld", _filelength(hd));
	_close(hd);



	//log
	sprintf_s(num.v25[cnt0].file_name, "/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	strcpy_s(num.v25[cnt0].error, "0000");    //0000

	sprintf_s(num.v25[cnt0].email, "%s", SAL08);     //SAL08(AO_email)
	sprintf_s(num.v25[cnt0].email_cc, "%s", SAL08_BRA03);     //SAL08_BRA03(分行經理_email)



	sprintf_s(smessageFile1_far, "/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	if ((hThread_all_far = CreateThread(NULL, 0, Thread_funCall_email_FAR, (LPVOID)sIN1_far, 0, &hThread_id_far)) == NULL)
	{
		fdbprintf("[Error]  CreateThread() error error error !!!!!!!!!!!!! \r\n");
		Sleep(1000);
	}
	else
	{
		Sleep(500);
	}
	//CloseHandle( hThread_all );
	Sleep(50);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01g() end    -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return(0);

}



//------------------------------------------------------------------------------
// FAR01h() 組密碼變更上行電文
//------------------------------------------------------------------------------
int FAR01h()
{

	char sPW1[30][10] = { "12345678","23456789","34567890","45678901","56789012","67890123","78901234","89012345","90123456","01234567",
					   "87654321","98765432","09876543","10987654","21098765","32109876","43210987","54321098","65432109","76543210" };
	char sPW2[30][10] = { "11111111","22222222","33333333","44444444","55555555","66666666","77777777","88888888","99999999","00000000" };


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01h() satart -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	//1.log-------------------------------------------------------------------
	//myExp->var[3]  = ID4 
	strcpy_s(num.v25[cnt0].id_no, myExp->var[3]);
	//myExp->var[4]  = 1產品2直接3改密碼 
	sprintf_s(num.v25[cnt0].trid, "%s", "3");   //*
	//strcpy_s(num.v25[0].error , "0000"  );    //0000




	//2.檢查升降及連續-------------------------------------------------------------------
	//myExp->var[7]  = PWD8 new1
	int i = 0;
	for (i = 0; i < 20 - 1; i++)
	{
		if (strcmp(myExp->var[7], sPW1[i]) == 0)
		{
			fdbprintf("升降=[%s] vxp->branch = 3071 \r\n", sPW1[i]);
			vxp->branch = 3071;
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- 4.FAR01h() end    -------------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			return(0);
		}
	}

	//myExp->var[7]  = PWD8 new1
	for (i = 0; i < 10 - 1; i++)
	{
		if (strcmp(myExp->var[7], sPW2[i]) == 0)
		{
			fdbprintf("連續=[%s] vxp->branch = 3071 \r\n", sPW2[i]);
			vxp->branch = 3072;
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- 4.FAR01h() end    -------------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			return(0);
		}
	}


	//3.計算MD5-------------------------------------------------------------------
	//test md5
	//void md5(char* lMessage,char *md5_str);    //lMessage為待加密字符串，md5_str為得到的md5
	//  6789000000000 -->  86f60893d3c7918b3c4265560872fdda
	//char md5_str[40];
	//char s[100];
	//strcpy_s(s,"6789000000000");
	//md5( s, md5_str);
	//fdbprintf("md5_str=[%s]  \r\n", md5_str);

	char sID_PWD[100];
	char spwd[100];
	sprintf_s(sID_PWD, "%s%s", myExp->var[1], myExp->var[2]);
	md5(sID_PWD, spwd);

	char sID_PWD_NEW[100];
	char spwd_new[100];
	sprintf_s(sID_PWD_NEW, "%s%s", myExp->var[1], myExp->var[7]);   //myExp->var[7]  = PWD8 new1
	md5(sID_PWD_NEW, spwd_new);


	//2.組密碼檢驗電文-------------------------------------------------------------------
	//myExp->var[1]  = ACO5      
	//myExp->var[2]  = PWD8    
	//myExp->var[7]  = PWD8 new1  
	sprintf_s(myExp->var[25], "INQ 01 %s %s %s END", myExp->var[1], spwd, spwd_new);
	fdbprintf("myExp->var[25]=[%s] \r\n", myExp->var[25]);

	strcpy_s(num.v25[cnt0].error, "E999");  //連線程式暫停服務,稍後再撥


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01h() end    -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return(0);

}



//------------------------------------------------------------------------------
// FAR01i() S01 01 下行:  拆解
//
//--Send  rec  host交易代號 S01
//--INQ  01: 密碼變更
//
//--上行 V25= INQ  01 acc pwd npwd END    acc:帳號 , pwd:密碼, npwd:新密碼

//--下行 V25= RES  0000  BRA01 BRA05 SAL08 SAL08_BRA03 END              
//--                                      0000:帳號密碼驗證成功   BRA01(分行代碼)  BRA05(區別名稱)  SAL08(AO_email)  SAL08_BRA03(分行經理_email) 

//--     V25= RES  E001  END              E001:帳號不存在
//--     V25= RES  E011  END              E011:和前3次密碼相同
//--     V25= RES  E998  END              E998:無法連接資料庫 
//
//------------------------------------------------------------------------------
int FAR01i()
{
	char error[50] = { 0x00 };


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01i() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	fdbprintf("myExp->var[25]=[%s]  \r\n", myExp->var[25]);

	sscanf_s(myExp->var[25], "%*s %s", error, sizeof(error));
	fdbprintf("error=%s \r\n", error);

	//log
	strcpy_s(num.v25[cnt0].error, error);

	if (strcmp(error, "0000") == 0)       //0000:帳號 密碼驗證成功
	{

		//    -- RES 0000:帳號密碼驗證成功   BRA01(分行代碼)  BRA05(區別名稱)  SAL08(AO_email)  SAL08_BRA03(分行經理_email) 

		//    -- 0000:帳號密碼驗證成功   
		memset(BRA01, 0x00, sizeof(BRA01));      // char BRA01[100];         //BRA01(分行代碼)  
		memset(BRA05, 0x00, sizeof(BRA05));      // char BRA05[100];         //BRA05(區別名稱)  
		memset(SAL08, 0x00, sizeof(SAL08));      // char SAL08[200];         //SAL08(AO_email)  
		memset(SAL08_BRA03, 0x00, sizeof(SAL08_BRA03));      // char SAL08_BRA03[200];   //SAL08_BRA03(分行經理_email) 

		//ching2 980504
		sscanf_s(myExp->var[25], "%*s %*s %s %s %s %s %s ", error, sizeof(error), BRA01, sizeof(BRA01), BRA05, sizeof(BRA05), SAL08, sizeof(SAL08), SAL08_BRA03, sizeof(SAL08_BRA03));

		fdbprintf("error=%s \r\n", error);
		fdbprintf("BRA01(分行代碼)=%s \r\n", BRA01);
		fdbprintf("BRA05(區別名稱) =%s \r\n", BRA05);
		fdbprintf("SAL08(AO_email)=%s \r\n", SAL08);
		fdbprintf("SAL08_BRA03(分行經理_email)=%s \r\n", SAL08_BRA03);
		//log
		strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
		strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱

		vxp->branch = 3100;
		cnt0 = cnt0 + 1;
	}
	else if (strcmp(error, "E001") == 0)  //E001:帳號不存在
	{
		vxp->branch = 3091;
		cnt0 = cnt0 + 1;

	}
	else if (strcmp(error, "E011") == 0)  //E011:和前3次密碼相同
	{
		vxp->branch = 3092;
		cnt0 = cnt0 + 1;
	}
	else                                   //E998:無法連接資料庫 
	{
		vxp->branch = 3098;
		strcpy_s(num.v25[cnt0].error, "E998");
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01i() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}






//------------------------------------------------------------------------------
// FAR01j() 檢查密碼變更不可為*或#
//------------------------------------------------------------------------------
int FAR01j()
{

	int i = 0;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01j() satart -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	for (i = 0; i < int(strlen(myExp->var[7])); i++)  //   V7=PWD8
	{
		if (myExp->var[7][i] == '#' || myExp->var[7][i] == '*')
		{
			fdbprintf(" V7=PWD8 myExp->var[7][i] == '#' || myExp->var[7][i] == '*'  goto 3032  \r\n");
			vxp->branch = 3032;
			return(0);
		}
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01j() end    -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return(0);


}

//------------------------------------------------------------------------------
// Get_ID_Mess(ID9) 檢查身份證後面9位數
//------------------------------------------------------------------------------
int Get_ID_Mess(char* IdNo)
{
	int  len, cc, En = 0, Cn, Cn1;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 5.Get_ID_Mess() satart    -----------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	len = strlen(IdNo);
	if (len != 9) En = -1;
	if (IdNo[0] != '1' && IdNo[0] != '2') En = -1;       //990119 add 身分證數字第一位非1或非2則錯誤
	for (cc = 0; cc < len; cc++)
		if (IdNo[cc] == '#' || IdNo[cc] == '*') En = -1;
	if (En != -1)
	{
		Cn = (IdNo[0] - 0x30) * 8 + (IdNo[1] - 0x30) * 7 + (IdNo[2] - 0x30) * 6 + (IdNo[3] - 0x30) * 5 + (IdNo[4] - 0x30) * 4 + (IdNo[5] - 0x30) * 3 + (IdNo[6] - 0x30) * 2 + (IdNo[7] - 0x30) * 1;
		Cn1 = IdNo[8] - 0x30;
		En = 10 - ((Cn + Cn1) % 10);
		if (En == 10)    En = 0;
	}

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 5.Get_ID_Mess() end      ------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");

	return (En);
}

//------------------------------------------------------------------------------
// FAR_serial_num() 產生流水編號,每天自0001~9999
//------------------------------------------------------------------------------
int FAR_serial_num()
{
	fdbprintf("==============================================\r\n");
	fdbprintf("============產生流水編號0001~9999=============\r\n");
	fdbprintf("==============================================\r\n");
	char sTime[128];

	//每天00:00:00重置,用hot寫?
	//20220210 OLD
	//long lt;
	//struct tm* stm;
	//time(&lt);
	//stm = localtime(&lt);

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	sprintf_s(sTime, "%04d/ %02d/ %02d %02d: %02d: %02d", newTime.tm_year + 1900, newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, newTime.tm_sec);
	fdbprintf("sTime=[%s]\r\n", sTime);

	if (newTime.tm_hour == 0 || newTime.tm_min == 0 || newTime.tm_sec == 0)
	{
		myExp->cnt[3] = 0;
	}

	myExp->cnt[3]++;
	sprintf_s(myExp->var[11], "%04d", myExp->cnt[3]);
	fdbprintf("serial num=[%s]\r\n", myExp->var[11]);

	return 0;
}



int isAccNoOk(char* accNo)
{
	int isRight = 0;
	char accBranch[4] = { 0 }, accNoB[4] = { 0 };
	char addchk1;
	char accountType[8] = { 0 };

	/*
	memcpy(accountType, strlen(accNo) == 16 ? &accNo[5] : &accNo[3], 3);
	if (strcmp(accountType, "041") == 0) {
	  // Fund account No., we does NOT check, return 1 always
	  return 1;
	}
	*/

	// Bank acclunt No.
	if (strlen(accNo) == 14) {
		memcpy(accBranch, accNo, 3);
		memcpy(accNoB, &accNo[3], 3);

		if (strcmp(accNoB, "003") != 0) {
			int add, len;
			char accNoEnd[8] = { 0 }, acadd[16] = { 0 };

			memcpy(accNoEnd, &accNo[6], 7);

			add = atoi(accBranch) + atoi(accNoB) + atoi(accNoEnd);
			sprintf_s(acadd, "%08d", add);
			add = (acadd[1] - '0') * 2 + (acadd[2] - '0') * 3 + (acadd[3] - '0') * 4 +
				(acadd[4] - '0') * 5 + (acadd[5] - '0') * 6 + (acadd[6] - '0') * 7 +
				(acadd[7] - '0') * 2;
			len = add % 9;
			add = 9 - len;

			addchk1 = (4 == add) ? '6' : add + '0';
		}
		else {
			int add, len;

			add = (accNo[9] - '0') * 5 + (accNo[10] - '0') * 7 +
				(accNo[11] - '0') * 3 + (accNo[12] - '0') * 1;
			len = add % 11;
			add = (11 - len) % 10;
			addchk1 = add + '0';
		}

		isRight = (addchk1 == accNo[13]) ? 1 : 0;
	}
	else {
		;
	}

	return isRight;
}





//------------------------------------------------------------------------------
// FAR01k() 身分證字號後九位數字檢查
//------------------------------------------------------------------------------
int FAR01k()
{
	int   mm, idx = 1, re;
	//char  id[10];

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01k() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	mm = strlen(myExp->var[21]);

	if (mm == 9)	//長度檢查
	{
		fdbprintf("ID length = 9 ok\r\n");
	}
	else
	{
		fdbprintf("ID length <> 9 error\r\n");

		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- FAR01k() end         -----------------------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		vxp->branch = 4075;

		return(0);
	}

	for (int i = 0; i < mm; i++)	//內容檢查
	{
		if (myExp->var[21][i] < '0' || myExp->var[21][i] > '9')
		{
			fdbprintf("ID content error\r\n");
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01k() end         -----------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			vxp->branch = 4075;

			return(0);
		}
	}

	re = Get_ID_Mess(myExp->var[21]);

	if (re == -1)
	{
		// myExp->v[idx++] =128;		//您輸入的身份證字號無法辨識，請重新輸入
		// myExp->v[idx++] = -1;
		vxp->branch = 4075;

		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- FAR01k() end        -----------------------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		return(0);
	}
	else
	{
		myExp->v[idx++] = 102;			//您的身份證字號字母為
		myExp->v[idx++] = 110 + re;

		sprintf_s(myExp->var[15], "%d", re);
	}


	myExp->v[idx++] = -1;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01k() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//------------------------------------------------------------------------------
// FAR01k1() ACC 外國人 14 位數字檢查
//------------------------------------------------------------------------------
int FAR01k1()
{
	int   mm, idx = 1;
	//char  id[10];

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01k1() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	mm = strlen(myExp->var[21]);

	if (mm == 14)	//長度檢查
	{
		fdbprintf("Acc length = 14 ok\r\n");
	}
	else
	{
		fdbprintf("Acc length <> 14 error\r\n");

		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- FAR01k1() end         -----------------------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		vxp->branch = 4075;

		return(0);
	}

	for (int i = 0; i < mm; i++)	//內容檢查
	{
		if (myExp->var[21][i] < '0' || myExp->var[21][i] > '9')
		{
			fdbprintf("ID/Acc content error\r\n");
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01k1() end         -----------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			vxp->branch = 4075;

			return(0);
		}
	}

	if (mm == 14)	//外國人銀行帳號
	{
		if (isAccNoOk(myExp->var[21]) == 1)
		{
			myExp->v[idx++] = 1111;	//您輸入的資料為
			idx = ifx(myExp->var[21], idx, 1);
			myExp->v[idx++] = -1;
			strcpy_s(num.v25[cnt0].id_no, myExp->var[3]);	//填報表

			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01k1() end        -----------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			return(0);
		}
		else
		{
			fdbprintf("Acc isAccNoOK = 0  error\r\n");

			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01k1() end         -----------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			vxp->branch = 4075;
			return(0);
		}


	}



	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01k1() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//------------------------------------------------------------------------------
// FAR01m() 組身份證音檔
//------------------------------------------------------------------------------
int FAR01m()
{
	char Alpha[12][6] = { "BNZ", "AMW", "KLY", "JVX", "HU", "GT", "FS", "ER", "DOQ", "CIP" };
	char re = ' ', idd[14] = { 0x00 };
	int idx = 1, pp;
	unsigned int kk;

	showvar(__LINE__);
	//strcpy_s(myExp->var[12], "2");

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("-FAR01m()  start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	if (myExp->var[12][0] == '0')
	{
		//myExp->v[idx++] =127;		//您輸入的身份證字號無法辨識，請重新輸入
		//myExp->v[idx++] = -1;
		vxp->branch = 4080;
		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("-FAR01m()id wrong  end ----------------------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		return(0);
	}
	pp = myExp->var[15][0] - 0x30;
	kk = atoi(myExp->var[12]) - 1;
	if (kk + 1 > strlen(Alpha[pp]))
	{
		vxp->branch = 4110;
	}
	else
	{
		idd[0] = Alpha[pp][kk];
		memcpy(idd + 1, myExp->var[21], 9);
		idd[10] = 0;
		fdbprintf("idd=[%s]\r\n", idd);
		myExp->v[idx++] = 120;			//您的身份證字號為
		idx = ifx(idd, idx, 1);
		strcpy_s(myExp->var[21], idd);
	}
	myExp->v[idx++] = -1;
	memcpy(myExp->var[3], myExp->var[21] + 6, 4);

	//1010529 old 
	//myExp->var[3][4]=0x00;
	//strcpy_s( num.v25[cnt0].id_no, myExp->var[3] );

	//1010529 new  外國人 填全部身份證
	strcpy_s(num.v25[cnt0].id_no, myExp->var[21]);



	/*strcpy_s( num.v25[cnt0].id_no, myExp->var[21] );*/


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01m()  end  branch=[%d]-----------------------------------------------\r\n", vxp->branch);
	fdbprintf("---------------------------------------------------------------------------\r\n");


	return 0;
}



/*
//------------------------------------------------------------------------------
// FAR01n()
// 1010323修改,風險宣告提前到drFAR1-4268
//------------------------------------------------------------------------------
int FAR01n()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01n() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	int isNo;
	int idx=1;
	//char sNo[20];   ////   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00
  char sNo[20+200];   ////   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00

	char s0[1000];
	int  i=0;
	int  fh;

	strcpy_s(s0,".\\conf\\uap_sNo.txt"  );

	for(  i= 0 ; i < 240 ; i++ )
	{
		fh = _sopen( s0 , _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE );
	if( fh < 0 )
		{
			fdbprintf( "open [%s] 失敗 \r\n", s0 );
		}
		else
		{
			if( _locking( fh, LK_NBLCK, 3L ) == 0 )  // Lock some bytes and read them. Then unlock.
			{
				//char sNo_In[100];  //   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00
				char sNo_In[100+200];  //   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00
				read(fh, sNo_In , 3L); //sL=sNo
		//   ver 2.4  1010910  ching2  FAR01n 流水號會錯 補 0x00
				sNo_In[3]=0x00;
		strcpy_s(sNo, sNo_In);  sNo[3]=0x00;

		fdbprintf("v11 = [%s]\r\n", myExp->var[11]);


				//抓時間
				struct   tm *stm;
				long     slt;
				char start_time[1024]={0};
				time(&slt);
				stm=localtime(&slt);
				//start_time=1000309
				sprintf_s(start_time, "%03d%02d%02d",stm->tm_year-11, stm->tm_mon+1, stm->tm_mday);
				//							 01234567890
				//產生流水編號 = 1000309001
				isNo= atoi(sNo);
				sprintf_s(myExp->var[11],"%s%s", start_time, sNo);
				myExp->var[11][10]=0x00;
				//myExp->v[idx++]=; //流水編號為
				//idx= ifx(myExp->var[11], idx, 1);

				fdbprintf("v11 = [%s]\r\n", myExp->var[11]);
				//改變流水編號,若超過999,重置為001
				isNo++;
				if(isNo >= 1000)
				{
					isNo= 1;
				}
				sprintf_s(sNo, "%03d", isNo);
				fdbprintf("isNo++ = [%s]", sNo);

				//寫檔

				_lseek( fh, 0L , SEEK_SET );
				write(fh, sNo , 3L);

				_lseek( fh, 0L , SEEK_SET );
				_locking( fh, LK_UNLCK, 3L );
				_close( fh );

				Sleep(200);

				break;
			}
			else
			{
				_close( fh );
			}
		}
		//} // if iSession > 5

		Sleep(500);   //980820  old 1000
	}

	idx = 1;
	myExp->v[idx++]=1204;        //m1204 您的流水編號為
	idx= ifx(myExp->var[11], idx, 1);
	myExp->v[idx++] = 9906; //嗶聲
	myExp->v[idx++]= -1;


	strcpy_s(num.v25[cnt0].sno, myExp->var[11]);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01n() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

*/

//------------------------------------------------------------------------------
// FAR01n() S01 02 下行:  拆解
//
//--Send  rec  host交易代號 S02
//--INQ  02: 取流水號
//
//--上行 V25= INQ  02  001  END      設定  uap_sno 的 uap_sno = 001  
//--上行 V25= INQ  02  ***  END      取 uap_sno 並且加1 更新回去

//--下行 V25= RES  0000  001 END              
//--     V25= RES  E998  END              E998:無法連接資料庫 
//
//------------------------------------------------------------------------------
int FAR01n()
{
	char error[50] = { 0x00 };
	int idx = 1;
	char uap_sno[20] = { 0x00 };


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01n() satart    -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();



	fdbprintf("myExp->var[25]=[%s]  \r\n", myExp->var[25]);

	sscanf_s(myExp->var[25], "%*s %s", error, sizeof(error));
	fdbprintf("error=%s \r\n", error);

	//log
	strcpy_s(num.v25[cnt0].error, error);

	if (strcmp(error, "0000") == 0)       //0000:
	{
		//    -- 0000:
		memset(uap_sno, 0x00, sizeof(uap_sno));
		sscanf_s(myExp->var[25], "%*s %s %s ", error, sizeof(error), uap_sno, sizeof(uap_sno));   ///"RES 0000 4 END"

		fdbprintf("uap_sno=%s \r\n", uap_sno);
	}
	else                                   //E998:無法連接資料庫 
	{
		vxp->branch = 4414;
		fdbprintf("error=%s E998:無法連接資料庫\r\n", "E998");
		strcpy_s(num.v25[cnt0].error, "E998");
	}

	char start_time[1024] = { 0 };

	//抓時間
	//20220210 OLD
	//struct   tm* stm;
	//long     slt;
	//time(&slt);
	//stm = localtime(&slt);

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	//start_time=1000309 
	sprintf_s(start_time, "%03d%02d%02d", newTime.tm_year - 11, newTime.tm_mon + 1, newTime.tm_mday);
	//							 01234567890
	//產生流水編號 = 1000309001

	sprintf_s(myExp->var[11], "%s%03s", start_time, uap_sno);
	myExp->var[11][10] = 0x00;
	fdbprintf("v11 = [%s]\r\n", myExp->var[11]);

	idx = 1;
	myExp->v[idx++] = 1204;        //m1204 您的流水編號為
	idx = ifx(myExp->var[11], idx, 1);
	myExp->v[idx++] = 9906; //嗶聲
	myExp->v[idx++] = -1;


	strcpy_s(num.v25[cnt0].sno, myExp->var[11]);


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01n() end      ------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}







//------------------------------------------------------------------------------
// FAR01n1() 
// 1010323修改,風險宣告 
//------------------------------------------------------------------------------
int FAR01n1()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01n1() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	//   ver 2.7  1030815  ching2  add drfar01 L4445  不接1-0 按鍵中斷

	//1030815 test Nok

	//ginn_anticipate(int func, int next, const char *p)
	// func : anticipate mode 
	//        0,1,2 如同 "按鍵播音方式", 3 不清 dtmf buffer, 4 清 dtmf buffer
	// next : > 0 時指定 vxp->branch
	// p : func 為 3 或 4 時, 設定可以停止播音的按鍵 (最多 3 個)
	//ginn_anticipate(3, 0, "#"); 


	fdbprintf("v12 = [%s]\r\n", myExp->var[12]);

	int idx = 1;
	if (strcmp(myExp->var[12], "1") == 0)	//基金交易
	{
		fdbprintf("基金交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 1205; //m1205 基金交易風險宣告 
		myExp->v[idx++] = 9906; //嗶聲	
	}
	else if (strcmp(myExp->var[12], "2") == 0)	//MCI交易
	{
		fdbprintf("MCI 交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 1206; //m1206 MCI交易風險宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}
	//1010810 add
	else if (strcmp(myExp->var[12], "3") == 0)	//結構型商品
	{
		fdbprintf("7400 結構型商品 交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 7400; //m7400 結構型商品  宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}


	//   ver 2.9  1040728  ching2  add   FAR01n1  press 按7: play 7700    ,  FAR01n1  press 按6: play 7600

	else if (strcmp(myExp->var[12], "6") == 0)	// 按6 XXXX
	{
		fdbprintf(" 按6 XXXX 7600  交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 7600; //m7600 XXXX  宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}

	else if (strcmp(myExp->var[12], "7") == 0)	// 按7 XXXX
	{
		fdbprintf(" 按7 XXXX 7700  交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 7700; //m7700 XXXX  宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}



	//1030807 add
	else if (strcmp(myExp->var[12], "8") == 0)	//
	{
		fdbprintf("7800  交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 7800; //m7800  宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}


	//   ver 2.3  1010831  ching2  add FAR01n1  press 按9:專業投資人 play 7900
	  //1010831 add
	else if (strcmp(myExp->var[12], "9") == 0)	//結構型商品
	{
		fdbprintf("按9:專業投資人 play 7900  交易\r\n");
		//	myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		myExp->v[idx++] = 7900; //m7900  專業投資人 宣告  
		myExp->v[idx++] = 9906; //嗶聲		
	}



	myExp->v[idx++] = -1;
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01n1() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


int cbDtmf(int c) // 收到按鍵時的 callback function (_uap_receive_dtmf), c 為 dtmf 按鍵
{
	//fdbprintf("---digit=(%c)---hook=(%c)\n",c,vxp->hook);
	SYSTEMTIME st;
	GetLocalTime(&st);

	fdbprintf("%d/%02d/%02d %02d:%02d:%02d.%03d ---digit=(%c)---hook=(%c)\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, c, vxp->hook);

	if (pound_effect == 0)
		return 0;

	if (c == '#') { // '#' 鍵時, 設定 flag (termPlay)
		termPlay = 1;
		fdbprintf("cbDtmf : termPlay(%d)\n", termPlay);
	}

	if (c == '*') { // '*' 鍵時, 設定 flag (termPlay)
		termPlay = 1;
		fdbprintf("cbDtmf : termPlay(%d)\n", termPlay);
	}

	return 0;
}

int cbPlay() // 播音時的 callback function (_uap_check_play), callback function 以回傳值來表示要不要打斷 play, 0: 不打斷, 1: 打斷
{
	if (termPlay) { // flag(termPlay) on 時, 回傳 1 來打斷 play
		fdbprintf("cbPlay : termPlay(%d)\n", termPlay);
		return(1);
	}
	return (0);
}



int setTermDig1()  // 設定按 '#' 打斷, 以 callback funtion 處理
{
	termPlay = 0;
	pound_effect = 1;

	fdbprintf("setTermDig1() termPlay = 0 \n");
	fdbprintf("setTermDig1() pound_effect = 1 \n");

	// 設定按鍵時的 callback function
	//setFuncPointToKer("_uap_receive_dtmf", (NFUNCPTR)cbDtmf);

	// 設定播音時的 callback function
	setFuncPointToKer("_uap_check_play", (NFUNCPTR)cbPlay);

	//setExpV_();
	FAR01n1();

	return (0);
}

int showDtmf() // 顯示 DTMF, 清除 callback function 及還原 anticipate mode
{
	//setFuncPointToKer("_uap_receive_dtmf", (NFUNCPTR)NULL);
	pound_effect = 0;
	fdbprintf("pound_effect = 0 \r\n");

	setFuncPointToKer("_uap_check_play", (NFUNCPTR)NULL);

	termPlay = 0;
	fdbprintf("termPlay = 0 \r\n");

	//ginn_anticipate(0, 0, "");
	fdbprintf("DTMF (%s)\n", myExp->var[3]);
	return (0);
}

int setTermDig2()  // 設定按 '#' 打斷, 以 callback funtion 處理
{

	pound_effect = 1;
	fdbprintf("setTermDig2() pound_effect = 1 \n");

	// 設定按鍵時的 callback function
	//setFuncPointToKer("_uap_receive_dtmf", (NFUNCPTR)cbDtmf);

	// 設定播音時的 callback function
	setFuncPointToKer("_uap_check_play", (NFUNCPTR)cbPlay);

	//setExpV_();
	//FAR01n1();

	return (0);
}



//------------------------------------------------------------------------------
// FAR01o() 密碼加密 
//------------------------------------------------------------------------------
int FAR01o()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01o() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	if (strlen(myExp->var[22]) != 4)
	{
		fdbprintf("password length != 4\r\n");
		vxp->branch = 4280;
		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- FAR01o() end        -----------------------------------------------------\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		return 0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (myExp->var[22][i] == '#' || myExp->var[22][i] == '*')
		{
			fdbprintf("password has # or * \r\n");
			vxp->branch = 4280;
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01o() end        -----------------------------------------------------\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			return 0;

		}
	}

	char pwd[100] = { 0 };
	desPass(myExp->var[22], pwd);
	strcpy_s(myExp->var[22], pwd);

	fdbprintf("pwd=[%s]\r\n", pwd);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01o() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01p() 處理g01下行電文
//------------------------------------------------------------------------------
int FAR01p()
{
	char errcode[50] = { 0 };
	char mess[10] = { 0 };
	int idx = 1;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01p() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	/*

	-------------------------------------------------------------

	Send 151 | [(f)(f)(f)(0)(1)Q(1)(0)(0)(5)(f)(f)  VRE010606001990000000000001206000050016204001GU1G5200010000900
	100000092  00008700000000000000006970       2               00900100000092 ]
	112/06/06 17:25:40 Recv Len:[320] Data:[0050016204001GU111G051026E215


								  ]
	Recv 320 | [0050016204001GU111G051026E215


	  ]
	 etran = G01
	 errorcode = G051

	-------------------------------------------------------------


	Send 136 | [(f)(f)(f)(0)(1)6(1)(0)(0)(8)(f)(f)  VIB010606001990000000000001206000080016207002GI1G0100020000000
	000000000  00008700000000000000009182       2F12193316200000]
	112/06/06 17:27:40 Recv Len:[320] Data:[0080016207002GI111M013301F121933162
						   030 00             10090040005001500030830+00000000000001140000000000098030100000001009
	0048004450900035025+000000000000011400000000001001007000000020090104004759900020030+00000000000000000000000000
	00000000000000                ]
	Recv 320 | [0080016207002GI111M013301F121933162                                                          030 0
	0             10090040005001500030830+000000000000011400000000000980301000000010090048004450900035025+00000000
	0000011400000000001001007000000020090104004759900020030+0000000000000000000000000000000000000000
	  ]
	 etran = G01
	 errorcode = M013


	-------------------------------------------------------------

	send return code = 136 C:\WinOneSys_FAR_????\hotfeb88\src\hotfeb88.cpp(619)
	Send 136 | [(f)(f)(f)(0)(1)6(1)(0)(0)(7)(f)(f)  VIB010606001990000000000001206000070016206002GI1G0100020000000
	000000000  00008700000000000000006631       2F12193316200000]
	112/06/06 17:27:27 Recv Len:[320] Data:[0070016206002GI111E215022100000000000000000000000000000000000000000000
	00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	000000000000000000000000000000]
	Recv 320 | [0070016206002GI111E2150221000000000000000000000000000000000000000000000000000000000000000000000000
	00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	00]
	 etran = G01
	 errorcode = E215





	*/


	//1000308 test ID:T222547136, PW:1234
	//0123456789012345678901234567890
	//000030016202001GI111M013365測試
	//                    **** errcode M013 ID OK
	//  0050016204001GU111G051026E215
	//  0070016206002GI111E21502210

	//sprintf_s(myExp->var[25], "%s", "[000020016201004GI111M013365.測試.                                                              04  00             10020030005880500030207+000000000000001400000000001000224000000010020046600308900030809+000000000000001400000000001000308000000010020076600308309930809+00000000000000000000000000099101400000001055004007672060");

	memcpy(errcode, myExp->var[25] + 20, 4); errcode[4] = 0x00;
	fdbprintf("v25=[%s],errcode=[%s]\r\n", myExp->var[25], errcode);


	if (strcmp(errcode, "G051") == 0)
	{

		memcpy(errcode, myExp->var[25] + 20 + 7, 4); errcode[4] = 0x00;
		fdbprintf("v25=[%s],G051 or G012 +7 errcode=[%s]\r\n", myExp->var[25], errcode);


		if (strcmp(errcode, "0000") == 0)
		{
			fdbprintf("ACC,pw ok\r\n");
			//myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
		  //myExp->v[idx++] = 9906; //嗶聲
			myExp->v[idx++] = -1;

			strcpy_s(num.v25[cnt0].error, errcode);
			fdbprintf("\r\n\r\n");
			fdbprintf("---------------------------------------------------------------------------\r\n");
			fdbprintf("- FAR01p() end vxp->branch=[%d]--------------------------------------------\r\n", vxp->branch);
			fdbprintf("---------------------------------------------------------------------------\r\n");
			return 0;

		}

	}

	if (strcmp(errcode, "G102") == 0)
	{

		memcpy(errcode, myExp->var[25] + 20 + 7, 4); errcode[4] = 0x00;
		fdbprintf("v25=[%s],G051 or G012 +7 errcode=[%s]\r\n", myExp->var[25], errcode);




		fdbprintf("ACC,pw ok\r\n");
		//myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
	  //myExp->v[idx++] = 9906; //嗶聲
		myExp->v[idx++] = -1;

		strcpy_s(num.v25[cnt0].error, errcode);
		fdbprintf("\r\n\r\n");
		fdbprintf("---------------------------------------------------------------------------\r\n");
		fdbprintf("- FAR01p() end vxp->branch=[%d]--------------------------------------------\r\n", vxp->branch);
		fdbprintf("---------------------------------------------------------------------------\r\n");
		return 0;



	}

	//test errorcode
	//sprintf_s(errcode,"M013");

	if (strcmp(errcode, "M013") == 0)
	{
		fdbprintf("id,pw ok\r\n");
		//myExp->v[idx++] = 1203;	//您的理財密碼確認無誤....
	  //myExp->v[idx++] = 9906; //嗶聲
	}
	//1000512 修改 E215 為密碼錯誤 重新輸入
	else if (strcmp(errcode, "E215") == 0)
	{
		fdbprintf("PASSWORD ERROR\r\n");
		vxp->branch = 4280;
	}
	//1000512 修改 E361 為無此帳號 重新輸入.  1000525確認為E367
	else if (strcmp(errcode, "E367") == 0)
	{
		fdbprintf("account ERROR\r\n");
		vxp->branch = 4075;
	}
	else
	{
		//myExp->v[idx++]= 3015;->1201 //錯誤訊息
		myExp->v[idx++] = 1201;
		fdbprintf("id,pw nok\r\n");
		if (funERR_EFS2CHT(errcode, mess) > 0)
		{
			myExp->v[idx++] = atoi(mess);
		}
		else
		{
			idx = ifx(errcode, idx, 1);
		}

		vxp->branch = 4235;
	}

	myExp->v[idx++] = -1;

	strcpy_s(num.v25[cnt0].error, errcode);
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01p() end vxp->branch=[%d]--------------------------------------------\r\n", vxp->branch);
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01pa() 處理g01下行電文 測試用 E215
//------------------------------------------------------------------------------
int FAR01pa()
{
	char errcode[50] = { 0 };
	char mess[10] = { 0 };
	int idx = 1;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01pa() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	//1000308 test ID:T222547136, PW:1234
	//0123456789012345678901234567890
	//000030016202001GI111M013365測試
	//                    **** errcode M013 ID OK 

	//sprintf_s(myExp->var[25], "%s", "[000020016201004GI111M013365.測試.                                                              04  00             10020030005880500030207+000000000000001400000000001000224000000010020046600308900030809+000000000000001400000000001000308000000010020076600308309930809+00000000000000000000000000099101400000001055004007672060");

	memcpy(errcode, myExp->var[25] + 20, 4); errcode[4] = 0x00;
	fdbprintf("v25=[%s],errcode=[%s]\r\n", myExp->var[25], errcode);

	//test errorcode
	sprintf_s(errcode, "M013");

	if (strcmp(errcode, "M013") == 0)
	{
		fdbprintf("id,pw ok\r\n");
		//myExp->v[idx++]= 1203;	
		//myExp->v[idx++] = 9906; //嗶聲
	}
	//1000512 修改 E215 為密碼錯誤 重新輸入
	else if (strcmp(errcode, "E215") == 0)
	{
		fdbprintf("PASSWORD ERROR\r\n");
		vxp->branch = 4280;
	}
	//1000512 修改 E361 為無此帳號 重新輸入
	else if (strcmp(errcode, "E361") == 0)
	{
		fdbprintf("account ERROR\r\n");
		vxp->branch = 4075;
	}
	else
	{
		//myExp->v[idx++]= 3015;->1201 //錯誤訊息
		myExp->v[idx++] = 1201;
		fdbprintf("id,pw nok\r\n");
		if (funERR_EFS2CHT(errcode, mess) > 0)
		{
			myExp->v[idx++] = atoi(mess);
		}
		else
		{
			idx = ifx(errcode, idx, 1);
		}

		vxp->branch = 4235;
	}

	myExp->v[idx++] = -1;

	strcpy_s(num.v25[cnt0].error, errcode);
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01pa() end vxp->branch=[%d]--------------------------------------------\r\n", vxp->branch);
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01pb() 處理g01下行電文 測試用 E361
//------------------------------------------------------------------------------
int FAR01pb()
{
	char errcode[50] = { 0 };
	char mess[10] = { 0 };
	int idx = 1;

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01pb() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();


	//1000308 test ID:T222547136, PW:1234
	//0123456789012345678901234567890
	//000030016202001GI111M013365測試
	//                    **** errcode M013 ID OK 

	//sprintf_s(myExp->var[25], "%s", "[000020016201004GI111M013365.測試.                                                              04  00             10020030005880500030207+000000000000001400000000001000224000000010020046600308900030809+000000000000001400000000001000308000000010020076600308309930809+00000000000000000000000000099101400000001055004007672060");

	memcpy(errcode, myExp->var[25] + 20, 4); errcode[4] = 0x00;
	fdbprintf("v25=[%s],errcode=[%s]\r\n", myExp->var[25], errcode);

	//test errorcode
	sprintf_s(errcode, "E361");

	if (strcmp(errcode, "M013") == 0)
	{
		fdbprintf("id,pw ok\r\n");
		myExp->v[idx++] = 1203;
	}
	//1000512 修改 E215 為密碼錯誤 重新輸入
	else if (strcmp(errcode, "E215") == 0)
	{
		fdbprintf("PASSWORD ERROR\r\n");
		vxp->branch = 4280;
	}
	//1000512 修改 E361 為無此帳號 重新輸入
	else if (strcmp(errcode, "E361") == 0)
	{
		fdbprintf("account ERROR\r\n");
		vxp->branch = 4075;
	}
	else
	{
		//myExp->v[idx++]= 3015;->1201 //錯誤訊息
		myExp->v[idx++] = 1201;
		fdbprintf("id,pw nok\r\n");
		if (funERR_EFS2CHT(errcode, mess) > 0)
		{
			myExp->v[idx++] = atoi(mess);
		}
		else
		{
			idx = ifx(errcode, idx, 1);
		}

		vxp->branch = 4235;
	}

	myExp->v[idx++] = -1;

	strcpy_s(num.v25[cnt0].error, errcode);
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01pb() end vxp->branch=[%d]--------------------------------------------\r\n", vxp->branch);
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//------------------------------------------------------------------------------
// FAR01q() 外撥錄音開始
//------------------------------------------------------------------------------
int FAR01q()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01q() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

    char sTemp[1024] = { 0 };

	//20220210 OLD
	//struct tm* tm;
	//long lt;
	//time(&lt);
	//tm = localtime(&lt);

	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	//mkdir
  //1000329 d:-->e:
  //sprintf_s( sTemp, "mkdir d:\\rec\\%s\\", myExp->var[1] );
	sprintf_s(sTemp, "mkdir e:\\rec\\%s\\", myExp->var[1]);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(100);


	char newname[1024] = { 0 };

	//   ver 3.4  1090423  ching2 v1090423_001 ching2   錄音檔名加民國年
	//1090423 old
//sprintf_s(myExp->var[18], "%s\\%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], tm->tm_mon+1, tm->tm_mday, 
//	tm->tm_hour, tm->tm_min, myExp->var[1], myExp->var[3]);

	//1090423 new
	sprintf_s(myExp->var[18], "%s\\%03d%02d%02d_%02d%02d_%s_%s.wav", myExp->var[1], newTime.tm_year - 11, newTime.tm_mon + 1, newTime.tm_mday,
		newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);


	//1000329 d:-->e:
	//sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR Record=d:\\rec\\%s", vxp->voie, myExp->var[18]);

	//   ver 3.1  1050120  ching2  解決WAV檔一直寫BUG , T/C=%03d  --> T/C=%03d%s

	sprintf_s(sv17_hhmmss, "%02d%02d%02d", newTime.tm_hour, newTime.tm_min, newTime.tm_sec);

	//old sprintf_s(myExp->var[17], "T/C=%03d Caller Add IVR Record=e:\\rec\\%s", vxp->voie, myExp->var[18]);
	sprintf_s(myExp->var[17], "T/C=%03d%s Caller Add IVR Record=e:\\rec\\%s", vxp->voie, sv17_hhmmss, myExp->var[18]);

	fdbprintf("v17=[%s]\r\n", myExp->var[17]);

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
	 //strcpy_s( myExp->var[23], "rec" );
	   //fdbprintf("var[23]=[%s]\r\n", myExp->var[23]);

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
	strcpy_s(myExp->var[24], "");
	fdbprintf("var[24]=[%s]\r\n", myExp->var[24]);


	//1000407 sven add, 轉檔用mp3檔名,直接連路徑一起命名
	//                     d:\ rec\11755\0406_1859_11755_7163.mp3
	//sprintf_s(myExp->var[19], "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3",myExp->var[1], tm->tm_mon+1, tm->tm_mday, 
	//	tm->tm_hour, tm->tm_min, myExp->var[1], myExp->var[3]);


		//   ver 3.4  1090423  ching2 v1090423_001 ching2   錄音檔名加民國年
		//1090423 old
	//sprintf_s(myExp->var[19], "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3",myExp->var[1], tm->tm_mon+1, tm->tm_mday, 
	//	tm->tm_hour, tm->tm_min, myExp->var[1], myExp->var[3]);

		//1090423 new 
	sprintf_s(myExp->var[19], "e:\\rec\\%s\\%03d%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_year - 11, newTime. tm_mon + 1, newTime.tm_mday,
		newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);

	fdbprintf("v19=[%s]\r\n", myExp->var[19]);


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01q() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01r1() 外撥錄音結束-步驟1
//------------------------------------------------------------------------------
int FAR01r1()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r1() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	char sTemp[1024] = { 0 };

	//20220210 OLD
	//struct tm* tm;
	//long lt;
	//time(&lt);
	//tm = localtime(&lt);

	////20220210 new
	//time_t now;
	//struct tm newTime;

	//time(&now);
	//errno_t errNoT = localtime_s(&newTime, &now);



	//1000329 d:-->e:
  //   ver 3.3  1051017  ching2 v1051017_001 ching2   錄音最後會有雜音出現 , Caller NoIVR Delete --> Caller Delete NoIVR
	// 1051017 old
	//sprintf_s(myExp->var[17], "T/C=%03d%s Caller NoIVR Delete", vxp->voie, sv17_hhmmss);	

	sprintf_s(myExp->var[17], "T/C=%03d%s Caller Delete NoIVR", vxp->voie, sv17_hhmmss);

	//sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR Delete", vxp->voie);

	fdbprintf("v17=[%s]\r\n", myExp->var[17]);

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
  //strcpy_s( myExp->var[24], "close1" );


	//sprintf_s(myExp->var[10], "d:\\rec\\%s", myExp->var[18]);	
	sprintf_s(myExp->var[10], "e:\\rec\\%s", myExp->var[18]);
	fdbprintf("v10=[%s]\r\n", myExp->var[10]);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r1() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01r2() 外撥錄音結束-步驟2
//------------------------------------------------------------------------------
int FAR01r2()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r2() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();
	char sTemp[1024] = { 0 };

	//20220210 OLD
	//struct tm* tm;
	//long lt;
	//time(&lt);
	//tm = localtime(&lt);

	////20220210 new
	//time_t now;
	//struct tm newTime;

	//time(&now);
	//errno_t errNoT = localtime_s(&newTime, &now)

	//1000329 d:-->e:
	//sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR No  NoRecord=d:\\rec\\%s", vxp->voie, myExp->var[18]);	
  //sprintf_s(myExp->var[17], "T/C=%03d Caller NoIVR No  NoRecord=e:\\rec\\%s", vxp->voie, myExp->var[18]);

  //   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
	//old sprintf_s(myExp->var[17], "T/C=%03d%s Caller Add IVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss, myExp->var[18]);
	sprintf_s(myExp->var[17], "T/C=%03d%s No Add NOIVR NoRecord=e:\\rec\\%s", vxp->voie, sv17_hhmmss, myExp->var[18]);     //add 	sv17_hhmmss

	fdbprintf("v17=[%s]\r\n", myExp->var[17]);

	//   ver 3.2  1050412  ching2  加錄音控制旗標  //myExp->var[23]=rec, myExp->var[24]=close1 close2 副總提到NO ADD NOIVR 修改錄音-1 SESSION 佔滿問題
  //strcpy_s( myExp->var[24], "close2" ); 


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r2() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}

//------------------------------------------------------------------------------
// FAR01r3() 外撥錄音結束-步驟2
// 音檔結束失敗 delay 3 sec
//------------------------------------------------------------------------------
int FAR01r3()
{
	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r3() start      -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	fdbprintf("\r\nSleep 3 sec \r\n");
	Sleep(3000);

	strcpy_s(num.v25[cnt0].error, "E999");    //0000
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- FAR01r3() end        -----------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return 0;
}


//---------------------------------------------
// FAR01s 分行錄音用的log
// log email, filename, filesize. conv wav to mp3
//---------------------------------------------
int FAR01s()
{
	char newname[1000], newname_mp3[1000];
	char sTemp[1000];

	//20220210 OLD
	//long    lt;
	//struct  tm* newtm;


	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01s() satart -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	show_time();

	//20220210 OLD
	//time(&lt);
	//newtm = localtime(&lt);
	//CTime now(time(NULL));


	//20220210 new
	time_t now;
	struct tm newTime;

	time(&now);
	errno_t errNoT = localtime_s(&newTime, &now);


	//log email
	fdbprintf("[log email]\r\n");
	sprintf_s(num.v25[cnt0].email, "%s", SAL08);     //SAL08(AO_email)
	sprintf_s(num.v25[cnt0].email_cc, "%s", SAL08_BRA03);     //SAL08_BRA03(分行經理_email)

	  //conv wav to mp3
	fdbprintf("[conv wav to mp3]\r\n");
	//d:\\rec\\%s, v18= wav filename
	//             v19= mp3 filename

	//1000329 d:-->e:
  //sprintf_s(newname_mp3, "d:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
  //sprintf_s(newname_mp3, "e:\\rec\\%s\\%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   

	//1000407 
	//更改far01q的v19,就可以更改路徑, v18就必須在這邊改路徑
	sprintf_s(newname_mp3, "%s", myExp->var[19]);
	//sprintf_s(newname,     "d:\\rec\\%s", myExp->var[18]);
	sprintf_s(newname, "e:\\rec\\%s", myExp->var[18]);

	fdbprintf("newname=[%s], newname_mp3=[%s]\r\n", newname, newname_mp3);

	sprintf_s(sTemp, "lame --quiet -V 2 %s %s", newname, newname_mp3);
	fdbprintf("\r\nSystem sTemp=[%s] \r\n", sTemp);
	system(sTemp);
	Sleep(200);

	//log filesize
	fdbprintf("[log filesize]\r\n");
	//980611 chinb2 add file_size   // 980611  v1.2 ching2  add log for file_size
	int hd;

	//20220210 old 
	//hd = open(newname_mp3, O_RDWR | O_BINARY);
	//20220210 new 
	errno_t myErrNoT = _sopen_s(&hd, newname_mp3, O_RDWR | O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE);


	fdbprintf("\r\nnewname_mp3=[%s], sizeof=[%ld] \r\n", newname_mp3, _filelength(hd));
	sprintf_s(num.v25[cnt0].file_size, "%ld", _filelength(hd));
	_close(hd);

	//log filename
	fdbprintf("[log filename]\r\n");
	//sprintf_s(num.v25[cnt0].file_name,"/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newtm->tm_mon+1, newtm->tm_mday, newtm->tm_hour, newtm->tm_min,  myExp->var[1], myExp->var[3]);   
	//    0123456789012345678901234567890123456
	  //v19=d:\rec\11755\0407_1531_11755_7163.mp3

	int sLen = strlen(myExp->var[19]);
	sLen = sLen - 3;
	memcpy(newname_mp3, myExp->var[19] + 3, sLen);
	for (int i = 0; i < sLen; i++)
	{
		if (newname_mp3[i] == '\\')
		{
			newname_mp3[i] = '/';
		}
	}
	newname_mp3[sLen] = '\0';
	fdbprintf("newname_mp3=[%s]\r\n", newname_mp3);
	sprintf_s(num.v25[cnt0].file_name, "/%s", newname_mp3);

	strcpy_s(num.v25[cnt0].error, "0000");    //0000
	strcpy_s(num.v25[cnt0].bra01, BRA01);   //分行代碼
	strcpy_s(num.v25[cnt0].bra05, BRA05);   //區別名稱

	sprintf_s(smessageFile1_far, "/rec/%s/%02d%02d_%02d%02d_%s_%s.mp3", myExp->var[1], newTime.tm_mon + 1, newTime.tm_mday, newTime.tm_hour, newTime.tm_min, myExp->var[1], myExp->var[3]);
	if ((hThread_all_far = CreateThread(NULL, 0, Thread_funCall_email_FAR, (LPVOID)sIN1_far, 0, &hThread_id_far)) == NULL)
	{
		fdbprintf("[Error]  CreateThread() error error error !!!!!!!!!!!!! \r\n");
		Sleep(1000);
	}
	else
	{
		Sleep(200);
	}
	//CloseHandle( Thread_all );
	Sleep(50);

	fdbprintf("\r\n\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	fdbprintf("- 4.FAR01s() end    -------------------------------------------------------\r\n");
	fdbprintf("---------------------------------------------------------------------------\r\n");
	return(0);
}

int FAR01t()
{
	int i;

	i = vxp->voie;

	sprintf_s(myExp->var[1], "TI,,,,,,%d,%d,%d,%d,%d", 1, 0, 0, i / 10, i % 10);
	fdbprintf("\r\n v1= [%s]\r\n", myExp->var[1]);

	return 0;
}











UAP uap4[] =
{



	//   ver 1.2   980422  ching2  for FAR

	//----------------------------------------------------------------
	//drFrec FrecA 錄音
	//----------------------------------------------------------------
	{"FrecA"     ,     FrecA  },          //drFrec  


	//----------------------------------------------------------------
	//drFAR01 FAR主選單
	//----------------------------------------------------------------
	{"FAR01a"     ,     FAR01a  },          //drFAR01  

	//   ver 3.0  1041027  ching2  add   FAR01n1  4.FAR01a1 *1  4.FAR01a2 *2
	{"FAR01a1"    ,     FAR01a1 },          //drFAR01  
	{"FAR01a2"    ,     FAR01a2 },          //drFAR01  


	{"FAR01b"     ,     FAR01b  },          //drFAR01  
	{"FAR01b2"    ,     FAR01b2 },          //drFAR01 
	{"FAR01b3"    ,     FAR01b3 },          //drFAR01     //   ver 3.1  1050120  ching2  解決WAV檔一直寫BUG , T/C=%03d  --> T/C=%03d%06d 


	{"FAR01c"     ,     FAR01c  },          //drFAR01  
	{"FAR01c2"    ,     FAR01c2 },          //drFAR01
	{"FAR01d"     ,     FAR01d  },          //drFAR01  
	{"FAR01e"     ,     FAR01e  },          //drFAR01  
	{"FAR01f"     ,     FAR01f  },          //drFAR01  
	{"FAR01g"     ,     FAR01g  },          //drFAR01  
	{"FAR01h"     ,     FAR01h  },          //drFAR01  
	{"FAR01i"     ,     FAR01i  },          //drFAR01  
	{"FAR01j"     ,     FAR01j  },          //drFAR01  

	{"FAR01k"     ,     FAR01k  },          //drFAR01 
	{"FAR01k1"     ,     FAR01k1  },          //drFAR01 

	{"FAR01m"     ,     FAR01m  },          //drFAR01 
	{"FAR01n"     ,     FAR01n  },          //drFAR01 
	{"FAR01n1"    ,     FAR01n1 },          //drFAR01 
	{"FAR01o"     ,     FAR01o  },          //drFAR01 
	{"FAR01p"     ,     FAR01p  },          //drFAR01 
	{"FAR01pa"    ,     FAR01pa },          //drFAR01 
	{"FAR01pb"    ,     FAR01pb },          //drFAR01 
	{"FAR01q"     ,     FAR01q  },          //drFAR01 
	{"FAR01r1"    ,     FAR01r1 },          //drFAR01
	{"FAR01r2"    ,     FAR01r2 },          //drFAR01
	{"FAR01r3"    ,     FAR01r3 },          //drFAR01
	{"FAR01s"     ,     FAR01s  },          //drFAR01
	{"FAR01t"     ,     FAR01t  },


	// for  drFAR02 
	/*
	{"FAR02a"     ,     FAR02a  },
	{"FAR02b"     ,     FAR02b  },
	{"FAR02c"     ,     FAR02c  },
	{"FAR02d"     ,     FAR02d  },
	{"FAR02e"     ,     FAR02e  },
*/


  {"sTerm1", setTermDig1},
  {"sDTMF",  showDtmf},
  {"sTerm2", setTermDig2},

 {""          ,   NULL     }

};


/*****************************************************************************/
int uap4_select(char *str)
{
	int i, k;
	for (i=0; uap4[i].name[0]!=0; i++) {
		if (strcmp(str, uap4[i].name) == 0) {
			k=(*uap4[i].func)(/*uap1[i].parm*/);
			return k;
		}
	}
	return -1;
}


