#include        <cclib.h>
#ifndef _GINN_
#include        "ginn.h"
#endif

enum    ISDN_CAR        {
        IC_NONE, IC_CNCT, IC_BUSY, IC_RING
};

int     ginn_isdnfp(FILE *fp);
int     ginn_initsrl(void);
int     isdn_close(void);
int     isdn_open(int chan, char *fedev);
int     isdn_onhook(void);
int     isdn_wtring(void);
int     isdn_makecall(char *phnum);
int     isdn_car(void);
int     isdn_stopcall(void);
int     isdn_getxmitslot(SC_TSINFO *scts);
int     isdn_listen(SC_TSINFO *scts);
int     isdn_unlisten(void);
int     isdn_hook(void);
int     isdn_dnis(char *p);
int     isdn_ani(char *p);
int     isdn_restart(void);
int     isdn_answercall(void);
int     isdn_inservice(void);
int     isdn_outofservice(void);
