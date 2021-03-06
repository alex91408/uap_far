extern  FUNCPFDB    fdbprintf;

extern  FUNCVXPTR   ginn_getvxp;
extern  FUNCEXPTR   ginn_getexp;
extern  FUNCEXXPTR  ginn_getexxp;

extern  FUNCSVPTR   ginn_setexpv;
extern  FUNCANTPTR  ginn_anticipate;
extern  FUNCMITPTR  ginn_getxmitslot;
extern  FUNCMITPTR  voice_getxmitslot;

extern  FUNCLSPTR   ginn_listen;
extern  FUNCLSPTR   voice_listen;
extern  FUNCCT      conv_time;

extern	FUNCPTR     get_comport;
extern	FUNCTMPTR   get_newtime;
extern	FUNCAERR    ibig;

extern  FUNCWTE     ginn_waitevt;

extern  FUNCPTR   wrtlog ;
extern	FUNCPTR   func_writelog;
extern  FUNCPTR   outofservice ;
extern  FUNCPTR   ginn_unlisten ;
extern  FUNCPTR   voice_unlisten ;
extern  FUNCPTR   ginn_playedbytes ;
extern  FUNCPTR   ginn_clrexpvar ;
extern  FUNCPTR   ginn_getrecordfnm ;
extern  FUNCPTR   ginn_answercall ;

extern  FUNCXPTR  play_phrase ;

extern  FUNCXPTR  ginn_setringtm ;
extern  FUNCXPTR  ginn_listenfe ;
extern  FUNCXPTR  ginn_listendx ;
extern  FUNCXPTR  voice_listenfe ;
extern  FUNCXPTR  voice_listendx ;  
extern  FUNCXPTR  ginn_clrexpvarbyuser ; 
extern  FUNCXPTR  ginn_setautoanswer ;
extern  FUNCXPTR  ginn_setplayfmtabs ;
extern  FUNCXPTR  ginn_setpreferedfnm ;
extern  FUNCXPTR  ginn_setrecordfnm ;
extern  FUNCXPTR  ginn_setchkoldmsgheader ;

extern  FUNCCPTR  ifx;
extern  FUNCCPTR  bnam;
extern  FUNCCPTR  ginn_bnam;

extern  FUNCPTPTR play_tone;
extern  FUNCIFMPTR  ifm;

extern	FUNCPTR   asrCheck;
extern	FUNCAERR  get_AsrErrcode ;

extern  FUNCXPTR  ginn_setbranch;
extern  FUNCPTR   ginn_gettoneidx;

//for fax
extern	FUNCPTR	  fax_check;
extern	FUNCPTR	  ginn_fxopen;
extern	FUNCPTR	  ginn_fxclose;
extern	FUNCFXSR  ginn_fxrecv;
extern	FUNCAERR  ginn_fxadd2sendlist;
extern  FUNCPTR   ginn_fxclrsendlist ;
extern	FUNCXPTR  ginn_fxsend;
extern	FUNCXPTR  ginn_fxsethdrattrib;    
extern	FUNCAERR  ginn_fxsethdruser;
extern	FUNCAERR  ginn_fxsetlocalid;
extern	FUNCXPTR  ginn_fxsetevttout;
extern	FUNCPTR   ginn_fxgetpagecount;
extern	FUNCPTR   ginn_fxgetestat;
extern  FUNCFXCONV    ginn_faxconvert;

extern  FUNCPTR   _uap_check_play ;
extern  FUNCPTR   _uap_check_dial ;
extern  FUNCPTR   _uap_check_rec ;
extern  FUNCPTR   _uap_check_wtring ;
extern  FUNCPTR   _uap_check_tone ;
extern  FUNCPTR   _uap_check_dtmf ;
extern  FUNCPTR   _uap_play_end ;