#ifndef _GINN_
#include        "ginn.h"
#endif

enum    T1_CAR          {
        IC_NONE, IC_CNCT, IC_BUSY, IC_RING
};

int     ginn_t1fp(FILE *fp);
//int     ginn_initsrl(void);
int     t1_close(void);
int     t1_open(int chan, char *fedev);
int     t1_makecall(char *phnum);
int     t1_car(void);
int     t1_stopcall(void);
int     t1_wtring(void);
int     t1_answercall(void);
int     t1_onhook(void);
int     t1_getxmitslot(SC_TSINFO *scts);
int     _t1_listen(long ts);
int     t1_listen(SC_TSINFO *scts);
int     t1_unlisten(void);
int     t1_dnis(char *p);
int     t1_ani(char *p);
int      t1_inservice(void);
int     t1_outofservice(void);
