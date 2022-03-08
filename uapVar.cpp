#include <uaplib.h>

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

#if defined(_GINN_UAP_USE_EXP_)
ex exp;
#endif

//the following func is got from kernel
//define them if you want to use
//func type is defined in parprog.h or uaplib.h
FUNCVXPTR   ginn_getvxp;
FUNCEXPTR   ginn_getexp;
FUNCEXXPTR  ginn_getexxp;

FUNCSVPTR   ginn_setexpv;
FUNCANTPTR  ginn_anticipate;
FUNCMITPTR  ginn_getxmitslot;
FUNCMITPTR  voice_getxmitslot;

FUNCLSPTR   ginn_listen;
FUNCLSPTR   voice_listen;
FUNCCT      conv_time;

FUNCPTR     get_comport;
FUNCPTR     get_maxport;
FUNCTMPTR   get_newtime;
FUNCAERR    ibig;

FUNCWTE     ginn_waitevt;

FUNCPTR   wrtlog ;
FUNCPTR   func_writelog;
FUNCPTR   ginn_unlisten ;
FUNCPTR   voice_unlisten ;
FUNCPTR   ginn_playedbytes ;
FUNCPTR   ginn_clrexpvar ;
FUNCPTR   ginn_getrecordfnm ;
FUNCPTR   ginn_answercall ;

FUNCXPTR  play_phrase ;

FUNCXPTR  ginn_setringtm ;
FUNCXPTR  ginn_listenfe ;
FUNCXPTR  ginn_listendx ;
FUNCXPTR  voice_listenfe ;
FUNCXPTR  voice_listendx ;
FUNCXPTR  ginn_clrexpvarbyuser ;
FUNCXPTR  ginn_setautoanswer ;
FUNCXPTR  ginn_setplayfmtabs ;
FUNCXPTR  ginn_setpreferedfnm ;
FUNCXPTR  ginn_setrecordfnm ;
FUNCXPTR  ginn_setchkoldmsgheader ;

FUNCCPTR  ifx;
FUNCCPTR  bnam;
FUNCCPTR  ginn_bnam;

FUNCPTPTR play_tone;
FUNCIFMPTR  ifm;

FUNCPTR   asrCheck;
FUNCAERR  get_AsrErrcode ;
FUNCAERR  set_AsrRecFilename;
FUNCASRRECP get_AsrRecPath;
FUNCASRRECP get_AsrRecFilename;
FUNCASRRECP get_AsrRecFormat;
FUNCASRRECRES  get_AsrRecResult  ;

FUNCPTR   ginn_outofservice;  //20040206
FUNCXPTR  ginn_setbranch;
FUNCPTR   ginn_clrbranch;
FUNCPTR   ginn_getbranch;
FUNCPTR  	ginn_gettoneidx;
FUNCAERR  ginn_ani;
FUNCAERR  ginn_dnis;

FUNCXPTR  ginn_setusetmpsynth;
FUNCAERR  ginn_setsynthext;
FUNCXPTR  ginn_setsynthplayfmt;


//for fax

FUNCPTR		fax_check;
FUNCPTR		ginn_fxopen;
FUNCPTR		ginn_fxclose;
FUNCXPTR  ginn_fxinitstat;
FUNCXPTR  ginn_fxsetrxcoding;
FUNCXPTR  ginn_fxsettxcoding;
FUNCXPTR	ginn_fxsethdrattrib;
FUNCAERR	ginn_fxsethdruser;
FUNCAERR  ginn_fxgetremoteid;
FUNCAERR	ginn_fxsetlocalid;
FUNCPTR   ginn_fxgettxbaudrate;
FUNCPTR   ginn_fxgetrxbaudrate;	
FUNCXPTR  ginn_fxsettxbaudrate;
FUNCXPTR  ginn_fxsetrxbaudrate;
FUNCXPTR  ginn_fxsettfpgbase;
FUNCXPTR  ginn_fxsetsendcont;
FUNCXPTR  ginn_fxsetevttout;
FUNCPTR   ginn_fxgetpagecount;
FUNCPTR   ginn_fxgetlasterr;
FUNCPTR   ginn_fxgetestat;
FUNCFXSR	ginn_fxrecvex;
FUNCFXSR	ginn_fxrecv;
FUNCPTR   ginn_fxclrsendlist;
FUNCFXSR  ginn_fxadd2sendlistex;
FUNCAERR  ginn_fxadd2sendlist;
FUNCPTR   ginn_fxgetsendlistcount;
FUNCXPTR	ginn_fxsendex;	
FUNCXPTR	ginn_fxsend;
FUNCFXSTLOG   set_fxconvlog;

FUNCXPTR  ginn_faxopenfxt;
FUNCAERR  ginn_fxtaddline;
FUNCXPTR  ginn_fxtaddform;
FUNCPTR   ginn_fxtnewpage;
FUNCAERR  ginn_fxtsetvar;
FUNCPTR   ginn_faxclosefxt;
FUNCFXCONV  ginn_faxconvertfxt;

//the following func is defined in uap and called by kernal
//give them function point which you define or give them NULL

//FUNCPTR   _uap_check_play = NULL;
//FUNCPTR   _uap_check_dial = NULL ;
//FUNCPTR   _uap_check_rec  = NULL ;
//FUNCPTR   _uap_check_wtring  = NULL ;
//FUNCPTR   _uap_check_tone = NULL ;
//FUNCPTR   _uap_check_dtmf =NULL;
//FUNCPTR   _uap_play_end = NULL;
//FUNCXPTR  _uap_receive_dtmf = NULL;
//FUNCFXSR   _uap_invalidApBranch = NULL;

int init_get_funcpt()
{
#if defined(_GINN_UAP_USE_EXP_)
  exp = exVar;
#endif  
  ginn_setexpv      = (FUNCSVPTR)getFuncPointFromKer("ginn_setexpv");

  ginn_anticipate   = (FUNCANTPTR)getFuncPointFromKer("ginn_anticipate");

  ginn_getxmitslot  = (FUNCMITPTR)getFuncPointFromKer("ginn_getxmitslot");

  voice_getxmitslot = (FUNCMITPTR)getFuncPointFromKer("voice_getxmitslot");

  ginn_listen       = (FUNCLSPTR)getFuncPointFromKer("ginn_listen");

  voice_listen      = (FUNCLSPTR)getFuncPointFromKer("voice_listen");

  ginn_getvxp       = (FUNCVXPTR)getFuncPointFromKer("ginn_getvxp");

  ginn_getexp       = (FUNCEXPTR)getFuncPointFromKer("ginn_getexp");

  ginn_getexxp      = (FUNCEXXPTR)getFuncPointFromKer("ginn_getexxp");

  ginn_waitevt      = (FUNCWTE)getFuncPointFromKer("ginn_waitevt");

  wrtlog            = (FUNCPTR)getFuncPointFromKer("wrtlog");

  ginn_unlisten     = (FUNCPTR)getFuncPointFromKer("ginn_unlisten");

  voice_unlisten    = (FUNCPTR)getFuncPointFromKer("voice_unlisten");

  ginn_playedbytes  = (FUNCPTR)getFuncPointFromKer("ginn_playedbytes");

  ginn_clrexpvar    = (FUNCPTR)getFuncPointFromKer("ginn_clrexpvar");

  ginn_getrecordfnm = (FUNCPTR)getFuncPointFromKer("ginn_getrecordfnm") ;

  ginn_answercall   = (FUNCPTR)getFuncPointFromKer("ginn_answercall");


  play_phrase       = (FUNCXPTR)getFuncPointFromKer("play_phrase");

  ginn_setringtm    = (FUNCXPTR)getFuncPointFromKer("ginn_setringtm");

  ginn_listenfe     = (FUNCXPTR)getFuncPointFromKer("ginn_listenfe");

  ginn_listendx     = (FUNCXPTR)getFuncPointFromKer("ginn_listendx");

  voice_listenfe    = (FUNCXPTR)getFuncPointFromKer("voice_listenfe");

  voice_listendx    = (FUNCXPTR)getFuncPointFromKer("voice_listendx");

  ginn_clrexpvarbyuser = (FUNCXPTR)getFuncPointFromKer("ginn_clrexpvarbyuser");

  ginn_setautoanswer   = (FUNCXPTR)getFuncPointFromKer("ginn_setautoanswer");

  ginn_setplayfmtabs   = (FUNCXPTR)getFuncPointFromKer("ginn_setplayfmtabs");

  ginn_setpreferedfnm  = (FUNCXPTR)getFuncPointFromKer("ginn_setpreferedfnm");

  ginn_setrecordfnm    = (FUNCXPTR)getFuncPointFromKer("ginn_setrecordfnm");

  ginn_setchkoldmsgheader = (FUNCXPTR)getFuncPointFromKer("ginn_setchkoldmsgheader");


  ifx       = (FUNCCPTR)getFuncPointFromKer("ifx");

  bnam      = (FUNCCPTR)getFuncPointFromKer("bnam");

  ginn_bnam = (FUNCCPTR)getFuncPointFromKer("ginn_bnam");


  play_tone = (FUNCPTPTR)getFuncPointFromKer("play_tone");


  ifm       = (FUNCIFMPTR)getFuncPointFromKer("ifm");


  conv_time = (FUNCCT)getFuncPointFromKer("conv_time");

 get_comport= (FUNCPTR)getFuncPointFromKer("get_comport");
  get_maxport= (FUNCPTR)getFuncPointFromKer("get_maxport");
get_newtime = (FUNCTMPTR)getFuncPointFromKer("get_newtime");
  ibig      = (FUNCAERR)getFuncPointFromKer("ibig");

  get_AsrErrcode = (FUNCAERR)getFuncPointFromKer("get_asrerrCode");

  asrCheck  = (FUNCPTR)getFuncPointFromKer("asrCheck");

  ginn_outofservice = (FUNCPTR)getFuncPointFromKer("ginn_outofservice");

  ginn_setbranch    = (FUNCXPTR)getFuncPointFromKer("ginn_setbranch");
  ginn_clrbranch    = (FUNCPTR)getFuncPointFromKer("ginn_clrbranch");
  ginn_getbranch    = (FUNCPTR)getFuncPointFromKer("ginn_getbranch");
  ginn_gettoneidx   = (FUNCPTR)getFuncPointFromKer("ginn_gettoneidx");
  ginn_ani          = (FUNCAERR)getFuncPointFromKer("ginn_ani");
  ginn_dnis         = (FUNCAERR)getFuncPointFromKer("ginn_dnis");


  ginn_setusetmpsynth  =(FUNCXPTR)getFuncPointFromKer("ginn_setusetmpsynth");
  ginn_setsynthext  = (FUNCAERR)getFuncPointFromKer("ginn_setsynthext");
  ginn_setsynthplayfmt  = (FUNCXPTR)getFuncPointFromKer("ginn_setsynthplayfmt");
//for fax func
  fax_check         = (FUNCPTR)getFuncPointFromKer("fax_check");
	ginn_fxopen       = (FUNCPTR)getFuncPointFromKer("ginn_fxopen");
	ginn_fxclose      = (FUNCPTR)getFuncPointFromKer("ginn_fxclose");
	ginn_fxinitstat   = (FUNCXPTR)getFuncPointFromKer("ginn_fxinitstat");
	ginn_fxsetrxcoding = (FUNCXPTR)getFuncPointFromKer("ginn_fxsetrxcoding");
	ginn_fxsettxcoding = (FUNCXPTR)getFuncPointFromKer("ginn_fxsettxcoding");
	ginn_fxsethdrattrib = (FUNCXPTR)getFuncPointFromKer("ginn_fxsethdrattrib");
	ginn_fxsethdruser = (FUNCAERR)getFuncPointFromKer("ginn_fxsethdruser");	
	ginn_fxgetremoteid = (FUNCAERR)getFuncPointFromKer("ginn_fxgetremoteid");
	ginn_fxsetlocalid = (FUNCAERR)getFuncPointFromKer("ginn_fxsetlocalid");	
	ginn_fxgettxbaudrate = (FUNCPTR)getFuncPointFromKer("ginn_fxgettxbaudrate");
	ginn_fxgetrxbaudrate = (FUNCPTR)getFuncPointFromKer("ginn_fxgetrxbaudrate");
	ginn_fxsettxbaudrate = (FUNCXPTR)getFuncPointFromKer("ginn_fxsettxbaudrate");
	ginn_fxsetrxbaudrate = (FUNCXPTR)getFuncPointFromKer("ginn_fxsetrxbaudrate");
	ginn_fxsettfpgbase = (FUNCXPTR)getFuncPointFromKer("ginn_fxsettfpgbase");
	ginn_fxsetsendcont = (FUNCXPTR)getFuncPointFromKer("ginn_fxsetsendcont");
  ginn_fxsetevttout = (FUNCXPTR)getFuncPointFromKer("ginn_fxsetevttout");
  ginn_fxgetpagecount = (FUNCPTR)getFuncPointFromKer("ginn_fxgetpagecount");
	ginn_fxgetlasterr = (FUNCPTR)getFuncPointFromKer("ginn_fxgetlasterr");
  ginn_fxgetestat     = (FUNCPTR)getFuncPointFromKer("ginn_fxgetestat");
	ginn_fxrecvex     = (FUNCFXSR)getFuncPointFromKer("ginn_fxrecvex");
	ginn_fxrecv       = (FUNCFXSR)getFuncPointFromKer("ginn_fxrecv");
  ginn_fxclrsendlist  = (FUNCPTR) getFuncPointFromKer("ginn_fxclrsendlist");
	ginn_fxadd2sendlistex = (FUNCFXSR)getFuncPointFromKer("ginn_fxadd2sendlistex");
  ginn_fxadd2sendlist = (FUNCAERR)getFuncPointFromKer("ginn_fxadd2sendlist");
	ginn_fxgetsendlistcount = (FUNCPTR)getFuncPointFromKer("ginn_fxgetsendlistcount");
	ginn_fxsendex     = (FUNCXPTR)getFuncPointFromKer("ginn_fxsendex");
	ginn_fxsend       = (FUNCXPTR)getFuncPointFromKer("ginn_fxsend");
  set_fxconvlog       = (FUNCFXSTLOG)getFuncPointFromKer("set_fxconvlog");

	ginn_faxopenfxt     = (FUNCXPTR)getFuncPointFromKer("ginn_faxopenfxt");
  ginn_fxtaddline     = (FUNCAERR)getFuncPointFromKer("ginn_fxtaddline");
  ginn_fxtaddform     = (FUNCXPTR)getFuncPointFromKer("ginn_fxtaddform");
  ginn_fxtnewpage     = (FUNCPTR)getFuncPointFromKer("ginn_fxtnewpage");
  ginn_fxtsetvar      = (FUNCAERR)getFuncPointFromKer("ginn_fxtsetvar");
  ginn_faxclosefxt    = (FUNCPTR)getFuncPointFromKer("ginn_faxclosefxt");
  ginn_faxconvertfxt  = (FUNCFXCONV)getFuncPointFromKer("ginn_faxconvertfxt");

  set_AsrRecFilename  = (FUNCAERR)getFuncPointFromKer("_set_AsrRecFilename");
  get_AsrRecResult    = (FUNCASRRECRES)getFuncPointFromKer("_get_AsrRecResult");

 //fax end

 // get_fdial_addp      = (FUNCRPTR)getFuncPointFromKer("get_fdial_addp");
  return 0;
}

// sample init_set_funcpt()
/* 
int init_set_funcpt()
{
  setFuncPointToKer("_uap_check_play",NULL); //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_check_dial",NULL); //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_check_rec",NULL);  //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_check_wtring",NULL); //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_check_tone",NULL);  //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_check_dtmf",NULL); //(NFUNCPTR)aa);
  setFuncPointToKer("_uap_play_end",NULL);  //(NFUNCPTR)aa1);
  setFuncPointToKer("_uap_receive_dtmf",(NFUNCPTR)recdt); //(NFUNCPTR)aa);
  setFuncPointToKer("_set_AsrRecSta",(NFUNCPTR)setAsrRecSta);
//  setFuncPointToKer("func_writelog",(NFUNCPTR)wtlog);
  //setFuncPointToKer("_uap_invalidApBranch", (NFUNCPTR)((FUNCFXSR)NULL)); 
  setFuncPointToKer("_uap_invalidApBranch", (NFUNCPTR)invalidApBranchHandler);

  return 0;
}
*/