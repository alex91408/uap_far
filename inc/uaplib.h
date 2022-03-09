enum    {
    GINN_FMT_CONF, GINN_FMT_ADPCM, GINN_FMT_ULAW, GINN_FMT_ALAW,
    GINN_FMT_WAVE_ULAW, GINN_FMT_WAVE_ALAW,
    GINN_FMT_MAX
};

enum    {
    GINN_FNM_MESS, GINN_FNM_VOX, GINN_FNM_ULAW, GINN_FNM_ALAW,
    GINN_FNM_WAVE_ULAW, GINN_FNM_WAVE_ALAW,
    GINN_FNM_MAX
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

extern  ex    exp;    /* for exvar */
extern  exx   exxp;
extern  vx    vxp;    /* for fcontrol */
extern  FUNCPFDB    fdbprintf;

//the follow two line is importent
extern  NFUNCPTR  getFuncPointFromKer;
extern  FUNCSETToKer  setFuncPointToKer;


typedef int   (*FUNCPTPTR)(int,int,int,char *);
typedef int   (*FUNCANTPTR)(int,int,char *);
typedef int   (*FUNCIFMPTR)(char *,char *,int,int);
typedef int   (*FUNCSVPTR)(int,unsigned short *);
typedef int   (*FUNCMITPTR)(long *);
typedef int   (*FUNCLSPTR)(long);
typedef void  (*FUNCCT)(void);
typedef int   (*FUNCWTE)(FUNCPTR);
typedef vx    (*FUNCVXPTR)(int);
typedef ex    (*FUNCEXPTR)(int);
typedef exx   (*FUNCEXXPTR)(int);
typedef int   (*FUNCFXCONV)(int,char *);
typedef void  (*FUNCFXSTLOG)(int);
typedef struct tm *(*FUNCTMPTR)();
typedef char *(*FUNCRPTR)();
//define your own func name got from kernel 



