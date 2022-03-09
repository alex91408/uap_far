#include "fcontrol.h"
#include "parprog.h"
#include "otsconf.h"
#include "app.h"
#include "apgen.h"
#include "dialhead.h"

#define  KER_PRINT      1
#define GINN_MAXDTMF    4096
#define  _GINN_USEXPB_

#ifndef TX0400D
#define GINN_CHANFILE   "./channel.prm"
#else 
#define GINN_CHANFILE   "./channel.telprm"
#endif
#define	GINN_FXEVTTOUT		180
#define	GINN_MINFXEVTTOUT	60
#define	GINN_MAXSENDLIST	10
#define	GINN_L_SYNTHEXT		16

enum    {
        GINN_ERROR = -1, GINN_NONE, GINN_DTI, GINN_AG
};

typedef int     (*GINN_FUNCPTR)(void);
typedef int     (*GINN_STREAMPTR)(char *, int);
typedef GINN_FUNCPTR    (*GINN_SELCHKHOST)(char *);

enum    {
        GINN_TN_NONE, GINN_TN_BUSY, GINN_TN_SPECIAL
};

enum    {
        GINN_SDC_NONE, GINN_SDC_TONEON, GINN_SDC_TONEOFF, GINN_SDC_TASKFAIL,
        GINN_SDC_DISCONNECTED, GINN_SDC_ABITON, GINN_SDC_ABITOFF,
        GINN_SDC_BBITON, GINN_SDC_BBITOFF, GINN_SDC_TN_BUSY,
        GINN_SDC_TN_SPECIAL, GINN_SDC_LCOFF, GINN_SDC_REMOTEHANGUP,
        GINN_SDC_MAXSDC,GINN_SDC_TN_DTMF
};

enum    {
        GINN_FMT_CONFMESS, GINN_FMT_ADPCM, GINN_FMT_ULAW, GINN_FMT_ALAW,
        GINN_FMT_WAVE_ULAW, GINN_FMT_WAVE_ALAW, GINN_FMT_CONFSYNTH,
        GINN_FMT_MAX
};

enum    {
        GINN_FNM_MESS, GINN_FNM_VOX, GINN_FNM_ULAW, GINN_FNM_ALAW,
        GINN_FNM_WAVE_ULAW, GINN_FNM_WAVE_ALAW,
        GINN_FNM_MAX
};

enum    {
        GCF_NONE, GCF_DTMF, GCF_RESULT, GCF_CSPINIT, GCF_CSPEND,
        GCF_MAX
};

enum    {
        GINN_CR_NONE, GINN_CR_BUSY, GINN_CR_NOANS, GINN_CR_NORB, GINN_CR_CNCT,
        GINN_CR_CEPT, GINN_CR_STOPD, GINN_CR_NODIALTONE, GINN_CR_FAXTONE,
        GINN_CR_ERROR,GINN_CR_UNKNOWN,GINN_CR_MAXCR
};

enum    {
        GINN_FX_HDRDISABLE, GINN_FX_HDRFMT1, GINN_FX_HDRFMT2,
        GINN_FX_MAXFX
};

enum	{
	GINN_FT_NORMAL, GINN_FT_VOICEREQ, GINN_FT_ERROR, GINN_FT_ABORT, 
	GINN_FT_EVTTOUT, GINN_FT_TIMEOUT,
	GINN_FT_MAXFT
};

extern  vx      vxp;
extern  ex      exp;
extern  ex      comp;
extern  exx     exxp;
extern  CONF    cf;
extern  CONF0   cf0;
extern  char    devnam[];
extern  int     erfd;
extern  CHANNEL chn;          /* for AP work file */
extern  FILE    *fdbfd;
extern  FILE    *dbg_fdbfd;
extern  struct  tm      *tm;
extern  long    lt;
extern  char    etab_buff[];
extern  char    host_buff[];
extern  int     wlog_pend;   /* 0 No pending, 1:pending 2:clear out */
extern  char    ckbuff[];
extern  int     ad_deduct;
extern  VTAB    vap1;
extern  vtab    vtabp;               /* for vap file */
extern  int     hup_stat;
extern  DRFDD   drfd;  /* for open drxxx AP file */

extern  char    ginn_drn[], ginn_typ[];
extern  char    ginn_callingpn[];
extern  FUNCPTR    _uap_check_wtring;
extern  FUNCPTR    _uap_check_play;
extern  FUNCPTR    _uap_check_dial;
extern  FUNCPTR    _uap_check_rec;
extern  FUNCPTR    _uap_check_tone;
extern  FUNCPTR    _uap_check_dtmf;
extern  FUNCPTR    _uap_play_end;
//extern  FUNCPTR   _uap_fdial_check;
extern  FUNCXPTR   _uap_receive_dtmf;
extern  NFUNCPTR    _uap_host_check;

extern  GINN_SELCHKHOST ginn_selchkhostp;
extern  GINN_FUNCPTR    ginn_cstfuncp;


void    conv_time(void);
int     v_playf(char *fname, char *termd, int clrdig, short vol_adj);

int     _ginn_hangup(void);
int     ginn_anticipate(int func, int next, char *p);
int     ginn_stopdx(int cause);
int     ginn_getxmitslot(long *ts);
int     ginn_listen(long ts);
int     ginn_unlisten(void);
int     ginn_dnis(char *p);
int     ginn_ani(char *p);
int		ginn_getStringBuf(char *p);
int     ginn_inservice(void);
int     ginn_outofservice(void);
int     voice_getxmitslot(long *ts);
int     voice_listen(long ts);
int     voice_unlisten(void);
int     ginn_setcallingpn(char *p);
int     ginn_answercall(void);
int     ginn_playedbytes(void);
int     ginn_getdtmflen(void);
int     ginn_getdtmfbuf(char *p);
int     ginn_clrdtmfbuf(void);
int     ginn_clrcallend(void);
int     ginn_setcallend(int cause);
int     ginn_getcallend(void);
int     ginn_gettoneidx(void);
void    ginn_clrtoneidx(void);
int     ginn_clrbranch(void);
int     ginn_setbranch(int branch);
int     ginn_getbranch(void);
int     ginn_setringtm(int tm);
int     ginn_setexpv(int vcnt, unsigned short *v);
int     ginn_listenfe(int voie);
int     ginn_listendx(int voie);
int     voice_listenfe(int voie);
int     voice_listendx(int voie);

int     ginn_waitevt(GINN_FUNCPTR p);
int     ginn_clrexpvarbyuser(int flag);
int     ginn_clrexpvar(void);
int     ginn_setAA(int autoanswer_flag);
int     ginn_anticipate(int func, int next, char *p);
int     ginn_setautoanswer(int autoanswer_flag);
int     ginn_setplayfmtabs(int fmt);
int     ginn_setpreferedfnm(int fnm);
int     ginn_getrecordmode(void);
int     ginn_getrecordfnm(void);
int     ginn_setrecordfnm(int fnm);
int     ginn_setchkoldmsgheader(int flag);
int     ginn_cspfunc(int messno, int len, char *grammar, char *result);
int     ginn_setexpv(int vcnt, unsigned short *v);
int     ginn_closetmpsynthfd();
int     ginn_setplaymode(int mode);

int     ginn_fxopen();
int     ginn_fxclose();
int     ginn_fxsethdrattrib(int attrib);
int     ginn_fxsethdruser(char *p);
int     ginn_fxsetlocalid(char *p);
int 	  ginn_fxsetevttout(int);
int	    ginn_fxgetpagecount(void);
int	    ginn_fxgetestat(void);
int     ginn_fxrecv(char *fname, int vrq);
int		  fax_check();
int     ginn_fxclrsendlist(void);
int     ginn_fxadd2sendlist(char *fname);
int     ginn_fxsend(int vrq);
int     ginn_faxconvert(int form, char *tiff);
void    set_fxconvlog(int log);