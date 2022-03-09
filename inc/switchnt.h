//
//  MODULE:   switchnt.h
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
 * AI Return Error Codes	       *
 ***************************************/
#define TR_SUCCESS	   0x00 	     //API no error
#define TR_INVFUNC	   0x06 	     //Invalid Function
#define TR_INVPARM	   0x07 	     //Invalid Input Parameter
#define TR_INVPORT	   0x08 	     //Invalid Port Number
#define TR_NOCONN	   0x0B 	     //disconnect no connected lines
#define TR_DIRECTERR	   0x0C 	     //disconnect direction error
#define TR_DUPCONN	   0x0D 	     //connect to already connect line
#define TR_INVAPID	   0x14 	     //AP input ID not equal lock ID
#define TR_NOFREEID	   0x15 	     //no free ID
#define TR_APIMISS	   0x80 	     //TSR not installed
#define TR_INITCARDERR	   0x81 	     //initial card failed
#define TR_MAPBUFFERR	   0x82 	     //Map audio buffer failed
#define TR_READREGERR	   0x83 	     //Read registry error
#define TR_MAPSRAMERR	   0x84 	     //Map SRAM address error (NT only)
#define TR_MUTEXERR	   0x85 	     //Create Mutex error

/* connect/disconnect action parameter */
#define CONNECTIT	0x1
#define DISCONNECTIT	0x0

/* connect/disconnect direction parameter */
#define DIRECTION_ATOB	0x0
#define DIRECTION_BTOA	0x1
#define DIRECTION_BOTH	0x2

/* connect/disconnect Speaker Mode parameter */
#define PORTOUTPUTTOSPEAKER	0	//connect/disc. port output to speaker
#define PORTINPUTTOSPEAKER	1	//connect/disc. port input to speaker
#define PORTBOTHTOSPEAKER	2	//connect/disc. port both to speaker

/* Create Conference Mode parameter */
#define CROSSCONFERENCE 0
#define STARCONFERENCE	1

//Device Type
#define DT_DAA		1
#define DT_SLIC 	2
#define DT_VOICECONNECT 3
#define DT_VOICE	4
#define DT_RECEIVER	5
#define DT_DIALER	6
#define DT_FAX		7
#define DT_SPEAKER	8
#define DT_AUDIOIN	9
#define DT_T1E1 	10
#define DT_E1CONTROL	12
#define DT_DID		13
#define DT_ISDN		14
#define DT_G729A	15	
#define DT_BRI		16	
#define DT_FULLDUPLEX 	17
#define DT_PRIMONITOR	18
#define DT_PRISLIC	19
#define DT_PRIVOIP	20	//12-20-2002

//Tone Type
#define TT_RINGBACK	1
#define TT_BUSY 	2
#define TT_DIAL 	3
#define TT_MUSIC	4
#define TT_WARNING	5
#define TT_CALLWAIT	6

//Special Port (Virtual)
//#define SPEAKERPORT1	383
//#define AUDIOINPORT1	384
#define RINGBTONEPORT1	385
#define RINGBTONEPORT2	386
#define BUSYTONEPORT	387
#define WARNTONEPORT	388
#define DIALTONEPORT	389
#define MUSICPORT	390
#define DIALTONEPORT2	391
#define DIALTONEPORT3	392
#define BUSYTONEPORT2	393
#define	CALLWAITTONEPORT	394

//Clock Source
#define CLOCK_INTERNAL	0
#define CLOCK_PORT1	1
#define CLOCK_PORT2	2
#define CLOCK_PORT3	3
#define CLOCK_PORT4	4

//-------------------------------------------------------------------------
// imported function declarations

#ifdef __cplusplus
extern "C" {
#endif

DLLIMPORT int WINAPI TS_StartSwitch(int *TotalPort,int *SwitchAPID);
DLLIMPORT int WINAPI TS_StopSwitch(int SwitchAPID);
DLLIMPORT int WINAPI TS_Switch(int Action,int PortA,int PortB,int Direction);
DLLIMPORT int WINAPI TS_ConnectStatus(int PortNo,int *PortString,int Direction);
DLLIMPORT int WINAPI TS_DisconnectAll();
DLLIMPORT int WINAPI TS_OnePortDisconnectAll(int PortNo,int Direction);
DLLIMPORT int WINAPI TS_SetBusyTone(short int *Cadence);
DLLIMPORT int WINAPI TS_SetRingbackTone(short int *Cadence,int SetNo);
DLLIMPORT int WINAPI TS_GetDevicePortNo(int DeviceType,int DeviceLineNo,int *PortNo);
DLLIMPORT int WINAPI TS_GetTonePortNo(int ToneType,int ToneSetNo,int *PortNo);
DLLIMPORT int WINAPI TS_SwitchToSpeaker(int Action,int PortNo,int SetNo, int Mode);
DLLIMPORT int WINAPI TS_SwitchToAudioIn(int Action,int PortNo,int SetNo);
DLLIMPORT int WINAPI TS_CreateConference(int Mode,int PortCount,int *PortString,int *pConferenceID);
DLLIMPORT int WINAPI TS_CloseConference(int ConferenceID);
DLLIMPORT int WINAPI TS_JoinConference(int ConferenceID, int PortNo);
DLLIMPORT int WINAPI TS_UnjoinConference(int ConferenceID, int PortNo);
DLLIMPORT int WINAPI TS_SwitchSCSA(int Action,int PortA,int SCSAbus,int SCSAslot,int Direction);
DLLIMPORT int WINAPI TS_GetPortTimeSlot(int PortNo,int *OutSCSAbus,int *OutSCSAslot,int *InSCSAbus,int *InSCSAslot);
DLLIMPORT int WINAPI TS_SetConferenceRoomSize(int RoomSize,int *MaxRoomNo);
DLLIMPORT int WINAPI TS_OpenConferenceRoomNumber(int RoomNo);
DLLIMPORT int WINAPI TS_OnlineChangeClockSource(int BoardNo, int ClockSource);

#ifdef __cplusplus
}
#endif

