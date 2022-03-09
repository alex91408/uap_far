#define GINN_MSGID      "OTSTECH MESSAGE FILE"
#define GINN_LLONGSTR   16

//#pragma pack(2)

typedef
        struct  {
        char    id[32];
        char    sampling[8];
        char    coding[8];
        char    size[GINN_LLONGSTR];
        char    offset[GINN_LLONGSTR];
        char    length[GINN_LLONGSTR];
        char    title[64];
}       _GINN_MSGHEAD;

typedef
        union   {
        char    rfu[256];
        _GINN_MSGHEAD   mh;
}       GINN_MSGHEAD;

typedef
        struct  {
        char    dig[4];
        int     next;
}       COND;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next;
        int     varno1;
        int     varno2;
        int     functm;
        int     retries;
        COND    cond[20];
        int     varno;
        char    svctrl[4];
        char    remark[32];
}       STRU_101, *stru_101;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     functm;
        int     next1;
        int     next2;
        char    remark[32];
}       STRU_102, *stru_102;

typedef
        struct  {
        int     cmd;
        int     funcno;                /*偵測撥號結果選擇*/ 
        int     next;                  /*撥通跳至行號*/
        char    telno[20];             /*撥號方式--電話號碼*/ 
        int     cntno;                 /*檔案計數器*/
        int     redialno;              /*重撥次數*/
        int     next_noans;            /*無人接聽跳至行號*/
        int     next_busy;             /*忙線跳至行號*/
        int     next_error;            /*錯誤跳至行號*/
        int     next_listend;          /*重撥超過次數跳至行號*/
        int     next_fax;              /*撥入傳真跳至行號*/
        char    remark[32];
}       STRU_108, *stru_108;

typedef                         /* send pages to modem */
        struct  {
        int     cmd;
        int     funcno;
        char    fname[24];
        int     discon;
        int     timeout;
        int     next1;
        int     next2;
        char    remark[32];
}       STRU_110, *stru_110;

typedef                         /* executing a user program */
        struct  {
        int     cmd;
        int     funcno;
        int     next;
        char    userprog[10];
        char    remark1[20];
        char    remark[32];
}       STRU_112, *stru_112;

typedef                         /* enter telephone figure */
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next1;
        int     next2;
        int     ndigs;
        char    termd[4];
        int     rmtermd;
        int     functm;
        int     iddtm;
        int     retries;
        int     varno;
        char    remark[32];
}       STRU_113, *stru_113;

typedef
        struct  {
        int     cmd;
        int     funcno;
        char    prompt[12];
        char    fname[24];
        int     rlen;
        int     rdelay;
        int     nexta;
        int     nextb;
        int     nextc;
        int     nextu1;
        int     nextu2;
        int     nexterr;
        char    remark[32];
}       STRU_117, *stru_117;

typedef                         /* play a synthetyzed message */
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next;
        char    remark[32];
}       STRU_118, *stru_118;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     next1;
        int     next2;
        char    tran[4];
        int     varno1;
        int     varno2;
        char    remark[32];
}       STRU_119, *stru_119;

typedef                                 /* wait host */
        struct  {
        int     cmd;
        int     funcno;
        int     next1;
        int     next2;
        char    tran[4];
        int     varno1;
        int     varno2;
        int     msgno1;
        int     msgno2;
        int     retries;
        char    userprog[10];
        char    remark1[20];
        char    remark[32];
}       STRU_120, *stru_120;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     ohnext;
        int     next;
        char    remark[32];
}       STRU_121, *stru_121;


typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next;
        char    pathname[128];    //80-->128 
        char    remark[32];
}STRU_122, *stru_122;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next;
        char    comment[32];
        char    remark[32];
}       STRU_123, *stru_123;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next1;
        int     next2;
        int     bhour;
        int     bminute;
        int     ehour;
        int     eminute;
        char    remark[32];
}       STRU_124, *stru_124;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     next1;
        int     next2;
        int     varno;
        int     functm;
        int     msgno;
        int     beep;
        char    remark[32];
}       STRU_127, *stru_127;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     next;
        char    remark[32];
}       STRU_129, *stru_129;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next1;
        int     next2;
        int     varno1;
        int     varno2;
        char    str[24];
        char    cmp[4];
        int     length;
        char    remark[32];
}       STRU_131, *stru_131;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next1;
        int     next2;
        int     countno;
        int     value1;
        int     value2;
        int     cmp;
        char    remark[32];
}       STRU_151, *stru_151;

typedef
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;
        int     next;
        int     gotonext;
        char    comment[32];
        int     type;
        char    fname[12];
        char    remark[32];
}       STRU_152, *stru_152;

typedef
        struct  {
        int     cmd;
        int     funcno;
        char    remark[32];
}       STRU_153, *stru_153;

typedef                       //asr ICon
        struct  {
        int     cmd;
        int     funcno;
        int     msgno;      //1-9999
        int     grammar;    //1-25
        int     result;      //1-25
        int     resultnum;  //1-
        int     waittm;     //n sec

        int     succnext;  
        int     noresultnext; 
        int     dtmfnext; 
        int     errornext; 
        int     timeoutnext;       
        int     resbusynext; 

        char    remark[32];
} STRU_201, *stru_201;

typedef
        struct  {
        int     cmd;
}       AP, *ap;


typedef struct
        { int idx;
          int data;
}       FD;


typedef
        struct {
        int     idx;
        int     data;
} DRFDD;

int dropen(DRFDD *fp, char *fname);
int drclose(DRFDD *fp);
int drread(DRFDD *fp,int line_no,char *buf);
