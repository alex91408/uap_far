#define _TXT2TIFF_FONTPATH      "./pbm/font"
#define _TXT2TIFF_BIG5UNIC      "./pbm/font/big5unic.dat"
#define _TXT2TIFF_PBM2G3        "./pbm/bin/pbm2g3"
#define _TXT2TIFF_FAX2TIFF      "./pbm/bin/g32tiff"
#define _TXT2TIFF_FAX2TIFFOPT   "-M -1 -m"
#define _TXT2TIFF_ACTION        WPBM_TXT2TIFF

#define GINN_FAXFORM            "./faxm/form%04d.txt"
#define GINN_FAXFXT             "./faxm/%03d_%04d.fxt"
#define GINN_FAXDXT             "./faxm/%03d_%04d.dxt"
#define GINN_FAXTIFF            "./faxm/%03d_%04d.tif"

#define  GINN_VAR_LEN            128  //20 //128
#define  GINN_CHAIN_LEN          2560
#define  GINN_VBUF_LEN           448  //keep sizeof(EX) <= 4096 bytes (4K);    


typedef int  (*FUNCPTR)(void);
typedef int  (*FUNCXPTR)(int);
typedef void  (*FUNCPFDB)(const char *fmt,...);
typedef int  (*FUNCCPTR)(char *,int,int);
typedef int  (*FUNCAERR)(char *);

typedef char * (*FUNCASRRECP)(void);

typedef int (*ASRSETFUNCPTR)(const int line,const int nBest, const char *grammar,const char * law,const int bargein,int *pos);
typedef int (*ASRCHKFUNCPTR)(char *result, int *rc,char *rcMes);
typedef int (*ASRCBKFUNCPTR)(const int line, char *buf, int length);


typedef FUNCPTR (*NFUNCPTR)(char *);
typedef void (*FUNCSETToKer)(char *,NFUNCPTR );

typedef int (*FUNCFXSR)(char *,int);

typedef int (*FUNCASRRECSTA)(int,int);
typedef int (*FUNCASRRECRES)(char *,char *,char *);

typedef struct fp {
  NFUNCPTR      getFuncPt;
  FUNCSETToKer  getFuncPtFromUap;
} FuncPoint;
 
typedef struct parpr 
{
	char data[32];
	char var[26][GINN_VAR_LEN];
	char fillr[GINN_CHAIN_LEN-GINN_VAR_LEN]; 
	int  cnt[10];
  int  vcnt;
  unsigned short  *v;  //20030901
  unsigned short vbuf[GINN_VBUF_LEN+2];  // postion v[0] reserved, position v[GINN_VBUF_LEN+1] for -1
	char etran[4];
	char esync;
	char fil1[3];
	int  evdeb;
	int  evfin;
	char eemis;   
	char rtran[4];
	char rsync;  
	char fil2[2];
	int  rvdeb; 
	int  rvfin; 
	char remis; 
	char fil3[3];
	int  dialinfo1;     /* reason dialout returned */
	int  dialinfo2;	    /* frequncy meet when return intercept */
	int  dialinfo3;     /* retry counter 0,1,2 */
	int  dialinfo4;
	int  dialinfo5;
	FuncPoint  fup;
  long  fets;
  long  dxts;
  char    _ginn_rfu[244];
} EX, *ex;

typedef struct parpr1 {
	char data[32];
  char var[25][GINN_VAR_LEN];  //[25][20]
  char chain[GINN_CHAIN_LEN];   //2560
	char fill[sizeof(EX) - (32+25*GINN_VAR_LEN+GINN_CHAIN_LEN)];  //3092
} EXX, *exx;


#define ex_size sizeof(EX)       
#define ex_key  42

typedef struct {
        char    *name;
        int     (*func)();
        int     parm;
} UAP;
