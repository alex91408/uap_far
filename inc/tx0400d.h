#include        "daa_nt.h"
#include        "v2761_nt.h"
#include        "switchnt.h"

typedef  int (*TYFUNCPTR)(void);

typedef int     (*TSYN_FULLDUPLEXP)(int seqNo, char *ptr, int len);

enum    TSYN_CAR        {
        IC_NONE, IC_CNCT, IC_BUSY, IC_RING, IC_NOANS, IC_NODIALTONE, IC_FAXTONE
};


extern  int     _ginn_appenddig(char *p);
extern  int     tsyn_voiceListen(int ts);
extern  int     tsyn_voiceUnListen();
extern  int     tsyn_daaListen(int ts);
extern  int     tsyn_daaUnListen();
extern  int     tsyn_hangUp(int cause);
extern  int     tsyn_waitEvent(int timeOut);
extern  int     tsyn_startDriver(int chan, char *dxDevice, char *feDevice);
extern  int     tsyn_remoteHangUpDetection(int flag);
extern  int     tsyn_stopDriver();
extern  int     tsyn_makeCall(char *dialNumber, int detectLcon);
extern  int     tsyn_blindDial(char *dialNumber);
extern  int     tsyn_onHook();
extern  int     tsyn_clearDigits();
extern  int     tsyn_stopChannel();
extern  int     tsyn_getDtmf(char *digitBuffer, unsigned int maxDigits, int iddTime, char *termd);
extern  int     tsyn_playf(char *fileName, char *termd, int clrDtmf);
extern  int     tsyn_recordf(char *fileName, unsigned int recTime, char *termd, int beep);
extern  int     tsyn_getAsyncFuncActiveVoice();
extern  void    tsyn_setWaitTime(int waitTime);
extern  int     tsyn_callProgress(int flag);
extern  int     tsyn_car();
extern  int     tsyn_playx(char *fileName, char *termd, int counter, TYFUNCPTR cfunc);
extern  int     tsyn_getRingEvent();
extern  void    tsyn_setFlashTime1(int value);
extern  void    tsyn_setPlayGain(int value);
extern  void    tsyn_setRecordGain(int value);
extern  int     tsyn_getXmitSlotDAA(long *ts);
extern  void    tsyn_setPauseTime(int value);
extern  int     tsyn_getXmitSlotVoice(long *ts);
extern  int     tsyn_offHook();
extern  int     tsyn_check_digitbuf();