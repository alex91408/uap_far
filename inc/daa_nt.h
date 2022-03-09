//
//  MODULE:   daa_nt.h
//
//  PURPOSE:
//    Contains declarations for use by applications and other DLLs that
//    link to this DLL.  It is not used to build the DLL itself.
//


#ifndef INC_DLLSKEL_H
#define INC_DLLSKEL_H
#endif	// INC_DLLSKEL_H

#include <windows.h>

#define DLLIMPORT __declspec(dllimport)

/***************************************
 * Result Codes (Event Code)	       *
 ***************************************/
#define NOEVENT 	0x00		//Event Queue Empty
#define LSTOP		0x03		//Line Stop from Application
#define OFFHC		0x08		//Offhook Complete Event
#define DIALCMPL	0x09		//'Dial' Complete Event
#define ONHC		0x0E		//Onhook Complete Event
#define CALLPROG	0x12		//Call Progress Report
#define SIGNALIN	0x14		//Signal incoming
#define RINGR		0x15		//Rings Received Event
#define RINGOFF 	0x16		//Rings Off Event
#define CALLERID	0x17		//Caller ID Received Event
#define LOOPCON 	0x24
#define LOOPCOFF	0x25
#define DIALTONE	0x31		//dialtone detected
#define BUSYTONE	0x32		//busy tone detected
#define VOICETONE	0x33		//voice detected
#define RINGBTONE	0x34		//ringbacktone detected
#define NODIALTONE	0x35		//no dial tone detected
#define REMOTEHANGUP	0x36		//remote hang up detected
#define ANSWERTONE	0x37		//B.B. call tone detected
#define PAGERTONE	0x37		//pager tone detected
#define POLECHANGE	0x38		//pole-change detected
#define FAXCALLTONE	0x3B		//fax calling tone
#define CEDTONE 	0x40		//ced tone detected
#define USERTONE1	0x51		//user define tone 1
#define USERTONE2	0x52		//user define tone 2
#define USERTONE3	0x53		//user define tone 3
#define USERTONE4	0x54		//user define tone 4
#define USERTONE5	0x55		//user define tone 5
#define USERTONE6	0x56		//user define tone 6
#define USERTONE7	0x57		//user define tone 7
#define USERTONE8	0x58		//user define tone 8
#define USERTONE9	0x59		//user define tone 9
#define USERTONE10	0x5A		//user define tone 10
#define TARGETLINEPICKUP 0x60
#define TARGETLINEHANGUP 0x61
#define PASSTHROUGHONHC  0x75
#define PASSTHROUGHOFFHC 0x76

/***************************************
 * AI Return Error Codes	       *
 ***************************************/
#define TR_SUCCESS	   0x00 	     //API no error
#define TR_FAILURE	   0x04 	     //System not Active
#define TR_INVFUNC	   0x06 	     //Invalid Function in AH
#define TR_INVPARM	   0x07 	     //Invalid Input Parameter
#define TR_LINEERR	   0x09 	     //Invalid Line Number
#define TR_LINEBUSY	   0x0A 	     //Line is Busy
#define TR_NOFREEID	   0x15 	     //no free ID
#define TR_APIMISS	   0x80 	     //TSR not installed
#define TR_INITCARDERR	   0x81 	     //initial card failed
#define TR_MAPBUFFERR	   0x82 	     //Map audio buffer failed
#define TR_READREGERR	   0x83 	     //Read registry error
#define TR_MAPSRAMERR	   0x84 	     //Map SRAM address error (NT only)
#define TR_MUTEXERR	   0x85 	     //Create Mutex error

/***************************************
 * Line Status Return Codes	       *
 ***************************************/
#define LS_ONHLINE	   0x00 	     //On Hook Line
#define LS_OFFHLINE	   0x01 	     //Off Hook Line
#define LS_OFFHOOKING	   0x06 	     //Off Hooking now
#define LS_SENDDTMFS	   0x07 	     //Sending DTMFs
#define LS_ONHOOKING	   0x08 	     //On Hooking now
#define LS_PASSTHROUGHON   0x11
#define LS_PASSTHROUGHOFF  0x12

/* Connect Gain Direction constants */
#define GAIN_INPUT	   0x0
#define GAIN_OUTPUT	   0x1
#define GAIN_BOTH	   0x2

/* caller id Detction Enable flag (signal type), 0: disable */
#define CID_FSKAFTERRING       0x1     	     //FSK after first ring
#define CID_DTMFBEFORERING     0x2           //DTMF before first ring
#define CID_FSKBEFORERING      0x3           //FSK before first ring
#define CID_DTMFAFTERRING      0x4           //DTMF after first ring

//Enable Flag
#define ENABLEIT	   0x1
#define DISABLEIT	   0x0

typedef int (WINAPI *TD_CALLBACK_ROUTINE)(int line, int vstatus, int vresult);
typedef TD_CALLBACK_ROUTINE LPTD_CALLBACK_ROUTINE;

//-------------------------------------------------------------------------
// imported function declarations

#ifdef __cplusplus
extern "C" {
#endif

DLLIMPORT int WINAPI TD_StartDAA(int *DAALineSet,int *DAALineCount,int *DAAAPID);
DLLIMPORT int WINAPI TD_StopDAA(int DAAAPID);
DLLIMPORT int WINAPI TD_OffHook(int DAALineNo);
DLLIMPORT int WINAPI TD_OnHook(int DAALineNo);
DLLIMPORT int WINAPI TD_PulseDial(int DAALineNo, char *DigitString);
DLLIMPORT int WINAPI TD_ReadCallerID(int DAALineNo, int *Length, char *CallerID);
DLLIMPORT int WINAPI TD_SetFlashTime1(int DAALineNo, int FlashTime);
DLLIMPORT int WINAPI TD_SetFlashTime2(int DAALineNo, int FlashTime);
DLLIMPORT int WINAPI TD_SetFlashSeparation(int DAALineNo, int FlashSeparation);
DLLIMPORT int WINAPI TD_SetPulsePauseTime(int DAALineNo, int PauseTime);
DLLIMPORT int WINAPI TD_SetMakeBreakRatio(int DAALineNo, int PMBratio);
DLLIMPORT int WINAPI TD_SetRingCount(int DAALineNo, int RingCount);
DLLIMPORT int WINAPI TD_SetRingCountResetDelay(int DAALineNo, int Delay);
DLLIMPORT int WINAPI TD_SetOffHookDelay(int DAALineNo, int Delay);
DLLIMPORT int WINAPI TD_SetOnHookDelay(int DAALineNo, int Delay);
DLLIMPORT int WINAPI TD_DAAResult(int DAALineNo, int TimeOutLen);
DLLIMPORT int WINAPI TD_DAALineStatus(int DAALineNo, int *StatusCode);
DLLIMPORT int WINAPI TD_SetCallerIDDetection(int DAALineNo, int Enable);
DLLIMPORT int WINAPI TD_SetConnectGain(int DAALineNo, unsigned char GainFactor, char Direction);
DLLIMPORT int WINAPI TD_ReadCallerTelephoneNumber(int DAALineNo, char *CallerTelephoneNumber);
DLLIMPORT int WINAPI TD_ReadCallerName(int DAALineNo, char *CallerName);
DLLIMPORT int WINAPI TD_SetPassThroughRelayOff(int DAALineNo);
DLLIMPORT int WINAPI TD_SetPassThroughRelayOn(int DAALineNo);
DLLIMPORT int WINAPI TD_SetWatchDog(int EnableFlag, int TimeInterval, int MaxTimes);
DLLIMPORT int WINAPI TD_SetAliveCounter();
DLLIMPORT int WINAPI TD_SetEchoSuppress(int DAALineNo, int EnableFlag);
DLLIMPORT int WINAPI TD_DAACallBack(int *DAALineSet,LPTD_CALLBACK_ROUTINE lpCallbackAddr,
		     int DelFlag, int RingFilter, int *DAACallBackID);


#ifdef __cplusplus
}
#endif

