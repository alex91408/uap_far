//
//  MODULE:   v2280_nt.h
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
#define NOEVENT 	   0x00 	     //Event Queue Empty
#define MAXDGTS 	   0x01 	     //Maximum Digits Received
#define TERMDIG1	   0x02 	     //Termination Digit Received (1)
#define LSTOP		   0x03 	     //Line Stop from Application
#define DOSERR		   0x04 	     //DOS Error Termination
#define MAXBYTES	   0x05 	     //Maximum Byte Count Reached
//#define BCODEOK	     0x06	       //Read Board Security Number Ok
#define MAXSECS 	   0x07 	     //Maxmimum Seconds Timeout
#define OFFHC		   0x08 	     //Offhook Complete Event
#define DIALCMPL	   0x09 	     //'Dial' Complete Event
#define MAXSIL		   0x0A 	     //Maximum Silence Timeout
#define PBEOF		   0x0B 	     //End-of-File Termination
#define LSTERM		   0x0C 	     //Terminating Loop Signal
#define TONERDY 	   0x0D 	     //Get Tone Value Ok
#define DIGREC		   0x0F 	     //Digit Received
#define BUFPROMPT	   0x10 	     //play/record circular buffer size event
#define CALLPROG	   0x12 	     //Call Progress Report
#define TERMDIG2	   0x1D 	     //Termination Digit Received (2)
#define IDDTERM 	   0x1E 	     //Interdigit Delay Timeout
#define MAXNSIL 	   0x1F 	     //Maximum Non-silence
#define SILON		   0x28 	     //silence on
#define SILOFF		   0x29 	     //silence off
#define CADENCERDY	   0x2A 	     //Get Cadence
#define DIALTONE	   0x31 	     //dialtone detected
#define BUSYTONE	   0x32 	     //busy tone detected
#define VOICETONE	   0x33 	     //voice detected
#define RINGBTONE	   0x34 	     //ringbacktone detected
#define NODIALTONE	   0x35 	     //no dial tone detected
#define REMOTEHANGUP	   0x36 	     //remote hang up detected
#define ANSWERTONE	   0x37 	     //B.B. call tone detected
#define PAGERTONE	   0x37 	     //pager tone detected
#define SILTIMEOUT	   0x39 	     //silence on/off time out detected
#define FAXCALLTONE	   0x3B 	     //fax calling tone
#define CEDTONE 	   0x40 	     //ced tone detected
#define DISKFULL	   0x41 	     //disk full
#define BUFFLOWERR	   0x42 	     //play/record buffer under/overflow
#define FILENOTFOUND	   0x43 	     //file not found
#define PATHNOTFOUND	   0x44 	     //path not found
#define NOFILEHANDLE	   0x45 	     //too many files opened
#define ACCESSDENIED	   0x46 	     //access denied
#define INVALIDDRIVE	   0x47 	     //invalid drive specified
#define USERTONE1	   0x51 	     //user define tone 1
#define USERTONE2	   0x52 	     //user define tone 2
#define USERTONE3	   0x53 	     //user define tone 3
#define USERTONE4	   0x54 	     //user define tone 4
#define USERTONE5	   0x55 	     //user define tone 5
#define USERTONE6	   0x56 	     //user define tone 6
#define USERTONE7	   0x57 	     //user define tone 7
#define USERTONE8	   0x58 	     //user define tone 8
#define USERTONE9	   0x59 	     //user define tone 9
#define USERTONE10	   0x5A 	     //user define tone 10

/***************************************
 * Call progress detection data codes  *
 ***************************************/
#define CP_DIAL 	   0x01 	     //dialtone detected
#define CP_BUSY 	   0x02 	     //busy tone detected
#define CP_VOICE	   0x04 	     //voice detected
#define CP_RINGB	   0x08 	     //ringbacktone detected
#define CP_NODIAL	   0x10 	     //no dial tone detected
#define CP_REMOTEHANGUP    0x20 	     //remote hang up detected
#define CP_ANSWER	   0x40 	     //B.B. call tone detected
#define CP_PAGER	   0x40 	     //pager tone detected
#define CP_CED		   0x41 	     //ced tone detected
#define CP_FAXCALLING	   0x43 	     //fax calling tone detected
#define CP_USERTONE1	   0x51
#define CP_USERTONE2	   0x52
#define CP_USERTONE3	   0x53
#define CP_USERTONE4	   0x54
#define CP_USERTONE5	   0x55
#define CP_USERTONE6	   0x56
#define CP_USERTONE7	   0x57
#define CP_USERTONE8	   0x58
#define CP_USERTONE9	   0x59
#define CP_USERTONE10	   0x5A

/***************************************
 * AI Return Error Codes	       *
 ***************************************/
#define TR_SUCCESS	   0x00 	     //API no error
#define TR_NORESULT	   0x00 	     //No result code
#define TR_NODIGITS	   0x02 	     //No Digits in Queue
#define TR_SYSACTIVE	   0x03 	     //System Active
#define TR_FAILURE	   0x04 	     //System not Active
#define TR_INVFUNC	   0x06 	     //Invalid Function in AH
#define TR_INVPARM	   0x07 	     //Invalid Input Parameter
#define TR_LINEERR	   0x09 	     //Invalid Line Number
#define TR_LINEBUSY	   0x0A 	     //Line is Busy
#define TR_NOCONN	   0x0B 	     //disconnect no connected lines
#define TR_DIRECTERR	   0x0C 	     //disconnect direction error
#define TR_DUPCONN	   0x0D 	     //connect to already connect line
#define TR_NOTERM	   0x0F 	     //No Terminating Option Specified
#define TR_LOCKED	   0x11 	     //Already be locked
#define TR_UNLOCKED	   0x12 	     //Already be unlocked
#define TR_NOAPID	   0x13 	     //AP ID is ZERO
#define TR_INVAPID	   0x14 	     //AP input ID not equal lock ID
#define TR_NOFREEID	   0x15 	     //no free ID
#define TR_TOTOP	   0x16 	     //play re-offset to TOP pos.
#define TR_TOEND	   0x17 	     //play re-offset to END pos.
#define TR_SENDBUFFULL	   0x18 	     //Send Frame buffer full
#define TR_APIMISS	   0x80 	     //TSR not installed
#define TR_INITCARDERR	   0x81 	     //initial card failed
#define TR_MAPBUFFERR	   0x82 	     //Map audio buffer failed
#define TR_READREGERR	   0x83 	     //Read registry error
#define TR_MAPSRAMERR	   0x84 	     //Map SRAM address error (NT only)
#define TR_MUTEXERR	   0x85 	     //Create Mutex error

/***************************************
 * Line Status Return Codes	       *
 ***************************************/
#define LS_RECORDING	   0x03 	     //Recording now
#define LS_PLAYING	   0x04 	     //Playing now
#define LS_GETDTMFS	   0x05 	     //Getting DTMFs
#define LS_SENDDTMFS	   0x07 	     //Sending DTMFs
#define LS_GETCADENCE	   0x09 	     //Getting Cadence Value
#define LS_GETTONE	   0x0B 	     //Getting Tone Value
#define LS_FULLDUPLEX	   0x0C 	     //Full duplex of I-Phone

/*
 * Compression Rate Value
 */
#define COMP31K 	2	//4K bytes, 4 bits, 8K sampling rate (G.721)
#define COMP_ADPCM	2	//4K bytes, 4 bits, 8K sampling rate (G.721)
#define COMP_MULAW	3	//8K bytes, 8 bits, 8K sampling rate (ulaw wav format)
#define COMP_ALAW	4	//8K bytes, 8 bits, 8K sampling rate (alaw wav format)
#define COMP_PCM	5	//16K bytes, 16 bits, 8K sampling rate (leanear)

/*
 * Enable/Disable State
 */
#define ENABLEIT	   0x1
#define DISABLEIT	   0x0

/*
 * Line Gain Direction
 */
#define GAININPUT	   0x0
#define GAINOUTPUT	   0x1
#define GAINBOTH	   0x2

/*
 * Pulse Make / Break ratio
 */
#define PM10B4060	   0x00
#define PM10B3366	   0x01
#define PM20B3366	   0x03

/*********************************************************************
 * Cadence Data Structures					     *
 *********************************************************************/
struct	CadenceAreaF {
	unsigned char	ca_busy_high1;
	unsigned char	ca_busy_low1;
	unsigned char	ca_busy_high2;
	unsigned char	ca_busy_low2;
	unsigned char	ca_busy_testtime;
	unsigned char	ca_busy_tolerance;
	unsigned char	ca_reorder_high1;
	unsigned char	ca_reorder_low1;
	unsigned char	ca_reorder_high2;
	unsigned char	ca_reorder_low2;
	unsigned char	ca_reorder_testtime;
	unsigned char	ca_reorder_tolerance;
	unsigned char	ca_ringb_high1;
	unsigned char	ca_ringb_low1;
	unsigned char	ca_ringb_high2;
	unsigned char	ca_ringb_low2;
	unsigned char	ca_ringb_testtime;
	unsigned char	ca_ringb_tolerance;
	};

#define CAF_SIZE sizeof(struct CadenceAreaF)

/*********************************************************************
 * Tone Data Structures 					     *
 *********************************************************************/
struct	ToneAreaF {
	unsigned short	ta_cp_coef1;
	unsigned short	ta_cp_coef2;
	unsigned short	ta_cp_coef3;
	unsigned short	ta_cp_coef4;
	unsigned short	ta_cp_coef5;
	unsigned short	ta_cp_coef6;
	unsigned short	ta_cp_coef7;
	unsigned short	ta_cp_coef8;
	unsigned short	ta_cp_harm1;
	unsigned short	ta_cp_harm2;
	unsigned short	ta_cp_harm3;
	unsigned short	ta_cp_harm4;
	unsigned short	ta_cp_harm5;
	unsigned short	ta_cp_harm6;
	unsigned short	ta_cp_harm7;
	unsigned short	ta_cp_harm8;
	unsigned char	ta_cp_evttbl[64];
	unsigned short	ta_ol_coef1;
	unsigned short	ta_ol_coef2;
	unsigned short	ta_ol_coef3;
	unsigned short	ta_ol_coef4;
	unsigned short	ta_ol_coef5;
	unsigned short	ta_ol_coef6;
	unsigned short	ta_ol_coef7;
	unsigned short	ta_ol_coef8;
	unsigned short	ta_ol_harm1;
	unsigned short	ta_ol_harm2;
	unsigned short	ta_ol_harm3;
	unsigned short	ta_ol_harm4;
	unsigned short	ta_ol_harm5;
	unsigned short	ta_ol_harm6;
	unsigned short	ta_ol_harm7;
	unsigned short	ta_ol_harm8;
	unsigned char	ta_ol_evttbl[64];
	};

#define TAF_SIZE sizeof(struct ToneAreaF)

/**************************************
 * System Configuration Area	      *
 **************************************/
struct	SysConfigAreaF {
	unsigned short	sca_ptime1;		//00H Pause Time 1
	unsigned char	sca_filler1[8];		//
	unsigned short	sca_tdid;		//0AH Tone Dialing Inter-digit Delay
	unsigned char	sca_filler2[6];
	unsigned short	sca_sild_on;		//12H Silence Detect On Count
	unsigned short	sca_sild_off;		//14H Silence Detect off Count
	unsigned char	sca_filler3[4];		//
	};

#define SCAF_SIZE sizeof(struct SysconfigAreaF)

typedef int (WINAPI *TR_CALLBACK_ROUTINE)(int line, int vstatus, int vresult);
typedef TR_CALLBACK_ROUTINE LPTR_CALLBACK_ROUTINE;

//-------------------------------------------------------------------------
// imported function declarations

#ifdef __cplusplus
extern "C" {
#endif

DLLIMPORT int WINAPI TRF_StartVoice(int *lineset,int *pLineCount,int *papid);
DLLIMPORT int WINAPI TRF_SetCompressionRate(int LineNumber, int CompRate);
DLLIMPORT int WINAPI TRF_StopVoice(int apid);
DLLIMPORT int WINAPI TRF_StopLine(int LineNumber);
DLLIMPORT int WINAPI TRF_ClearDtmfBuffer(int LineNumber);
DLLIMPORT int WINAPI TRF_ReadDtmf(int LineNumber, char *pDigit);
DLLIMPORT int WINAPI TRF_Result(int LineNumber);
DLLIMPORT int WINAPI TRF_ViewResult(int LineNumber);
DLLIMPORT int WINAPI TRF_WaitResult(int LineNumber, int TimeOutLen);
DLLIMPORT int WINAPI TRF_ClearLIOA(int LineNumber);
DLLIMPORT int WINAPI TRF_RecordVoice(int LineNumber, char *FileName, int MaxTime, char DtmfAbort);
DLLIMPORT int WINAPI TRF_RecordVoice1(int LineNumber, char *FileName, int MaxTick, char DtmfAbort);
DLLIMPORT int WINAPI TRF_RecordVoice2(int LineNumber, char *FileName,
				     int MaxTime,int MaxSilence,char DtmfAbort);
DLLIMPORT int WINAPI TRF_RecordBuffer(int LineNumber, char *DataBuffer, long *pBufLength, int MaxTime, char DtmfAbort);
DLLIMPORT int WINAPI TRF_RecordCirBuf(int LineNumber, char *DataBuffer, int BufLength, int *pBufRead,
		     int *pBufWrite, int *pPromptLen, int MaxTime, char DtmfAbort);
DLLIMPORT int WINAPI TRF_PlayVoice(int LineNumber, char *FileName, char DtmfAbort);
DLLIMPORT int WINAPI TRF_PlayIndex(int LineNumber, char *FileName, char DtmfAbort, int *IndexNums);
DLLIMPORT int WINAPI TRF_PlayIndexVB(int LineNumber, char *FileName, char DtmfAbort, int *IndexNums);
DLLIMPORT int WINAPI TRF_PlayBuffer(int LineNumber, char *DataBuffer, long DataLength, char DtmfAbort);
DLLIMPORT int WINAPI TRF_PlayCirBuf(int LineNumber, char *DataBuffer, int BufLength,
		     int *pBufRead, int *pBufWrite, int *pPromptLen, char DtmfAbort);
DLLIMPORT int WINAPI TRF_SendDtmfs(int LineNumber, char *DtmfString);
DLLIMPORT int WINAPI TRF_ReadDtmfs(int LineNumber, char *pDtmfBuffer, char MaxDtmfs, char TimeOut, char DtmfAbort);
DLLIMPORT int WINAPI TRF_ReadDtmfsVB(int LineNumber, char MaxDtmfs, char TimeOut, char DtmfAbort);
DLLIMPORT int WINAPI TRF_CopyDtmfsVB(int LineNumber, int *pDtmfLength, char *pDtmfBuffer);
DLLIMPORT int WINAPI TRF_SetPauseTime(char PauseTime);
DLLIMPORT int WINAPI TRF_SetBeep(int LineNumber);
DLLIMPORT int WINAPI TRF_GetCadence(int LineNumber, char *pReturnCode);
DLLIMPORT int WINAPI TRF_SetCadence(int LineNumber, struct CadenceAreaF *Cadence);
DLLIMPORT int WINAPI TRF_SetCallProgress(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_SetDtmfDetection(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_SetSilenceDetection(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_SetVoiceDetection(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_SetSysConfig(struct SysConfigAreaF *pSCA);
DLLIMPORT int WINAPI TRF_Lock(int LineNumber, int apid);
DLLIMPORT int WINAPI TRF_Unlock(int LineNumber, int apid);
DLLIMPORT int WINAPI TRF_SetLineGain(int LineNumber, unsigned char GainFactor,char Direction);
DLLIMPORT int WINAPI TRF_SetRemoteHangUpDetection(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_SetDtmfDelay(char IDdelay);
DLLIMPORT int WINAPI TRF_GetLineState(int LineNumber, int *pStatus);
DLLIMPORT int WINAPI TRF_Result2(int LineNumber,int *evtcode, int *evtdata);
DLLIMPORT int WINAPI TRF_ViewDtmfs(int LineNumber, int *pDtmfLength, char *pDtmfBuffer);
//DLLIMPORT int WINAPI TR_ReadMakerID(int LineNumber, unsigned long Password, unsigned long *pMakerid);
DLLIMPORT int WINAPI TRF_SetAdvanceCallProgress(int LineNumber, char Enable);
DLLIMPORT int WINAPI TRF_GetTone(int LineNumber, unsigned short *pReturnVal);
DLLIMPORT int WINAPI TRF_SetTone(int LineNumber, struct ToneAreaF *pToneData);
DLLIMPORT int WINAPI TRF_PlaySilence(int LineNumber, unsigned long *pdatas);
DLLIMPORT int WINAPI TRF_PlayContinue(int LineNumber, long shiftbytes);
DLLIMPORT int WINAPI TRF_SetRecordingSource(int LineNumber,char SourceFlag);
DLLIMPORT int WINAPI TRF_XSoundLevel(int LineNumber,int *SoundLevel);
DLLIMPORT int WINAPI TRF_GetCardType(int LineNumber, char *CardType);
DLLIMPORT int WINAPI TRF_XSilenceThreshold(int LineNumber, int Threshold);
//DLLIMPORT int WINAPI TR_SetAGC(int LineNumber, int Enable);
DLLIMPORT int WINAPI TRF_FullDuplex(int LineNumber, int Compression);
DLLIMPORT int WINAPI TRF_ReceiveFrame(int LineNumber, char *pBuffer, int *pReceivedBytes);
DLLIMPORT int WINAPI TRF_SendFrame(int LineNumber, char *pBuffer, int BufferLen, int *pSendBytes);
DLLIMPORT int WINAPI TRF_GetBufPtr(int LineNumber, int *pBufPtr);

DLLIMPORT int WINAPI TRF_SetDTMFTonePulseDuration(int DurationTime);
DLLIMPORT int WINAPI TRF_SetBeepTonePulseDuration(int DurationTime);
DLLIMPORT int WINAPI TRF_SetSilenceOnDetectCount(int TimeLen);
DLLIMPORT int WINAPI TRF_SetSilenceOffDetectCount(int TimeLen);

DLLIMPORT int WINAPI TRF_CallBack(int *lineset,LPTR_CALLBACK_ROUTINE lpCallbackAddr,
		     unsigned char filter, int *pcbid, char delflag);

#ifdef __cplusplus
}
#endif

