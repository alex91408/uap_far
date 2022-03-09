#define	GINN_CONFPATH	"conf"
#define	GINN_BINPATH	"bin"
#define DBGPATH       "dbg"
#define TROL_SERPATH   "serv"

typedef struct {
   char apn[8];     /* AP name without 'dr' */
   char mpa[20];    /* message path */
   char kxn[10];     /* kxxxx file for telephone parameter */
   char log[26];    /* path and name for logging */
   char drn[4];     /* V:drintv64 M0,M1,M2:drfaxm64 D:datxxx H:hotxxx */
   char ast[2];        /* 1:auto start   0:no start   */
   char rst[2];        /* 1:auto restart 0:no restart */
   char typ[2];        /* 0:telephone, 1:E1, 2:T1     */
   char fill[80];
} CONF, *conf;

typedef struct {
   char mxln[4];     /* total line No. in the system */
   char vapn[2];     /* 1-9: load systh1-9 header to shm,  0: not load */
   char vrsn[2];     /* version number */
   char show[2];     /* 1: show telephone entered 0:not show */
   char lang[10];    /* lanquage file for directive */
   char apth[20];    /* AP path */
   char appn[8];     /* AP name for default */
   char mpth[20];    /* message file path for default */
   char kxxx[10];    /* kxxxxx for default */
   char dbname[16];  /* debug name for trol */
   char setno[2];    /* set number of system */
   char AD_deduct[4]; /* Deduct from A.D. year. 1911 for Chinese year */
   char sv_log[4];    /* save logfile months */
   char bill_log[2];  /* log format is done by user */
   char messhead[2];  /* 1:need messhead 0:no need */
   char rpname[20];   /* report program on trol */
   char comln[4];     /* The exp of the line is used for Common Global area */
   char beep[2];      /* 0:beep on error message 1:No beep */
   int  exbeg;        /* Begin code for user-defined Chinese (for IBM etc.) */
   int  exend;        /* End code for user-defined Chinese code */
   int  exbeg5;       /* Begin code for user-defined BIG5 code */
   int  exend5;       /* End code for user-defined BIG5 code */
   char font[2];      /* 0:Space 0x2020 1:Square 0xa1bc */
   char cfont[2];     // 0:Big5 1:Chinese
   char abort[2];     // 1:Abort Without T,1
   char fill[24];
} CONF0, *conf0;

