
#include  "StdAfx.h"
#include  <stdlib.h>
#include  <stdio.h>
#include  <io.h>
#include  <string.h>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <sys/timeb.h> 
#include  <time.h>
#include  <fcntl.h> 

#include  "conference.h"
#include  "DXCALLP.H"
#include  "parprog.h"
#include  "fcontrol.h"
#include  "uaplib.h"
#include  "morfunc.h" 
#include  "SkLink.h"

extern    FUNCAERR  get_AsrErrcode ;
extern    FUNCAERR  ginn_dnis;
extern    FUNCAERR  ginn_ani; 
extern	  FUNCAERR  ginn_getStringBuf;
extern	  FUNCPTR	ginn_outofservice; 

extern	  int		checkIfAttendent(char *telNo);
extern	  int		allowMail(char *mailBox);
extern	  char		attendentID[32];		// representative of auto attendent

FwdEntry  fwd, *fwdp;

//#define  MaxPhoneNo		4
//#define  MaxExtPerPhone	64
//#define  MaxZJ			4
#define  ON_DUTY			1
#define  OFF_DUTY			0
#define	 FXO				0
#define	 FXS				1
#define	 WEB				2
#define  NOWIRE             3
#define  MAXPREFIX			32
#define  MAXFASTDIAL		32
#define	 TotalCfrNo			8
#define	 CfrExpireTime		900		// 15 minutes
typedef struct {
	int		date;			// 未接電話日期
	int		time;			// 時間
	char	telNo[32];		// 來電號碼
} NRCD;

typedef struct {
	int		menNo;			// 80xx 
	char	telNo[32];		// 轉撥之電話號碼
	int		type;			// 0:原碼通 1:簡碼撥號
	int		valid;			// 1:valid 0:deleted
	char	handset[20];	// 手機代號
	long	startDate;		// 起用日期 time(&lt)
	long	endDate;		// 終止日期
    NRCD	nrc[10];		// 最近十通之未接電話日期、時間、來電號碼
	char	fill[256];
} ymtd;

TelList		telList[3], *tlap, *tlcp, *tldp;
long		ymtOffset;
long		ymtFreeOffset;

//char pno[MaxPhoneNo][16];				// pno[4][16];
//Ext  extno[MaxPhoneNo][200];			// extno[4][200];
//char    pno_zj[MaxPhoneNo][MaxZJ][8];	// pno_zj[4][4][8];
char	aniCaller[32], dnisCalled[32];
char	aniCallerRef[64];				// for call forward setting, Real Extension No.
int		inFrom = FXO, duty, starting;
int		ymdValue, yValue, mValue, dValue;
FILE	*fpt;
int		keys[100];
char	dutyArray[7][3][16];
int		totalLoc;
int		voiceMail = 0;
char	voiceMailPorter[16];
char	publicMailBox[16];
char	localID[32];
char	groupID[32];
char	handsetGateway[32];
char	handsetExtension[24];
char	handsetID[24];
char	handsetType[16];		// A:go direct to AVS 0,1,2,..,9 go through PBX to PSTN.
								// Call to extension need Gateway-ID and extension# to exists.
long	ltEnd = -1;				// timeout for digit in
int		ltLen;					// last length of digits
ymtd	ymt;
//char	attendent[16][32];
//int	attendentCount; 
int		maxExtLen;				// Max extension Length, normal is 3
char	trunkID[32];
char	extensionToTrunk = '9';	// Extension Dial '0' to PSTN 
char	trunkToOperator = '9';	// PSTN dial '9' to OP
char	callerTransparent = 'N';// 'N': use IVR ID to accounting and callerNo
char	autoAttendent = 'Y';
char	pstnTalkTime;
char	playOnHook = 0;			// 0:Answer Immediately 1:Answer only Ballance correct
char	backupToPstn = 0;		// 0:No backup to PSTN. 1:Backup to PSTN.
int		balanceAnnounce = 1;	// 1:Announce Balance 0:Not
int		cfrID;
int		chnum;					// total line No. in sysconf

int		notPassDtmf;
char	pickupList[32][8];		// Same group for pickup use
//char  exto[4];				// if 'o', should pass DTMF to the ext.
char	dialCodecCmd;			// codec exists in dial command.
char	dialRecCmd;				// Record exists in dial command
char	aniCallerAAType = 0;	// 1:AA 0:not AA(Auto-Attendent)
char	vipCall = 0;			// 0:Not to send short message
char	greetingType;			// 0:normal |1:conference |2:voicemail		
char	telCfrPorter[8];		// To enter conference system
long	nowTime, ltTime;

char	internetPrefix[16];		// Add prefix to called Number when to internet

int SelectRecordP(char *dataset, char *fieldName, char *fieldValue, int type);
int GetDataP(char *fieldName, char *buf, int len, int loc);
int checkIfExtension(TelList *tlxp, char *phone, int type);
/*-----------------User defined functions--------------------------------------------------*/
/*
int test1()
{
  int i = 1,j;
  char empNo[32], empName[32], nameCardExt[32], dialExt[32];  
  char tmpBuf[128];
  char *digAry[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
  FILE *fy;

  printf("客戶按鍵或辨試=[%s]\r\n",exp->var[1]);
  if ((exp->var[1][0] == '!') || (exp->var[1][0] == NULL)){
	  vxp->branch=600;
	  return 0;
  }
  fy = fopen("otsEmpNo.txt", "r");
  memset(tmpBuf, 0, sizeof(tmpBuf));
  for (; fscanf(fy, "%s %s %s %s", empNo, empName, nameCardExt, dialExt) != EOF; ) {
    if (strcmp(nameCardExt, exp->var[1]) == 0) {
      strcpy(tmpBuf, empName);
      for (j = 0; j < (int)strlen(nameCardExt); j++) {
        int idx = (int)nameCardExt[j] - 0x30;

        strcat(tmpBuf, digAry[idx]);
      }
      break;
    }
  }
  fclose(fy);

  if (strlen(tmpBuf) == 0) {
//    strcpy(tmpBuf, "無此分機號碼, 我幫您轉總機八零零");
    exp->v[i++]=104;
//	exp->v[i++]=105;
//	i=ifx("800",i,1);
//  strcpy(dialExt, "800");
    vxp->branch=55;
    printf("dialno is err !!\n");
  } else {
	  printf("%s\n", tmpBuf);
	  i = bnam(tmpBuf, i, 1);	
  }
  exp->v[i] = -1 ;
  sprintf(exp->var[1], "%s%s", "&", dialExt);
  return 0;
}

int count;
 FUNCPTR fp;
int check_cnt()
{
 count ++;
 if (count >= 300)
   return 1;
 else 
   return 0;
}

int setl2()
{
  
  fdbprintf("l2: exp->var[3]=(%s),exp->var[1]=(%s),exxp->var[1]=(%s),vxp->voie=(%d)\n",\
    exp->var[3],exp->var[1],exxp->var[1],vxp->voie);

  ginn_clrexpvar();
  fdbprintf("l2: exp->var[3]=(%s),exp->var[1]=(%s),exxp->var[1]=(%s),vxp->voie=(%d)\n",\
  exp->var[3],exp->var[1],exxp->var[1],vxp->voie);
  strcpy(exp->var[3],"abcde");
  strcpy(exxp->var[1],"111222");
  return 0;
}

int getl2(){
  ex  ex0;
  vx  vx0;
  exx exx0;

  ex0 = ginn_getexp(2);
  vx0 = ginn_getvxp(2);
  exx0 = ginn_getexxp(2);

 // fdbprintf("l1: exp->var[2]=(%s),exxp->var[1]=(%s),vxp->voie=(%d)\n",\
 //   exp->var[2],exxp->var[1],vxp->voie);

  fdbprintf("l2: exp->var[3]=(%s),exp->var[1]=(%s),exxp->var[1]=(%s),\
    vxp->voie=(%d)\n", ex0->var[3],ex0->var[1],exx0->var[1],vx0->voie);

  return 0;
}
int usclr()
{
  ginn_clrexpvarbyuser(1);
  return 0;
}


int ant()
{
  ginn_anticipate(2,410,"");
  return 0;
}
int sv1()
{


  int i = 1;
 // fdbprintf("uap 2.sv1\n");
 // strcpy(exp->var[1],"d:\\otswin1_work_tel\\run\\otsEmp.xml");
 // strcpy(exp->var[2],"5566");
//
 // i = ginn_bnam("你們好",i,1);


  //  fdbprintf("exp->v[%d]=%d\n",j,exp->v[j]);

    exp->v[i++] = 101;
  //  i = ifx("170",i,1);

  //i = bnam("橋星資訊",i,1);
  i = ifm("170","",i,1);  
   exp->v[i++] = 100;
     exp->v[i++] = 102;
 
  exp->v[i] = -1;
 
   

   // strcpy(exp->var[1],"C:\\Program Files\\TeleSynergy\\TeleAPI-PCI\\Sample\\C\\Ivr0400F\\");
  //  strcpy(exp->var[1],"1122334");
  //  strcpy(exp->var[3],"busy.wav");

 
 //strcpy(vxp->message,exp->var[2]);
  return 0;
}
*/
/*
int sv2()
{ 
 int i = 1;// ginn_clrexpvarbyuser(1);


  exp->v[i++] = 3000;
  i = ginn_bnam("你們好",i,1); 
  i = ifx("4567890abc123",i,1);
  i = bnam("你們好",i,1);
  i = ifm(exp->var[2],"35",i,1);
  exp->v[i] = -1;
 
  return 0;
}

int gslot()
{
//  SC_TSINFO       scts;
  long ts;

  fdbprintf("fets=%ld dxts=%ld \n",exp->fets,exp->dxts);
//  scts.sc_numts = 1;
//  scts.sc_tsarrayp = &ts;
  if (ginn_getxmitslot(&ts) == -1)
    fdbprintf("error get ginn slot\n");
  fdbprintf("ginn timeslot=(%ld)\n",ts);

  if (voice_getxmitslot(&ts) == -1)
       fdbprintf("error get voice slot\n");
  fdbprintf("voice timeslot=(%ld)\n",ts);

  return 0;
}
int gls()
{
  
  ginn_listen(1);  //line2 dx
  
  return 0;
}
int guls()
{
  ginn_unlisten();
  ginn_listen(exp->dxts);
  
  return 0;
}

int vls()
{
  ex ex0;
  ex0 = ginn_getexp(2);
  voice_listen(ex0->fets);   //line2 ts
  return 0;
}
int vuls()
{
  voice_unlisten();
  voice_listen(exp->fets);
  return 0;
}
int glsf()
{
  ginn_listenfe(2);
  return 0;
}
int glsd()
{
  ginn_listendx(vxp->voie);
  return 0;
}
int vlsf()
{
  voice_listenfe(2);
  return 0;
}
int vlsf1()
{
  voice_listenfe(vxp->voie);
  return 0;
}
int vlsd()
{
  fdbprintf("exp->var[1]=%s\n",exp->var[1]);
  voice_listendx(1);
  return 0;
}

int chk_evt()
{
  ex ex0;
  ex0 = ginn_getexp(2);

  if (!strcmp(ex0->var[1],"123"))
    return 1;
  else 
    return 0;
}
int wevt()
{
//  int rc;

  //if ((ginn_waitevt(-1,chk_evt)) == 0)
  if ((ginn_waitevt(chk_evt)) == 0)
    fdbprintf(" line(%d) disconnect\n",vxp->voie);
  else
    fdbprintf(" line(%d) status \n",vxp->voie);
  return 0;
}
int urclr()
{
  ginn_clrexpvarbyuser(0);
  return 0;
}
int clr()
{
  ginn_clrexpvar();
  return 0;
}
int stans()
{
  ginn_setautoanswer(0);
  return 0;
}
int ans()
{
  ginn_answercall();
  return 0;
}
int stpfmt()
{
  ginn_setplayfmtabs(GINN_FMT_ALAW);
  return 0;
}
int stpre()
{
  ginn_setpreferedfnm(GINN_FNM_VOX);
  return 0;
}
int gtrfnm()
{
  int re = ginn_getrecordfnm();
  fdbprintf("re=%d\n",re);
  return 0;
}
int strfnm()
{
  int re = ginn_setrecordfnm(GINN_FNM_ULAW);
  fdbprintf("re=%d\n",re);
  return 0;
}
int strin()
{
  ginn_setringtm(5);
  return 0;
}

/*
int chfile()
{
  strcpy(exp->var[1],"C:\\Program Files\\CrystalVoice\\Click-To-Talk");
 // strcpy(exp->var[1],"11223344556677889900112233445566");
 // strcpy(exp->var[1],"d:\\otswin1_work\\run\\abcd");
  return 0;
}


int nosul()
{
  char errBuf[512];
  fdbprintf("asr no result\n");
  int ret = get_AsrErrcode(errBuf);
  fdbprintf("get_AsrErrcode ret = %d ,errBuf=%s\n",ret,errBuf);
  return 0;
}

//==================================================================================
/*
int _get_ext_pos(int pos,char *ext)
{
  int k ;

  for (k=0;k<MaxExtPerPhone;k++){ // for (k = 0; k < 64; k++)
    if ((strncmp(extno[pos][k].extno,ext,strlen(ext)) == 0) &&(extno[pos][k].use_flag == 1))
//-from chani()-> if ((strncmp(extno[i][k].extno, exp_var[2], strlen(ext)) == 0) && (extno[i][k].use_flag == 1))	
		fdbprintf("_get_ext_pos's k = (%d)\r\n", k);
      return k; 
    if ((strncmp(extno[pos][k].extno,ext,strlen(ext)) == 0) &&(extno[pos][k].use_flag == 0))
      return -2;
  }
  return -1;
}

int ckani(char *ani)
{
  int i;


  for (i=0; i< MaxPhoneNo ;i++) {  //check if the caller's ext is available 
	  // for (i = 0; i < 4; i++) {
    if (strlen(pno[i]) == 0) break;
    if (strncmp(pno[i],ani,strlen(pno[i])) == 0) { 
      strcpy(exp->var[2],&ani[strlen(pno[i])]); 
      if (_get_ext_pos(i,exp->var[2]) >= 0) {    
        strcpy(exp->var[1],pno[i]);  
        return i;
      }
      return -2;
    }       
  }
  return -1;  
*/
/*  
  exp->var[1][0] = 0;
  strcpy(exp->var[2], ani);
  return(0);
*/
//}
/*
int ckdnis(char *dnis)
{
  int i ;

  for (i=0; i< MaxPhoneNo; i++){
    //if (strlen(pno[i]) == 0) break;
    if (strncmp(pno[i],dnis,strlen(pno[i])) == 0){             
      strcpy(exp->var[4],pno[i]);
      strcpy(exp->var[5],&dnis[strlen(pno[i])]);    
      return i;
    }
  }
  return -1;
}
*/

int reOpenDatabase()
{
	CloseDatabase();
	int k = OpenDatabase("db222", "root", "");
	if (k >= 0) fdbprintf("ReOpenDatabase OK.\r\n");
	return(k);
}

int	IfAttd()
{
	if (duty == OFF_DUTY) vxp->branch = 120;		// thanks for calling
fdbprintf("cnt=%d\r\n", exp->cnt[5]);
	exp->cnt[5] += 1;
	if (exp->cnt[5] >= 3) vxp->branch = 120;
	return(1);
}

int	getAllDuty()
{
	int		i, k, key;
	char	buffer[128], buf[16][16];
	long	today;
	tm		*tm;

	for (i=0; i<7; i++) {
		keys[i] = i + 1;						// 1-7
		for (k=0; k<3; k++) strcpy(dutyArray[i][k], "-");
	}
	for (i=7; i<100; i++) keys[i] = 0;
	totalLoc = 8;
	if (fpt = fopen(".\\conf\\DutyTime.txt", "r+b")) {
		fdbprintf("open DutyTime.txt ok\r\n");
	} else {
		return(0);
	}
	tm=localtime(&nowTime);
	today = (tm->tm_year - 11) * 10000 + (tm->tm_mon+1) * 100 + tm->tm_mday;
//fdbprintf("today=%d\r\n", today);
	for (i=0; i<700; i++) {
		if (fgets(buffer, 120, fpt) == NULL)		// No more data
			break;
		sscanf(buffer, "%s", &buf[0]);
		key = atoi(buf[0]);
//fdbprintf("key=%d\r\n", key);
		if (key > 0 && key <= 7) {		// Format of week day
			sscanf(buffer, "%*s %s %s %s", 
				&dutyArray[key-1][0], &dutyArray[key-1][1], &dutyArray[key-1][2]);
//fdbprintf("duty=%s %s %s\r\n", 	dutyArray[key-1][0], dutyArray[key-1][1], dutyArray[key-1][2]);		
		} else {
			if (key > 940000) {
				for (k=0; k<12; k++) buf[k][0] = 0;
				sscanf(buffer, "%s %s %s %s %s %s %s %s %s %s %s %s", 
					&buf[0], &buf[1], &buf[2], &buf[3], &buf[4], &buf[5],
					&buf[6], &buf[7], &buf[8], &buf[9], &buf[10], &buf[11]);
				for (k=0; k<12; k++) {
					if (buf[k][0] == 0) break;
					key = atoi(buf[k]);
					if (key >= today && key < 1999999) {
						keys[totalLoc] = key;
						totalLoc += 1;
fdbprintf("keys=%d[%d]\r\n", keys[totalLoc], totalLoc);
					}
				}
			}
		}
	}
	fclose(fpt);
	return(i);
}

int putAllDuty()
{
	char	buffer[128];
	int		i;

	if (fpt = fopen(".\\conf\\DutyTime.txt", "w+b")) {		// create and truncate file
		fdbprintf("open DutyTime.txt ok\r\n");
	} else {
		return(-1);
	}
	strcpy(buffer, "#\r\n# Duty Time:\r\n#\r\n");
	fputs(buffer, fpt);
	strcpy(buffer, "#\tSection-1\tSection-2\tSection-3\r\n\r\n");
	fputs(buffer, fpt);
	for (i=0; i<7; i++) {
fdbprintf("key=%d array=%s %s %s\r\n", keys[i], dutyArray[i][0], dutyArray[i][1], dutyArray[i][2]);
		sprintf(buffer, "%d\t%s\t%s\t%s\r\n", keys[i], dutyArray[i][0], dutyArray[i][1], 
			dutyArray[i][2]);
fdbprintf("BUF=%s", buffer);
		fputs(buffer, fpt);
	}
	strcpy(buffer, "\r\n#\r\n# Holiday:\r\n#\r\n\r\n");
	fputs(buffer, fpt);
	buffer[0] = 0;
fdbprintf("totalLoc=%d\r\n", totalLoc);
	for (i=8; i<totalLoc; i++) {
		sprintf(buffer, "%06d\r\n", keys[i]);
		fputs(buffer, fpt);
	}
	fclose(fpt);
	return(totalLoc);
}

int checkYyMmDdGood(char *yymmdd)
{
	char yy[4], mm[4], dd[4];
//	long lt;
	tm	 *tm;
	int  today;

//	time(&lt);
	tm=localtime(&nowTime);
	today = (tm->tm_year - 11) * 10000 + (tm->tm_mon+1) * 100 + tm->tm_mday;
	ymdValue = atoi(yymmdd);
	if (ymdValue < today) return(-1);
	if (ymdValue > (today + 20000)) return(-1);		// max. within 2 years
	strncpy(yy, yymmdd, 2);
	yy[2] = 0;
	strncpy(mm, &yymmdd[2], 2);
	mm[2] = 0;
	strncpy(dd, &yymmdd[4], 2);
	dd[2] = 0;
	yValue = atoi(yy);
	mValue = atoi(mm);
	dValue = atoi(dd);
	if (mValue > 12 || mValue < 1) return(-1);
	if (dValue > 31 || dValue < 1) return(-1);
	tm->tm_year = yValue + 11;
	tm->tm_mon = mValue - 1;
	tm->tm_mday = dValue;
	ltTime=mktime(tm);
	tm=localtime(&ltTime);
	if (tm->tm_mday != dValue) return(-1);
	return(1);
}

int	checkHhMmGood(int value)
{
	if (value >= 2400) return(-1);		// hour = 00-23
	value %= 100;
	if (value >= 60) return(-1);		// minute = 00-59
	return(1);
}

// Check if holiday is reasonable
int CkHday()
{
	int		k;
	if (checkYyMmDdGood(exp->var[10]) < 0) {
		vxp->branch -= 5;				// Error play branch
		return(1);
	}
	k = 1;
	exp->v[k++] = 546;				// Entered is ...
	exp->v[k++] = 547;				// min-guo
	exp->v[k++] = 510 + yValue;		// xx nian2
	exp->v[k++] = 610 + mValue;		// xx yue4
	exp->v[k++] = 630 + dValue;		// xx ri4
	exp->v[k] = -1;
	return(1);
}

int SyHday()
{
	int		k, i;
	char	buf[80];

	getAllDuty();
	k = 1;
	if (totalLoc == 8) {
		exp->v[k++] = 552;				// No holiday setting yet
		exp->v[k] = -1;
		return(1);
	}
	exp->v[k++] = 549;					// Holiday is ...
	for (i=8; i<totalLoc; i++) {
		sprintf(buf, "%d", keys[i]);
		if (checkYyMmDdGood(buf) < 0) continue;
		exp->v[k++] = 547;				// min-guo
		exp->v[k++] = 510 + yValue;		// xx nian2
		exp->v[k++] = 610 + mValue;		// xx yue4
		exp->v[k++] = 630 + dValue;		// xx ri4
		exp->v[k++] = 509;				// Silence 1 Sec.
	}
	exp->v[k] = -1;
	return(1);
}

// Check if duty hour is reasonable
int	CkDuty()
{
	int		value;

	value = atoi(exp->var[10]);
	if (checkHhMmGood(value) < 0)
		vxp->branch -= 5;				// Error play branch
	return(1);
}

int	synthesisDayTime(char *strHhMm, int k)
{
	int		hhmm, hh, mm, dayZone;
	char	chhmm[8];

	strncpy(chhmm, strHhMm, 4);
	chhmm[4] = 0;
	hhmm = atoi(chhmm);
	if (hhmm < 0 || hhmm > 2400) return(k);
	mm = hhmm % 100;
	if (mm > 59) return(k);
	hh = (hhmm - mm) / 100;
	if (hh < 6) dayZone = 3;					// night
	else if (hh < 12) dayZone = 0;				// morning
	else if (hh == 12 && mm == 00) dayZone = 1;	// noon
	else if(hh < 19) dayZone = 2;				// afternoon
	else dayZone = 3;							// night
	exp->v[k++] = 695 + dayZone;
	if (hh > 12) hh -= 12;
	exp->v[k++] = 680 + hh;						// hh
	if (mm > 0)
	   exp->v[k++] = 700 + mm;					// mm
	return(k);
}

// Get DutyTime.txt and Synthesis to Play
int	GtDuty()
{
//	FILE	*fpt;
	char	buffer[128] = {0};
	char	buf[12][32];
	char	dutyTime[3][32];
	char	*p;
	int		weekDay, dutyWday, dutyWdayEnd, meetWeekDay;
	int		i, k, key, loc;

	loc = 1;
	fpt = fopen(".\\conf\\DutyTime.txt", "r");
	if (fpt == NULL) {
		exp->v[loc++] = 543;			// All day long On Duty
		exp->v[loc] = -1;
		return(1);
	}
	// Get Weekday's duty time
	weekDay = atoi(exp->var[9]);
	meetWeekDay = 0;
	for (i=0; i<700; i++) {
		if (fgets(buffer, 120, fpt) == NULL)		// No more data
			break;
		for (k=0; k<12; k++) buf[k][0] = 0;
		if ((k=sscanf(buffer, "%s %s %s %s", 
			buf[0], buf[1], buf[2], buf[3])) < 1) 
			continue;
		key = atoi(buf[0]);
		if (key > 950000) break;
		if (key > 0 && key <= 7) {		// Format of week day
			dutyWday = key;
			if (p=strchr(buf[0], '-'))	// Perhaps 1-5  0900-1200 ....
				dutyWdayEnd = atoi(p+1);
			else dutyWdayEnd = dutyWday;
			if (dutyWdayEnd < dutyWday || dutyWdayEnd > 7)
				dutyWdayEnd = dutyWday;
			if (weekDay >= dutyWday && weekDay <= dutyWdayEnd) {
				strcpy(dutyTime[0], buf[1]);
				strcpy(dutyTime[1], buf[2]);
				strcpy(dutyTime[2], buf[3]);
				meetWeekDay = 1;
				break;
			}
		} 
	}
	if (meetWeekDay == 0 || dutyTime[0][0] == 0 ||
		dutyTime[0][0] == '-') {					// Off duty
		exp->v[loc++] = 542;						// you...
		exp->v[loc++] = weekDay + 670;				// Monday...
		exp->v[loc++] = 541;						// Off Duty
		exp->v[loc] = -1;
		fclose(fpt);
		return(1);
	}
	if (strcmp(dutyTime[0], "0000-2359") == 0) {
		exp->v[loc++] = 542;						// you...
		exp->v[loc++] = weekDay + 670;				// Monday...
		exp->v[loc++] = 554;						// On Duty All Day Long
		exp->v[loc] = -1;
		fclose(fpt);
		return(1);
	}
	exp->v[loc++] = 542;							// You ...
	exp->v[loc++] = weekDay + 670;					// Monday...
	exp->v[loc++] = 544;							// Duty time is...

	for (i=0; i<3; i++) {							// check 3 section of duty time
		if (dutyTime[i][0] == '-') break;			// no more

		loc = synthesisDayTime(dutyTime[i], loc);	// Morning(Noon...) xx o'clock xx minute
		p=strchr(dutyTime[i], '-');
		if (p && (*(p+1) != 0)) {
			exp->v[loc++] = 536;					// to
			loc = synthesisDayTime(p+1, loc);		// Morning(Noon...) xx o'clock xx minute
			exp->v[loc++] = 509;					// Silence
		} else {
			break;									// No ending 
		}
	}
	exp->v[loc] = -1;
	fclose(fpt);
	return(1);
}

int updateHoliday()
{
	int holidays[100];
	int	i, loc;

	for (i=8; i<totalLoc; i++) 
		holidays[i] = keys[i];
	for (i=totalLoc; i<100; i++) holidays[i] = 0;
	loc = 8;
	for (i=8; i<totalLoc; i++) {
		if (ymdValue < holidays[i]) {
			keys[loc++] = ymdValue;
			keys[loc++] = holidays[i];
//			totalLoc += 1;
			break;
		} else {
			if (ymdValue == holidays[i]) {
				keys[loc++] = holidays[i];
				break;
			}
		}
		keys[loc++] = holidays[i];
	}
	if (i >= totalLoc) {		// ymdValue is Max.
		keys[loc++] = ymdValue;
//		totalLoc += 1;
	} else {
		for (i=i+1; i<totalLoc; i++)
			keys[loc++] = holidays[i];
	}
	totalLoc = loc;
	return(1);
}

int deleteHoliday()
{
	int holidays[100];
	int	i, loc, found = 0;

	for (i=8; i<totalLoc; i++) 
		holidays[i] = keys[i];
	for (i=totalLoc; i<100; i++) holidays[i] = 0;
	loc = 8;
	for (i=8; i<totalLoc; i++) {
		if (ymdValue == holidays[i]) {
			found = 1;
			break;
		}
		keys[loc++] = holidays[i];
	}
	if (found == 0) return(-1);
	for (i=i+1; i<totalLoc; i++)
		keys[loc++] = holidays[i];
	totalLoc = loc;
	return(1);
}

int updateDuty()
{
	int	weekDay, i;

	weekDay = atoi(exp->var[9]);
	if (starting == 1) {
		starting = 0;
		for (i=0; i<3; i++)
			strcpy(dutyArray[weekDay-1][i], "-");		// clear all duty time for 1st time
	}
	if (strcmp(exp->var[10], exp->var[11]) == 0) return(1);
	for (i=0; i<3; i++) {
		if (dutyArray[weekDay-1][i][0] == '-') {
			sprintf(dutyArray[weekDay-1][i], "%s-%s", exp->var[10], exp->var[11]);
fdbprintf("weekday=%d array=%s\r\n", weekDay, dutyArray[weekDay-1][i]);
			break;
		}
	}
	return(1);
}

// save Holiday
int	SvHday()
{
	getAllDuty();
	updateHoliday();
	putAllDuty();
	return(1);
}

// Delete Holiday
int DlHday()
{
	if (checkYyMmDdGood(exp->var[10]) < 0) {
		vxp->branch -= 5;				// Error play branch
		return(1);
	}
	getAllDuty();
	if (deleteHoliday() < 0) {			// Not Found
		vxp->branch -= 5;
		return(1);
	}
	putAllDuty();
	return(1);
}


// save duty hour and minute
int SvDuty()
{
	getAllDuty();
	updateDuty();
	putAllDuty();
	exp->cnt[5] += 1;
	if (exp->cnt[5] >= 3) vxp->branch -= 5;		// 3 Section is completed
	return(1);
}

// synthesis duty time for Setting
int	SyDuty()
{
	int	k, n10, n11;

	n11 = atoi(exp->var[11]);
	n10 = atoi(exp->var[10]);
	if (n11 < n10) {					// end time should > begin time
		vxp->branch -= 5;
		return(1);
	}
	if (checkHhMmGood(n11) < 0) {		// Check end duty time
		vxp->branch -= 5;
		return(1);
	}
	k = 1;
	if (n11 == n10) {					// Off duty setting
		exp->v[k++] = 535;
		exp->v[k++] = 541;
	} else {
		exp->v[k++] = 535;							// Duty time you entered is...
		k = synthesisDayTime(exp->var[10], k);		// Morning(Noon...) xx o'clock xx minute
		exp->v[k++] = 536;							// to...
		k = synthesisDayTime(exp->var[11], k);		// Morning(Noon...) xx o'clock xx minute
	}
	exp->v[k] = -1;								// End
	return(1);
}

// Check if password has already been enterd
int	IfPwd()
{
	if (strlen(exp->var[8]) > 3) 				// password already entered
		vxp->branch += 10;						// jump over enter password

	exp->cnt[5] = 0;							// password enter count
	return(1);
}

int checkDuty()
{
//	long	lt;
	struct  tm		*tm;
//	FILE	*fpt;
	char	buffer[128] = {0};
	char	buf[12][32];
	char	dutyTime[3][32];
	char	*p;
	int		num, weekDay, dutyWday, dutyWdayEnd, toDate, meetWeekDay;
	int		dutyHour, dutyHourEnd, now;
	int		holiday;
	int		i, k, key;

//	time(&lt);
	tm=localtime(&nowTime);
	if (tm->tm_wday == 0) weekDay = 7;
	else weekDay = tm->tm_wday;
	toDate = (tm->tm_year - 11) * 10000 + (tm->tm_mon+1) * 100 + tm->tm_mday;
	now = tm->tm_hour * 100 + tm->tm_min;
fdbprintf("Today=%d now=%d weekday=%d\r\n", toDate, now, weekDay);

	fpt = fopen(".\\conf\\DutyTime.txt", "r");
	if (fpt == NULL) return(ON_DUTY);				// No file, take as All on duty
	for (i=0; i<3; i++)	dutyTime[i][0] = 0;

	// Get Weekday's duty time
	meetWeekDay = 0;
	for (i=0; i<700; i++) {
		if (fgets(buffer, 120, fpt) == NULL)		// No more data
			break;
		for (k=0; k<12; k++) buf[k][0] = 0;
		if ((num=sscanf(buffer, "%s %s %s %s %s %s %s %s %s %s %s %s", 
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6],
			buf[7], buf[8], buf[9], buf[10], buf[11])) < 1) 
			continue;
		key = atoi(buf[0]);
		if (key > 0 && key <= 7) {		// Format of week day
			dutyWday = key;
			if (p=strchr(buf[0], '-'))
				dutyWdayEnd = atoi(p+1);
			else dutyWdayEnd = dutyWday;
			if (dutyWdayEnd < dutyWday || dutyWdayEnd > 7)
				dutyWdayEnd = dutyWday;
			if (weekDay >= dutyWday && weekDay <= dutyWdayEnd) {
				strcpy(dutyTime[0], buf[1]);
				strcpy(dutyTime[1], buf[2]);
				strcpy(dutyTime[2], buf[3]);
				meetWeekDay = 1;
			}
		} else {
			if (key > 940000 && key < 9999999) {
				for (k=0; k<num; k++) {
					holiday = atoi(buf[k]);
fdbprintf("holiday=%d ", holiday);
					if (holiday == toDate) {
						fclose(fpt);
						return(OFF_DUTY);
					}
				}
			}
		}
	}
	if (meetWeekDay == 1) {
		for (i=0; i<3; i++) {				// check 3 section of duty time
			// Not Set on-duty, Take as off-duty
			if (dutyTime[i][0] == 0 || dutyTime[i][0] == '-') break;
			p=strchr(dutyTime[i], '-');
			if (p) dutyHourEnd = atoi(p+1);
			else dutyHourEnd = 9999;
			if (dutyHourEnd == 0) dutyHourEnd = 9999;
			dutyHour = atoi(dutyTime[i]);
fdbprintf("dutyHour=%d-%d now=%d\r\n", dutyHour, dutyHourEnd, now);
			if (now >= dutyHour && now <= dutyHourEnd) {
				fclose(fpt);
				return(ON_DUTY);
			}
		}
	}
	fclose(fpt);
	return(OFF_DUTY);					// Switch to Night
}

// type = 0: Meet Full 1:partial match
int checkIfExtension(TelList *tlxp, char *phone, int type)
{
	char	tmp[120];
	int		loc;

	tlxp->vmHomeWork = '0';
	if (strncmp(aniCaller, phone, strlen(phone)) == 0) return(-1);
	// 2nd caller(=called) dial to called, called Must not caller2, and caller1.
	// It's OK in drstar1, but Not in drfxop/fxsp when caller2 hangup, and caller1 takes his place.
	// Mark off for it.
//	if (dnisCalled[0] == '*')
//		if (strncmp(&dnisCalled[1], phone, strlen(phone)) == 0) return(-2);
	tmp[0] = 0;
	if ((loc = SelectRecordP("gtellist", "gTelNo", phone, type)) >= 0) {	// Meet Group
		GetDataP("telNo1", tmp, 32, loc);
		CleanSelectResult(loc);
	}
	if (tmp[0] == 0) strcpy(tmp, phone);
	if ((loc = SelectRecordP("tellist", "telNo", tmp, type)) >= 0) {		// Meet telNo
		GetDataP("attribute", tlxp->attribute, 8, loc);
		tlxp->attribute[0] |= 0x20;
		if (tlxp->attribute[0] == 'e') {									// It is extention
//			tlxp->exto = tlxp->attribute[3];
			GetDataP("telNo", tlxp->telNo, 32, loc);
			tmp[0] = 0;
			GetDataP("coCall1", tmp, 32, loc);
			if (tmp[0] == 0) tlxp->coCall = 0;
			else tlxp->coCall = 1;
//fdbprintf("exto1=%x\r\n", tlxp->exto);
			CleanSelectResult(loc);

			// To get vmHomeWork. if yes, direct jump to xxx's voicemail to leave message.
			if ((loc = SelectRecordP("extensionInfo", "extensionNo", tlxp->telNo, type)) >= 0) {
				// Meet extensionNo
				GetDataP("vmHomeWork", tmp, 32, loc);
				tlxp->vmHomeWork = tmp[0];
				CleanSelectResult(loc);
			}
			return(1);
		}
		CleanSelectResult(loc);
	}
	fdbprintf("Not extension\r\n");
	return(-1);
}

int	checkTaiwanTelno(char *telno, int len)
{
	if (telno[0] == '0') {
		if (telno[1] == '9' || telno[1] == '2') {
			if (len == 10) return(1);
		} else 
		if (telno[1] == '4') {
			if (telno[2] == '7' || telno[2] == '8') {
				if (len == 9) return(1);
			} else {
				if (len == 10) return(1);
			}
		} else {
			if (telno[1] >= 3 && telno[1] <= 8) {
				if (strncmp(telno, "0800", 4) == 0) {
					if (len == 10) return(1);
				} else {
					if (len == 9) return(1);
				}
			}
		}
	}
	return(0);
}

// end of check if (1) # entered. (2) silence over 4 sec. (3) extension No. extered.
int check_on_play()
{
	char	dig[64];
	int		len;
//	long	now;
	int		reason = 0;

	dig[0] = 0;
	len=ginn_getStringBuf(dig);
fdbprintf("stringin=%s\r\n", dig);
	if (len == 0) {					// Not enter 1st digit yet
		ltLen = 0;
		time(&ltEnd);
		ltEnd += 20;				// next time out on, allow longer greeting 
		return(-1);
	}
//	time(&now);
	if (len > ltLen) {				// New digit entered
		ltLen = len;
		ltEnd = nowTime + 4;		// Next timeout after 4 sec.
		if (dig[len-1] == '#') {	// # entered
			reason = 1;
			goto end_of_check;
		}
	}
	if (nowTime >= ltEnd) {				// timeOut
		reason = 2;
		goto end_of_check;
	}

	if (checkIfExtension(tlcp, dig, 0) >= 0) {
		reason = 3;
		goto end_of_check;			// extension No. entered
	}

	if (checkTaiwanTelno(dig, len) > 0) {
		reason = 4;
		goto end_of_check;
	}
//do_nothing:

	return(-1);

end_of_check:			// Ask to End of Play

	fdbprintf("End reason=%d\r\n", reason);
//	setFuncPointToKer("_uap_check_play", NULL);
	return(1);
}

int checkFromHandset()
{
	// dnisCalled=168800, aniCaller=886926xxxxxx calledNo=2000m
	FILE	*fpt;
	char	extension[16], handset[32], gateway[32], type[32];
	char	buffer[120];

	fpt = fopen(".\\conf\\NoWireTable.txt", "r");
	if (fpt == NULL) return(-1);					// File Not Exists

	// Get caller's Gateway and if called is extension in PBX
	while(1) {
		if (fgets(buffer, 120, fpt) == NULL) break;	// No more data
		if (sscanf(buffer, "%s %s %s %s", handset, gateway, extension, type) < 3) continue;
//fdbprintf("handset=[%s][%s]\r\n", handset, aniCaller);
		if (strcmp(handset, aniCaller) == 0) {		// Match to caller
			strcpy(handsetGateway, gateway);		// caller's gatewayID
			strcpy(handsetID, handset);				// caller's handsetID
			strcpy(handsetExtension, extension);	// caller's extension
			strcpy(handsetType, type);				// caller's dial type
			fclose(fpt);
			return(1);
		}
	}
	fclose(fpt);
	return(-1);
}

int fromHandSet()									// call from handset
{
	// Get caller's Gateway and if called is extension in PBX
	if (checkFromHandset() > 0) {
		vxp->branch = 403;
		inFrom = NOWIRE;
		return(1);
	}
	// called=168800, caller=8869xx-xxx-xxx
	if (strncmp(aniCaller, "8869", 4) == 0) {
//fdbprintf("Not Service You\r\n");
		vxp->branch = 123;							// Not Service You, to the end
		return(1);
	}
	return(-1);
}

int toHandSet()
{
	// dnisCalled=168, aniCaller=2000x calledNo=926xxxxxxx
	FILE	*fpt;
	char	extension[16], handset[32], gateway[32], type[32];
	char	buffer[120];
//	int		loc;

	fpt = fopen(".\\conf\\NoWireTable.txt", "r");
	if (fpt == NULL) return(-1);					// File Not Exists

	// Check if caller = Gateway
	while(1) {
		if (fgets(buffer, 120, fpt) == NULL) break;	// No more data
		if (sscanf(buffer, "%s %s %s %s", handset, gateway, extension, type) < 3) continue;
		if (strcmp(gateway, aniCaller) == 0) {		// Match to caller
			strcpy(handsetID, handset);				// caller's handsetID
			strcpy(handsetExtension, extension);	// caller's extension
			strcpy(handsetType, type);
			// generate T&called/caller
			if (strncmp(handsetID, "886", 3) == 0) {
				sprintf(exp->var[13], "T&0%s", &handsetID[3]);	// [loc] bypass 886. 
			} else {
				sprintf(exp->var[13], "T&%s", handsetID);
			}
			vxp->branch = 500;
			fdbprintf("var[13]==%s\r\n", exp->var[13]);
			fclose(fpt);
			return(1);
		}
	}
	fclose(fpt);
	return(-1);
}

// ***********************************************
// **** match to phone and get entry  ************

int getForward(char *phone)
{
	char inphone[32] = {0}, uncondition[32], busy[32] = {0}, noans[32] = {0}, netfail[32] = {0};
	char buffer[128] = {0}, stat[32], noDisturb[32];
	FILE *fpt;
	int	 meetPhone = 0;
	char *p;

	fpt = fopen(".\\conf\\CallForward.txt", "r");
	if (fpt == NULL) return(-1);

	fwd.extension[0] = 0;
	fwd.busy[0] = 0;
	fwd.noans[0] = 0;
	fwd.uncondition[0] = 0;
	fwd.netfail[0] = 0;
	fwd.stat[0] = 0;
	fwd.noDisturb[0] = 0;
	for (int i = 0; i <700; i++) {
		if (fgets(buffer, 120, fpt) == NULL) {
			break;
		}
		if (sscanf(buffer, "%s %s %s %s %s %s %s", inphone, uncondition, busy, noans, netfail, 
			stat, noDisturb) <= 1) 
			continue;
//fdbprintf("phone =[%s], inphone=[%s]\r\n", phone, inphone);
		if (p=strchr(inphone, '/')) {
			*p = 0;
			p += 1; 
			if (strcmp(p, phone) == 0) meetPhone = 1;
		}
		if (strcmp(inphone, phone) == 0) meetPhone = 1;		// call forward exists
		if (meetPhone == 1) {
			strcpy(fwd.extension, phone);
			strcpy(fwd.busy, busy);
			strcpy(fwd.noans, noans);
			strcpy(fwd.uncondition, uncondition);
			strcpy(fwd.netfail, netfail);
			strcpy(fwd.stat, stat);
			strcpy(fwd.noDisturb, noDisturb);
			fclose(fpt);
			if (stat[0] == 'C') return(-2);		// close
			return(1);
		}
	}
	fclose(fpt);
	return(-1);
}

int synForward(int noEntry)
{
	int	setup = 0, i = 1, iSave;

    // 分機號碼, 無條件轉移, 忙線轉移, 無應答轉移

    exp->v[i++] = 501;			// 分機
    i = ifx(aniCaller, i, 1);
	if (noEntry == 1) {
		exp->v[i++] = 508;		// 目前未設定任何呼叫轉移電話
		exp->v[i++] = 509;		// 靜音
		exp->v[i] = -1;
		return(1);
	}
	iSave = i;
    exp->v[i++] = 502;			// 已設定之呼叫轉移電話為...
	if (fwd.uncondition[0] != '-') {
		setup = 1;
		exp->v[i++] = 503;      // 無條件轉移:
		i = ifx(fwd.uncondition, i, 1);
		exp->v[i++] = 509;		// 靜音
	}
	if (fwd.busy[0] != '-') {
		setup = 1;
		exp->v[i++] = 504;      // 忙線轉移:
		i = ifx(fwd.busy, i, 1);
		exp->v[i++] = 509;		// 靜音
	}
	if (fwd.noans[0] != '-') {
		setup = 1;
		exp->v[i++] = 505;      // 無人應答轉移:		
		i = ifx(fwd.noans, i, 1);
		exp->v[i++] = 509;		// 靜音
	}
	if (fwd.netfail[0] != '-') {
		setup = 1;
		exp->v[i++] = 506;      // 無人應答轉移:		
		i = ifx(fwd.netfail, i, 1);
		exp->v[i++] = 509;		// 靜音
	}
	if (fwd.stat[0] == 'C')		// forword is closed
		exp->v[i++] = 507;

	if (setup == 0) {
		i = iSave;
		exp->v[i++] = 508;		// 目前未設定任何呼叫轉移電話
		exp->v[i++] = 509;		// 靜音
	}
	exp->v[i] = -1;
	return(1);
}
 
// Get Ymt and send to fxsp
int sendYmt(int callNo)
{
	int		fid;
	int		offset;

	if ((fid = open(".\\ymt.dat", O_RDWR|O_BINARY, 0644)) < 0) {
		fdbprintf("Open ymt.dat error %d\r\n", fid);
		return(-1);
	}

	offset = (callNo - 810) * sizeof(ymtd);
	lseek(fid, offset, SEEK_SET);
	if (read(fid, &ymt, sizeof(ymtd)) <= 0) goto ErrorClose;
	if (!ymt.valid || ymt.startDate == 0) goto ErrorClose;
	time(&ymt.endDate);
	lseek(fid, offset, SEEK_SET);
	write(fid, &ymt, sizeof(ymtd));
	strcpy(exp->var[16], ".\\mess\\RingBack");
	sprintf(exp->var[13], "T&,%s/%s//%s/var16", ymt.telNo, aniCaller, ymt.handset);
//	sprintf(exp->var[13], "T&,%s/886223881115//%s/var16", ymt.telNo,  ymt.handset);	// for test
	close(fid);
	ymtOffset = offset;		// For RtErrY() to update NRC.
	return(1);
ErrorClose:
	close(fid);
	return(-1);			// No valid Ymt
}

// check if in blacklist.txt
int	checkIfBlack(char *called, char *caller)
{
	char fileName[32];
	FILE	*fd;
	char	buf[200];
	int		blackType;
	char	blackTel[32];

//	exp->var[17][0] = 0;
	if (dialRecCmd == 1) return(1);
	dialRecCmd = 1;
	strcpy(fileName, ".\\conf\\blacklist.txt");
	if ((fd=fopen(fileName, "r")) == NULL) {
		fdbprintf("Open .\\conf\\blacklist.txt Error\r\n");
		return(-1);
	} 
	while(1) {					// Loop to Get line by line
		if( fgets(buf, 100, fd) == NULL) {
			fclose(fd);
			return(-2);			// End of file
		}
		blackTel[0] = 0;
		blackType = 0;
		sscanf(buf, "%s %d", blackTel, &blackType);
		if (blackType < 1 || blackType > 3) continue;
fdbprintf("%s %d\r\n", blackTel, blackType);
		if (strcmp(blackTel, called) == 0) break;
		if (strcmp(blackTel, caller) == 0) break;
	}
	fclose(fd);

	sprintf(buf, "/C=%d%04d Caller Add NOIVR Record=./rec/%d%4d.wav", vxp->voie+1, cfrID, 
		vxp->voie+1, cfrID);
	strcat(exp->var[17], buf);
//	strcpy(exp->var[17], &exp->var[19][1]);  // var[19]="T/C...."
	return(blackType);
}

typedef struct {
	char	prefixStart[MAXPREFIX][16];
	char	prefixEnd[MAXPREFIX][16];
	int		lengthStart[MAXPREFIX];
	int		lengthEnd[MAXPREFIX];
	char	destination[MAXPREFIX][16];
	char	result[MAXPREFIX];
	int		totalPrefix;
//	int		modifyTime;
} prfxx;

prfxx	prfx;

int		pstnResultLength;

void resetPrefixResult()
{
	for (int i=0; i<MAXPREFIX; i++)
		prfx.result[i] = 0;
	pstnResultLength = 0;
	return;
}

int	getAllPrefix(int limitModule)
{
	int		i, loc = 0, len;
	char	setName[40], errorMsg[120];
	char	wkBuf[128];
	static  int	currModule = 100;

	// 0 - 7 limit Module
	if (limitModule < 0) limitModule = 0;
	else if (limitModule >= 8) limitModule = 7;

	if (limitModule == currModule) return(1);
	currModule = limitModule;

	sprintf(setName, "prefixGroup%d", limitModule);
fdbprintf("setname=%s\r\n", setName);
	prfx.totalPrefix = 0;

	wkBuf[0] = 0;
fdbprintf("prefixGroup = 'ALL'\r\n");
	if ((loc = SelectRecorder("*", setName, wkBuf, NULL)) < 0) {
		GetErrorMessage(wkBuf, 119);
		fdbprintf("Select %s with %s Error1:%s\r\n", setName, wkBuf, errorMsg);
		if (reOpenDatabase() < 0) return(-1);
		if ((loc = SelectRecorder("*", setName, wkBuf, NULL)) < 0) 
			return(-1);							// No Match
	}
	for(i=0; i<MAXPREFIX; i++) {
fdbprintf("i=%d max=%d\r\n", i, MAXPREFIX);
		if (i > 0) NextData(loc);
		if (BeEOF(loc) < 0) break;
		GetDataP("prefixStart", wkBuf, 16, loc);
		if ((wkBuf[0] != '*') && (wkBuf[0] != '#') &&
			(wkBuf[0] < 0x30 || wkBuf[0] > 0x39)) {
			fdbprintf("Prefix start Error on %d\r\n", i); 
			continue;
		}
		strcpy(prfx.prefixStart[i], wkBuf);
		GetDataP("prefixEnd", wkBuf, 16, loc);
		if (wkBuf[0] == 0)	// NULL String
			strcpy(prfx.prefixEnd[i], prfx.prefixStart[i]);
		else {
			if (wkBuf[0] < 0x30 || wkBuf[0] > 0x39) {
				fdbprintf("Prefix End Error on %d\r\n", i); 
				continue;
			}
			strcpy(prfx.prefixEnd[i], wkBuf);
		}
		GetDataP("lengthStart", wkBuf, 8, loc);
		prfx.lengthStart[i] = atoi(wkBuf);

		len = strlen(prfx.prefixStart[i]);
		if (prfx.lengthStart[i] < len)
			prfx.lengthStart[i] = len;
		GetDataP("lengthEnd", wkBuf, 8, loc);
		prfx.lengthEnd[i] = atoi(wkBuf);
		if (prfx.lengthEnd[i] < prfx.lengthStart[i])
			prfx.lengthEnd[i] = prfx.lengthStart[i];
		GetDataP("destination", wkBuf, 16, loc);
		wkBuf[0] &= 0x5f;
		if (wkBuf[1] > 0x39) wkBuf[1] = 0;		// If Internet not I800
		strcpy(prfx.destination[i], wkBuf);
fdbprintf("prefix=%s %s len=%d %d destine=%s\r\n", prfx.prefixStart[i], prfx.prefixEnd[i],
prfx.lengthStart[i], prfx.lengthEnd[i], prfx.destination[i]);
	}
fdbprintf("End of Getprefix %d\r\n", loc);
	CleanSelectResult(loc);
	prfx.totalPrefix = i;
	return(1);
}

//****************************************************
// Check if to Internet Only
// Assume telNo is full length
// return(2) to Internet
// retunr(0) default, all allow to internet
// return(-1) to other
int	checkInternet(char *telNos, char *destination)
{
	int		loc, preLen, telLen, telValue, preValue1, preValue2;
	char	prefix1[32], prefix2[32];
//	char	destination[32];
	int		maxLen = 0, resultLength = 0;
	char	telNo[64];

	// Assume come here a digit more then previuos one
	destination[1] = 0;								// Reset Prefix
	if (prfx.totalPrefix == 0) return('I');			// Default is OK to internet at all.
	strcpy(telNo, telNos);
	telLen = strlen(telNo);
	for (loc=0; loc<prfx.totalPrefix; loc++) {
//fdbprintf("Destination=%x\r\n", destination);
		if (telNo[0] == '*' || telNo[0] == '#') {	// Not Allow range
			strcpy(prefix1, prfx.prefixStart[loc]);
			preLen = strlen(prefix1);
			if (strncmp(telNo, prefix1, preLen) != 0) {
				prfx.result[loc] = -1;
				continue;
			}
//fdbprintf("telno1=%s prefix=%s\r\n", telNo, prefix1);
			prfx.result[loc] = 1;
			// Take the length Match
			if (preLen >= prfx.lengthStart[loc] && preLen <= prfx.lengthEnd[loc] 
				&& preLen > maxLen) { // take the max. length of prefix in table
				strcpy(destination, prfx.destination[loc]);
				resultLength = prfx.lengthEnd[loc];
				maxLen = preLen;
				continue;
			}
		} else {	// Not *, #
			strcpy(prefix1, prfx.prefixStart[loc]);
			strcpy(prefix2, prfx.prefixEnd[loc]);
fdbprintf("prefix=%s-%s\r\n", prefix1, prefix2);
			preLen = strlen(prefix1);
//			telLen = strlen(telNo);
			if (prefix1[0] == '*' || prefix1[0] == '#') {		// avoid *,#
				prfx.result[loc] = -1;
				continue;
			}
//fdbprintf("telno2=%s prefix=%s\r\n", telNo, prefix1);
			telNo[preLen] = 0;
			telValue = atoi(telNo);
			preValue1 = atoi(prefix1);
			preValue2 = atoi(prefix2);
			if (telValue < preValue1 || telValue > preValue2) {
				prfx.result[loc] = -1;
				strcpy(telNo, telNos);
				continue;
			}
fdbprintf("maxlen=%d prelen=%d\r\n", maxLen, preLen);
			if (prfx.lengthStart[loc] == prfx.lengthEnd[loc])		// length exactly same
				if (prfx.lengthStart[loc] == telLen) {
					strcpy(destination, prfx.destination[loc]);
					resultLength = prfx.lengthEnd[loc];
					break;
				}
			if (telLen < prfx.lengthStart[loc] || telLen > prfx.lengthEnd[loc])
				continue;
			if (maxLen < preLen) {
				maxLen = preLen;
				strcpy(destination, prfx.destination[loc]);
				resultLength = prfx.lengthEnd[loc];
				strcpy(telNo, telNos);
fdbprintf("dest=%s length=%d telno=%s\r\n", destination, resultLength, telNo);
				continue;
			}
			strcpy(telNo, telNos);
			continue;
		}
	}
fdbprintf("destination=%s\r\n", destination);
	if (destination[0] == 0) return(-1);
	return(destination[0]);
}

//****************************************************
// Check if send telNo to PSTN or Internet or forbid
// return(1) to Pstn
// return(2) to Inernet
// return(3) forbidden
// return(0) No result
int	checkPSTN(char *telNo, char *destination)
{
	int		loc, preLen, telLen, telValue, preValue1, preValue2;
	char	prefix1[32], prefix2[32];
	char	superDestine = 0;					// iiii
	int		maxLen = 0, len, returnResult = -1, meetCount = 0, resultLength = 0;

	// Assume come here a digit more then previous one
//	if (prfxp->totalPrefix == 0) return(3);
	if (prfx.totalPrefix == 0) return(1);		// If No InternetOrPstn.txt, take as to PSTN.
	                                            // InternetOrPstnX.txt is rejected before, if totalPrefix = 0
	telLen = strlen(telNo);
	for (loc=0; loc<prfx.totalPrefix; loc++) {
		if (prfx.result[loc] == -1) continue;
		if (prfx.result[loc] == 1) {
			len = strlen(prfx.prefixStart[loc]);
			if (len > maxLen) {			// Take the longest match
				strcpy(destination, prfx.destination[loc]);
				resultLength = prfx.lengthEnd[loc];
				meetCount += 1;
				maxLen = len;
			}
			continue;
		}
		if (telNo[0] == '*' || telNo[0] == '#') {	// Not Allow range
			strcpy(prefix1, prfx.prefixStart[loc]);
			telLen = strlen(telNo);
			preLen = strlen(prefix1);
			if (telLen <= preLen) {
				if (strncmp(telNo, prefix1, telLen) != 0) {
					prfx.result[loc] = -1;
					continue;
				}
fdbprintf("telno1=%s prefix=%s\r\n", telNo, prefix1);
				if (telLen == preLen) {
					prfx.result[loc] = 1;
					// preLen must > maxLen, Take the longest Match
					strcpy(destination, prfx.destination[loc]);
					resultLength = prfx.lengthEnd[loc];
					meetCount += 1;
					maxLen = preLen;
					continue;
				}
fdbprintf("superDestine1=%x %s\r\n", superDestine, prfx.destination[loc]);
				if (superDestine == 0) superDestine = prfx.destination[loc][0];
				if (superDestine != prfx.destination[loc][0])	// Destine Not Match iiii
					returnResult = 0;
			}
		} else {	// Not *, #
			strcpy(prefix1, prfx.prefixStart[loc]);
			strcpy(prefix2, prfx.prefixEnd[loc]);
			preLen = strlen(prefix1);
			telLen = strlen(telNo);
			if (telLen <= preLen) {
				prefix1[telLen] = 0;
				prefix2[telLen] = 0;
				if (prefix1[0] == '*' || prefix1[0] == '#') {		// avoid *,#
					prfx.result[loc] = -1;
					continue;
				}
				telValue = atoi(telNo);
				preValue1 = atoi(prefix1);
				preValue2 = atoi(prefix2);
				if (telValue < preValue1 || telValue > preValue2) {
					prfx.result[loc] = -1;
					continue;
				}
fdbprintf("telno2=%s prefix=%s\r\n", telNo, prefix1);
				if (telLen == preLen) {
					prfx.result[loc] = 1;
					// preLen must > maxLen, Take the longest Match
					strcpy(destination, prfx.destination[loc]);
					resultLength = prfx.lengthEnd[loc];
					meetCount += 1;
					maxLen = preLen;
					continue;
				}
fdbprintf("superDestine2=%x %x\r\n", superDestine, prfx.destination[loc][0]);
				if (superDestine == 0) superDestine = prfx.destination[loc][0];
				if (superDestine != prfx.destination[loc][0])	// Not Match superDestine
					returnResult = 0;
			}
		}
	}
fdbprintf("returResult=%d destine=%x %x meetCount=%d length=%d\r\n", 
returnResult, superDestine, destination[0], meetCount, resultLength); 
	if (returnResult >= 0) return(returnResult);
	if (superDestine != 0) {
		if (destination[0] != 0) {
			if (superDestine != destination[0]) return(0);	// Not Match
		}
		destination[0] = superDestine;
	}
	if (meetCount == 1) pstnResultLength = resultLength;
	if (destination[0] == 'I') return(2);					// to Internet
	else if (destination[0] == 'F') return(3);				// Forbidden
	else if (destination[0] == 'P') return(1);				// to PSTN
	return(3);												// Not meet
}

int CkPstn()
{
	int		len, newOne, result;

	newOne = strlen(exp->var[8]);
//	if (exp->var[8][0] == '#')	newOne = 0;

	if (newOne == 1) {
		len = strlen(exp->var[7]);
		strcat(exp->var[7], exp->var[8]);
		len += 1;
		if (pstnResultLength > 0) {			// The check is finished
			if (len == pstnResultLength)
				vxp->branch = 100;			// Hangup to connect
			else vxp->branch = 526;			// get next digit
			return(1);
		}
		result = checkPSTN(exp->var[7], internetPrefix);
fdbprintf("pstnresult=%d len=%d\r\n", result, len, pstnResultLength);
		switch(result) {
		  case 2:
			  exp->var[7][0] = 0;
			  exp->var[8][0] = 0;
			  vxp->branch = 560;			// it is to internet, switch to internet
			  return(1);
		  case 1:
			  if (len == pstnResultLength)	// The check is finished
				 vxp->branch = 100;			// Hangup to connect
			  else vxp->branch = 526;		// It is PSTN, get next digit
			  return(1);
		  case 3:
			  vxp->branch = 530;			// Forbidden
			  return(1);
		  default:							// Not decided, get next digit
			  vxp->branch = 526;
			  return(1);
		}
	}
	// No digit entered
	if (strlen(exp->var[7]) == 0)
		vxp->branch = 530;					// Flash back and hangup
	else vxp->branch = 100;					// Connect All
	return(1);
}

int	CkLan()
{
	int	len, newOne;
	char	tAnd[8];
//long	lt;

//time(&lt);
fdbprintf("lt=%d digit=%c\r\n", nowTime, exp->var[8][0]);
	// Use Fast Mode except aaTel(caller2) who will be interfered with accepting called Number by ringing. 
	strcpy(tAnd, "T&,");
	newOne = strlen(exp->var[8]);
	if (exp->var[8][0] == '#')	{
		exp->var[8][0] = 0;
		newOne = 0;
	}
	if (newOne == 1) {
		strcat(exp->var[7], exp->var[8]);
		len = strlen(exp->var[7]);
		if (pstnResultLength <= 0)
		   checkPSTN(exp->var[7], internetPrefix); 

		if (pstnResultLength > 0) {			// The check is finished
			if (len == pstnResultLength) {	// goto dialout
				checkIfBlack(exp->var[7], aniCaller);
				// Mark off for dial to internet must be T&T
//				if (aniCallerAAType == 1)		// If caller is AA, it should be normal mode with codec G729
					strcpy(tAnd, "T&T,");
				// Dial to Internet will always G729
				if (dialCodecCmd == 0) {
					strcat(exp->var[17], "/Codec=g729");
					dialCodecCmd = 1;
				}
				strcpy(exp->var[16], ".\\mess\\RingLong");
				sprintf(exp->var[13], "%s%s%s/var16%s", tAnd, &internetPrefix[1], exp->var[7], exp->var[17]);
fdbprintf("Send out\r\n");
				return(1);
			}
		}
		vxp->branch = 570;					// get next digit
		return(1);
	}
	// No digit entered
fdbprintf("No digit Entered \r\n");
	checkIfBlack(exp->var[7], aniCaller); 	// In BlackList
//	if (strcmp(aniCaller, tlp->aaTel) == 0)	// If caller is AA, it should be normal mode with codec G729
	if (aniCallerAAType == 1)
		strcpy(tAnd, "T&T,");

	// Dial to Internet will always G729
	if (dialCodecCmd == 0) {
		strcat(exp->var[17], "/Codec=g729");
		dialCodecCmd = 1;
	}
	strcpy(exp->var[16], ".\\mess\\RingLong");
	sprintf(exp->var[13], "%s%s/var16%s", tAnd, exp->var[7], exp->var[17]);
	return(1);
}

int	checkIfVip()
{
	FILE	*fd;
	char	buffer[120];
	char	vipTel[64], vipExt[32];
	char	fileName[40];

	strcpy(fileName, ".\\conf\\VipList.txt");

	fd = fopen(fileName, "r");
	if (fd == NULL) return(-1);

	while(1) {
		if (fgets(buffer, 120, fd) == NULL) break;	// No more data 
		if (sscanf(buffer, "%s %s %s %s %s %s %[^\r\n]s", vipTel, exp->var[13], exp->var[14], vipExt, 
			exp->var[10],							// backup phone 
			exp->var[11],							// sMS show phone 
			exp->var[12]) < 2)						// SMS content
			 continue;
		if (strcmp(vipTel, aniCaller) == 0) {		// Caller is VIP
			strcpy(exp->var[7], vipExt);
			strcpy(exp->var[8], "#");
			fdbprintf("VIP=[%s] [%s] [%s] [%s] [%s]\r\n", vipTel, vipExt, 
				exp->var[10], exp->var[11],	exp->var[12]);
			vipCall = 1;
			vxp->branch = 48;						// set hangup then CkExt()
			fclose(fd);
			return(1);
		}
	}
	fclose(fd);
	return(-1);
}

//******************** Greeting Synthesis ****************
int	greeting(int type)
{
	int k = 1;

	exp->v[k++] = 480;
	if (type & 1) exp->v[k++] = 481;		// conference
	exp->v[k++] = 482;
	if (type & 2) exp->v[k++] = 483;		// voiceMail
	exp->v[k] = -1;
	return(1);
}

int	GetDataP(char *a, char *b, int c, int loc)
{
	GetData(a, b, c, loc);
	fdbprintf("%s=[%s] loc=%d\r\n", a, b, loc);
	return(1);
}

// Get need items in tellist
//**********************************************************
int	getTellistFields(int loc)
{
	char	tmp[8];

	GetDataP("attribute", tlap->attribute, 8, loc);
	tlap->attribute[0] |= 0x20;
	GetDataP("limitModule", tmp, 8, loc);
	tlap->limitModule = atoi(tmp);
	GetDataP("telNo",tlap->telNo, 32, loc);
	return(1);
}

// Could be partial match
//**************************************************************
int SelectRecordP(char *dataset, char *fieldName, char *fieldValue, int type)
{
//	char	pKeys[64];
	char	wkBuf[120], errorMsg[120];
//	int		lens;
	int		len, loc;

	len = strlen(fieldValue);

	sprintf(wkBuf, "%s = '%s'", fieldName,  fieldValue);
fdbprintf("%s\r\n", wkBuf);
	if ((loc = SelectRecorder("*", dataset, wkBuf, NULL)) < 0) {
		GetErrorMessage(errorMsg, 119);
		fdbprintf("Select %s with %s Error1:%s\r\n", dataset, wkBuf, errorMsg);
		if (reOpenDatabase() < 0) return(-1);
		if ((loc = SelectRecorder("*", dataset, wkBuf, NULL)) < 0) {
			if (type == 0) return(-1);			// Need Exact Match
		}
	}
	if (BeEOF(loc) == 0) {
fdbprintf("loc=%d !!!!!!!\r\n", loc);
		return(loc);
	}
	CleanSelectResult(loc);
	// Partial Match
	sprintf(wkBuf, "%s like concat(%s, \"%s\")", fieldValue, fieldName, "%");
fdbprintf("%s\r\n", wkBuf);
	if ((loc = SelectRecorder("*", dataset, wkBuf, NULL)) < 0) {
		GetErrorMessage(errorMsg, 119);
		fdbprintf("Select dataset from %s Error2:%s\r\n", dataset, wkBuf, errorMsg);
		if (reOpenDatabase() < 0) return(-1);
		if ((loc = SelectRecorder("*", dataset, wkBuf, NULL)) < 0)
			return(-1);							// Need Exact Match
	}
	if (BeEOF(loc) == 0) {
		GetDataP("matchSize", wkBuf, 8, loc);
		if (wkBuf[0] == '0') return(loc);	// No need to match Size
	}
	CleanSelectResult(loc);
	return(-1);
}

//******************** check called/caller ****************
int CkFunc()
{
  char	tmp[64], sTelNo[64], *p;
  int	calledLen, i, dlen, callerLen, lens, sCallerExist, sCalledExist, loc;
//int	calledNo; // callerNo;
//static count=0;

  memset(tmp, 0, sizeof(tmp));
  exp->var[4][0] = 0;
  exp->var[7][0] = 0;
  exp->var[10][0] = 0;
  exp->var[11][0] = 0;
  exp->var[12][0] = 0;
  exp->var[13][0] = 0;
  exp->var[17][0] = 0;
  exp->var[18][0] = 0;
  exp->cnt[1] = 0;
  cfrID = (cfrID + 1) % 10000;			// for conference Use
  notPassDtmf = 0;
  dialCodecCmd = 0;
  dialRecCmd = 0;
  vxp->codec = -1;						// No opinion about codec
  aniCallerAAType = 0;
  greetingType = 0;
  if (voiceMail == 1) greetingType |= 2;
  if (telCfrPorter[0] != 'n') greetingType |= 1;
  vipCall = 0;
  tlap=(TelList *)&telList[0];			// for aniCaller
  tlcp=(TelList *)&telList[1];
  tldp=(TelList *)&telList[2];
  for (i=0; i<3; i++)
	  memset(&telList[i], 0, sizeof(TelList));
  time(&nowTime);
  // Check On/Off Duty, Get mess1500 or mess1530(Greeting)
  lens = ginn_ani(tmp);		//取得主被叫號   
  if (lens == 0) {
	 fdbprintf("line(%d) incoming call, but can not found ani(%s)!!\n",vxp->voie,tmp);
     vxp->branch = 10;
     return 0;
  }
  fdbprintf("line(%d) incoming call, ani(%s)!!\n", vxp->voie, tmp);
  p = strchr(tmp, '/');
  if (p) {
	  *p  = 0;
	  strcpy(aniCaller, p+1);			// caller  
	  strcpy(dnisCalled, tmp);
  } else {
	aniCaller[0] = 0;
	strcpy(dnisCalled, tmp);
  }

  // for test
  // sprintf(exp->var[19], "T/C=%d%d%d Caller Add IVR Record=.\\rec\\%d%d.wav", rand(), vxp->voie, count++, aniCaller, count);

  setFuncPointToKer("_uap_check_play", NULL);

  inFrom = FXO;							// default from FXO
fdbprintf("inFrom=FXO\r\n");

  // called = 168xxxx 168=groupID
  dlen = strlen(groupID);
  callerLen = strlen(aniCaller);
  calledLen = strlen(dnisCalled);

  // get gtellist to find if biasName of aniCaller Exists, and take the shorter as extensionNo
  sCallerExist = sCalledExist = 0;
  sTelNo[0] = 0;
  if ((loc = SelectRecordP("gtellist", "gTelNo", aniCaller, 0)) >= 0) {
 	 if (BeEOF(loc) == 0) {
		GetDataP("telNo2", tmp, 5, loc); 
		if (tmp[0] == 0) 						// Only 1 item Max
			GetDataP("telNo1", sTelNo, 5, loc);	// sTelNo is telNo, aniCaller is bTelNo 
	 }
	 CleanSelectResult(loc);
  }
  if (sTelNo[0] == 0) strcpy(sTelNo, aniCaller);

  aniCallerAAType = checkIfAttendent(aniCaller);	// 1:Caller is attendent

  // get tellist entry using sTelNo
  tlap->extensionNo[0] = 0;
  if ((loc = SelectRecordP( "tellist", "telNo", sTelNo, 0)) >= 0) {
	 sCallerExist = 1;
	 getTellistFields(loc);
	 lens = strlen(sTelNo);
	 if (lens < callerLen) strcpy(tlap->extensionNo, sTelNo);
	 else strcpy(tlap->extensionNo, aniCaller);
	 CleanSelectResult(loc);
  }
  if ((duty=checkDuty()) == OFF_DUTY) {
	 strcpy(exp->var[21], "1530");
	 if (allowMail(publicMailBox) > 0) {
		strcpy(exp->var[4], publicMailBox);
		strcpy(exp->var[22], "1536");
	 } else
		strcpy(exp->var[22], "1535");
  } else {
	 strcpy(exp->var[21], "1500");
	 strcpy(exp->var[22], "1515");
  }

  // 168 from FXO or FXS or WEB
  if (strncmp(dnisCalled, groupID, dlen) == 0) {
	 // Check if from Not-AutoAnswer here

//   calledNo = atoi(&dnisCalled[dlen]);		// called=1682000x caller=xxxxxx
	 if (dnisCalled[calledLen-1] == '#') {
		calledLen -= 1;
		dnisCalled[calledLen] = 0;
	 }
	 calledLen -= dlen;
	 if (tlap->attribute[0] == 'e') {			// if caller is extension
		if ((tlap->attribute[3] | 0x20) != 'o')	// if 'o', should pass DTMF to 
			notPassDtmf |= 1;					// Not Pass to Caller.
		inFrom = FXS;
		fdbprintf("inFrom=FXS\r\n");
		getForward(aniCaller);					// Get fwd.noDisturb(Yes/-)
		getAllPrefix(tlap->limitModule);		// Use caller's prefixGroup to destine called
		resetPrefixResult();					// Initialize prefix table
		if (prfx.totalPrefix == 0 &&
			tlap->limitModule != 0) {			// No internetOrPstnX.txt or Empty
			fdbprintf("1.No internetOrPstn%d.txt exists\r\n", tlap->limitModule);
			vxp->branch = 100;
			ginn_answercall();					// Answer the call
			return(1);
		}
		if (dnisCalled[dlen] == extensionToTrunk) {// 1689 to reach FXO
			if (pstnTalkTime > 0) {
				sprintf(tmp, "/TalkTime=%d", pstnTalkTime);
				strcat(exp->var[17], tmp);
			}
			strcpy(exp->var[16], ".\\mess\\mess0600");
			checkIfBlack(trunkID, aniCaller);
			if (aniCallerAAType == 1) {		// Caller is attendent
				if (dialCodecCmd == 0) {
					strcat(exp->var[17], "/Codec=g729");
					dialCodecCmd = 1;
				}
				vxp->codec = 18;			// G729 for hook off
			}
			sprintf(exp->var[13], "T&B%s/%s/var16%s", trunkID, aniCaller, exp->var[17]);	// reach 1st one
			vxp->branch = 510;
			ginn_answercall();				// Answer the call
			return(1); 
		}
		ginn_answercall();					// Answer the call
		// Not put Representive No. in aniCallerRef for setForward(). 
		sprintf(aniCallerRef, "%s/%s", aniCaller, sTelNo);
     	if (calledLen >= 1) {				// tel No. included, Maybe 9.
			strcpy(exp->var[7], &dnisCalled[3]);
			strcpy(exp->var[8], "#");
			if (fwd.noDisturb[0] == 'Y') {	// You have set NO disturb
				vxp->branch = 391;
			} else
				vxp->branch = 401;
			return(1);						// FXS CkExts()
		}
		greeting(greetingType);

		if (fwd.noDisturb[0] == 'Y') {
			vxp->branch = 390;
		} else
			vxp->branch = 400;				// FXS flow
		return(1);
	 } else {	// Not extension
		if (calledLen >= 2) {			// tel No. included
			strcpy(exp->var[7], &dnisCalled[dlen]);
			strcpy(exp->var[8], "#");
			vxp->branch = 50;			// CkExt()
		} else {
			if (checkIfVip() < 0) {		// Caller is VIP
				if (autoAttendent == 'n') {
					exp->var[7][0] = trunkToOperator;
					exp->var[7][1] = 0;
					strcpy(exp->var[8], "#");
					vxp->branch = 50;	// CkExt()
				} else					// Put left to stringin	
					ginn_dnis(&dnisCalled[dlen]);
			}
		}
		ginn_answercall();					// Answer the call
		if (tlap->attribute[0] == 'w') {	// WEB
			inFrom = WEB;
			fdbprintf("inFrom=WEB\r\n");
			if (duty == OFF_DUTY) vxp->branch = 122;
		}
		return(1);
	 }
  } else {	// Not 168xxxxx
	 if (dnisCalled[0] == '*') {
		 // Special Function(*1, *2, *3) for FXS only, called should be
		 // in FXS(Extension Number), who initiates *.
	     ginn_answercall();					// Answer the call

		// get gtellist to find if called has same telNo with different number
		sCalledExist = 0;
//		sprintf(tmp, "gTelNo = '%s'", &dnisCalled[1]);
		if ((loc = SelectRecordP("gtellist", "gTelNo", &dnisCalled[1], 0)) >= 0) {
			if (BeEOF(loc) == 0) sCalledExist = 1;
			CleanSelectResult(loc);
		}
		if (sCalledExist == 0) {
			// get tellist entry
//			sprintf(tmp, "telNo = '%s'", );
			if ((loc = SelectRecordP("tellist", "telNo", &dnisCalled[1], 0)) >= 0) {
				if (BeEOF(loc) == 0) sCalledExist = 1;
				CleanSelectResult(loc);
			}
		}
		if (sCalledExist == 1) {
			vxp->branch = 410;				// Star1 Flow for FXO
			// Remove mark off. for necessary to announce when enter *1 V1.29
			strcpy(exp->var[22], "1518");	// Set for *1 anouncement
			// caller inFrom FXO or FXS ?
			inFrom = FXO;					// for *1(Transfer), *2(Hold), *3(Conference)
			if (sCallerExist == 1) {
				inFrom = FXS;
				if ((tlap->attribute[3] | 0x20) != 'o')	// if 'o', should pass DTMF to caller
					notPassDtmf |= 1;					// Not Pass to Caller
				getAllPrefix(tlap->limitModule);
				resetPrefixResult();					// Initialize prefix table
				if (prfx.totalPrefix == 0 &&
					tlap->limitModule != 0) {			// No internetOrPstnX.txt or Empty
					fdbprintf("2.No internetOrPstn%c.txt exists\r\n", tlap->limitModule);
					vxp->branch = 100;
					ginn_answercall();					// Answer the call
					return(1);
				}
			}
fdbprintf("inFrom1=%d\r\n", inFrom);
			return(1);
		}
		fdbprintf("Caller %s Not in Tellist\r\n", dnisCalled);
		vxp->branch = 100;
		return(1);
	 }
	 // called other than 168xxxxx and *, process here
	 // To get the prefix of called maybe 169. Take ext as from tk...
	 if ((loc = SelectRecordP( "tellist", "telNo", dnisCalled, 1)) >= 0) {
		GetDataP("telNo", sTelNo, 63, loc);
		CleanSelectResult(loc);
		dlen = strlen(sTelNo);

	    if (dnisCalled[calledLen-1] == '#') {
		   calledLen -= 1;
		   dnisCalled[calledLen] = 0;
		}
fdbprintf("dlen=%d calledLen=%d\r\n", dlen, calledLen);
		calledLen -= dlen;

		if (calledLen >= 2) {			// tel No. included
			strcpy(exp->var[7], &dnisCalled[dlen]);
			strcpy(exp->var[8], "#");
			vxp->branch = 50;			// CkExt()
		} else {
			if (checkIfVip() < 0) {		// Caller is Not VIP
				if (autoAttendent == 'n') {
					exp->var[7][0] = trunkToOperator;
					exp->var[7][1] = 0;
					strcpy(exp->var[8], "#");
					vxp->branch = 50;	// CkExt()
				} else					// Put left to stringin	
					ginn_dnis(&dnisCalled[dlen]);
			}
		}
		ginn_answercall();				// Answer the call
		return(1);
	 }
  }
  fdbprintf("called %s is Not Allowed\r\n", dnisCalled);
  vxp->branch = 123;
  ginn_answercall();					// Answer the call
  return(1);
}

int getCallerGroup()
{
	char	buf[20][8];
	char	bufHead[16];
	char	buffer[120];
	int		count = 0, i, k;

	fpt = fopen(".\\conf\\PickupGroup.txt", "r");
	if (fpt == NULL) {
		strcpy(pickupList[0], "@");
		fdbprintf("No File. All same group\r\n");
		return(1);					// File Not Exists, All are same group
	}
	bufHead[0] = 0;
	while(1) {
		if (fgets(buffer, 120, fpt) == NULL) break;	// No more data
		bufHead[0] = 0;
		if ((k=sscanf(buffer, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
			bufHead, buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10],
			buf[11], buf[12], buf[13], buf[14], buf[15], buf[16], buf[17], buf[18], buf[19])) < 1)
			 continue;
		fdbprintf("%s count=%d k=%d\r\n", buffer, count, k);
		if (strncmp(&bufHead[1], "roup", 4) == 0) {
			if (count != 0) {
				for (i=0; i<count; i++) {
					if (strncmp(tlap->extensionNo, pickupList[i], strlen(pickupList[i])) == 0) {	// Meet Group Now
						pickupList[count][0] = 0;
						fclose(fpt);
						return(1);
					}
				}
				count = 0;
			}
			continue;
		}
		if (bufHead[0] == '@') {
			strcpy(pickupList[0], "@");
			fdbprintf("All same Group\r\n");
			fclose(fpt);
			return(1);						// Take as default
		}
		strcpy(buf[0], bufHead);
fdbprintf("buf0=%s\r\n", buf[0]);
		int len = 30 - count;
		if (k >= len) k = len;			// Avoid Overflow
		for (i=0; i<k; i++)				// Save currect group
			strcpy(pickupList[count++], buf[i]);
fdbprintf("count=%d\r\n", count);
	}
	if (count != 0) {
		if (dnisCalled[0] == '*') strcpy(buffer, &dnisCalled[1]);
		else strcpy(buffer, tlap->extensionNo);
		for (i=0; i<count; i++) {
fdbprintf("call=%s list=%s\r\n", buffer, pickupList[i]);
			
			if (strncmp(buffer, pickupList[i], strlen(pickupList[i])) == 0) {	// Meet Group Now
				pickupList[count][0] = 0;
				fclose(fpt);
				return(1);
			}
		}
	}
	pickupList[0][0] = 0;
	fdbprintf("Meet No Group, Need to enter Extension No.\r\n");
	fclose(fpt);
	return(-1);										// Take as Not match
}

int matchRingGroup()
{
	ex		ex0;
	vx		vx0;
	int		i, k, len;
	char	*p;
	int		extNow = 0;
//	char	tmp[120];

	for (i=0; i<chnum; i++) {
		ex0 = ginn_getexp(i);
		vx0 = ginn_getvxp(i);
		if (strcmp(vx0->pathName, vxp->pathName) != 0) continue;			// Not my Task
fdbprintf("etatlig[%d]=%x name=%s\r\n", i, vx0->etatlig, vx0->pathName);
		if (strncmp(ex0->var[13], "T&", 2) != 0) continue;
		if (vx0->etatlig != '4') continue;								// Not ringing 
		for (k=2; k<5; k++) {
			if (ex0->var[13][k] >= 0x30 && ex0->var[13][k] <= 0x39)	{	// bypass , A F, locate at number
				p = &ex0->var[13][k];
				break;
			}
		}
		if (k >= 5) continue;		// No digits(No called)
		fdbprintf("ex0->var[13]=(%s)\r\n", ex0->var[13]);
	
		if (checkIfExtension(tlcp, p, 1) > 0) {			// p is partially extension
			for (k=0; k<32; k++) {
				if (pickupList[k][0] == 0)				// at end, not found
					break;
				if (pickupList[k][0] == '@') {
					sprintf(exp->var[13],"T&P%s", p);	// Include /C if exists
					return(1);
				}
				len = strlen(pickupList[k]);
				if (strncmp(p, pickupList[k], len) == 0) {
					sprintf(exp->var[13],"T&P%s", p);	// Include /C if exists
					return(1);
				}
			}
			extNow = 1;
			continue;
		}
	}
	if (extNow == 1) return(-2);	// Has some ringing
	return(-1);						// Not meet
}

int checkRing(char *extToMatch)   //check and find ring line and 代接
{
	ex		ex0;
	vx		vx0;
	int		i, k, len;
	char	*p, tmp[120];


	for (i=0; i<chnum; i++) {
		ex0 = ginn_getexp(i);
		vx0 = ginn_getvxp(i);
		if (strcmp(vx0->pathName, vxp->pathName) != 0) continue;		// Not my Task
fdbprintf("etatlig[%d]=%x name=%s\r\n", i, vx0->etatlig, vx0->pathName);
		if (strncmp(ex0->var[13], "T&", 2) != 0) continue;
		if (vx0->etatlig != '4') continue;								// Not ringing 
		for (k=2; k<5; k++) {
			if (ex0->var[13][k] >= 0x30 && ex0->var[13][k] <= 0x39)	{	// bypass , A F, locate at number
				p = &ex0->var[13][k];
				break;
			}
		}
		if (k >= 5) continue;		// No digits(No called)
		fdbprintf("ex0->var[13]=(%s)\r\n", ex0->var[13]);

		if (checkIfExtension(tlcp, p, 1) > 0) {			// ext
			if (extToMatch == NULL) break;
			strncpy(tmp, extToMatch, 32);
			len = strlen(tmp);
			if (tmp[len-1] == '*') {					// wild card in the end.
				len -= 1;
				tmp[len] = 0;
			}
			if (len > 0) {
				if (strncmp(extToMatch, p, len) == 0) break;
			} else break;
		}
	} // for i=0; i<chnum i++
	if (i < chnum) {						// Meet ext. ringing
		sprintf(exp->var[13],"T&P%s", p);	// Include /C if exists
		return(2);
	}
	return(1);
}

int	CkRing()
{
	int		len, k;

	if (exp->var[7][0] == 'S') {		// No extension entered yet
		exp->var[7][0] = 0;
		if (getCallerGroup() < 0) {		// Not meet group
			vxp->branch = 190;			// Must enter extension No.
			return(1);
		}
		k = matchRingGroup();
		if (k == -2) {					// Has Some ring line
			vxp->branch = 190;			// Must enter extension No.
			return(1);
		} else
		if (k < 0) {
			vxp->branch = 100;
			return(1);
		}
		if (exp->var[6][0] == '4') 
			vxp->branch = 220;			// dial pickup from talking phone.
		return(1);						// dial pickup(from idle phone)
	}
	if (exp->var[8][0] == '*' || exp->var[8][0] == '#' || exp->var[8][0] == 0)
	{ // *:wild card, #:end 0:Timeout
		if (checkRing(exp->var[7]) == 2) {
			if (exp->var[6][0] == '4') 
				vxp->branch = 220;		// dial pickup from talking phone.
			return(1);					// dial pickup
		}
		vxp->branch = 100;				// hangup
		return(1);					
	}
	strcat(exp->var[7], exp->var[8]);
	len = strlen(exp->var[7]);
	if (len == maxExtLen) {
		if (checkRing(exp->var[7]) == 2) {
			if (exp->var[6][0] == '4') 
				vxp->branch = 220;		// dial pickup from talking phone.
			return(1);					// dial pickup
		}
		vxp->branch = 100;				// hangup
		return(1);					
	}
	vxp->branch = 192;								// Enter other digit
	return(1);

}

// IVR is waiting for caller2 to enter * to hangup.
int CkBack()
{
	if (exp->var[8][0] == '*') {
		if (vxp->pendingDial > 0)
		{ // Caller1 Pending dial, caller2 re-enter called No.
fdbprintf("pending hangup1\r\n");
			exp->var[7][0] = 0;
			exp->var[8][0] = 0;
			strcpy(exp->var[22], "1517");
			vxp->branch = 40;					// Re-enter phone No.
		}	
		return(1);
	}
	if (vxp->error == 0x4000) {					// Called HangUp, HungUp(Caller2 talk to Caller1)
		vxp->error = 0;
		if (vxp->pendingDial > 0)
		{ // Caller1 Pending dial, caller2 re-enter called No.
fdbprintf("pending hangup1\r\n");
			exp->var[7][0] = 0;
			exp->var[8][0] = 0;
			strcpy(exp->var[22], "1517");
			vxp->branch = 40;					// Re-enter phone No.
		}	
		return(1);
	}
	if (vxp->error == 0x2000) {					// Caller2 HangUp, Hangup(caller1 talk to called)
		vxp->error = 0;
		if (vxp->pendingDial > 0)
		{ // Caller1 Pending dial, Say "Wait a Moment" to called
fdbprintf("pending hangup2\r\n");
			vxp->branch = 190;					// and wait for pending release.
		}	
		return(1);
	}
	exp->cnt[8] += 1;
	if (exp->cnt[8] > 10) {
		if (vxp->pendingDial > 0) {				// Caller1 still ringing after caller2 talk to called timeover.
		}
		return(1);								// hangUp after 20 Sec. Max.
	}
	vxp->branch = 200;							// Wait for * again
	return(1);
}

char	shortFastBuf[MAXFASTDIAL][16];
char	longFastBuf[MAXFASTDIAL][32];
int		totalFastLoc;

int getAllFastDial()
{
	int		loc = 0;
	char	buffer[120];
	char	shortBuf[32], longBuf[32];
	static	int	modifyTime = 0;
//	long	lt;
	char	fileName[32];
	struct	_stat st;

//	time(&lt);
	strcpy(fileName, ".\\conf\\fastDialTable.txt");
	if (_stat(fileName , &st) < 0) return(-1);		// Not Exist
fdbprintf("%s time=%d-%d\r\n", fileName, st.st_mtime, modifyTime);
	if (st.st_mtime == modifyTime) return(1);		// No modified yet
	modifyTime = st.st_mtime;
	fpt = fopen(fileName, "r");
	if (fpt == NULL) return(-1);
	while(1) {
		if (fgets(buffer, 120, fpt) == NULL) break;	// No more data
		if (sscanf(buffer, "%s %s %s", shortBuf, longBuf) < 2)
			 continue;
		if ((shortBuf[0] != '*') && (shortBuf[0] < 0x30 || shortBuf[0] > 0x39)) continue;
		fdbprintf("telno=%s %s\r\n", shortBuf, longBuf);
		// Get item range
		if (strlen(shortBuf) >= 15) shortBuf[15] = 0;
		strcpy(shortFastBuf[loc], shortBuf);
		strcpy(longFastBuf[loc], longBuf);
		loc += 1;
		if (loc >= MAXFASTDIAL) break;
	}
	fclose(fpt);
	totalFastLoc = loc;
	return(1);
}

int	checkFastDial(char *telNo, char *telOut)
{
	int		loc;

	strcpy(telOut, telNo);
	if (getAllFastDial() < 0) return(-1);	// No meet
	for (loc=0; loc<totalFastLoc; loc++) {
		if (strcmp(telNo, shortFastBuf[loc]) == 0) {
			strcpy(telOut, longFastBuf[loc]);
			return(1);
		}
	}
	return(-1);
}

//**********************
// For star1 dedicated
int CkExtt()
{
	int		len, loc, loc1, k;
	char	tAnd[8];
	char	tmp[128];

	// Expect caller2 receive ringback from IVR, and then called.  fast mode is not allowed for ringing transfer.
//	strcpy(tAnd, "T&,");
	strcpy(tAnd, "T&T,");
	strcpy(exp->var[16], ".\\mess\\RingLong");
	while(1) {
		len=strlen(exp->var[8]);
		if (len == 0 || exp->var[8][0] == '#') {	// end of string
			if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
				if (dnisCalled[0] != '*' ||
					strncmp(&dnisCalled[1], exp->var[7], strlen(exp->var[7])) != 0) {
					if (voiceMail == 1)
						strcpy(exp->var[4], exp->var[7]);	// Save Extension No. for Voice Mail
					if (tlcp->coCall == 1) strcpy(tAnd, "T&A,");// co call is true
					break;
				} else goto ExtensionError;
			}
			if (strcmp(exp->var[7], "*") == 0) {		// HangUp, Goback to talk
				vxp->branch = 100;
				return(0);
			}
			if (exp->var[6][0] == '3') break;			// 3:Conference, allow non-extension
ExtensionError:
			strcpy(exp->var[21], "1504");				// extension No. Error
			strcpy(exp->var[22], "1517");
			exp->var[13][0] = 0;
			exp->var[7][0] = 0;
			vxp->branch = 105;
fdbprintf("Error ext=%s\r\n", exp->var[7]);
			return(0);
		}
//		if (exp->var[8][0] == '*') {					// HangUp, Goback to talk
//			vxp->branch = 100;
//			return(0);
//		}
		strcat(exp->var[7], exp->var[8]);
		
		if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
			if (dnisCalled[0] != '*' ||
				strncmp(&dnisCalled[1], exp->var[7], strlen(exp->var[7])) != 0) {
				if (voiceMail == 1)
					strcpy(exp->var[4], exp->var[7]);		// Save Extension No for Voice Mail
				if (tlcp->coCall == 1) strcpy(tAnd, "T&A,");
				break;
			} else goto ExtensionError;
		}		
		if (exp->var[7][0] == trunkToOperator) {	// transfer to OP
			strcpy(exp->var[7], attendentID);
			break;
		}
		vxp->branch = 45;							// Accept another digit
		return(0);
	}
	strcat(exp->var[17], "/NotPassDtmf=3");			// Assume Caller1 and called are not IVR
	k=checkIfBlack(exp->var[7], aniCaller);			// In BlackList to var[17]
	// 	"/C=%d%04d Caller Add IVR Record=./rec/%d%4d.wav", vxp->voie+1, cfrID, vxp->voie+1, cfrID);

	if (exp->var[6][0] == '3' && k < 0) { 			// Conference
		sprintf(tmp, "/C=%d%04d Caller Add NOIVR", vxp->voie+1, cfrID);
		strcat(exp->var[17], tmp);
	}
	if (loc >= 0) {	// Extension
		sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, exp->var[7], aniCaller, exp->var[17]);
		// No need to say "please wait a moment" when transfer to extension.
		vxp->branch = 60;
	} else
		sprintf(exp->var[13], "%s%s/var16%s", tAnd, exp->var[7], exp->var[17]);
	if (getForward(exp->var[7]) > 0) {
		if (fwd.uncondition[0] != '-') {							// uncondition transfer set
			checkIfBlack(fwd.uncondition, aniCaller);		 		// In BlackList
			if ((loc1=checkIfExtension(tldp, fwd.uncondition, 0)) >= 0) {	// extension exists
				if (tlcp->coCall == 1) strcpy(tAnd, "T&A,");
				sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, fwd.uncondition, aniCaller, exp->var[17]);
				// No need to say "please wait a moment" when transfer to Extension.
				vxp->branch = 60;
			} else { // Call forward to other phone
				if (callerTransparent == 'Y')						// if owner call
					sprintf(exp->var[13], "%s%s/%s//%s/var16%s", tAnd, fwd.uncondition, 
					      tlcp->telNo, tlcp->telNo, exp->var[17]);
				else												// Use IVR ID for accounting
					sprintf(exp->var[13], "%s%s/var16%s", tAnd, fwd.uncondition, exp->var[17]);
			}


			strcpy(exp->var[7], fwd.uncondition);
		}
	}
fdbprintf("4.var[13]=[%s] var[7]=[%s]\r\n", exp->var[13], exp->var[7]);
	exp->var[17][0] = 0;							// Clear Up for Not duplicated.
	exp->cnt[7] = 0;								// Set call forward once. avoid loop
	exp->cnt[8] = 0;								// Set wait hangup or enter *, avoid loop
	return(1);
}

//*****************************************************
// If digit from No wire, check here instead of ckExts
// It always is digit by digit, never stringIn in called No(as 168800).
int checkNoWireDigit()
{
	char	tAnd[8];
	int		len, len1;

fdbprintf("NoWire var[7]=[%s] var[8]=[%s]\r\n", exp->var[7], exp->var[8]);

	if (ltEnd != -1) {		// Set On uap_check_play
		setFuncPointToKer("_uap_check_play", NULL);
		ltEnd = -1;
	}
	while(1) {	// For break to String Out
		len=strlen(exp->var[8]);
		if (len == 0 || exp->var[8][0] == '#') {	// end of string
			len = strlen(exp->var[7]);
			if (len == 0) {
				vxp->branch = 100;
				return(0);
			}
			break;
		}
		strcat(exp->var[7], exp->var[8]);
		exp->var[8][0] = 0;				// clear to make No more data in if continue next lines
		len = strlen(exp->var[7]);

		if (handsetType[0] == 'A') {	// Call to AVS
			if (checkTaiwanTelno(exp->var[7], len) == 1) 
				break;
		} else {					// Call to PBX
			if (handsetType[0] != 'N') {					// Caller use handsetType to access PSTN
				if (strcmp(exp->var[7], handsetType) == 0) 	// Caller Is Want to dial to PBX
					break;

				len1 = strlen(handsetExtension);			// Called is Extension No of PBX
				if (len == len1 && strncmp(exp->var[7], handsetType, len) != 0)
					break;
			}
		}
		vxp->branch = 45;							// Accept another digit
		return(0);
	}
	if (handsetType[0] == 'A')	{					// To AVS directly.
		strcpy(tAnd, "T&,");
		strcpy(exp->var[16], ".\\mess\\RingBack");
		// exp->var[14] is called prefix to AVS
		sprintf(exp->var[13], "%s%s%s/%s/var16", tAnd, exp->var[14], exp->var[7], handsetID);
		return(1);
	} else {
		if (handsetType[0] == 'N') {
			strcpy(tAnd, "T&,");
			sprintf(exp->var[13], "%s%s%s/%s", tAnd, handsetGateway, exp->var[7], handsetID);
			return(1);
		} else {  // auto set '9' in called No.
			strcpy(tAnd, "T&,");
			sprintf(exp->var[13], "%s%s%s%s/%s", tAnd, handsetGateway, handsetType, 
				exp->var[7], handsetID);
			return(1);
		}
	}
}

int checkIfExtensionInfo(char *telNo)
{
	int	loc;

	loc = SelectRecordP("extensionInfo", "extensionNo", telNo, NULL);
	if (loc >= 0) {
		if (BeEOF(loc) >= 0) {		// Not exists
			CleanSelectResult(loc);
			return(1);
		}
		CleanSelectResult(loc);
	}
	return(-1);
}

//************************************************************************
// For FXS meet # or timeout or meet 9 or meet extension go to dial
int CkExtS()
{
	int		len, loc=-1, loc1;
	char	tAnd[8], tmp[16];
	int		k, k1, k2;

	if (inFrom == NOWIRE) {
		checkNoWireDigit();
		notPassDtmf |= 1;			// Not pass to caller
		return(1);
	}

fdbprintf("var[7]=[%s] var[8]=[%s]\r\n", exp->var[7], exp->var[8]);

	strcpy(tAnd, "T&,");
	while(1) {
		len=strlen(exp->var[8]);
		if (len == 0 || exp->var[8][0] == '#') {	// end of string
			len = strlen(exp->var[7]);
			if (exp->var[7][0] == '*') {			// *xxxxxxxxxx
				switch(len) {
				 case 1:							// * Only: Enquiry
					 greeting(greetingType);
//					 if (voiceMail == 1) {
//						strcpy(exp->var[5], "500");
//					 } else
//						strcpy(exp->var[5], "510");
					strcpy(exp->var[1], aniCaller);	// Use in *8
					vxp->branch = 400;
					return(1);
				 case 2:
					switch(exp->var[7][1]) {
					  case '2':							// *2: forward set
						  vxp->branch = 410;
						  return(1);
					  case '3':							// *3 telphone conference drcfr
						  if (telCfrPorter[0] != 'n') {
							  vxp->branch = 480;
							  strcpy(exp->var[1], aniCaller);
							  return(1);
						  }
						  vxp->branch = 100;
						  return(1);
					  case '4':							// *4: 代接, go to Enter telNo
						  exp->var[6][0] = 0;			// Not from talking line
						  if (getCallerGroup() < 0) {	// Not meet group
							  exp->var[7][0] = 0;		// Enter extension buffer
							  vxp->branch = 420;		// Must enter extension No.
							  return(1);
						  }
						  k = matchRingGroup();
						  if (k == -2) {				// Has Some ring line
							  exp->var[7][0] = 0;
						  	  vxp->branch = 420;		// Must enter extension No.
							  return(1);
						  } else
						  if (k < 0) {
							  vxp->branch = 100;
							  return(1);
						  }
						  vxp->branch = 422;			// *4 dialout
						  return(1);
					  case '5':							// *5: Record
						  vxp->branch = 430;
						  return(1);
					  case '6':
						  vxp->branch = 440;
						  return(1);
					  case '7':
						  vxp->branch = 460;
						  return(1);
					  case '8':							// *8:Voice Mail
						  if (voiceMail == 1) {
							vxp->branch = 450;
							strcpy(exp->var[1], aniCaller);
							return(1);
						  }
						  break;
					  default:
						  break;
					}
					break;
				 case 3:							// if >=3. may conflict with *25231172
					switch(exp->var[7][1]) {
					  case '2':						// *2: forward set
						  vxp->branch = 410;
						  ginn_dnis(&exp->var[7][2]);	// Set to stingin(etab_buff)
					  case '4':
						  exp->var[6][0] = 0;			// Not from talking line
						  strcpy(tmp, &exp->var[7][2]);
					      if (checkRing(tmp) == 2) {	// ring pending
						     vxp->branch = 422;			// Dial out(T&P...)
						     return(1);
						  }
					      vxp->branch = 100;			// hangUp
			  	  	      return(1);
					  case '5':						// *5: Record
						  vxp->branch = 430;
						  ginn_dnis(&exp->var[7][2]);
						  return(1);
					  case '6':						// duty time
						  vxp->branch = 440;
						  ginn_dnis(&exp->var[7][2]);
						  return(1);
					  case '7':						// No disturb
						  vxp->branch = 460;
						  ginn_dnis(&exp->var[7][2]);
						  return(1);
					  default:
						  break; 
					}
					break;
				  default:							
					if (exp->var[7][1] == '4' && len < 7) {	// *4xxxxx for 代接xxxxx.
						exp->var[6][0] = 0;			// Not from talking line
						strcpy(tmp, &exp->var[7][2]);
					   if (checkRing(tmp) == 2) {	// ring pending
						  vxp->branch = 422;		// Dial out(T&P...)
						  return(1);
					   }
					   vxp->branch = 100;		// hangUp
					   return(1);
					}
					break;
				}
			}
			// Mark off for if digit by digit, or 1689(a string in) has been processed.
//			if (exp->var[7][0] == extensionToTrunk) {	// transfer to Trunk Line
//				strcpy(exp->var[7], tlp->tkTel[0]);		// reach 1st one
//				checkIfBlack(exp->var[7], aniCaller);
//				if (pstnTalkTime > 0) {
//					sprintf(tmp, "/TalkTime=%d", pstnTalkTime);
//					strcat(exp->var[17], tmp);
//				}
//				sprintf(exp->var[13], "%s%s%s", tAnd, exp->var[7], exp->var[17]);
//				vxp->branch = 110;						// dial/hangup
//				return(1);
//			}
			if (voiceMail == 1) {						// if voicemail porter
				if (strcmp(exp->var[7], voiceMailPorter) == 0) {
					if (checkIfExtensionInfo(aniCaller) < 0) {	// you are not in extensionInfo
						vxp->branch = 567;
						return(1);
					}
//					vxp->branch = 452;
					vxp->branch = 450;
					strcpy(exp->var[1], aniCaller);
					return(1);
				}
			}
			checkFastDial(exp->var[7], exp->var[7]);	// 速撥
			len = strlen(exp->var[7]);
			if (len <= maxExtLen) {
				if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
					if (voiceMail == 1)
						strcpy(exp->var[4], exp->var[7]);	// Save Extension No for Voice Mail
					if (tlcp->coCall == 1) strcpy(tAnd, "T&A,");
					if (tlcp->attribute[3] != 'o')
						notPassDtmf |= 2;		// Not pass to called
					break;
				}
				if (len == 0) {
					vxp->branch = 100;
					return(0);
				}
				if (strcmp(exp->var[7], telCfrPorter) == 0) {	// Want to go conference system
					strcpy(exp->var[1], aniCaller);
					vxp->branch = 480;
					return(1);
				}
				strcpy(exp->var[21], "1504");
				strcpy(exp->var[22], "9999");
				vxp->branch = 105;						// extension No. error
				return(0);
			}
			if (checkInternet(exp->var[7], internetPrefix) != 'I') {	// Not Allow to Internet
				strcpy(exp->var[21], "1504");
				strcpy(exp->var[22], "9999");
				vxp->branch = 105;						// extension No. error
				return(0);
			}
			checkIfBlack(exp->var[7], aniCaller);		// In BlackList
fdbprintf("caller=%s %s\r\n", aniCaller, attendentID); 
			strcpy(tAnd, "T&T,");						// once need ringing transfer. 
//			if (strcmp(aniCaller, tlp->aaTel) == 0) {	// If caller is AA, it should be normal mode
			if (aniCallerAAType == 1) {
				if (dialCodecCmd == 0) {
					strcat(exp->var[17], "/Codec=g729");
					dialCodecCmd = 1;
				}
			}
			strcpy(exp->var[16], ".\\mess\\RingLong");				
			sprintf(exp->var[13], "%s%s%s/var16%s", tAnd, &internetPrefix[1], exp->var[7], exp->var[17]);
			vxp->branch = 110;							// dial/hangup to other phone
			return(1);
		} // if len=0 or #
		strcat(exp->var[7], exp->var[8]);
		if (exp->var[7][0] == extensionToTrunk) {		// transfer to Trunk Line
			strcpy(exp->var[7], trunkID);		// reach 1st one
			checkIfBlack(exp->var[7], aniCaller);	// In BlackList
			if (pstnTalkTime > 0) {
				sprintf(tmp, "/TalkTime=%d", pstnTalkTime);
				strcat(exp->var[17], tmp);
			}
//			if (strcmp(aniCaller, tlp->aaTel) == 0) {	// If caller is AA, it should be normal mode
			if (aniCallerAAType == 1) {
				strcpy(tAnd, "T&T,");					// once need ringing transfer. 
				if (dialCodecCmd == 0) {
					strcat(exp->var[17], "/Codec=g729");
					dialCodecCmd = 1;
				}
			}
			sprintf(exp->var[13], "%s%s%s", tAnd, exp->var[7], exp->var[17]);
fdbprintf("%s\r\n", exp->var[13]); 
			vxp->branch = 110;						// dial/hangup
			return(1);
		}
		if (strncmp(exp->var[7], "*4", 2) == 0) {	// *4: 代接
			exp->var[6][0] = 0;				// Not from talking line
			len = strlen(exp->var[7]);
			if (len == 2) {							// *4 only
				k1 = getCallerGroup();
				k2 = matchRingGroup();
				if (k2 == -1) {						// No one ringing
					vxp->branch = 100;
					return(1);
				}
				if (k1 >= 0 && k2 > 0) {
					vxp->branch = 422;
					return(1);
				}
			}
			if (exp->var[7][len-1] == '*') {		// Last One is Wild Card.
				if (checkRing(exp->var[7]) == 2) {	// ring pending
					vxp->branch = 422;
					return(1);
				}
			}
		}
		exp->var[8][0] = 0;								// clear to make No more data in if continue next lines
		if (strcmp(exp->var[7], telCfrPorter) == 0) {	// Want to go conference system
			strcpy(exp->var[1], aniCaller);
			vxp->branch = 480;
			return(1);
		}
		len = strlen(exp->var[7]);
		if (checkTaiwanTelno(exp->var[7], len) == 1)
			continue;

		if (voiceMail == 1) {
			if (strcmp(exp->var[7], voiceMailPorter) == 0) {	// Voice mail to enter manager
//				vxp->branch = 452;
				vxp->branch = 450;
				if (checkIfExtensionInfo(aniCaller) < 0) {
					vxp->branch = 567;
					return(1);
				}
				strcpy(exp->var[1], aniCaller);
				return(1);
			}
		}
		if ((loc=checkIfExtension(tlcp, exp->var[7], 1)) >= 0) {	// If xxx#, take as Not Extension
			if (voiceMail == 1)
				strcpy(exp->var[4], exp->var[7]);			// Save Extension No for Voice Mail
			if (tlcp->coCall == 1) strcpy(tAnd, "T&A,");
			if (tlcp->attribute[3] != 'o')
				notPassDtmf |= 2;							// Not pass to called
			break;
		}
		vxp->branch = 45;									// Accept another digit
		return(0);
	}
	// extension No.
fdbprintf("loc=%d infrom=%d notpass=%d\r\n", loc, inFrom, notPassDtmf);
	if (notPassDtmf != 0) {
		sprintf(tmp, "/NotPassDtmf=%d", notPassDtmf);
		strcat(exp->var[17], tmp);
	}
	if (loc >= 0) {
		checkIfBlack(exp->var[7], aniCaller);		// In BlackList
//		if (strcmp(aniCaller, tlp->aaTel) == 0) {	// If caller is AA, it should be normal mode
		if (aniCallerAAType == 1) {
			strcpy(tAnd, "T&T,");					// once need ringing transfer. 
			if (dialCodecCmd == 0) {
				strcat(exp->var[17], "/Codec=g729");
				dialCodecCmd = 1;
			}
		}
		strcpy(exp->var[16], ".\\mess\\RingLong");	
		// Add back aniCaller for 華隆來電顯示. 
		sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, exp->var[7], aniCaller, exp->var[17]);
//		sprintf(exp->var[13], "%s%s/%s%s", tAnd, exp->var[7], aniCaller, exp->var[17]);
		
		if (getForward(exp->var[7]) > 0) {
			if (fwd.uncondition[0] != '-') {							// uncondition transfer set
				checkIfBlack(fwd.uncondition, aniCaller);				// In BlackList
				if ((loc1=checkIfExtension(tldp, fwd.uncondition, 0)) >= 0) {	// extension exists
					if (tlcp->coCall == 1)	strcpy(tAnd, "T&A,");
					sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, fwd.uncondition, aniCaller, exp->var[17]);
				} else { // Call forward to other phone
					if (callerTransparent == 'Y')						// if owner call
						sprintf(exp->var[13], "%s%s/%s//%s/var16%s", tAnd, fwd.uncondition, 
						tlcp->telNo, tlcp->telNo, exp->var[17]);
					else												// Use IVR ID for accounting
						sprintf(exp->var[13], "%s%s/var16%s", tAnd, fwd.uncondition, exp->var[17]);
				}
				strcpy(exp->var[7], fwd.uncondition);
			}
		}
		if (fwd.noDisturb[0] == 'Y') {						// No disturb zzzzzz
			strcpy(exp->var[21], "1501");					// Busy
			strcpy(exp->var[22], "1526");					// dial Later
			vxp->branch = 105;
			return(1);
		}
	}
	fdbprintf("5.var[13]=[%s] var[7]=[%s]\r\n", exp->var[13], exp->var[7]);
	exp->var[17][0] = 0;
	exp->cnt[7] = 0;								// Set call forward once. avoid loop
	return(1);
}

//************************************************************************
// For FXO meet # or timeout or meet 9 or meet extension go to dial
int CkExt()
{
	int		len, loc;
	char	tmp[16];

	if (inFrom == FXS || inFrom == NOWIRE) {
		vxp->branch = 401;			// *1 and inFrom=FXS
		return(1);
	}
	while(1) {
		len=strlen(exp->var[8]);
		if (len == 0 || exp->var[8][0] == '#') {	// end of string
			if (strcmp(exp->var[7], "8") == 0) {
				if (exp->var[4][0] >= '0') {		// to Enter VoiceMail
					vxp->branch = 402;
					return(1);
				} else
				if (exp->var[4][0] == 0) {			// Not enter extension yet
					if (allowMail(publicMailBox) > 0) {
						strcpy(exp->var[4], publicMailBox);
						vxp->branch = 402;
						return(1);
					}
				}
			}
//fdbprintf("voicemail=%d %s %s\r\n", voiceMail, exp->var[7], voiceMailPorter);
			if (voiceMail == 1) {
				if (strcmp(exp->var[7], voiceMailPorter) == 0) 
				{	// To enter voiceMail management
					vxp->branch = 404;
					return(1);
				}
			}
			if (strcmp(exp->var[7], telCfrPorter) == 0) {	// Want to go conference system
				vxp->branch = 407;
				return(1);
			}
			if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
				if (voiceMail == 1) {
					strcpy(exp->var[4], exp->var[7]);		// Save Extension No for Voice Mail
					if (tlcp->vmHomeWork == '1') {			// Has honeWork set
						vxp->branch = 412;
						return(1);
					}
				}
				if (tlcp->attribute[3] != 'o')
					notPassDtmf |= 2;
				break;
			}
			if (inFrom == WEB) {
				strcpy(exp->var[21], "1524");		// extension No. Error
				exp->var[13][0] = 0;
				exp->var[7][0] = 0;
				vxp->branch = 105;
			} else {
				if (exp->var[7][0] == trunkToOperator) {// Direct transfer to OP
					strcpy(exp->var[7], attendentID);
					vxp->branch = 60;					// Without saying "Wait a Moment"
					break;
				}
				if (duty == ON_DUTY) {
					strcpy(exp->var[21], "1504");		// extension No. Error
					strcpy(exp->var[22], "1514");		// re enter or 9
				} else {
					strcpy(exp->var[21], "1504");		// extension No. Error
					strcpy(exp->var[22], "1534");		// re enter or call on duty
				}
//				if (dnisCalled[0] == '*')				// re enter
//					strcpy(exp->var[22], "1517");

				exp->var[13][0] = 0;
				exp->var[7][0] = 0;
				vxp->branch = 105;
			}
			return(0);
		}
//		if (dnisCalled[0] == '*' && exp->var[8][0] == '*') { // Goback to talk
//			vxp->branch = 100;
//			return(0);
//		}
		strcat(exp->var[7], exp->var[8]);
		
		if (voiceMail == 1) {
			if (strcmp(exp->var[7], voiceMailPorter) == 0) 
			{	// To enter voiceMail management
				vxp->branch = 404;
				return(1);
			}
		}
		if (strcmp(exp->var[7], telCfrPorter) == 0) {	// Want to go conference system
			vxp->branch = 407;
			return(1);
		}
		if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
			if (voiceMail == 1) {
				strcpy(exp->var[4], exp->var[7]);		// Save Extension No for Voice Mail
				if (tlcp->vmHomeWork == '1') {			// Has honeWork set
					vxp->branch = 412;
					return(1);
				}
			}
			if (tlcp->attribute[3] != 'o')				// output DTMF to extension
				notPassDtmf |= 2;						// Not pass DTMF to called
			break;
		}		
		if (exp->var[7][0] == trunkToOperator) {		// transfer to OP
			strcpy(exp->var[7], attendentID);
			break;
		}
		// Extension Length = 3, Not accept any digit any more
		len = strlen(exp->var[7]);
		if (len == maxExtLen) {
			if (duty == ON_DUTY) {
				strcpy(exp->var[21], "1504");		// extension No. Error
				strcpy(exp->var[22], "1514");		// re enter or 9
			} else {
				strcpy(exp->var[21], "1504");		// extension No. Error
				strcpy(exp->var[22], "1534");		// re enter or call on duty
			}
			exp->var[13][0] = 0;
			exp->var[7][0] = 0;
			vxp->branch = 105;
			return(1);
		}
		vxp->branch = 45;								// Accept another digit
		return(0); 
	}
	if (notPassDtmf != 0) {
		sprintf(tmp, "/NotPassDtmf=%d", notPassDtmf);
		strcat(exp->var[17], tmp);
	}
	checkIfBlack(exp->var[7], aniCaller);				// In BlackList
	strcpy(exp->var[16], ".\\mess\\RingLong");
	if (loc >= 0) {
		sprintf(exp->var[13], "T&A,%s/%s/var16%s", exp->var[7], aniCaller, exp->var[17]);
	} else {
		sprintf(exp->var[13], "T&A,%s/var16%s", exp->var[7], exp->var[17]);
	}
	if (getForward(exp->var[7]) > 0) {
		if (fwd.uncondition[0] != '-') {					// uncondition transfer set
			checkIfBlack(fwd.uncondition, aniCaller);		// In BlackList
			if (checkIfExtension(tldp, fwd.uncondition, 0) >= 0)		// extension exists
				sprintf(exp->var[13], "T&A,%s/var16%s", fwd.uncondition, exp->var[17]);
			else {// call forward to other phone
				 // 睿耀 need to display real caller when callforward to handset. 
				 // But, it is dangerous if some cheator use 睿耀's device and a different caller display.
//				sprintf(exp->var[13], "T&A,%s/%s/var16%s", fwd.uncondition, aniCaller, exp->var[17]);
				if (callerTransparent == 'Y')						// if owner call
					sprintf(exp->var[13], "T&T,%s/%s//%s/var16%s", fwd.uncondition, 
						tlcp->telNo, tlcp->telNo, exp->var[17]);
				else												// Use IVR ID for accounting
					sprintf(exp->var[13], "T&T,%s/var16%s", fwd.uncondition, exp->var[17]);
			}
			strcpy(exp->var[7], fwd.uncondition);
		}
	}
	fdbprintf("1.var[13]=[%s] var[7]=[%s]\r\n", exp->var[13], exp->var[7]);
	exp->var[17][0] = 0;
	exp->cnt[7] = 0;								// Set call forward once. avoid loop
	if (exp->var[10][0] != 0)						// VIP set here
		vxp->branch = 60;							// Not to say'wait a moment'
	return(1);
}

int SvErr()
{
	exp->cnt[6] = vxp->error;
fdbprintf("Uap Error=0x%x pending=%d\r\n", exp->cnt[6], vxp->pendingDial);
	if (exp->cnt[6] == 190) {		// When ring to called, caller2 press * to stop ring.
		if (vxp->pendingDial <= 0)
			vxp->branch = 100;		// Hangup to let caller1 return to talk to caller2.
		else 
			strcpy(exp->var[22], "1517");// change extension No.
			vxp->branch = 40;			// Enter extension No. Again
		return(1);
	}
	if (exp->cnt[6] == 257) {			// Ringing transfer, pending dial
fdbprintf("Goto3 *1\r\n");
	    vxp->branch = 470;				// goto * 1 process
	    strcpy(exp->var[22], "1518");	// Please dial extension No.
	    exp->var[13][0] = 0;
	    exp->var[7][0] = 0;
	    return(0);
	}
	return(1);
}

// Busy/Noans/Error/to announcement and end For FXS
int RtErrS()
{
	exp->cnt[6] = vxp->error;
	switch(vxp->error & 0xfff) {
	  case CR_BUSY:
		   strcpy(exp->var[21], "1501");
		   break;
	  case CR_NOANS:
		   strcpy(exp->var[21], "1502");
		   break;
//	  case 404:
//	  case 408:
//	  case 488:
//		   strcpy(exp->var[21], "1505");	// No response
//		   break;
	  case 257:
fdbprintf("Goto *1\r\n");
		   vxp->branch = 470;				// goto * 1 process
		   strcpy(exp->var[22], "1518");	// Please dial extension No.
		   exp->var[13][0] = 0;
		   exp->var[7][0] = 0;
		   return(0);
	  default:
		   if (backupToPstn == 1) {
			  strcpy(exp->var[16], ".\\mess\\mess0600");
			  checkIfBlack(trunkID, aniCaller);
			  sprintf(exp->var[13], "T&B%s/%s/var16%s", trunkID, aniCaller, exp->var[17]);	// reach 1st one
			  sprintf(exp->var[14], "TI%s", exp->var[7]);	// Second dial telNo
			  vxp->branch = 590;
		   } else strcpy(exp->var[21], "1505");				// 1503 not reach
		   break;
	}
	strcpy(exp->var[22], "1526");		
	exp->var[13][0] = 0;
	exp->var[7][0] = 0;
	return 0;
}

int setForward()
{
	FILE *fptr;
	char tel[80] = {0}, ufw[80] = {0}, bfw[80] = {0}, nfw[80] = {0}, ifw[80]={0};
	char buf[86] = {0}, phone[8] = {0}, stat[20]={0}, noDisturb[20]={0};
	int i, k = 0, empty=-1;
//	char name1[48], name2[48];

	if (fptr = fopen(".\\conf\\CallForward.txt", "r+b")) {
		fdbprintf("open CallForward.txt ok\r\n");
	} else {
		if (fptr = fopen(".\\conf\\CallForward.txt", "w+b")) {	// Create & trancate
			fdbprintf("Create CallForward.txt ok\r\n");
		} else {
			fdbprintf("open CallForward.txt fail\r\n");
			return(-1);
		}
	}
// Mark off for Not avoiding dup entry as 201/886225231172 and 201/886223881115.
// Because we need both 886225231172 and 886223881115 devices independently.
// If you want to change device ID, remember to modify the callforward.txt.

//	strcpy(name1, aniCallerRef);			// Meet name1 or name2 will do,
//	strcpy(name2, "default");				// to avoid dup entry as 201/886225231172
//	char *p=strchr(name1, '/');				// and 201/886223881115 when same extension for devices
//	if (p) {
//		*p = 0;
//		p += 1;
//		strcpy(name2, p);
//	}
	for (i = 0; i<7000; i++) {
		tel[0] = 0;
		if (fgets(buf, sizeof(buf), fptr) == NULL)
			break;
		if (sscanf(buf, "%s %s %s %s %s %s", tel, ufw, bfw, nfw, ifw, stat, noDisturb) < 3) {
			i -= 1;
			continue; 
		}
		// 分機號碼, 無條件轉移, 忙線轉移, 無應答轉移

		fdbprintf("i=[%d],buf=[%s]\r\n", i, buf);
		if (strcmp(tel, aniCallerRef) == 0) break;
//		char *p=strchr(tel, '/');
//		if (p) {
//			*p = 0;
//			p += 1;
//			if (strcmp(name1, p) == 0) break;
//			if (strcpy(name2, p) == 0) break;
//		}
//		if (strcmp(name1, tel) == 0) break;
//		if (strcmp(name2, tel) == 0) break;
	}
	if (tel[0] == 0) {						// No entry meet
		if (exp->var[10][0] != '1') {
			fclose(fptr);
			return(-1);						// for reset, close, open
		}
		strcpy(tel, aniCallerRef);			// initialize
		strcpy(ufw, "-");
		strcpy(bfw, "-");
		strcpy(nfw, "-");
		strcpy(ifw, "-");
		strcpy(stat, "Open");
		strcpy(noDisturb, "-");
	} else {						
		if (ufw[0] == '-' && bfw[0] == '-' &&
			nfw[0] == '-' && ifw[0] == '-')	// Empty callforward setting
			strcpy(stat, "Open");
	}
	fdbprintf("i=[%d], caller=[%s], buf=[%s]\r\n", i, aniCallerRef, buf);

	if (i == 0) {
		memset(buf, ' ', 76);
		buf[76] = 0x0d;
		buf[77] = 0x0a;
		buf[78] = 0x0d;
		buf[79] = 0x0a;
		strcpy(buf, "Tel\tuncondition\tBusy\tNoAns\tNetFail\tStatus\tNoDisturb");
		k = fwrite(buf, 80, 1, fptr);
		i = 1;
	}

	k = fseek(fptr, 80 * i, SEEK_SET);
	if (k < 0) {
		if (empty >= 0) 
			k = fseek(fptr, 80 * empty, SEEK_SET);
		if (k < 0) {
			fdbprintf("k=[%d],fseek fail\r\n", k);
			k = fseek(fptr, 0, SEEK_END);
		}
	}
	// exp->var[10] = 1:Set 2:reset 3:close 4:open	
    // exp->var[11] = 1.無條件 2.忙線 3.無應答 4:網路不通 5:Set/Reset All 6:set/Reset NoDisturb
    // exp->var[12] = 欲轉移之分機號碼 or '-'
    // 0x09 = Tab鍵   0x0D 0x0A =>Enter鍵

	memset(buf, ' ', 80);
	fdbprintf("var[10]=[%s] var[11]=[%s] var[12]=[%s]\r\n", 
		exp->var[10], exp->var[11], exp->var[12]);
	if (exp->var[10][0] == '3') {		// close
		sprintf(buf, "%s\t%s\t%s\t%s\t%s\tClose\t%s", aniCallerRef, ufw, bfw, nfw, ifw, noDisturb);
		strcpy(exp->var[9], "518");
	} else {
		if (exp->var[10][0] == '4') {	// Open
			sprintf(buf, "%s\t%s\t%s\t%s\t%s\tOpen\t%s", aniCallerRef, ufw, bfw, nfw, ifw, noDisturb);
			strcpy(exp->var[9], "519");
		} else {						// Set and Reset
//			if (exp->var[10][0] == '1') {
//				if (stat[0] == 'D') strcpy(stat, "Open");
//			}
			switch(exp->var[11][0]) {
				case '1':										// 無條件
					sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t%s", aniCallerRef, 
						exp->var[12], bfw, nfw, ifw, stat, noDisturb);
					break;
				case '2':										// 忙線
					sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t%s", aniCallerRef,
						ufw, exp->var[12], nfw, ifw, stat, noDisturb);
					break;
				case '3':										// 無應答 
					sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t%s", aniCallerRef,
						ufw, bfw, exp->var[12], ifw, stat, noDisturb);
					break;
				case '4':
					sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t%s", aniCallerRef,
						ufw, bfw, nfw, exp->var[12], stat, noDisturb);
					break;
				case '5':										// set(reset) all
					if (exp->var[10][0] == '2') 				// 2:reset
						sprintf(buf, "%s\t-\t-\t-\t-\t%s\t%s", aniCallerRef, stat, noDisturb);
					else
						// Modify to exclude uncondition for set all.
//						sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t", aniCallerRef,
//						exp->var[12], exp->var[12], exp->var[12], exp->var[12], stat, noDisturb);
						sprintf(buf, "%s\t-\t%s\t%s\t%s\t%s\t%s", aniCallerRef,
						exp->var[12], exp->var[12], exp->var[12], stat, noDisturb);
					break;
				case '6':										// set(reset) NoDisturb
					if (exp->var[10][0] == '2') 				// 2:reset
						sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\t-", aniCallerRef,
							ufw, bfw, nfw, ifw, stat);
					else
						sprintf(buf, "%s\t%s\t%s\t%s\t%s\t%s\tYes", aniCallerRef,
							ufw, bfw, nfw, ifw, stat);
					break;
			}
		}
	}
	buf[78] = 0x0d;
	buf[79] = 0x0a;
	fdbprintf("i=[%d],buf=[%s]\r\n", i, buf);
  	k = fwrite(buf, 80, 1, fptr);
	fflush(fptr);
	fclose(fptr);
	fdbprintf("k=[%d],written\r\n", k); 
	return(1);
}

//**************************************************************************************
int RstFwd()
{
	strcpy(exp->var[12], "-");						// tel. No.
	if (setForward() < 0) vxp->branch = 100;
	return(1);
}

//**************************************************************************************
int SamFwd()			// if same telno on continuous enter
{
	if (strcmp(exp->var[8], exp->var[12]) != 0) {		// Transfer TelNo. Not Same
		vxp->branch = 85;
		return(1);
	}
	if (setForward() < 0) vxp->branch = 100;
	return(1);
}

int	OpFwd()		// Open or Close Forward
{
	int	noEntry = 0;
	if (exp->var[10][0] == '5') {			// Enquiry
		if (getForward(aniCaller) == -1)	// -2 is closed with stat=close 
			noEntry = 1;
		synForward(noEntry);
		vxp->branch = 320;					// play synthesis
		return(1);
	}
	if (setForward() < 0) vxp->branch = 100;
	return(1);
}

//**************************************************************************************
int CanFwd()		// can do call forward setting
{
//	int		i;

	if (checkIfExtension(tlcp, aniCaller, 0) > 0) {
		exp->cnt[5] = 0;	// To check over times
		return(1);			// meet extension No.
	}
    vxp->branch = 48;			// Not extension No.
	return(1);
/*
	for (i=0; i<tlp->extLoc; i++) 
		if (strcmp(aniCaller, tlp->extTel[i]) == 0 ||
			strcmp(aniCaller, tlp->extTelRef[i]) == 0) {
			exp->cnt[5] = 0;	// To check over times
			return(1);			// meet extension No.
		}
    vxp->branch = 48;			// Not extension No.
	return(1);
*/
}

// send short message
// Initially, ShortMessage.dat is empty
// uap write append to the end.
// server get record from begining, and update status to 0
// To maintain, just open(O_TRUNC);
int	sendSM(char *telNo, char *message, char *caller, char *company, char *branch)
{
	static		int	fid = -1;
	char		buf[520];
	tm			*tm;
//	long		lt;
	char		*p;

	typedef struct {
		int		status;			// 0:Get by hotSMG to send 1:Ask to send 3:Send returned.
		int		errorCode;
		char	telNo[32];
		char	company[20];
		char	branch[20];
		char	inTime[24];		// yyyy/mm/dd hh:mm:ss
		char	outTime[24];
		char	filler[100];	// Make total 512 bytes
		char	message[284];	// 70 chinese = 280char for unicode
	} SM, *Sm;

	Sm			sm;	

	if (telNo[0] == 0) {
		fdbprintf("sendSM No telNo\r\n");
		return(-1);
	}
	if (message[0] == 0) {
		fdbprintf("sendSM No short message\r\n");
		return(-1);
	}
	if (fid < 0) {
		if ((fid = _open(".\\ShortMessage.dat", O_RDWR|O_BINARY)) < 0) {
			fdbprintf("Open ShortMessage.dat error %d\r\n", fid);
			return(-1);
		}
	}
fdbprintf("Open ShortMessage.dat OK\r\n");
	sm = (Sm)buf;
	strcpy(sm->telNo, telNo);
	if (company[0] == '-') sm->company[0] = 0;
	else strcpy(sm->company, company);
	if (branch[0] == '-') sm->branch[0] = 0;
	else strcpy(sm->branch, branch);
	message[131] = 0;
	p = strchr(message, '%');
	if (p) {
		*p = 0;
		p += 1;
		sprintf(sm->message, "%s%s %s %s %s", message, caller, sm->company, sm->branch, p);
	} else {
		strcpy(sm->message, message);
	}
//	time(&lt);
	tm=localtime(&nowTime);
	sprintf(sm->inTime, "%4d/%02d/%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);
	sm->outTime[0] = 0;
	sm->status = 1;
	sm->errorCode = 0;
fdbprintf("Write to the end\r\n");
	_lseek(fid, 0, SEEK_END);
	_write(fid, buf, sizeof(SM));
	_commit(fid);
	return(1);
}


// if pending VIP call, send short MSG
int	SndSM()
{
	if (vipCall == 0) return(1);		// No send message pending
	sendSM(exp->var[11], exp->var[12], aniCaller, exp->var[13], exp->var[14]);	
	return(1);
}

//**************************************************************************************
int CkFwd()		// check forward
{
	char phone[32], tAnd[8];
	int	 loc, loc1;

	strcpy(tAnd, "T&,");
	phone[0] = 0;
	if (exp->cnt[7] < 2) {											// call forward limit to 2 times
		if (vipCall > 0) {
			vipCall = 0;											// Send OK
			if (exp->var[10][0] >= 0x30) {							// Not \0 and not '-'(0x2d) for second tel
				strcpy(exp->var[16], ".\\mess\\RingLong");
				exp->cnt[7] += 1;									// times of call forward
				if ((loc1=checkIfExtension(tldp, exp->var[10], 0)) >= 0) {	// extension exists
					if (tldp->coCall == 1) strcpy(tAnd, "T&T,");
					strcpy(phone, exp->var[10]);
					sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, phone, aniCaller, exp->var[17]);
					vxp->branch = 60;								// dial extension No.
				} else {   // dial transfer to other phone
					strcpy(tAnd, "T&T,");
					if (exp->var[10][0] == extensionToTrunk)
						sprintf(phone, "%s%s", trunkID, &exp->var[10][1]);
					else strcpy(phone, exp->var[10]);
					sprintf(exp->var[13], "%s%s/var16%s", tAnd, phone, exp->var[17]);
				}
				strcpy(exp->var[7], phone);
fdbprintf("2.var[13]=[%s] var[7]=[%s] loc1=%d short=%s %s\r\n", exp->var[13], exp->var[7], loc1,
 exp->var[11], exp->var[12]);
				// Send Short Message
				if (exp->var[11][0] >= 0x30 && exp->var[12][0] != 0) // Not \0 and not '-'(0x2d) for SM
					sendSM(exp->var[11], exp->var[12], aniCaller, exp->var[13], exp->var[14]);
				return(1);
			}
			if (exp->var[11][0] >= 0x30 && exp->var[12][0] != 0) 	// Not \0 and not '-'(0x2d) for SM
				sendSM(exp->var[11], exp->var[12], aniCaller, exp->var[13], exp->var[14]);
		}
		if (getForward(exp->var[7]) > 0) {			// call forward exists
			switch(exp->cnt[6] & 0xfff) {			// Initial all fwd phone the same
			  case CR_BUSY: 
				if (fwd.busy[0] != '-')
					strcpy(phone, fwd.busy);		// OpenFile SetCommState
				break;
			  case CR_NOANS: 
				if (fwd.noans[0] != '-')
					strcpy(phone, fwd.noans);
				break;
			  default:
				if (fwd.netfail[0] != '-')
					strcpy(phone, fwd.netfail);
				break;
			}
			if (phone[0] != 0) {
				strcpy(exp->var[16], ".\\mess\\RingLong");
				exp->cnt[7] += 1;						// times of call forward
				if ((loc1=checkIfExtension(tldp, phone, 0)) >= 0) {		// extension exists
					if (tldp->coCall == 1) strcpy(tAnd, "T&T,");
					checkIfBlack(phone, aniCaller);				// In BlackList
					sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, phone, aniCaller, exp->var[17]);
					strcpy(exp->var[7], phone);
fdbprintf("2.var[13]=[%s] var[7]=[%s]\r\n", exp->var[13], exp->var[7]);
					vxp->branch = 60;					// dial extension No.
					return(1);
				} else {   // dial transfer to other phone
					if ((loc=checkIfExtension(tlcp, exp->var[7], 0)) >= 0) {
						if (tlcp->coCall == 1) strcpy(tAnd, "T&T,");
						checkIfBlack(phone, tlcp->telNo);		// In BlackList
						sprintf(exp->var[13], "%s%s/%s/var16%s", tAnd, phone, tlcp->telNo, exp->var[17]);
						strcpy(exp->var[7], phone);
fdbprintf("3.var[13]=[%s] var[7]=[%s]\r\n", exp->var[13], exp->var[7]);
						return(1);
					}
				}
			}
		}
	}
fdbprintf("inFrom2=%d\r\n", inFrom);
	switch(exp->cnt[6] & 0xfff) {
	  case CR_BUSY:
		   strcpy(exp->var[21], "1501");
		   break;
	  case CR_NOANS:
		   strcpy(exp->var[21], "1502");
		   break;
	  case 257:								// ringing transfer, dial pending
fdbprintf("Goto2 *1\r\n");
		   vxp->branch = 470;				// goto * 1 process
		   strcpy(exp->var[22], "1518");	// Please dial extension No.
		   exp->var[13][0] = 0;
		   exp->var[7][0] = 0;
		   return(0);
//	  case 404:
//	  case 408:
//	  case 488:
//		   strcpy(exp->var[21], "1505");	// No response
//		   break;
	  default:
		   strcpy(exp->var[21], "1505");	// 1503 Not reach 1.27
		   break;
	}
	if (inFrom == WEB) {
		vxp->branch = 95; 								// will retry
	} else {
		if (inFrom == FXS || inFrom == NOWIRE) {
			strcpy(exp->var[22], "1526");				// Dial Later		
		} else {
			if (allowMail(exp->var[4]) <= 0) exp->var[4][0] = 1;	// Not allow 

			if (duty == ON_DUTY) {
				if (exp->var[4][0] < 2)					// 1:Not Allow, 0:No Extension No. yet
					strcpy(exp->var[22], "1513");		// change Ext. No. or 9
				else strcpy(exp->var[22], "1521");		// change Ext. voice mail or 9
			} else {
				if (exp->var[4][0] < 2)
				   strcpy(exp->var[22], "1533");		// change Ext. No. or call later
				else strcpy(exp->var[22], "1522");		// change Ext. voice mail or call later
			}
//			if (dnisCalled[0] == '*') 
//				strcpy(exp->var[22], "1516");			// change Ext. No. 
		}
		exp->var[13][0] = 0;
		exp->var[7][0] = 0;
		vxp->branch = 105;								// Noans/busy ask to re-enter or stop(fxs)
	}
	return 0;
}

int CkFwdS()
{
	CkFwd();
	return(1);
}

// Check forward for transfer
int CkFwdt()
{
	CkFwd();
	if (exp->cnt[6] & 0x2000) {			// Caller2 HangUp
		if (vxp->pendingDial == -1) 	// Caller2 hangup, caller1 pickup, called noanswer, while ringing transfer
			vxp->branch = 270;
		else
		if (inFrom == FXS || inFrom == NOWIRE)
			vxp->branch = 260;			// goback to fxsp to say busy...
		else vxp->branch = 250;			// goback to fxop to say busy...
		return(1);
	} 
//	if (inFrom == FXS)					// Markoff for caller1 from Tk, and caller2 key in wrong No.
	strcpy(exp->var[22], "1516");		// change extension No.
	return(1);
}

//****************************************************************************
int CkPwd()
{
	FILE *fptr;
	char pas[32] = {0}, temp[32] = {0};

	if (fptr = fopen(".\\password.txt", "r")) {
		fdbprintf("open password.txt ok\r\n");
		fgets(temp, sizeof(temp), fptr);
		sscanf(temp, "%s", pas);
		fdbprintf("pas = [%s]\r\n", pas);
		fclose(fptr);
	}
	if (strcmp(exp->var[8], pas) != 0 &&
		strcmp(exp->var[8], "1111111") != 0) {	// Password Error
		vxp->branch -= 6;						// jump to error announce
		return(1);
	}
	exp->cnt[5] = 0;
	starting = 1;								// Set to indicate start transaction
	return(1);
}

//****************************************************************************
int changePassword()
{
	FILE *fptr;
	char pas[32] = {0}, spe[32] = {0};
	int  i, k;

	if (fptr = fopen(".\\password.txt", "r+b")) {
		fdbprintf("open password.txt ok\r\n");
		k = 32 - strlen(exp->var[12]);
		memset(spe, 0x20, k);
		fdbprintf("k = [%d], spe = [%s]\r\n", k, spe);
		sprintf(pas, "%s%s", exp->var[12], spe);
		i = fwrite(pas, strlen(pas), 1, fptr);
		if (i<0) fdbprintf("Write Password Error\r\n");
		fdbprintf("pas = [%s]\r\n", pas);
		fclose(fptr);
	}
	return 0;
}

//****************************************************************************
int CkRHld()		// reset hold
{
	if (exp->var[8][0] == '*') vxp->branch = 100;
	return(1);
}

//****************************************************************************
int	SvMess()
{
	char cmd[80];

	sprintf(cmd, "copy  .\\mess\\mess1599 .\\mess\\mess%s\r\n", exp->var[9]);
	system(cmd);
	return(1);
}

//****************************************************************************
int	CkMess()
{
	int		k;
	
	k = atoi(exp->var[9]);
	if (strcmp(exp->var[8], "1111111") != 0)
		if (k >= 1590 || k < 1500) vxp->branch = 84;	// For Security
	strcpy(exp->var[10], "1599");						// record here temperarily
	return(1);
}

//****************************************************************************
int CkNPwd()
{
	if (strcmp(exp->var[8], exp->var[12]) != 0) {	// NEW Password Not same
		vxp->branch = 334;
		return(1);
	}
	changePassword();
	exp->cnt[5] = 0;
	return(1);
}

//****************************************************************************
int StDstb()		// Set/Clear/Quer No Disturb
{
	int		noSet = 0;

	switch(exp->var[10][0]) {
	  case '1':								// Set
		  strcpy(exp->var[11], "6");		// update NoDisturb field
		  if (setForward() < 0) vxp->branch = 100;
		  break;
	  case '2':								// Clear
		  strcpy(exp->var[11], "6");		// update NoDisturb field
		  if (setForward() < 0) vxp->branch = 100;
		  vxp->branch = 150;
		  break;
	  case '3':								// Query
		  if (getForward(aniCaller) == -1)	// -2 is closed with stat=close 
			  noSet = 1;
		  if (fwd.noDisturb[0] != 'Y') noSet = 1;
		  if (noSet == 1) vxp->branch = 220;
		  else vxp->branch = 200;			// No disturb is set.
		  break;
	  default:
		  vxp->branch = 100;
		  return(1);
	}
	return(1);
}

//****************************************************************************
int plyPas()
{
  int i = 1;

  exp->v[i++] = 106;
  i = ifx(exp->var[13], i, 1);
  exp->v[i] = -1;
  return 0; 
}

int clearYmtBuf()
{
	memset(&ymt, 0, sizeof(ymtd));
	ymt.menNo = ymtFreeOffset / sizeof(ymtd) + 8010;
	time(&ymt.endDate);
	return(1);
}

int checkYmtExpire()
{
	tm		*tm;
	long	lt;

	tm=localtime(&ymt.endDate);
	tm->tm_mon += 1;					// exoires 1 month later
	lt=mktime(tm);
//	time(&now);
	if (lt < nowTime) return(1);		// expires
	return(0);
}

int updateYmt(int offset)
{
	int		fid;

	if ((fid = open(".\\ymt.dat", O_RDWR|O_BINARY, 0644)) < 0) {
		fdbprintf("Open ymt.dat error %d\r\n", fid);
		return(-1);
	}
	lseek(fid, offset, SEEK_SET);
	write(fid, &ymt, sizeof(ymtd));
	close(fid);
	return(1);
}

// Get Ymt, if none, Get empty Ymt
int getYmtByOwner()
{
	int		fid;
	int		offset, invalidOffset;

	ymtFreeOffset = -1;
	ymtOffset = -1;
	invalidOffset = -1;
	if ((fid = open(".\\ymt.dat", O_RDWR|O_BINARY, 0644)) < 0) {
		fdbprintf("Open ymt.dat error %d\r\n", fid);
		return(-1);
	}
	offset = 0;
	while(1) {
		lseek(fid, offset, SEEK_SET);
		if (read(fid, &ymt, sizeof(ymtd)) <= 0) break;
fdbprintf("ymt handset=%s\r\n", ymt.handset);	
		if (strcmp(ymt.handset, aniCaller) == 0) {
			close(fid);
			if (!ymt.valid || ymt.startDate == 0)
			{	// deleted or temperary occupy
				ymtFreeOffset = offset;
				return(-4);
			}
			ymtOffset = offset;
			return(1);
		}
		if (ymtFreeOffset < 0) {				// Get 1st idle offset
			if (ymt.startDate == 0) {
				ymtFreeOffset = offset;
			} else {							// Get Last invalid offset
				if (ymt.valid && !checkYmtExpire())
					invalidOffset = offset;
			}
		}
		offset += sizeof(ymtd);
	}
	if (ymtFreeOffset < 0)
		if (invalidOffset >= 0) ymtFreeOffset = invalidOffset;

	if (ymtFreeOffset >= 0) {
		clearYmtBuf();
		lseek(fid, ymtFreeOffset, SEEK_SET);
		write(fid, &ymt, sizeof(ymtd));
		close(fid);
		return(-3);		// No meet Ymt, but has free Ymt
	}
	close(fid);
	return(-2);			// No meet Ymt, no free Ymt
}

//****************************************************************************
int  YmtIni()
{
	int		result;		// 1:OK -1:No Entry
	int		loc = 1;
	char	buf[8];

	result = getYmtByOwner();
	switch(exp->var[11][0]) {
	  case '1':	// Apply
		if (result > 0) {					// You already have
			exp->v[loc++] = 802;			// You have Ymt
			exp->v[loc++] = 803;			// Your menNo is ...
			sprintf(buf, "%d", ymt.menNo);
			loc = ifx(buf, loc, 1);   
			exp->v[loc++] = 804;			// TransTo telNo is ...
			loc = ifx(ymt.telNo, loc, 1);   
			exp->v[loc] = -1;
			vxp->branch = 212;
			return(1);
		}
		if (result == -2) {
			vxp->branch = 214;				// No menNo left
			return(1);
		}
		if (result == -1) {					// Not open yet
			vxp->branch = 80;
			return(1);
		}
		if (checkFromHandset() < 0) {		// Not allowable caller
			vxp->branch = 42;
			return(1);
		}
		vxp->branch = 220;
		break;
	  case '2':	// Change
		if (result < 0) {				// You have None
			vxp->branch = 216;
			return(1);
		}
		exp->v[loc++] = 804;			//  TransTo telNo is ...
		loc = ifx(ymt.telNo, loc, 1);   
		exp->v[loc] = -1;
		vxp->branch = 400;
		break;
	  case '3':	// Delete
		if (result < 0) {				// You have None
			vxp->branch = 216;
			return(1);
		}
		vxp->branch = 560;
		break;
	  case '4':	// Enquiry
	  default:
		switch(exp->var[12][0]) {
		  case '1':						// setting Value
			if (result < 0) {			// You have None
				vxp->branch = 216;
				return(1);
			}
			exp->v[loc++] = 803;		// Your menNo is ...
			sprintf(buf, "%d", ymt.menNo);
			loc = ifx(buf, loc, 1);   
			exp->v[loc++] = 804;		// TransTo telNo is ...
			loc = ifx(ymt.telNo, loc, 1);   
			exp->v[loc] = -1;
			vxp->branch = 630;
			break;
		  case '2':						// Not Received Calls
			if (result < 0) {			// You have None
				vxp->branch = 216;
				return(1);
			}
			vxp->branch = 650;
			exp->cnt[1] = -1;			// initiate count of NC call
			break;
		  case '3':
			vxp->branch = 720;
			return(1);
		  case '4':
			vxp->branch = 760;
			return(1);
		  default:
			vxp->branch = 100;
		}
		break;
	}
	return(0);
}

//****************************************************************************
int	YmtEq()							// equal
{
	int		offset, loc = 1;
	char	buf[12];

	if (strcmp(exp->var[16], exp->var[17]) != 0) {	// Not equal
		if (exp->var[11][0] == '1')			// Apply
			vxp->branch = 242;
		else							// Change
			vxp->branch = 442;
		return(1);
	}
	// update menNo
	if (exp->var[11][0] == '1')	{		// Apply
		offset = ymtFreeOffset;
	    exp->v[loc++] = 839;			// Ymt Set OK. menNo is ...
		sprintf(buf, "%d", ymt.menNo);
		loc = ifx(buf, loc, 1);
		exp->v[loc++] = 804;			// TransTo telNo is ...
		loc = ifx(exp->var[16], loc, 1);   
		exp->v[loc++] = 840;			// Remenber to Call transfer here
		exp->v[loc] = -1;
	} else {							// Change
		offset = ymtOffset;
		exp->v[loc++] = 804;			//  TransTo telNo is ...
		loc = ifx(exp->var[16], loc, 1);   
		exp->v[loc] = -1;
	}
fdbprintf("v11=%s offset=%d menNo=%d telNo=%s\r\n", exp->var[11], offset, ymt.menNo, exp->var[16]);
	time(&ymt.startDate);
	ymt.endDate = ymt.startDate;
	strcpy(ymt.handset, aniCaller);
	strcpy(ymt.telNo, exp->var[16]);
	ymt.valid = true;

	updateYmt(offset);
	return(1);
}

//****************************************************************************
int	YmtDel()						// Delete
{
	ymt.valid = false;
	updateYmt(ymtOffset);
	return(1);
}

//****************************************************************************
int	YmtNR()							// Not Received Call
{
	int		i, loc=1, count=0, hh, mm, dayZone;
	char	buf[8], curLoc;

	curLoc = exp->cnt[1];
	if (curLoc == -1) {
		for (i=0; i<10; i++)
			if (ymt.nrc[i].date == 0) break;

		if (i == 0) {
			vxp->branch = 652;
			return(1);
		}
		exp->v[loc++] = 833;			// Your recent
		sprintf(buf, "%d", i);
		loc = ifx(buf, loc, 1);	
		exp->v[loc++] = 834;			// NR calls are as follow:
		exp->cnt[1] = 0;
		curLoc = 0;
	}
	if (ymt.nrc[curLoc].date == 0) {	// End of NR call
		vxp->branch = 654;
		return(1);
	}
	mm = ymt.nrc[curLoc].date/100;		// Month
	exp->v[loc++] = mm + 610;
	mm = ymt.nrc[curLoc].date % 100;	// day
	exp->v[loc++] = mm + 630;
	hh = ymt.nrc[curLoc].time/100;		// hour
	mm = ymt.nrc[curLoc].time % 100;	// Minute
	if (hh < 6) dayZone = 3;					// night
	else if (hh < 12) dayZone = 0;				// morning
	else if (hh == 12 && mm == 00) dayZone = 1;	// noon
	else if(hh < 19) dayZone = 2;				// afternoon
	else dayZone = 3;							// night
	exp->v[loc++] = 695 + dayZone;
	if (hh > 12) hh -= 12;
	exp->v[loc++] = 680 + hh;					// hh
	if (mm > 0)
	   exp->v[loc++] = 700 + mm;				// mm
	exp->v[loc++] = 835;				// Has 1 NR call, No is..
	loc = ifx(ymt.nrc[curLoc].telNo, loc, 1);
	exp->v[loc] = -1;

	exp->cnt[1] += 1;					// Next NR Call
	return(1);
}

//****************************************************************************
int	YmtNRD()						// Not Received call Delete
{
	int	curLoc;

	exp->cnt[1] -= 1;			// Current Location Now
	curLoc = exp->cnt[1];
	for (int i=curLoc; i<9; i++) 
		memcpy(&ymt.nrc[i], &ymt.nrc[i+1], sizeof(NRCD));
	ymt.nrc[i].date = 0;

	updateYmt(ymtOffset);
	return(1);
}

//****************************************************************************
int RtErrY()
{
	int		fid, i;
//	long	lt;
	tm		*tm;

	RtErrS();

	if ((fid = open(".\\ymt.dat", O_RDWR|O_BINARY, 0644)) < 0) {
		fdbprintf("Open ymt.dat error %d\r\n", fid);
		return(-1);
	}
	lseek(fid, ymtOffset, SEEK_SET);
	read(fid, &ymt, sizeof(ymtd));

	for (i=9; i>=0; i--)
		if (ymt.nrc[i].date != 0) break;

	if (i == 9) {
		for (i=0; i<9; i++)
			memcpy(&ymt.nrc[i], &ymt.nrc[i+1], sizeof(NRCD));
		memset(&ymt.nrc[9], 0, sizeof(NRCD));
		// Now i=9
	} else 
		i += 1;
//	time(&lt);
	tm=localtime(&nowTime);
	ymt.nrc[i].date = (tm->tm_mon + 1) * 100 + tm->tm_mday;
	ymt.nrc[i].time = (tm->tm_hour + 1) * 100 + tm->tm_min;
	strcpy(ymt.nrc[i].telNo, aniCaller);

	lseek(fid, ymtOffset, SEEK_SET);
	write(fid, &ymt, sizeof(ymtd));
	close(fid);
	return(1);
}

int BalIni()
{
	char	buf[120], fileName[32];
	FILE    *fd;
	int		k, i, errorNo;
//	int		ifd;

	if (balanceAnnounce == 0) {
		vxp->branch = 235;					// play "Enter telNo" instead of play Balance
		if (playOnHook == 1) ginn_answercall();
		return(1);
	}
	sprintf(fileName, "Bal%d", vxp->voie);
	fdbprintf("filename=%s\r\n", fileName);
	remove(fileName);
//	if ((ifd=open(fileName, O_CREAT|O_TRUNC|O_RDWR, 0666)) >= 0) close(ifd);		// Truncate file
	sprintf(buf, "curl -k -s -m10 -o %s https://61.61.132.70/Company/ShowMoney.php?Username=%s", fileName, aniCaller);
//	sprintf(buf, "curl -k -s -m10 -o %s https://61.61.132.70/Company/ShowMoney.php?Username=886989484745",
//        fileName);		// for test balance
	fdbprintf("command=%s\r\n", buf);
  	system(buf);
	if ((fd=fopen(fileName, "rt")) == NULL) {
		fdbprintf("Open [%s] Error\r\n", fileName);
		vxp->branch = 290;
		strcpy(exp->var[21], "850");
		return(1);
	}
	fgets(buf, 120, fd);
	fdbprintf("bal=%s\r\n", buf);
	fclose(fd);
	if (buf[0] == 'E') {
		errorNo = atoi(&buf[1]);
		switch(errorNo) {
		    case 3:	// Pay monthly
				switch(exp->v[1]) {
					case 1:						// From Call Out
						vxp->branch = 235;		// play "Enter telNo" instead of play Balance
						if (playOnHook == 1) ginn_answercall();
						return(1);
					case 2:						// From Balance Enquiry(via Voice Service)
					case 3:						// From Balance Enquiry(via YMT)
						vxp->branch = 290;
						strcpy(exp->var[21], "854");	// Play "You have No Balance"
						return(1);
					default:
						vxp->branch = 99999;	// let it die
						return(1);
					
				}
			case 1:	// UserName Error
			case 2:	// Please Input UserName
			default:
				vxp->branch = 290;
				strcpy(exp->var[21], "567");		// Not serve your telNo
				return(1);
		}
	}
	for (i=0; i<120; i++) {
		if (buf[i] == '.') {
			buf[i] = 0;
			i += 1;
			break;
		}
		if (buf[i] == 0) {
			i += 1;
			strcpy(&buf[i], "00");
			break;
		}
		if (buf[i] >= 0x40) {
			vxp->branch = 290;
			strcpy(exp->var[21], "567");		// Not serve your telNo
			return(1);
		}
	}
	if (buf[0] == '-' || atoi(buf) == 0) {
		if (exp->v[1] == 1) {					// From CallOut
			vxp->branch = 290;
			strcpy(exp->var[21], "855");		// Balance Not Enough
			return(1);
		}
	}

	exp->v[1] = 852;				// Your balance is ...
	k = 2;
	if (buf[0] == '-')
		k = bnam("負", k, 1);
	k = ifm(buf, &buf[i], k, 1);	// Get Chinese Amount Number
	k = bnam("元", k, 1);
	exp->v[k] = -1;
	if (playOnHook == 1) ginn_answercall();
	return(1);
}

int	CkOts()			// Check before entering OTS Service
{
	char	tmp[64];
	int		i, dlen, len;

	memset(tmp, 0, 64);
	exp->var[7][0] = 0;
	exp->var[13][0] = 0;
	exp->var[4][0] = 0;

	len = ginn_ani(tmp);		//取得主被叫號   
	if (len == 0) {
		fdbprintf("line(%d) incoming call, but can not found ani(%s)!!\n",vxp->voie,tmp);
		vxp->branch = 100;
		return 0;
	}
	fdbprintf("ots line(%d) incoming call, ani(%s)!!\n", vxp->voie, tmp);
	for (i=0; i<len; i++)  
		if (tmp[i] == '/') break;

	strcpy(aniCaller, &tmp[i+1]);			// caller  
	strncpy(dnisCalled, tmp, i);			// called
	dnisCalled[i] = 0;
	setFuncPointToKer("_uap_check_play", NULL);

	ginn_answercall();					// Answer the call
	dlen = strlen(localID);
	if (strncmp(dnisCalled, localID, dlen) == 0) 	// localid(ex. 07091111164)
		ginn_dnis(&dnisCalled[dlen]);				// Put left to stringin
	exp->v[1] = 2;
	return(1);
}

int	StPmpt()								// set pre-empt On Balance Play
{
	if (handsetType[0] == 'A') {
		vxp->branch = 210;					// Use FXS to accept called Number.
		time(&ltEnd);
		ltEnd += 5;							// time out on 5 sec. later
		ltLen = 0;
		setFuncPointToKer("_uap_check_play", (NFUNCPTR)check_on_play);
	} else {
		vxp->branch = 220;					// Interrupt Prompt on key stroke
	}
	exp->v[1] = 1;							// for Balini
	return(1);
}

EXTS	ext;								// Define in conference.h

TTab	ttab, ttabn;
CfrR	cfrr;
int		ttabFd = -1, cfrrFd = -1;
int		cfrrLoc, ttabLoc;
int		sYDay, eYDay, cYDay, qSess, qHour, qRefYear, qCount, endDay;
int		saveStartYDay;
//int	extInfoLoc;

int	openCfrFile()
{
	int	sess, i, k;

	if (ttabFd >= 0) return(1);

fdbprintf("OpenCfrFile Here\r\n");

	ttabFd = open(".\\CfrTimeTable.dat", O_RDWR|O_BINARY);
	if (ttabFd < 0) {						// File Not exists
		ttabFd = open(".\\CfrTimeTable.dat", O_CREAT|O_TRUNC|O_RDWR|O_BINARY, _S_IWRITE);
		if (ttabFd < 0) return(-1);

		memset((char *)&ttab, 0, sizeof(TTab));
		for (sess=0; sess<TotalCfrNo; sess++) {
			for (i=0; i<366; i++)
				for (k=0; k<8; k++)
					write(ttabFd, (char *)&ttab, sizeof(TTab));
		}
		close(ttabFd);
		ttabFd = open(".\\CfrTimeTable.dat", O_RDWR|O_BINARY);	// Make to be shared
		if (ttabFd < 0) return(-2);
	}
	cfrrFd = open(".\\CfrRecord.dat", O_RDWR|O_BINARY);
	if (cfrrFd < 0) {					// File Not exists
		cfrrFd = open(".\\CfrRecord.dat", O_CREAT|O_TRUNC|O_RDWR|O_BINARY, _S_IWRITE);
		if (cfrrFd < 0) {
			close(ttabFd);
			ttabFd = -1;
			return(-3);
		}
		memset((char *)&cfrr, 0, sizeof(CfrR));
		for (sess=0; sess<TotalCfrNo; sess++) {
			for (i=0; i<10000; i++)
				write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
		}
		close(cfrrFd);
		cfrrFd = open(".\\CfrRecord.dat", O_RDWR|O_BINARY);
		if (cfrrFd < 0) {
			close(ttabFd);
			ttabFd = -1;
			return(-4);
		}
	}
	return(1);
}

// (1) 分機按*3: 走s3
// (2) 分機按888: 走s3
// (3) 外線按888: 走s5輸入分機，走s1,s2,s3
int	CkCfr()
{
	char	tmp[120];
	int		ret, loc;

	exp->cnt[2] = 0;						// initialize for password over time 
	if (exp->cnt[1] > 0) {					// s1 from entered Extension Number.
		if (checkIfExtension(tlcp, exp->var[1], 0) < 0) {
			vxp->branch = 45;				// exp->cnt[1] += 1 and enter ext. No
			return(1);
		}
	}
	ret = openCfrFile();
	if (ret < 0) {							// Files Not exists
		fdbprintf("OpenCfrFile Error=%d\r\n", ret);
		vxp->branch = 21;
		return(1);
	}
	if (exp->var[1][0] != 0) {				// s3 Now Extension
		if ((loc = SelectRecordP("extensionInfo", "telNo", exp->var[1], 0)) >= 0) {
			GetDataP("deleted", tmp, 8, loc);
			if (tmp[0] != '0') {			// Deleted
				fdbprintf("Extension Deleted\r\n");
				vxp->branch = 18;			// Not Open Yet
				CleanSelectResult(loc);
				return(1);
			}
			GetDataP("password", ext.password, 16, loc);
			strcpy(ext.extensionNo, exp->var[1]);
			GetDataP("name", ext.name, 32, loc);
			GetData("handset", ext.handset, 32, loc);
		    GetData("emailAddrress", ext.emailAddress, 64, loc);
			if (strcmp(ext.password, "000000") == 0) {
				if (exp->var[5][0] != '4') {		// Change password
					strcpy(exp->var[22], "2156");	// Change password first
					vxp->branch = 24;
				}
			}
			CleanSelectResult(loc);
			return(1);						// Caller is extension, goto enter Password
		}
		fdbprintf("Not found extension in ExtensionInfo\r\n");
		vxp->branch = 18;					// Not Service You
		return(1);
	}
	// If Not extension
	vxp->branch = 30;						// s5 Enter Ext. No.
	return(1);
/*
		while(1) {
			// Read ExtensionInfo.txt at end break
fdbprintf("size of buffer=%d\r\n", strlen(buffer));
			extInfoLoc += strlen(buffer) + 1;				// add 1 for \n(0xa)
			if (fgets(buffer, 120, fpt) == NULL) break;		// No more data
			if (sscanf(buffer, "%s %s %s %s %s", ext.extension, ext.name, 
				ext.password, ext.deleted, ext.handset) < 3) continue;
			if (strcmp(exp->var[1], ext.extension) == 0) {
				fclose(fpt);
				if (ext.deleted[0] == 'D') {				// deleted
					fdbprintf("Extension Deleted\r\n");
					vxp->branch = 18;						// Not Open Yet
					return(1);
				}
				if (strcmp(ext.password, "000000") == 0) {	// need change password
					if (exp->var[5][0] != '4') {			// Change password
						strcpy(exp->var[22], "2156");			// Change password first
						vxp->branch = 24;
						return(1);
					}
				}
				return(1);					// Caller is extension, goto enter Password
			}
		}
		fdbprintf("Not found extension in ExtensionInfo.txt\r\n");
		vxp->branch = 18;					// Not Service You
		fclose(fpt);
		return(1);
	}
	// If Not extension
	while(1) {
		// Read ExtensionInfo.txt at end break s4
		extInfoLoc += strlen(buffer);
		if (fgets(buffer, 120, fpt) == NULL) break;		// No more data
		if (sscanf(buffer, "%s %s %s %s %s", ext.extension, ext.name, 
			ext.password, ext.deleted, ext.handset) < 3) continue;
		if (strcmp(aniCaller, ext.handset) == 0) {
			if (ext.deleted[0] == 'D') {		// deleted
				fdbprintf("handset Deleted\r\n");
				vxp->branch = 21;
				fclose(fpt);
				return(1);
			}
			strcpy(exp->var[1], ext.extension);
			fclose(fpt);
			return(1);
		}
	}
	vxp->branch = 30;						// s5 Enter Ext. No.
	fclose(fpt);
	return(1);
	*/
}

int UpdateRecordP(char *dataSet, char *object, char *where)
{
	HANDLE	hHandle;
	int		k;
	char	buf[120];

fdbprintf("[%s] where [%s]\r\n", object, where);
	hHandle = CreateMutex(NULL, FALSE, "extInfo");		// 鎖住extensioninfo
	WaitForSingleObject(hHandle, 10 * 1000);			// 等待10秒
	k = UpdateRecorder(dataSet , object , where);
	if (k < 0) {
		GetErrorMessage(buf, 120);
		fdbprintf("Error=%s, reopen database\r\n", buf);
		k = reOpenDatabase();
		if (k >= 0) 
			k = UpdateRecorder(dataSet , object , where);
	}
	CloseHandle(hHandle);
	return(k);
}

// Expect password field MUST has 9 digits for password(8 digits Max.) and spaces.
int updateCfrPswd()
{
	char	object[60], where[60];

	sprintf(object, "password = '%s'", exp->var[4]);
	sprintf(where, "extensionNo = %s and deleted = '0'", exp->var[1]);
	UpdateRecordP("extensionInfo", object, where);
	return(1);
}

int	CkCfrP()		// Check Password
{
	if (strcmp(exp->var[2], ext.password) != 0) {
		strcpy(exp->var[22], "564");
		vxp->branch = 65;
		return(1);
	}
	exp->cnt[2] = 0;
	switch(exp->var[5][0]) {
		case '3':					// Play Recording
		case '1':					// Cancel
			vxp->branch = 200;
			return(1);
		case '2':
			vxp->branch = 300;		// Enquiry
			qCount = 0;				// No mmdd-mmdd process yet
			sYDay = -1;
			return(1);
		case '4':					// Change password
			vxp->branch = 550;
			return(1);
		default:
			break;
	}
	return(1);
}

int cfrYear, cfrYday;
int cfrMm, cfrDd, cfrWw, cfrHh;

int	CkCfrD()		// Check date
{
	tm		*tm;
	long	dueDateTime;
	int		mmdd, mmddToday;

	tm = localtime(&nowTime);
	mmddToday = (tm->tm_mon + 1) * 100 + tm->tm_mday;

	tm->tm_mday += 14;
	dueDateTime = mktime(tm);

fdbprintf("mmddtoday=%d duedatetime=%d\r\n", mmddToday, dueDateTime);

	mmdd = atoi(exp->var[3]);
	tm->tm_mday = mmdd % 100;
	tm->tm_mon = mmdd / 100 - 1;
	if (mmdd < mmddToday)						// exp->var[3] 跨年
		tm->tm_year += 1;
	ltTime = mktime(tm);

	tm = localtime(&ltTime);					// Check mmdd syntex
	if (mmdd != ((tm->tm_mon+1) * 100 + tm->tm_mday)) {
		vxp->branch = 112;
		return(1);
	}
fdbprintf("lttime=%d duedatetime=%d\r\n", ltTime, dueDateTime);
	if (ltTime > dueDateTime) {
		if ((ltTime - 5184000) < dueDateTime) { // in 60 days
			vxp->branch = 114;					// Over 14 days
		} else {
			vxp->branch = 112;					// Date Error
		}
		return(1);
	}
fdbprintf("mmdd=%d %d %d\r\n", mmdd, tm->tm_mon+1, tm->tm_mday);
	cfrYear = tm->tm_year;
	cfrYday = tm->tm_yday;
	cfrMm = tm->tm_mon+1;
	cfrDd = tm->tm_mday;
	cfrWw = tm->tm_wday;
	cfrHh = tm->tm_hour;
	if (cfrWw == 0) cfrWw = 7;				// Sunday
	return(1);
}

int	getAllYearDay()
{
	int		sMm, sDd, eMm, eDd, refYDay, sYear, eYear, sTime, eTime;
	char	buf[16];
//	long	lt, now;
	tm		*tm;

fdbprintf("exp->var[6] = %s\r\n", exp->var[6]);
	strncpy(buf, exp->var[6], 2);
	buf[2] = 0;
	sMm = atoi(buf); 
	strncpy(buf, &exp->var[6][2], 2);
	sDd = atoi(buf); 
	strncpy(buf, &exp->var[6][4], 2);
	eMm = atoi(buf); 
	strncpy(buf, &exp->var[6][6], 2);
	eDd = atoi(buf); 
fdbprintf("date=%d/%d - %d/%d\r\n", sMm, sDd, eMm, eDd);

//	time(&now);
	tm = localtime(&nowTime);
	tm->tm_mday += 14;
	ltTime = mktime(tm);
	tm = localtime(&ltTime);
	qRefYear = tm->tm_year;		// The year of the ending reservable date.
	refYDay = tm->tm_yday;
fdbprintf("refDay=%d %d\r\n", qRefYear, refYDay);

	// get start day's year
	if ((sMm - 1) > tm->tm_mon) sYear = qRefYear - 1;
	else if (((sMm - 1) == tm->tm_mon) && sDd > tm->tm_mday) sYear = qRefYear - 1;
	else sYear = qRefYear;
	// get End day's year
	if ((eMm - 1) > tm->tm_mon) eYear = qRefYear - 1;
	else if (((eMm - 1) == tm->tm_mon) && eDd > tm->tm_mday) eYear = qRefYear - 1;
	else eYear = qRefYear;

	tm->tm_year = sYear;
	tm->tm_mon = sMm - 1;
	tm->tm_mday = sDd;
	ltTime = mktime(tm);
	tm = localtime(&ltTime);
	if (tm->tm_mon != (sMm - 1) || tm->tm_mday != sDd) {
		strcpy(exp->var[22], "2112");
		vxp->branch = 315;
		return(-1);
	}
	sYDay = tm->tm_yday;
	sTime = ltTime;
fdbprintf("sYDay=%d\r\n", sYDay);

	tm->tm_year = eYear;		// end date Uses same year as start date
	tm->tm_mon = eMm - 1;
	tm->tm_mday = eDd;
	ltTime = mktime(tm);
	tm = localtime(&ltTime);
	if (tm->tm_mon != (eMm - 1) || tm->tm_mday != eDd) {
		strcpy(exp->var[22], "2112");
		vxp->branch = 315;
		return(-2);
	}
	eTime = ltTime;
	eYDay = tm->tm_yday;
fdbprintf("eYDay=%d\r\n", eYDay);

	if (sTime > eTime) {
		strcpy(exp->var[22], "2112");
		vxp->branch = 315;
		return(-1);
	}
	cYDay = 999;
	if (sYDay > eYDay) {				// Cross over year
		tm->tm_year = qRefYear - 1;
		tm->tm_mday = 31;
		tm->tm_mon = 11;
		ltTime = mktime(tm);
		tm = localtime(&ltTime);
		cYDay = tm->tm_yday;	// End of the year(c:cross over year)
	}
fdbprintf("yday=%d %d %d\r\n", sYDay, eYDay, cYDay);
	return(1);
}
// Check enquiry mmdd-mmdd 
int CkCfr8()
{
	int		loc, tLoc, cLoc;
	char	str[32];
	
	if (sYDay == -1) {			// mmdd-mmdd not process yet
		loc = getAllYearDay();	// Get sYDay, eYDay, cYDay
		if (loc < 0) {			// Error On date
			fdbprintf("Error date = %d\r\n", loc);
			sYDay = -1;
			return(1);
		}
		qHour = 0;
		qSess = -1;
		saveStartYDay = sYDay;
		endDay = 0;
		qCount = 0;
	}
	while(1) {
		qSess += 1;
		if (qSess >= TotalCfrNo) {
			qSess = 0;
			qHour += 2;									// Must meet one of the two hour
			if (qHour >= 24) {							// End of hour
				if (eYDay == saveStartYDay) break;		// sYDay = eYDay
				qHour = 0;
				sYDay += 1;
				if (endDay == 1) break;
				if (sYDay > cYDay) sYDay = 0;
				if (sYDay == eYDay) endDay = 1;
			}
		}
		tLoc = ((qSess * 366 + sYDay) * 24 + qHour) * sizeof(TTab);
		lseek(ttabFd, tLoc, SEEK_SET);
		ttab.password = 0;
		read(ttabFd, (char *)&ttab, sizeof(TTab));
fdbprintf("year=%d %d tLoc=%d qSess=%d %d %d yday=%d %d\r\n", ttab.year, qRefYear, tLoc,
		  qSess, sYDay, qHour, sYDay, eYDay);
		if (ttab.password == 0)	continue;
		cLoc = (ttab.cfrNo * 10000 + ttab.password) << 9;	// location to cfrRecord.dat
		lseek(cfrrFd, cLoc, SEEK_SET);
		memset((char *)&cfrr, 0, sizeof(CfrR));
		read(cfrrFd, (char *)&cfrr, sizeof(CfrR));
fdbprintf("extension=%s %s, password=%d %d, cfrNo=%d %d, year=%d %d\r\n", 
cfrr.extension, exp->var[1], ttab.password, cfrr.password, ttab.cfrNo, cfrr.cfrNo, ttab.year, cfrr.year);
		if (strcmp(exp->var[1], cfrr.extension) != 0) 
			continue;										// Not the reserver, can't enq.
		if (ttab.password != cfrr.password || ttab.cfrNo != cfrr.cfrNo)
			continue;										// cfrr being occupied by other.
		if (ttab.year != cfrr.year)
			continue;										// Not the same year
		qCount += 1;
		// Synthesis
		loc = 1;
		exp->v[loc++] = cfrr.mm + 610;			// x月
		exp->v[loc++] = cfrr.dd + 630;			// x日
		sprintf(str, "%02d00", cfrr.hh);
		loc = synthesisDayTime(str, loc);		// Morning(Noon...) xx o'clock xx minute
		exp->v[loc++] = 2127;					// room password is ...
		sprintf(str, "%d%04d", cfrr.cfrNo, cfrr.password);
		loc = ifx(str, loc, 1);
		exp->v[loc++] = 9999;					// To avoid end noice
		exp->v[loc] = -1;
		return(1);
	}
	sYDay = saveStartYDay;									// sYday will not be destroyed
	if (qCount == 0) 
		strcpy(exp->var[22], "2130");						// No record
	else
		strcpy(exp->var[22], "2129");						// No more record
	vxp->branch = 340;
	sYDay = -1;
	return(1);
}

// Check cfr room password
int CkCfrR()
{
	tm		*tm;
	int		loc, i, ret, firstComer, password;
	char	str[32];
	int		endTime = 0;
	long	expireTime;
	int		cfrPassword;

	ret = openCfrFile();							// Join meeting may not open files yet
	if (ret < 0) {									// Files Not exists
		fdbprintf("OpenCfrFile Error=%d\r\n", ret);
		vxp->branch = 21;
		return(1);
	}
	password = atoi(exp->var[6]);
	cfrrLoc = (password) << 9;				// location to cfrRecord.dat (<< 9) = (* 512)
	cfrr.password = 0;
	lseek(cfrrFd, cfrrLoc, SEEK_SET);
	read(cfrrFd, (char *)&cfrr, sizeof(CfrR));
//fdbprintf("password=%d %d %d meetime=%d\r\n", password, cfrr.password, cfrrLoc, cfrr.meetingTime);
	cfrPassword = cfrr.password + cfrr.cfrNo * 10000;
	if (cfrr.password == 0 || cfrPassword != password) {
		strcpy(exp->var[22], "2138");				// password error
		vxp->branch = 215;
		return(1);
	}
	switch(exp->var[5][0]) {
		case '0':										// To Join the meeting
			if (nowTime < (cfrr.meetingTime - 600)) {	// Too early to 10 minutes
				strcpy(exp->var[22], "2140");
				vxp->branch = 24;
				return(1);
			}
			loc = -1;
			firstComer = 1;
			for (i = 0; i < 8; i++) {
//fdbprintf("attender=%s %d %d\r\n", cfrr.attender[i], cfrr.inTime[i], cfrr.outTime[i]);
				if ((strcmp(cfrr.attender[i], aniCaller) == 0 && cfrr.outTime[i] != 0)
					|| cfrr.inTime[i] == 0) {
					if (loc == -1) loc = i;
				}
				if (cfrr.inTime[i] != 0 && cfrr.outTime[i] == 0) firstComer = 0;
			}
			if (loc == -1) {
				strcpy(exp->var[22], "2142");		// room is full
				vxp->branch = 24;
				return(1);
			}
			if (cfrr.inTime[loc] == 0) {				// First time come in for this attender
				if (cfrr.registerTime > cfrr.meetingTime) {
					expireTime = cfrr.registerTime + CfrExpireTime;
				} else {
					expireTime = cfrr.meetingTime + CfrExpireTime;
				}
			} else {
				expireTime = cfrr.meetingTime +	6600;	// 110 minutes * 60 seconds = 6600
			}
			if (nowTime > expireTime) {					// over meeting time
				strcpy(exp->var[22], "2146");
				vxp->branch = 24;
				return(1);
			}
			cfrr.inTime[loc] = nowTime;
			cfrr.outTime[loc] = 0;
			strcpy(cfrr.attender[loc], aniCaller);		// No exp->var[1] entered for join meeting.
			cfrr.status[i] = 0;
			lseek(cfrrFd, cfrrLoc, SEEK_SET);
			write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			_commit(cfrrFd);
fdbprintf("attender=%s %d %d\r\n", cfrr.attender[loc], cfrr.inTime[loc], cfrr.outTime[loc]);
			if (firstComer == 1) {
				strcpy(exp->var[22], "2154");			// 1st comer wait a moment
				strcpy(exp->var[23], "9999");
				vxp->branch = 505;
			} else { 
				strcpy(exp->var[22], "2144");			// Say hello
				strcpy(exp->var[23], "2148");			// Ding Dong
				vxp->branch = 510;
			}
			sprintf(exp->var[13], "T/C=%d%04d-%d Caller Add IVR", cfrr.cfrNo, cfrr.password, loc+1); 
			sprintf(exp->var[14], "T/C=%d%04d-%d Caller Add NOIVR", cfrr.cfrNo, cfrr.password, loc+1); 
			break;
		case '3':									// Play Recording
			if (strcmp(cfrr.extension, exp->var[1]) != 0)
			{										// Not originator
				strcpy(exp->var[22], "2113");
				vxp->branch = 215;
				return(1);
			}
			if (cfrr.inTime[0] == 0) {
				strcpy(exp->var[22], "2137");		// Not held
				vxp->branch = 215;
				return(1);
			}
			exp->v[1] = 2104;
			loc = 2;
			exp->v[loc++] = cfrr.mm + 610;			// x月
			exp->v[loc++] = cfrr.dd + 630;			// x日
			sprintf(str, "%02d00", cfrr.hh);
			loc = synthesisDayTime(str, loc);		// Morning(Noon...) xx o'clock xx minute
			exp->v[loc++] = 2133;					// Total recording time is
			for (i=0; i<8; i++)
				if (cfrr.outTime[i] > endTime) endTime = cfrr.outTime[i];
			if (cfrr.meetingTime > cfrr.registerTime)
				endTime -= cfrr.meetingTime;		// Duration seconds
			else endTime -= cfrr.registerTime;

			endTime /= 60;							// to minutes
			if (endTime> 115) endTime = 115;
			if (endTime >= 60) {
				exp->v[loc++] = 2134;				// 1 hour
				endTime -= 60;
			}
			if (endTime > 0) exp->v[loc++] = endTime + 700;	// minutes
			exp->v[loc++] = 2135;					// recording started...
			exp->v[loc] = -1;
			strcpy(exp->var[7], cfrr.recFileName);
			strcat(exp->var[7], "A");				// Allow 7,8,9 to speed up.
			vxp->branch = 420;
fdbprintf("var[7]=%s\r\n", exp->var[7]);
			break;
		case '1':									// Cancel
			if (strcmp(cfrr.extension, exp->var[1]) != 0) 
			{										// Not originator
				strcpy(exp->var[22], "2113");
				vxp->branch = 215;
				return(1);
			}
			tm = localtime(&nowTime);
			tm->tm_year = cfrr.year;
			tm->tm_mon = cfrr.mm - 1;
			tm->tm_mday = cfrr.dd;
			tm->tm_hour = cfrr.hh;
			ltTime = mktime(tm);
			if (ltTime < nowTime) {						// can't cancel
				strcpy(exp->var[22], "2125");
				vxp->branch = 215;
				return(1);
			}
			loc = 1;
			exp->v[loc++] = 2122;					// you want to cancel meeting is ...
			exp->v[loc++] = 2104;					// meeting time is ...
			exp->v[loc++] = cfrr.mm + 610;			// x月
			exp->v[loc++] = cfrr.dd + 630;			// x日
			sprintf(str, "%02d00", cfrr.hh);
			loc = synthesisDayTime(str, loc);		// Morning(Noon...) xx o'clock xx minute
			exp->v[loc] = -1;
			break;
		default:
			break;
	}
	return(1);
}

int	CnCfrR()
{
	char	message[256], buff[4];

	sprintf(message, "會議取消通知：原定於%d月%d日%d時，召開之電話會議，因故取消，特此通知。會議主持人%s",
			  cfrr.mm, cfrr.dd, cfrr.hh, cfrr.name);
	strcpy(buff, "-");
	sendSM(cfrr.handset, message, buff, buff, buff);
	memset((char *)&cfrr, 0, sizeof(CfrR)); 
	lseek(cfrrFd, cfrrLoc, SEEK_SET);
fdbprintf("cfrWrite cancel3\r\n");
	write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
	_commit(cfrrFd);

	ttab.year = 0;
	ttab.password = 0;
	lseek(ttabFd, ttabLoc, SEEK_SET);
fdbprintf("cfrWrite Cancel\r\n");
	write(ttabFd, (char *)&ttab, sizeof(TTab));	// free the meeting 
	write(ttabFd, (char *)&ttab, sizeof(TTab));
	return(1);
}

int		cfrStartHour = -1, cfrEndHour = 24, cfrSess = 0;
int		odd[8] = {7, 17, 37, 97, 137, 167, 227, 307};	

int	getOccupiedRange(int tLoc, int sess)
{
	int		i, saveLoc, freeCount = 0;
	int		hour, startHour = -1, endHour = 24;

	// find previous unoccupied
	hour = atoi(exp->var[4]);
	saveLoc = tLoc;
	tLoc += sizeof(TTab);
	for (i=hour; i >= 0; i--) {
		tLoc -= sizeof(TTab);
		lseek(ttabFd, tLoc, SEEK_SET);
		read(ttabFd, (char *)&ttab, sizeof(TTab));
		if (ttab.year == cfrYear) {
			freeCount = 0;
			continue;
		}
		freeCount += 1;
		if (freeCount == 2) {
			startHour = i + 2;
			break;
		}
	}
	freeCount = 0;
	tLoc = saveLoc - sizeof(TTab);
	for (i=hour; i < 24; i++) {
		tLoc += sizeof(TTab);
		lseek(ttabFd, tLoc, SEEK_SET);
		read(ttabFd, (char *)&ttab, sizeof(TTab));
		if (ttab.year == cfrYear) {
			freeCount = 0;
			continue;
		}
		freeCount += 1;
		if (freeCount == 2) {
			endHour = i - 2;
			break;
		}
	}
	// save the max Span location
	if ((endHour - startHour) > (cfrEndHour - cfrStartHour)) {
		cfrEndHour = endHour;
		cfrStartHour = startHour;
		cfrSess = sess;
	}
	return(1);
}

int	clearCfrPassword()
{
	int		cLoc = -1, cLocn = -1;

	memset((char *)&cfrr, 0, sizeof(CfrR));
	if (ttab.year != cfrYear && ttab.year != 0) {			// Expired
fdbprintf("cfrno=%d password=%d\r\n", ttab.cfrNo, ttab.password);
		if (ttab.password != 0) {
			cLoc = (ttab.cfrNo * 10000 + ttab.password) << 9;	// location to cfrRecord.dat
			lseek(cfrrFd, cLoc, SEEK_SET);
fdbprintf("cfrWrite clearPassword\r\n");
			write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			_commit(cfrrFd);
		}
	}
	if (ttabn.year != cfrYear && ttabn.year != 0) {			// Expired
fdbprintf("cfrno=%d password=%d\r\n", ttabn.cfrNo, ttabn.password);
		if (ttabn.password != 0) {
			cLoc = (ttabn.cfrNo * 10000 + ttabn.password) << 9;	// location to cfrRecord.dat
			lseek(cfrrFd, cLoc, SEEK_SET);
fdbprintf("cfrWrite clearpassword2\r\n");
			write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			_commit(cfrrFd);
		}
	}
	return(1);
}

int	setCfrPassword(int sess)		// Get randum number for password. If dup, retry.
{
	long	loc, sessPart;
	int		password;
	int		oddLoc, count = 0;

//	time(&lt);
	sessPart = sess * 10000;
	password = nowTime % 10000;
	oddLoc = nowTime % 7;
	loc = (sessPart + password) << 9;		// location to cfrRecord.dat (<< 9) = (* 512)
	while(1) {
		if (password > 0) {					// if password = 0, ignore it
			lseek(cfrrFd, loc, SEEK_SET);
			read(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			if (cfrr.password == 0) break;	// Released
		}
		count += 1;
		fdbprintf("repeat=%d rand=%d\r\n", count, password);
		password += odd[oddLoc];
		if (password >= 10000) password -= 10000;
		loc = (sessPart + password) << 9;	// location to cfrRecord.dat
	}
	memset((char *)&cfrr, 0, sizeof(CfrR));
fdbprintf("password=%d %d\r\n", sess, password);
	cfrr.password = password;
	cfrr.cfrNo = sess;
	return(loc);
}

int	CkCfrT()			// Check time
{
	int		hour, refHour;
	int		sess, loc;
	char	str[32], password[32];
	tm		*tm;
	char	message[256], buff[8];

	tm = localtime(&nowTime);
	refHour = 0;
	if (cfrMm == (tm->tm_mon + 1) && cfrDd == tm->tm_mday) refHour = cfrHh;
	hour = atoi(exp->var[4]);
	if (hour >= 24 || hour < refHour) {		// The hour is passed
		strcpy(exp->var[22], "2109");
		vxp->branch = 132;					// time error
		return(1);
	}
	// Check if all session occupied
	cfrStartHour = -1;
	cfrEndHour = 24;
	cfrSess = 0;
	for (sess = 0; sess < TotalCfrNo; sess++) {
		ttabLoc = ((sess * 366 + cfrYday) * 24 + hour) * sizeof(TTab);
		lseek(ttabFd, ttabLoc, SEEK_SET);
		read(ttabFd, (char *)&ttab, sizeof(TTab));
		read(ttabFd, (char *)&ttabn, sizeof(TTab));
fdbprintf("sess=%d yday=%d hour=%d loc=%d year=%d %d\r\n", sess, cfrYday, hour, ttabLoc, ttab.year, ttabn.year);
		if (ttab.year == cfrYear || ttabn.year == cfrYear) {	// Occupied
			// Check if reserved yet by the extension
			cfrrLoc = (ttab.cfrNo * 10000 + ttab.password) << 9;
			lseek(cfrrFd, cfrrLoc, SEEK_SET);
			read(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			if (strcmp(cfrr.extension, exp->var[1]) == 0 && cfrr.password != 0) {
				strcpy(exp->var[22], "2114");					// You have reserved room at the hour
				vxp->branch = 132;
				return(1);
			}
			// Look for Occupied range
			getOccupiedRange(ttabLoc, sess);
			continue;
		}
		break;
	}
	if (sess >= TotalCfrNo) {				// No Sessions are free
		exp->v[1] = 2110;					// reserved range are ...
		if (cfrStartHour == -1) cfrStartHour = 0;
		loc = 2;
		sprintf(str, "%02d00", cfrStartHour);
		loc = synthesisDayTime(str, loc);	// Morning(Noon...) xx o'clock xx minute
		exp->v[loc++] = 536;				// to ...
		sprintf(str, "%02d00", cfrEndHour);
		loc = synthesisDayTime(str, loc);	// Morning(Noon...) xx o'clock xx minute
		exp->v[loc] = -1;
		vxp->branch = 134;					// Play reservation occupied
		return(1);
	}
	// Clear Old One if exists
	clearCfrPassword();
	// Update cfrTimeTable.dat, cfrRecord.dat
	cfrrLoc = setCfrPassword(sess);			// Session start from 0
	ttab.password = cfrr.password;
	ttab.cfrNo = sess;
	ttab.year = cfrYear;
	ttabn.password = cfrr.password;
	ttabn.cfrNo = sess;
	ttabn.year = cfrYear;
fdbprintf("loc=%d year=%d password=%d %d\r\n", ttabLoc, ttab.year, ttab.cfrNo, ttab.password);
	lseek(ttabFd, ttabLoc, SEEK_SET);
fdbprintf("cfrWrite effect\r\n");
	write(ttabFd, (char *)&ttab, sizeof(TTab));
	write(ttabFd, (char *)&ttabn, sizeof(TTab));
	_commit(ttabFd);
	strcpy(cfrr.extension, exp->var[1]);	// Save extension No.
	cfrr.hh = hour;							// time
	cfrr.mm = cfrMm;
	cfrr.dd = cfrDd;
	cfrr.year = cfrYear;
//	time(&lt);
	tm=localtime(&nowTime);
	tm->tm_year = cfrYear;
	tm->tm_mon = cfrMm - 1;
	tm->tm_mday = cfrDd;
	tm->tm_hour = hour;
	tm->tm_min = 0;
	tm->tm_sec = 0;
	ltTime = mktime(tm);
	cfrr.meetingTime = ltTime;
	cfrr.registerTime = nowTime;
	strcpy(cfrr.name, ext.name);
	strcpy(cfrr.handset, ext.handset);
	sprintf(cfrr.recFileName, ".\\crec\\cfr%d%04d", cfrr.cfrNo, cfrr.password);
	lseek(cfrrFd, cfrrLoc, SEEK_SET);
fdbprintf("cfrWrite effect2\r\n");
	write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
	_commit(cfrrFd);
	// Play Message
	exp->v[1] = 2103;						// reserve OK, password is...
	sprintf(password, "%d%04d", cfrr.cfrNo, cfrr.password);
	loc = 2;
	loc = ifx(password, loc, 1);			// password, include room No.
	exp->v[loc++] = 2104;					// meeting time is ...
	exp->v[loc++] = cfrMm + 610;			// x月
	exp->v[loc++] = cfrDd + 630;			// x日
	exp->v[loc++] = cfrWw + 670;			// 星期x
	sprintf(str, "%02d00", hour);
	loc = synthesisDayTime(str, loc);		// Morning(Noon...) xx o'clock xx minute
	exp->v[loc++] = 536;					// to ...
	sprintf(str, "%02d50", hour+1);			// x時50分
	loc = synthesisDayTime(str, loc);		// Morning(Noon...) xx o'clock xx minute
	exp->v[loc++] = 2105;					// Notice will send to 
	if (ext.handset[0] != 0) 				// handset
		exp->v[loc++] = 2106;
	exp->v[loc++] = 2107;	
	exp->v[loc] = -1;
	sprintf(message,
	"開會通知:玆定於%d月%d日%d時正,召開電話會議,請準時撥打本公司分機%s,"
	"並輸入會議室密碼%s,以加入會議.召集人%s",
	cfrr.mm, cfrr.dd, cfrr.hh, telCfrPorter, password, cfrr.name);
	strcpy(buff, "-");
fdbprintf("message=%s handset=%s\r\n", cfrr.handset, message);
	sendSM(cfrr.handset, message, buff, buff, buff);
	// Send eMail
fdbprintf("Send Email\r\n");
	return(1);
}

TTab	ttabs[TotalCfrNo];
int		ttabsLoc[TotalCfrNo];
CfrR    cfrrs[TotalCfrNo];
int		cfrrsLoc[TotalCfrNo];
char	needRecord[TotalCfrNo];			// 0: Empty 1:wait for recording 2:need recording 3:recording 4:end
char	needSpeak[TotalCfrNo];			// 0:No say 1:Need to say. 
char	needCancel[TotalCfrNo];			// 0:No Cancel 1:Need to Cancel. 
char	needSpeakDongDing[TotalCfrNo];
char	saveOutTime[TotalCfrNo][8];		// When attender in, it set to 0. when attender out it set to 1
char	needBreak = 0;

char	minutesToSpeak[4] = {40, 45, 49};
char	enableToSpeak[4] = {1, 1, 1};
char	nextToSpeak[4] = {1, 2, 0};
int		messToSpeak[4] = {2149, 2150, 2151};
int		lastMinute, firstHour;

int rightHourProcess(tm *tm, int currentHour)
{
	int		sess, i, count;
	long	expireTime;

	for (sess = 0; sess < TotalCfrNo; sess++) {
		switch(needRecord[sess]) {
		  case -1:						// Before right hour to meeting
			if (tm->tm_min == 0) needRecord[sess] = 0;
			break;
		  case 0:						// Check if need to start recording	
			// Read to take the room reservation now
			ttabLoc = ((sess * 366 + tm->tm_yday) * 24 + currentHour) * sizeof(TTab);
			lseek(ttabFd, ttabLoc, SEEK_SET);
			read(ttabFd, (char *)&ttab, sizeof(TTab));
			if (ttab.year != tm->tm_year) continue;				// Over date
			read(ttabFd, (char *)&ttabn, sizeof(TTab));
fdbprintf("year=%d %d %d pass=%d %d\r\n", ttab.year, ttabn.year, tm->tm_year, 
  ttab.password, ttabn.password);
			if (ttab.year != ttabn.year || ttab.password != ttabn.password) {
				ttabLoc -= sizeof(TTab);						// Now maybe 2nd hour
				lseek(ttabFd, ttabLoc, SEEK_SET);
				read(ttabFd, (char *)&ttab, sizeof(TTab));
				read(ttabFd, (char *)&ttabn, sizeof(TTab));
				if (ttab.year != tm->tm_year) continue;			// Over date
				if (ttab.year != ttabn.year) continue;
				if (ttab.password != ttabn.password) continue;
			}
			cfrrsLoc[sess] = (ttab.cfrNo * 10000 + ttab.password) << 9;
			lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
			read(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
fdbprintf("pass=%d %d minute=%d hour=%d %d\r\n", ttab.password, cfrrs[sess].password,
		  tm->tm_min, tm->tm_hour, cfrrs[sess].hh);
			if (ttab.password != cfrrs[sess].password) continue;
			strcpy((char *)&ttabs[sess], (char *)&ttab);
			ttabsLoc[sess] = ttabLoc;
			// Read hh. In front of new hh. 
			if (tm->tm_min >= 50 && tm->tm_hour != cfrrs[sess].hh) 
			{	// If nowhour is before hh, goto -1 to wait
				// 1:50-1:59 get hh=2, goto -1. 2:50-2:59 get hh=2, not to goto -1. 
				needRecord[sess] = -1;
				continue;
			}
			// Find someone in conference
			for (i=0; i<8; i++) {
fdbprintf("attender=%s outTime=%d\r\n", cfrrs[sess].attender[i], cfrrs[sess].outTime[i]);
				if (cfrrs[sess].attender[i][0] != 0 && cfrrs[sess].outTime[i] == 0) break;
			}
			if (i >= 8) {
				needRecord[sess] = 1;								// record wait till someone in.
			} else {
				needRecord[sess] = 2;								// Need to recording
				needBreak |= 1;
fdbprintf("1.record=%s sess=%d", cfrrs[sess].attender[i], sess);
			}
			continue;
		  case 1:				// Check if someone come in conference
			lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
			read(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
			for (i=0; i<8; i++) 
				if (cfrrs[sess].attender[i][0] != 0 && cfrrs[sess].outTime[i] == 0) break;
			if (i >= 8) {
				if (cfrrs[sess].meetingTime > cfrrs[sess].registerTime)
					expireTime = cfrrs[sess].meetingTime + CfrExpireTime;
				else expireTime = cfrrs[sess].registerTime + CfrExpireTime;
fdbprintf("time=%d %d %d %d\r\n", nowTime, cfrrs[sess].meetingTime, cfrrs[sess].registerTime, expireTime);
				if (nowTime > expireTime) {					// Over 15 minutes no one come in.
					needCancel[sess] = 1;
					needRecord[sess] = 0;
					needBreak |= 2;
				}
			} else {
				needRecord[sess] = 2;							// Need to recording
				needBreak |= 1;
fdbprintf("2.record=%s sess=%d", cfrrs[sess].attender[i], sess);
			}
			continue;
		  case 3:							// On recording
			for (i = 0; i < 3; i++) {
				if (tm->tm_min == minutesToSpeak[i] && tm->tm_min != lastMinute) {
					if (tm->tm_hour != cfrrs[sess].hh) {	// meet second hour
fdbprintf("Now %d minutes left %d %d hour=%d %d\r\n", (50 - tm->tm_min), tm->tm_hour, cfrrs[sess].hh);
						needSpeak[sess] = 1;
						exp->cnt[8] = messToSpeak[i];
						needBreak |= 4;
						sprintf(vxp->message, "%d minutes left %d", (50 - tm->tm_min), sess);
fdbprintf("%s", vxp->message);
					}
				}
			}
			// Not read new hh. at end of conference
			if (tm->tm_min >= 50 && tm->tm_hour != cfrrs[sess].hh) {
				needBreak |= 32;										// Close and End
				needRecord[sess] = 6;
				continue;
			}
			count = 0;
			lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
			read(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
			for (i=0; i<8; i++) {
fdbprintf("attenders=%s outTime=%d\r\n", cfrrs[sess].attender[i], cfrrs[sess].outTime[i]);
				if (cfrrs[sess].attender[i][0] != 0 && cfrrs[sess].outTime[i] == 0) count += 1;
			}
			if (count == 0) {					// No one Inside Ask to stop recording
				// The last one left(status=1) will make count to 0. We have to clear status,
				// and never say DongDing again.
				int needUpdate = 0;
				for (i = 0; i < 8; i++) {
					if (cfrrs[sess].status[i] == 1) {
						cfrrs[sess].status[i] = 0;
						needUpdate = 1;
					}
				}
				if (needUpdate == 1) {
					lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
					write(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
					_commit(cfrrFd);
				}
				needBreak |= 16;
				needRecord[sess] = 4;
				continue;
			}
			break;
		  case 5:							// Stop To Record, wait for any one come in again
			lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
			read(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
			for (i=0; i<8; i++) {
				if (cfrrs[sess].attender[i][0] != 0 && cfrrs[sess].outTime[i] == 0) {
					needRecord[sess] = 2;								// Need to recording
					needBreak |= 1;
fdbprintf("3.record=%s sess=%d", cfrrs[sess].attender[i], sess);
					break;
				}
			}
			// Not get new hh, to stop current session.
			if (tm->tm_min >= 50 && tm->tm_hour != cfrrs[sess].hh) {
				needBreak |= 32;
				needRecord[sess] = 6;
			}
			continue;
		  case 2:							// Starting to record
		  case 4:
		  case 6:
			continue;
		} // switch()
		// Check if someone leave and someone inside
		lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);
		read(cfrrFd, (char *)&cfrrs[sess], sizeof(CfrR));
		count = 0;		
		for (i = 0; i < 8; i++) {
fdbprintf("attenderleave=%s outTime=%d\r\n", cfrrs[sess].attender[i], cfrrs[sess].outTime[i]);
			if (cfrrs[sess].attender[i][0] != 0) {			// Attender exists
				if (cfrrs[sess].outTime[i] == 0) {			// attender is in now
					saveOutTime[sess][i] = 0;				// attender set to in
					count += 1;
				} else {									// attender is out now
					if (saveOutTime[sess][i] == 0) {		// But last time attender is in
						needSpeakDongDing[sess] += 1;		// say "Dong Ding" one more time
						saveOutTime[sess][i] = 1;			// attender set to out
					}
				}
			}
		}
		if (needSpeakDongDing[sess] > 0) {
			if (count > 0) {
				needBreak |= 8;
				fdbprintf("Send DongDing\r\n");
			} else needSpeakDongDing[sess] = 0;
		}
	} // for sess 
	lastMinute = tm->tm_min;
	return(1);
}


// Monitor Conference
int	MnCfr()
{
	static  int	sessEndTime, currentHour;
	int		sess;
	tm		*tm;
	long	lt;

//	fdbprintf("count=%d\r\n", exp->cnt[1]);
	if (exp->cnt[1] == 1) {
		exp->cnt[1] = 2;
		ginn_outofservice();				// Hook off
		int ret = openCfrFile();
		if (ret < 0) {						// Files Not exists
			fdbprintf("OpenCfrFile Error1=%d\r\n", ret);
			vxp->branch = 21;
			return(1);
		}
		for (sess = 0; sess < TotalCfrNo; sess++) {
			needRecord[sess] = 0;
			needSpeak[sess] = 0;
			needCancel[sess] = 0;
			needSpeakDongDing[sess] = 0;
		}
		needBreak = 0;
		sessEndTime = 0;
		currentHour = -1;
	}
while(1) {
	if (vxp->command == '3' || vxp->command == '5') {
		vxp->branch = 10;
		return(1);
	}
	time(&nowTime);
	// to thrink calculation to one time per hour.
	if (nowTime >= sessEndTime) {			// sessEdnTime is always on 095000(0r 0 initial)
		lt = nowTime + 600;					// 600:10 minutes. ex. 09:50 will be hour 10.
		tm = localtime(&lt);
		if (tm->tm_hour != currentHour) {
			currentHour = tm->tm_hour;		// to get end location.
			tm->tm_min = 50;
			tm->tm_sec = 0;
			sessEndTime = mktime(tm);		// sessEdnTime is always on 095000
		}
	}
	tm = localtime(&nowTime);
	rightHourProcess(tm, currentHour);
	if (needBreak & 1) {					// Need to Record
		vxp->branch = 30;
		return(1);
	}
	if (needBreak & 2) {					// Reset meeting
		vxp->branch = 230;
		return(1);
	}
	if (needBreak & 4) {					// Say 10 minutes left
		vxp->branch = 130;
		return(1);
	}
	if (needBreak & 8) {					// Say DongDing
		vxp->branch = 130;
		return(1);
	}
	if (needBreak & 16) {					// Stop recording
		vxp->branch = 330;
		return(1);
	}
	if (needBreak & 32) {					// Stop recording, and bye to all
		vxp->branch = 330;
		return(1);
	}
	Sleep(2000);
}
//	vxp->branch = 80;						// Sleep 2 Sec.
	return(1);
}

// Stop record and/or bye to all
int ByeCfr()
{
	char	buf[16];
	int		sess;

	for (sess = 0; sess < TotalCfrNo; sess++) {
		if (needRecord[sess] == 6) {
			needRecord[sess] = 0;			// Go to get new hh after all.
			sprintf(buf, "%d%04d", cfrrs[sess].cfrNo, cfrrs[sess].password);
			sprintf(exp->var[13], "T/C=%s Caller Close NOIVR NoRecord", buf); 
			return(1);
		}
	}
	for (sess = 0; sess < TotalCfrNo; sess++) {
fdbprintf("Sess=%d %d\r\n", sess, needRecord[sess]);
		if (needRecord[sess] == 4) {
			needRecord[sess] = 5;
			sprintf(buf, "%d%04d", cfrrs[sess].cfrNo, cfrrs[sess].password);
			sprintf(exp->var[13], "T/C=%s Caller No NOIVR NoRecord", buf); 
			return(1);
		}
	}
	needBreak &= 0xffcf;		// disable 16/32
	vxp->branch = 20;			// Goback to monitor conference
	return(1);
}


int	RecCfr()
{
	char	buf[16];

	for (int sess = 0; sess < TotalCfrNo; sess++) {
		if (needRecord[sess] == 2) {
			needRecord[sess] = 3;
			sprintf(buf, "%d%04d", cfrrs[sess].cfrNo, cfrrs[sess].password);
			sprintf(exp->var[13], "T/C=%s Caller No NOIVR Record=./crec/cfr%s", buf, buf); 
			return(1);
		}
	}
	needBreak &= 0xfffe;		// disable 1
	vxp->branch = 20;			// Goback to monitor conference
	return(1);
}

// say that the left minutes is 10, 5, 1... or 'do so when someone hangup
int LftCfr()
{
	char	buf[16];
	int		i, loc;

	for (int sess = 0; sess < TotalCfrNo; sess++) {
		loc = 1;
		if (needSpeak[sess] > 0) {
			// What to say is in exp->cnt[8]
			exp->v[loc++] = exp->cnt[8];				// Say left minutes
			needSpeak[sess] = 0;
		}
		if (needSpeakDongDing[sess] > 0) {
			for (i = 0; i < needSpeakDongDing[sess]; i++) 
				exp->v[loc++] = 2152;				// Say "DongDing" several times
			needSpeakDongDing[sess] = 0;
		}
		if (loc != 1) {
			exp->v[loc] = -1;
			sprintf(buf, "%d%04d", cfrrs[sess].cfrNo, cfrrs[sess].password);
			sprintf(exp->var[13], "T/C=%s Caller No IVR", buf, buf); 
			sprintf(exp->var[14], "T/C=%s Caller No NOIVR", buf, buf);
			return(1);
		}
	}
	needBreak &= 0xfff3;		// Disable 8 and 4.
	vxp->branch = 20;			// Goback to monitor conference
	return(1);
}

// Cancel conference expired on holding time
int	CnCfrE()
{
	int		sess;
	char	message[256], buff[4];

	for (sess = 0; sess < TotalCfrNo; sess++) {
fdbprintf("sess cancel=%d %d\r\n", sess, needCancel[sess]);
		if (needCancel[sess] == 1) {
			needCancel[sess] = 0;
			memset((char *)&cfrr, 0, sizeof(CfrR));
			lseek(cfrrFd, cfrrsLoc[sess], SEEK_SET);			// location to cfrRecord.dat
			write(cfrrFd, (char *)&cfrr, sizeof(CfrR));
			_commit(cfrrFd);
fdbprintf("cfrWrite Over Meeting time cleared\r\n");
			ttabs[sess].year = 0;
			ttabs[sess].password = 0;
			lseek(ttabFd, ttabsLoc[sess], SEEK_SET);
			write(ttabFd, (char *)&ttabs[sess], sizeof(TTab));	// free the meeting 
			write(ttabFd, (char *)&ttabs[sess], sizeof(TTab));
fdbprintf("cfrWrite Cancel2\r\n");
			sprintf(message, 
			  "會議取消通知：原定於%d月%d日%d時，召開之電話會議，因逾時無人參加而取消。特此通知。",
			  cfrrs[sess].mm, cfrrs[sess].dd, cfrrs[sess].hh);
			strcpy(buff, "-");
			sendSM(cfrrs[sess].handset, message, buff, buff, buff);
			return(1);
		}
	}
	needBreak &= 0xfffd;		// disable 2
	vxp->branch = 20;			// Goback to monitor conference
	return(1);
}

//*****************************************************************************
int	VerSo()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return(128);
}

//**********************************************************************************
UAP uap2[]={  
	{"CkFunc",    CkFunc},
	{"CkFwd",	  CkFwd},
	{"CkFwdS",    CkFwdS},
	{"CkFwdt",    CkFwdt},
	{"CkExt",     CkExt},
	{"CkExtS",    CkExtS},
	{"CkExtt",    CkExtt},
	{"CkBack",    CkBack},
	{"CkPstn",    CkPstn},
	{"CkLan",     CkLan},
	{"CanFwd",    CanFwd},
	{"SamFwd",    SamFwd},
	{"RstFwd",    RstFwd},
	{"OpFwd",     OpFwd},
	{"CkRing",    CkRing},
	{"CkPwd" ,    CkPwd },
	{"CkNPwd",    CkNPwd},
	{"CkMess",    CkMess},
	{"SvMess",    SvMess},
	{"SvErr",     SvErr},
	{"RtErrS",    RtErrS},
	{"CkRHld",    CkRHld},
	{"IfAttd",    IfAttd},
	{"IfPwd",     IfPwd},
	{"CkDuty",    CkDuty},
	{"SyDuty",    SyDuty},			// Setting Use
	{"SvDuty",    SvDuty},
	{"GtDuty",    GtDuty},
	{"CkHday",    CkHday},
	{"SvHday",    SvHday},
	{"SyHday",    SyHday},
	{"DlHday",    DlHday},			// Delete Holiday
	{"StDstb",    StDstb},			// Set/Clear/Query disturb
	{"YmtIni",    YmtIni},			// YMT=Yuan2 ma3 tong1
	{"YmtEq",     YmtEq},			// equal
	{"YmtDel",    YmtDel},			// Delete
	{"YmtNR",     YmtNR},			// Not Received Call
	{"YmtNRD",    YmtNRD},			// Not Received call Delete
	{"RtErrY",    RtErrY},			// Sialout Error On drymtx
	{"BalIni",    BalIni},          // Balance Enquiry initialization
	{"CkOts",     CkOts},			// Check before into OTS Service
	{"StPmpt",    StPmpt},			// Set Pre-empt for no-interrupt on play balance
	{"SndSM",     SndSM},			// If Send SM pending, Send SM
	{"CkCfr",     CkCfr},			// If tel conference allowed
	{"CkCfrP",    CkCfrP},			// Check password of cfr
	{"CkCfrD",    CkCfrD},			// Check date of cfr
	{"CkCfrT",    CkCfrT},			// Check time of cfr
	{"CkCfrR",    CkCfrR},			// Check room password of cfr
	{"CkCfr8",    CkCfr8},			// Check enquiry mmdd - mmdd of vfr
	{"MnCfr",     MnCfr},			// monitor conference
	{"CnCfrE",    CnCfrE},			// Cancel conference when expired
	{"CnCfrR",    CnCfrR},			// Cancel Reserved conference
	{"RecCfr",    RecCfr},			// start recording to cfr
	{"LftCfr",    LftCfr},			// 1:left minutes 2:do so on someone hangup.
	{"ByeCfr",    ByeCfr},			
	{"VerSo",     VerSo},
//  {"plyPas" ,   plyPas},
	{"",          NULL}};
/*****************************************************************************/
int uap2_select(char *str)
{
    int i, k;
    for (i=0; uap2[i].name[0]!=0; i++) {
        if (strcmp(str, uap2[i].name) == 0) {
           k=(*uap2[i].func)(/*uap1[i].parm*/);
           return k;
        }
    }
    return -1;
}
       