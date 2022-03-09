/*********************************************************************
 *        FILE: dxxxlib.h
 * DESCRIPTION: Header File for DIALOGIC D/XXX Windows NT/95 library
 *
 *   Copyright (c) 1991-1996 Dialogic Corp. All Rights Reserved
 *
 *   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF Dialogic Corp.
 *   The copyright notice above does not evidence any actual or
 *   intended publication of such source code.
 ********************************************************************/
//07-07-1999 [cjl] Update The defines for the Feature Table play/record 
//						fields to match the additional fields in firmware.
//02-24-2000 [cjl] Added FT_IBI #define
//03-08-2000 [cjl] move DM_VADEVTS to dxxxlib.h where the others are.
//04-25-2000 [cjl] add support for dx_callp
//05-19-2000 [cjl] PTR 18000 - Fix dx_callp flags
//05-25-2000 [cjl] PTR 18111 - Add PVD_Id and PAMD_Id parms to dx_callp.
//06-08-2000 [cjl] add CT_BMH100 to bus defines
//06-21-2000 [cjl] change FT_IBI to FT_CSP
//10-05-2000 [cjl] synct the CT_ defs with dtlib.h
//01-29-2002 [mem] ptr 24852 - Add DXCH_DSPCARRIERDETECTDEBOUNCE and DXCH_DSPCARRIERDETECTTHRESHOLD defines for 2way FSK.
//                 This was needed since these defines where never added to lib originally.

#ifndef __DXXXLIB_H__
#define __DXXXLIB_H__

#ifdef __STANDALONE__            /* List of required header files */
#endif


/*
 * Required header files
 */

/* NOTE: srllib.h must be included before here for DV_TPT */

#include "dxdevdef.h"
#include "dxcallp.h"
#include "dxdigit.h"
#include "dxr2mf.h"
#include "dxsync.h"
#include "dxtables.h"
#include "d40low.h"
#include "dxxxlow.h"
#include "dxuio.h"
#include "srltpt.h"

/*
 * The following equates and structures are D/4x dependent
 */

#ifndef VOXLIB

/*
 * Macros to get at the class and model parts of a device ID
 */
#define dl_devclass(i)  ((i) & 0xFF00)
#define dl_devmodel(i)  ((i) & 0x00FF)

#define DEV_CLASS_VOICE "Voice"
#define DEV_CLASS_AUDIO_IN "ai"

/*
 * Maximum terminator values.
 */
#define MAX_TC_TIMER 6000  /* Max time units for term. conditions */


/*
 * Values for setting hook state
 */
#define DL_ONHOOK             0
#define DL_OFFHOOK            1
#define DX_ONHOOK             0
#define DX_OFFHOOK            1


/**
 ** Define Event Types
 **/
#define TDX_PLAY        0x81     /* Play Completed */
#define TDX_RECORD      0x82     /* Record Completed */
#define TDX_GETDIG      0x83     /* Get Digits Completed */
#define TDX_DIAL        0x84     /* Dial Completed */
#define TDX_CALLP       0x85     /* Call Progress Completed */
#define TDX_CST         0x86     /* CST Event Received */
#define TDX_SETHOOK     0x87     /* SetHook Completed */
#define TDX_WINK        0x88     /* Wink Completed */
#define TDX_ERROR       0x89     /* Error Event */
#define TDX_PLAYTONE    0x8A     /* Play Tone Completed */
#define TDX_GETR2MF     0x8B     /* Get R2MF completed */
#define TDX_BARGEIN     0x8C     /* Barge in completed */
#define TDX_NOSTOP      0x8D     /* No Stop needed to be Issued */

#define TDX_TXDATA	0x90	 /* Transmit Data Completed */
#define TDX_RXDATA	0x91	 /* Transmit Data Completed */

#define DX_ATOMIC_ERR   0xEE     /* Error event for Atomic Funcs */

/*
 *	Added to handle new sendevt() capability.
 */
#define	TDX_UNKNOWN		1000		/* Yes, Decimal 1000 */


/**
 ** Define sendevt flag values
 **/
#define EVFL_SENDSELF   0x01     /* Send event to self process */
#define EVFL_SENDOTHERS 0x02     /* Send event to other processes */
#define EVFL_SENDALL    0x03     /* Send event to all processes */


/*
 * Error codes returned by ATDV_LASTERR()
 */
#define EDX_NOERROR     0     /* No Errors */
#define EDX_SYSTEM      1     /* System Error */
#define EDX_FWERROR     2     /* Firmware Error */
#define EDX_TIMEOUT     3     /* Function Timed Out */
#define EDX_BADIOTT     4     /* Invalid Entry in the DX_IOTT */
#define EDX_BADTPT      5     /* Invalid Entry in the DX_TPT */
#define EDX_BADPARM     6     /* Invalid Parameter in Function Call */
#define EDX_BADDEV      7     /* Invalid Device Descriptor */
#define EDX_BADPROD     8     /* Func. Not Supported on this Board */
#define EDX_BUSY        9     /* Device is Already Busy */
#define EDX_IDLE        10    /* Device is Idle */
#define EDX_STOPRINGS   11    /* Stop waitrings (MT only) */
#define EDX_WTRINGSTOP  11    /* Wait for Rings stopped by user */
#define EDX_BADWAVEFILE 12    /* Bad/Unsupported WAV file */
#define EDX_XPBPARM     13    /* Bad XPB structure */
#define EDX_NOSUPPORT   14    /* Data format not supported */
#define EDX_NOTIMP      15    /* Function not implemented */

//01142000, WEIHSIN, ADD NEW ERROR CODE
#define EDX_BADSUBCOMMAND              16
#define EDX_BADCHANNELNUMBER           17
#define EDX_BADRESOURCEID              18
#define EDX_NORESOURCE                 19    /* No Resources */
#define EDX_DSPERROR                   20    /* Resource DSP error */
//#define EDX_CHANNEL_BUSY_ERROR         21
#define EDX_INUSE								21
//END

/*
 * GTD Error Codes
 */
#define EDX_TONEID      0x41  /* Bad Tone Template ID */
#define EDX_MAXTMPLT    0x42  /* Max number of Templates Exists */
#define EDX_INVSUBCMD   0x43  /* Invalid Sub Command Number */
#define EDX_CHANNUM     0x44  /* Invalid Channel Number Specified */
#define EDX_FREQDET     0x45  /* Invalid Freq Component Values */
                              /* in Tone Template Description */
#define EDX_CADENCE     0x46  /* Invalid Cadence Component Values */
                              /* in Tone Template Description */
#define EDX_ASCII       0x47  /* Invalid Ascii Value */
                              /* in Tone Template Description */
#define EDX_DIGTYPE     0x48  /* Invalid Dig_Type Value */
                              /* in Tone Template Description */
#define EDX_MSGSTATUS   0x49  /* Invalid Message Status Setting */

/*
 * Speed and Volume Control Error Codes
 */
#define EDX_SVADJBLKS   0x4A  /* Invalid Number of Speed/Volume */
                              /* Adjustment Blocks */
#define EDX_SPDVOL      0x4B  /* Must Specify either SV_SPEEDTBL or */
                              /* SV_VOLUMETBL */
#define EDX_SVMTSIZE    0x4C  /* Invalid Table Size Specified */
#define EDX_SVMTRANGE   0x4D  /* An out of Range entry in DX_SVMT */
#define EDX_NONZEROSIZE 0x4E  /* Reset to Default was Requested but */
                              /* size was non-zero */

/*
 * GTG Error Codes
 */
#define EDX_FLAGGEN     0x4F  /* Invalid tg_dflag field in */
                              /* Tone Generation Template */
#define EDX_FREQGEN     0x50  /* Invalid Frequency Component in */
                              /* Tone Generation Template */
#define EDX_AMPLGEN     0x51  /* Invalid Amplitude Value in */
                              /* Tone Generation Template */

/*
 * Switch Handler / SCSA  Error Codes
 */
#define EDX_SH_CMDBLOCK   0x59  /* Blocking Command is in progress */
#define EDX_SH_BADCMD     0x60  /* Command not supported */
#define EDX_SH_LIBBSY     0x61  /* Switching Handler Lib is busy */
#define EDX_SH_BADINDX    0x62  /* Invalid Switching Handler indx # */
#define EDX_SH_LIBNOTINIT 0x63  /* Switching Handler Library has not been initialized */
#define EDX_SH_NOCLK      0x64  /* Switching Handler Clock fallback failed */
#define EDX_SH_MISSING    0x66  /* Switching Handler is not Present */
#define EDX_SH_BADMODE    0x6A  /* Invalid Switching Handler Bus Mode */
#define EDX_SH_BADLCLTS   0x6F  /* Invalid local timeslot (Channel) */
#define EDX_SH_BADTYPE    0x70  /* Invalid local timeslot type */
#define EDX_SH_BADEXTTS   0x71  /* External timeslot not supported at current clock rate */
#define EDX_SH_LCLTSCNCT  0x72  /* Channel is already connected to SCbus */
#define EDX_SH_LCLDSCNCT  0x73  /* Channel is already disconnected from SCbus */


/*
 * Error Codes Specific to caller ID
 */
#define EDX_CLIDINFO 0x80  /* caller ID info/sub-msg not available */
#define EDX_CLIDBLK  0x81  /* caller ID private ('P') or blocked   */
#define EDX_CLIDOOA  0x82  /* caller ID out of area ('O')          */
#define EDX_CLIDPUB  0x83  /* caller ID public phone ('C')	   */
#define EDX_CLIDPLAN 0x84  /* caller ID unknown plan ('S')	   */

/*
 * Error Codes Specific to PBXpert TSF loading
 */
#define	EDX_BADREGVALUE		0x90
#define	EDX_BADTSFFILE			0x91
#define	EDX_BADTSFDATA			0x92
#define	EDX_FEATUREDISABLED	0x93

/*
 * Error Codes Specific to EC TAP
 */
#define	EDX_BADMODE				0x90
#define	EDX_UNSUPPORTED		0x91

/*
 * Equates for generic caller ID message type IDs 
 */
#define  CLIDINFO_CMPLT        0x100   /* complete caller ID message   */
#define  CLIDINFO_GENERAL      0x101   /* date,time,phone #,name       */
#define  CLIDINFO_CALLID       0x102   /* caller ID                    */
#define  CLIDINFO_FRAMETYPE    0x103   /* see frame type equates       */

/*
 * Equates for CLASS 
 */
#define  CLASSFRAME_SDM    0x04    /* Single Data Message caller ID frame   */
#define  CLASSFRAME_MDM    0x80    /* Multiple Data Message caller ID frame */
/* CLASS MDM message IDs */
#define  MCLASS_DATETIME   0x01    /* date and time w/o '/" & ':'      */
#define  MCLASS_DN         0x02    /* calling line directory number    */
#define  MCLASS_DDN        0x03    /* dialed number                    */
#define  MCLASS_ABSENCE1   0x04    /* caller ID absence: 'O' or 'P'    */
#define  MCLASS_REDIRECT   0x05    /* call frwd-universal,busy,or unanswered */
#define  MCLASS_QUALIFIER  0x06    /* 'L' for long distance            */
#define  MCLASS_NAME       0x07    /* caller name                      */
#define  MCLASS_ABSENCE2   0x08    /* name absence- 'O' or 'P'         */

/*
 * Equates for CLIP 
 */
#define  CLIPFRAME_MDM     0x80    /* Multiple Data Message caller ID frame */
/* CLIP message IDs */
#define  CLIP_DATETIME     0x01    /* date and time (w/o '/" & ':')    */
#define  CLIP_DN           0x02    /* calling line directory number    */
#define  CLIP_DDN          0x03    /* dialed number                    */
#define  CLIP_ABSENCE1     0x04    /* caller ID absence: 'O' or 'P'    */
#define  CLIP_NAME         0x07    /* caller name                      */
#define  CLIP_ABSENCE2     0x08    /* name absence- 'O' or 'P'         */
#define  CLIP_CALLTYPE     0x11    /* voice call,rng-bck-when-free call or msg waiting call */
#define  CLIP_NETMSG       0x13    /* no. of message waiting             */

/*
 * Equates for A-CLIP 
 */
#define  ACLIPFRAME_SDM    0x04    /* Single Data Message caller ID frame   */
#define  ACLIPFRAME_MDM    0x80    /* Multiple Data Message caller ID frame */
/* A-CLIP MDM message IDs */
#define  MACLIP_DATETIME   0x01    /* date and time (w/o '/" & ':'     */
#define  MACLIP_DN         0x02    /* calling line directory number    */
#define  MACLIP_DDN        0x03    /* dialed number                    */
#define  MACLIP_ABSENCE1   0x04    /* caller ID absence: 'O' or 'P'    */
#define  MACLIP_REDIRECT   0x05    /* call frwd-universal,busy,or unanswered */
#define  MACLIP_QUALIFIER  0x06    /* 'L' for long distance            */
#define  MACLIP_NAME       0x07    /* caller name                      */
#define  MACLIP_ABSENCE2   0x08    /* name absence- 'O' or 'P'         */

/*
 * Equates for Japan Caller ID  JCLIP
 */
#define  JCLIPFRAME_MDM    0x40    /* Multiple Data Message caller ID frame */
#define  JCLIP_DN          0x02    /* calling line directory number    */
#define  JCLIP_DDN         0x09    /* dialed number                    */
#define  JCLIP_ABSENCE1    0x04    /* caller ID absence: 'O' or 'P'    */
#define  JCLIP_ABSENCE2    0x08    /* name absence- 'O' or 'P'         */


/*
 * Defines for for channel state values
 */
#define CS_IDLE      1     /* Channel is idle */
#define CS_PLAY      2     /* Channel is playing back */
#define CS_RECD      3     /* Channel is recording */
#define CS_DIAL      4     /* Channel is dialing */
#define CS_GTDIG     5     /* Channel is getting digits */
#define CS_TONE      6     /* Channel is generating a tone */
#define CS_STOPD     7     /* Operation has terminated */
#define CS_SENDFAX   8     /* Channel is sending a fax */
#define CS_RECVFAX   9     /* Channel is receiving a fax */
#define CS_CALL      13    /* Channel is Call Progress Mode */
#define CS_GETR2MF   14    /* Channel is Getting R2MF */
#define CS_BLOCKED   16    /* Channel is blocked */

/* 
 * This is a complex state composed of one of the 
 * above states and faxmode. 
 */
#define CS_FAXIO     10    /* Channel is between fax pages */

/*
 * Define a channel state for the remaining blocking commands
 */
#define CS_HOOK      11    /* A change in hookstate is in progress */
#define CS_WINK      12    /* A wink operation is in progress */
#define CS_RINGS     15    /* Call status Rings state */

/*	
 *	Added this to have the behavior if user uses getevt to
 *	wait for rings.
 */
#define	CS_WAITEVT	(CS_RINGS)

/*
 * D/4X Events and masks 
 */
#define DE_RINGS     1     /* Rings received */
#define DE_SILON     2     /* Silence on */
#define DE_SILOF     3     /* Silenec off */
#define DE_LCON      4     /* Loop current on */
#define DE_LCOF      5     /* Loop current off */
#define DE_WINK      6     /* Wink received */
#define DE_RNGOFF    7     /* Ring off event */
#define DE_DIGITS    8     /* Digit Received */
#define DE_DIGOFF    9     /* Digit tone off event */
#define DE_LCREV     13    /* Loop current reversal   */
#define DE_TONEON    17    /* Tone ON  Event Received */
#define DE_TONEOFF   18    /* Tone OFF Event Received */
#define DE_STOPRINGS 19    /* Stop ring detect state */
#define DE_VAD			20		/* Voice Energy detected */


/* Alt. defines for DM_SILOF, DM_LCOF are DM_SILOFF and DM_LCOFF */
/*
 * Event mask values
 */
#define DM_RINGS     ( 1 << (DE_RINGS - 1) )
#define DM_SILON     ( 1 << (DE_SILON - 1) )
#define DM_SILOF     ( 1 << (DE_SILOF - 1) )
#define DM_LCON      ( 1 << (DE_LCON - 1) )
#define DM_LCOF      ( 1 << (DE_LCOF - 1) )
#define DM_LCREV     ( 1 << (DE_LCREV - 1) )
#define DM_WINK      ( 1 << (DE_WINK - 1) )
#define DM_RNGOFF    ( 1 << (DE_RNGOFF - 1) )
#define DM_DIGITS    ( 1 << (DE_DIGITS - 1) )
#define DM_DIGOFF    ( 1 << (DE_DIGOFF - 1) )
#define DM_VADEVTS	( 1 << (DE_VAD - 1) )


/*
 * Termination reasons
 */
#define T_NORML      0     /* Normal termination */
#define T_MXDIG      1     /* Max. digits received */
#define T_MXSIL      2     /* Max. silence exceeded */
#define T_MXNSIL     3     /* Max. non-silence exceeded */
#define T_LOOP       4     /* Loop current drop */
#define T_IDIG       5     /* Max. inter-digit delay exceeded */
#define T_MXSEC      6     /* Max. time elapsed */
#define T_TDIG       7     /* Terminating digit received */
#define T_PATRN      8     /* Pattern match detected */
#define T_STOP       9     /* Stopped by user */
#define T_EOD        10    /* End of data on playback */
#define T_ERR        13    /* I/O device error */


/*
 * Masked DTMF termination/initiation equates
 */
#define  DM_D        0x0001    /* Mask for DTMF d. */
#define  DM_1        0x0002    /* Mask for DTMF 1. */
#define  DM_2        0x0004    /* Mask for DTMF 2. */
#define  DM_3        0x0008    /* Mask for DTMF 3. */
#define  DM_4        0x0010    /* Mask for DTMF 4. */
#define  DM_5        0x0020    /* Mask for DTMF 5. */
#define  DM_6        0x0040    /* Mask for DTMF 6. */
#define  DM_7        0x0080    /* Mask for DTMF 7. */
#define  DM_8        0x0100    /* Mask for DTMF 8. */
#define  DM_9        0x0200    /* Mask for DTMF 9. */
#define  DM_0        0x0400    /* Mask for DTMF 0. */
#define  DM_S        0x0800    /* Mask for DTMF *. */
#define  DM_P        0x1000    /* Mask for DTMF #. */
#define  DM_A        0x2000    /* Mask for DTMF a. */
#define  DM_B        0x4000    /* Mask for DTMF b. */
#define  DM_C        0x8000    /* Mask for DTMF c. */

/*
 *  Standard DTMF Tone Ids
 */
#define TN_DTMF_1		0x8001
#define TN_DTMF_2		0x8002
#define TN_DTMF_3		0x8003
#define TN_DTMF_4		0x8004
#define TN_DTMF_5		0x8005
#define TN_DTMF_6		0x8006
#define TN_DTMF_7		0x8007
#define TN_DTMF_8		0x8008
#define TN_DTMF_9		0x8009
#define TN_DTMF_STAR		0x800e
#define TN_DTMF_0		0x8000
#define TN_DTMF_POUND		0x800f
#define TN_DTMF_A		0x800a
#define TN_DTMF_B		0x800b
#define TN_DTMF_C		0x800c
#define TN_DTMF_D		0x800d

/*
 * Macros to get the parts out of a parameter ID
 */
#define parmtype(id) (((id) >> 8) & 0xF)   /* High byte, lo nibble */
#define parmnumb(id) (((id) & 0xFF) - 1)   /* Low byte */


/*
 * D/4x Parameter Type Equates
 */
#define PT_BD        0      /* Board parameter */
#define PT_CH        1      /* Channel parameter */


/*
 * Defines used by the parameter functions
 */
#define PM_BD        0x00800000L   /* Board Level Parameter */
#define PM_CH        0x00000000L   /* Channel Level Parameter */

#define PM_DXXX      0x00000000L   /* D/xxx Parameter */
#define PM_D12X      0x01000000L   /* D/12x Parameter */
#define PM_MF40      0x02000000L   /* MF/40 Parameter */
#define PM_D12XDEV   0x04000000L

#define PM_FW        0x00000000L   /* Firmware Parameter */
#define PM_DRV       0x08000000L   /* Driver Parameter */
#define PM_LIB       0x10000000L   /* Library Parameter */
#define PM_NOIDLE		0x00400000L		/* don't do check for idle */

#define PRM_DEST     0x18000000L
#define PRM_DEVTYP   0x07000000L
#define PRM_DATTYP   0xE0000000L
#define PRM_NUM      0x0000FFFFL
#define PRM_TERM     0x007F0000L

#define PM_BYTE      0x00000000L   /* Byte */
#define PM_SHORT     0x20000000L   /* Short */
#define PM_INT       0x40000000L   /* Int */
#define PM_LONG      0x60000000L   /* Long */
#define PM_VLSTR     0x80000000L   /* Variable Length String */
#define PM_FLSTR     0xA0000000L   /* Fixed Length String */

#define PM_VLSTR_MAXLEN 128 /* Max Length for Variable Length Parms */

/*
 * CHANNEL PARAMETERS
 */
/* DTMF anti-talkoff during playback */
#define DXCH_DTMFTLK    ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0101L)

/* DTMF debounce time */
#define DXCH_DTMFDEB    ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0201L)

/* DTMF initiation bitmap */
#define DXCH_DTINITSET  ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0203L)

/* Delay after ring recvd before winking */
#define DXCH_WINKDLY    ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0204L)

/* Duration of wink (off-hook state) */
#define DXCH_WINKLEN    ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0205L)

/* Min LC on to be recognized as wink */
#define DXCH_MINRWINK   ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0206L)

/* Max LC on to be recognized as wink */
#define DXCH_MAXRWINK   ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0207L)

/* Length of DTMF digit for dialing */
#define DXCH_TTDATA     ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0208L)

/* Length of TT inter digit delay */
#define DXCH_T_IDD      ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0209L)

/* Length of ADSI alert tone */
#define DXCH_ADSIALERT_LENGTH ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x020DL)

/* Time to wait for DTMF A */
#define DXCH_ADSIALERT_ACK ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x020EL)

/* Length of DTMF to accept */
#define DXCH_ADSIACK_LENGTH ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x020FL)

/* Pause after end of DTMF */
#define DXCH_ADSIACK_FSK ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0210L)

/* Level to generate CAS tone */
#define DXCH_ADSIALERT_AMPL ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0211L)

/* MF detection mask */
#define DXCH_MFMODE     ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0201L)

/* Diagnostic mask */
#define DXCH_MFDIAG     ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0202L)

/* Per channel dig rate: play (D/xxx only) */
#define DXCH_PLAYDRATE  ((PM_SHORT|PM_FW|PM_D12X|PM_CH) | 0x0E01L)

/* Per channel dig rate: rec (D/xxx only)*/
#define DXCH_RECRDRATE  ((PM_SHORT|PM_FW|PM_D12X|PM_CH) | 0x0E02L)

/* DTMF detection edge select */
#define DXCH_DFLAGS     ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0801L)

/* Per channel ring count */
#define DXCH_RINGCNT    ((PM_SHORT|PM_DRV|PM_DXXX|PM_CH) | 0x0001L)

/* Enable/disable Caller ID */
#define DXCH_CALLID     ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0E04L)

/* Enable/disable Caller ID values */
#define DX_CALLIDDISABLE   0x0000   /* Disable Caller ID */
#define DX_CALLIDENABLE    0x0001   /* Enable Caller ID */

/* Enable/disable Audio line-in */
#define DXCH_AUDIOLINEIN ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0E05L)

/* Enable/disable Audio line-in values */
#define DX_LINEINDISABLE   0x0000   /* Disable audio line-in connection */
#define DX_LINEINENABLE    0x0001   /* Enable audio line-in connection */

/* DTMF Digit buffering mode */
#define DXCH_DIGBUFMODE ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0002L)

/* Per channel I/O buffer Parameters */
#define DXCH_XFERBUFSIZE ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0003L)		//sets both
#define DXCH_RXDATABUFSIZE ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0004L)	//record only
#define DXCH_TXDATABUFSIZE ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0005L)	//play only
#define DXCH_NUMRXBUFFERS ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0006L)	//num record
#define DXCH_NUMTXBUFFERS ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0007L)	//num play

//per channel tone trimming
#define DXCH_DONOTTRIMTONES ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0008L)

// Both Play and Bargein events on a barge in?
#define DXCH_BARGEINONLY  ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0009L)	//play + Bargein


//variable number of buffers for using buffers > the default 2 @ 32K size
#define DXCH_VARNUMBUFFERS	((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0010L)

// Silence Compressed Recording Parameter
#define DXCH_SCRFEATURE  ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0011L)
#define DXCH_SCRDISABLED	0
#define DXCH_SCRENABLED		1

// FSK Interblock Timeout for data Receive mode	
#define DXCH_FSKINTERBLKTIMEOUT  ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0012L)

/* Per channel EC TAP */
#define DXCH_EC_TAP_LENGTH ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x21BL)

/* ASR Barge-in channel parameters */
#define DXCH_BARGEIN_RECFORMAT    ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0212L)
#define DXCH_VADTIMEOUT           ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0213L)
#define DXCH_SPEECHSNR            ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0214L)
#define DXCH_SPEECHTHRESH         ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0215L)
#define DXCH_SPEECHPLAYTHRESH     ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0215L)
#define DXCH_SPEECHPLAYTRIGG      ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0216L)
#define DXCH_SPEECHNONPLAYTRIGG   ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0217L)
#define DXCH_SPEECHPLAYWINDOW     ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0218L)
#define DXCH_SPEECHNONPLAYWINDOW  ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0219L)
#define DXCH_SPEECHNONPLAYTHRESH  ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x021AL)

/* Added FSK defines for ptr 24852. */
#define DXCH_DSPCARRIERDETECTDEBOUNCE   ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0232L)
#define DXCH_DSPCARRIERDETECTTHRESHOLD  ((PM_SHORT|PM_FW|PM_DXXX|PM_CH) | 0x0233L)

/* DTMF Digit buffering modes */
#define DX_DIGCYCLIC    1    /* Cyclic shift digits once buffer is full */
#define DX_DIGTRUNC     2    /* Truncate digits once buffer is full */

/* Channel I/O transfer buffer identifiers */
#define BUF_4K    0
#define BUF_8K    1
#define BUF_16K   2
#define BUF_2K    4
#define BUF_1K    5
#define BUF_1_5K  6
#define BUF_DFLT  BUF_8K


/* 
 * Board Parameters
 */
/* Size of the ping-pong PLAY buffers on board */
#define DXBD_TXBUFSIZE  ((PM_SHORT|PM_FW|PM_D12XDEV|PM_BD) | 0x00F6L)

/* Size of the ping-pong RECORD buffers on board */
#define DXBD_RXBUFSIZE  ((PM_SHORT|PM_FW|PM_D12XDEV|PM_BD) | 0x00F7L)

/* Flash character in dial string */
#define DXBD_FLASHCHR   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0301L)

/* Init delay time */
#define DXBD_INITDLY    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0302L)

/* Min time of LC on for LPD */
#define DXBD_MINPDON    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0303L)

/* Min time of LC off for LPD */
#define DXBD_MINPDOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0304L)

/* Length of DTMF digit for dialing*/
#define DXBD_TTDATA     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0305L)

/* Min time of silence on for APD */
#define DXBD_MINSLON    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0306L)

/* Min time for silence off for APD */
#define DXBD_MINSLOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0307L)

/* Min time for dti signal on */
#define DXBD_MINTION    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0308L)

/* Min time for dti signal off*/ 
#define DXBD_MINTIOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0309L)

/* Edge of ring detection */
#define DXBD_R_EDGE     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x030AL)

/* Flash time during dialing */
#define DXBD_FLASHTM    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0401L)

/* Pause time during dialing */
#define DXBD_PAUSETM    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0402L)

/* Minimum off-hook time */
#define DXBD_MINOFFHKTM ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0403L)

/* Length of pulse dialing make */
#define DXBD_P_MK       ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0404L)

/* Length of pulse dialing break */
#define DXBD_P_BK       ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0405L)

/* Length of pulse inter digit delay*/
#define DXBD_P_IDD      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0406L)

/* Length of TT inter digit delay */
#define DXBD_T_IDD      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0407L)

/* Delay before offhook finished */
#define DXBD_OFFHDLY    ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0408L)

/* Min time for ring detection*/
#define DXBD_R_ON       ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0409L)

/* Min time for for the end of a ring*/
#define DXBD_R_OFF      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040AL)

/* Max wait between rings */
#define DXBD_R_IRD      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040BL)

/* Silence on and off debounce time */
#define DXBD_S_BNC      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040CL)

/* Min interpulse digit time for LPD */
#define DXBD_MINIPD     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040DL)

/* Min time of lc off before message*/
#define DXBD_MINLCOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040EL)

/* Max time for lc off for LPD */
#define DXBD_MAXPDOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x040FL)

/* Min time for silence on for APD */
#define DXBD_MINISL     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0410L)

/* Max time for silence off for  APD */
#define DXBD_MAXSLOFF   ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0411L)

/* Either a D/40 or D/41 */
#define DXBD_HWTYPE     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0601L)

/* Number of channels on board */
#define DXBD_CHNUM      ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0602L)

/* System configuration */
#define DXBD_SYSCFG     ((PM_SHORT|PM_FW|PM_DXXX|PM_BD) | 0x0604L)

/*
 * NOTE: Must use PM_CH instead of PM_BD on MF40 paramters.
 */
/* Min time for MF detection */
#define DXBD_MFMINON    ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0101L)

/* Duration of MF tone during dial */
#define DXBD_MFTONE     ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0102L)

/* Inter-digit delay during MF dialing */
#define DXBD_MFDELAY    ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0103L)

/* Duration of LKP tone during MF dialing */
#define DXBD_MFLKPTONE  ((PM_SHORT|PM_FW|PM_MF40|PM_CH) | 0x0104L)

/*
 * Board Parameter values
 */

/*
 * When a rings received message is sent (BD_R_EDGE)
 */
#define ET_RON       1   /* At the beginning of the ring */
#define ET_ROFF      2   /* At the end of the ring */


/*
 * Channel Mode values
 */
#define MD_ADPCM     0x0000    /* ADPCM data (the default) */
#define MD_PCM       0x0100    /* Mu-Law PCM data */
#define MD_WAV       0x0200	   /* .wav (liner PCM) */
#define MD_FFT       0x0200    /* FFT data (debugging) */
#define MD_GAIN      0x0000    /* AGC on */
#define MD_NOGAIN    0x1000    /* AGC off */
#define PM_TONE      0x0001    /* Tone initiated play/record */
#define RM_TONE      PM_TONE
#define PM_SR6       0x2000    /* 6KHz sampling rate (digitization) */
#define PM_SR8       0x4000    /* 8KHz sampling rate (digitization) */
#define RM_SR6       PM_SR6
#define RM_SR8       PM_SR8
#define PM_ALAW      0x0020    /* Play A-Law data         */
#define RM_ALAW      PM_ALAW   /* Record data using A-Law */
#define PM_DTINIT    0x0002    /* Play with DTMF init */
#define RM_DTINIT    PM_DTINIT /* Record with DTMF init */
#define PM_DTINITSET 0x0010 | PM_DTINIT /* Play with DTMF init set */
#define RM_DTINITSET PM_DTINITSET   /* Record with DTMF init set */
#define R2_COMPELDIG 0x0400    /* R2MF Compelled signalling */

/*
 * dx_stopch modes
 */
#define EV_NOSTOP    0x200     /* Have dx_stopch queue an event if channel is idle */

/*
 * Channel modes for ADSI support
 */
#define PM_RAW       0x0200    /* Raw playback mode */
#define PM_ADSI      0x0080    /* ADSI playback mode */
#define PM_ADSIALERT PM_ADSI | PM_DTINITSET | PM_TONE


#define PM_NOREADWRITE  0x0400 /* Don't perform read/writes */
#define PM_BARGEIN      0x0800 /* Enable bargein during playback */

/*
 *
 */
#define PM_BARGEIN_VADOFF 	0x1000
#define RM_BARGEIN 		0x0800

/*
 * dx_dial modes
 */
#define DX_CNGTONE	2      /* Generate CNG tone after dialing */

#endif


/* 
 * Alternate defines for DE_SILOF, DM_SILOF, DE_LCOF, DM_LCOF
 */
#define DE_SILOFF    DE_SILOF
#define DE_LCOFF     DE_LCOF
#define DM_SILOFF    DM_SILOF
#define DM_LCOFF     DM_LCOF


/*
 * Define's for Mode Checking
 */
#define MD_SELECT    (MD_PCM)     

#define EV_ASYNC     0x8000
#define EV_SYNC      0x0000


/*
 * Raw Line Status Defines
 */
#define RLS_SILENCE  0x80  /* Sil Bit in Raw Line Status */
#define RLS_DTMF     0x40  /* DTMF Signal Bit in Raw Line Status */
#define RLS_LCSENSE  0x20  /* Loop Current Sense Bit in Raw Line Status */
#define RLS_RING     0x10  /* Ring Detect Bit in Raw Line Status */
#define RLS_HOOK     0x08  /* Hook Switch Status Bit in Raw Line Status */
#define RLS_RINGBK   0x04  /* Audible Ringback Detect Bit in Raw Line Status */


/*
 * GTD Defines
 */
#define DM_TONEON    0x01  /* Tone ON Mask */
#define DM_TONEOFF   0x02  /* Tone OFF Mask */

#define TONEALL      0xFFFFFFFF   /* Enable/Disable All Tone ID's */

#define TN_SINGLE    0     /* Single Tone */
#define TN_DUAL      1     /* Dual Tone */

/*
 * Template Modes and Frequency for GTD
 */
#define TN_FREQDEV   5     /* Frequency Deviation */

#define TN_CADENCE   0x01  /* Cadence Detection */
#define TN_LEADING   0x02  /* Leading Edge Detection */
#define TN_TRAILING  0x04  /* Trailing Edge Detection */

//defines for Call Progress Analysis function
#define CA_SIT		0x01		// look for a previously defined SIT tone
#define CA_PAMD	0x02		// use a previously defined PAMD template
#define CA_PVD		0x04		// use a previously defined PVD template.


/*
 * Digit Type Values for User-Defined Tone Templates for GTD
 */
#define DG_USER1     5     /* User Defined Tone */
#define DG_USER2     6     /* User Defined Tone */
#define DG_USER3     7     /* User Defined Tone */
#define DG_USER4     8     /* User Defined Tone */
#define DG_USER5     9     /* User Defined Tone */
#define MAKE_DIGTYPE(id,digit) ((((id)<<8))|digit)


/**
 ** Speed and Volume Control Defines
 **/
#define SV_SPEEDTBL     0x01     /* Modify Speed */
#define SV_VOLUMETBL    0x02     /* Modify Volume */

#define SV_ABSPOS       0x00     /* Absolute Position */
#define SV_RELCURPOS    0x10     /* Relative to Current Position */
#define SV_TOGGLE       0x20     /* Toggle */

#define SV_WRAPMOD      0x0010
#define SV_SETDEFAULT   0x0020
#define SV_LEVEL        0x0100
#define SV_BEGINPLAY    0x0200

/*
 * Toggle Modes for Play Adjustment Conditions
 */
#define SV_TOGORIGIN    0x00  /* Toggle Between Origin and Last */
                              /* Modified Position */
#define SV_CURORIGIN    0x01  /* Reset Current Position to Origin */
#define SV_CURLASTMOD   0x02  /* Reset Current Position to Last */
                              /* Modified Position */
#define SV_RESETORIG    0x03  /* Reset Current Position and Last */
                              /* Modified State to Origin */

/*
 * Defines for dx_addspddig()
 */
#define SV_ADD10PCT   1    /* Speed up Play-Back 10 Percent */
#define SV_ADD20PCT   2    /* Speed up Play-Back 20 Percent */
#define SV_ADD30PCT   3    /* Speed up Play-Back 30 Percent */
#define SV_ADD40PCT   4    /* Speed up Play-Back 40 Percent */
#define SV_ADD50PCT   5    /* Speed up Play-Back 50 Percent */
#define SV_SUB10PCT  -1    /* Slow Down Play-Back 10 Percent */
#define SV_SUB20PCT  -2    /* Slow Down Play-Back 20 Percent */
#define SV_SUB30PCT  -3    /* Slow Down Play-Back 30 Percent */
#define SV_SUB40PCT  -4    /* Slow Down Play-Back 40 Percent */

#define SV_NORMAL    0xFF  /* Set Play-Back to Normal Speed/Volume */

/*
 * Defines for dx_addvoldig()
 */
#define SV_ADD2DB     1    /* Increase Play-Back Volume by 2db */
#define SV_ADD4DB     2    /* Increase Play-Back Volume by 4db */
#define SV_ADD6DB     3    /* Increase Play-Back Volume by 6db */
#define SV_ADD8DB     4    /* Increase Play-Back Volume by 8db */
#define SV_SUB2DB    -1    /* Decrease Play-Back Volume by 2db */
#define SV_SUB4DB    -2    /* Decrease Play-Back Volume by 4db */
#define SV_SUB6DB    -3    /* Decrease Play-Back Volume by 6db */
#define SV_SUB8DB    -4    /* Decrease Play-Back Volume by 8db */

#define IGNORESTATE   1

/*
 * Wave file support defines
 */
/*
 * File formats
 */
#define FILE_FORMAT_VOX    1     /* Dialogic VOX format */
#define FILE_FORMAT_WAVE   2     /* Microsoft Wave format */
#define FILE_FORMAT_NONE   3     /* No file being used */

/*
 * Sampling rate
 */
#define DRT_6KHZ           0x30  /* 6KHz */
#define DRT_8KHZ           0x40  /* 8KHz */
#define DRT_11KHZ          0x58  /* 11KHz */

/*
 * Data format
 */
#define DATA_FORMAT_DIALOGIC_ADPCM		        0x1		/* OKI ADPCM */
#define DATA_FORMAT_ALAW				        0x3		/* alaw PCM  */
#define DATA_FORMAT_G726				        0x4		/* G.726     */
#define DATA_FORMAT_MULAW				        0x7		/* mulaw PCM */
#define DATA_FORMAT_PCM					        0x8		/* PCM       */
#define DATA_FORMAT_G729A				        0x0C	/* CELP coder */
#define DATA_FORMAT_GSM610				        0x0D	/* Microsoft GSM (backward compatible*/
#define DATA_FORMAT_GSM610_MICROSOFT	        0x0D	/* Microsoft GSM */
#define DATA_FORMAT_GSM610_ETSI			        0x0E	/* ETSI standard framing */
#define DATA_FORMAT_GSM610_TIPHON		        0x0F	/* ETSI TIPHON bit order */
#define DATA_FORMAT_LC_CELP			            0x10		/* Lucent CELP Coder */
#define DATA_FORMAT_TRUESPEECH			        0x10		/* TRUESPEECH Coder */
#define DATA_FORMAT_G711_ALAW	                DATA_FORMAT_ALAW
#define DATA_FORMAT_G711_ALAW_8BIT_REV	        0x11
#define DATA_FORMAT_G711_ALAW_16BIT_REV	        0x12
#define DATA_FORMAT_G711_MULAW	                DATA_FORMAT_MULAW
#define DATA_FORMAT_G711_MULAW_8BIT_REV	        0x13
#define DATA_FORMAT_G711_MULAW_16BIT_REV	    0x14
#define DATA_FORMAT_G721	                    0x15
#define DATA_FORMAT_G721_8BIT_REV	            0x16
#define DATA_FORMAT_G721_16BIT_REV	            0x17
#define DATA_FORMAT_G721_16BIT_REV_NIBBLE_SWAP	0x18


#define DATA_FORMAT_FFT             0xFF  /* fft data  */

/*
 * dx_gtsernum() subfunctions
 */
#define GS_SN  0x0000   /* ret. board serial #, 8 bytes ASCIIZ string */
#define GS_SSN 0x0001   /* ret. board silicon serial number, 8 bytes */


/*
 * Channel I/O status defines
 */
#ifndef IN_SERVICE
#define IN_SERVICE  0      /* Put the channel back into service */
#endif
#ifndef OUT_SERVICE
#define OUT_SERVICE 1      /* Take the channel out of service */
#endif


/*
 * DX_EBLK
 *
 * Event block structure
 * [NOTE: All user-accessible structures must be defined so as to be
 *        unaffected by structure packing.]
 */
typedef struct dx_eblk {
   unsigned short  ev_event;     /* Event that occured */
   unsigned short  ev_data;      /* Event-specific data */
   unsigned char   ev_rfu[12];   /* RFU for packing-independence */
} DX_EBLK;


/*
 * DX_CST
 *
 * Call Status Transition Structure
 * [NOTE: All user-accessible structures must be defined so as to be
 *        unaffected by structure packing.]
 */
typedef struct dx_cst {
   unsigned short cst_event;     /* CST Event */
   unsigned short cst_data;      /* Data Associated with the Event */
} DX_CST;


/*
 * Speed and Volume Control typedefs
 */

/*
 * Speed/Volume Condition Block
 */
typedef struct dx_svcb {
   unsigned short type;       /* Bit Mask */
   short          adjsize;    /* Adjustment Size */
   unsigned char  digit;      /* ASCII digit value that causes the action */
   unsigned char  digtype;    /* Digit Type (e.g. 0 = DTMF) */
} DX_SVCB;


/*
 * Speed/Volume Modification Table
 */
typedef struct dx_svmt {
  char decrease[ 10 ];        /* Ten Downward Steps */
  char origin;                /* Regular Speed and Volume */
  char increase[ 10 ];        /* Ten Upward Steps */
} DX_SVMT;


/*
 * Standard Call Progress Signal Definitions
 */
#define CP_DIAL                 dx_get_tngencad ( 1 )   
#define CP_REORDER              dx_get_tngencad ( 2 )   
#define CP_BUSY                 dx_get_tngencad ( 3 )   
#define CP_RINGBACK1            dx_get_tngencad ( 4 )   
#define CP_RINGBACK2            dx_get_tngencad ( 5 )   
#define CP_RINGBACK1_CALLWAIT   dx_get_tngencad ( 6 )   
#define CP_RINGBACK2_CALLWAIT   dx_get_tngencad ( 7 )
#define CP_RECALL_DIAL          dx_get_tngencad ( 8 )
#define CP_INTERCEPT            dx_get_tngencad ( 9 )
#define CP_CALLWAIT1            dx_get_tngencad ( 10 )
#define CP_CALLWAIT2            dx_get_tngencad ( 11 )
#define CP_BUSY_VERIFY_A        dx_get_tngencad ( 12 )
#define CP_BUSY_VERIFY_B        dx_get_tngencad ( 13 )
#define CP_EXEC_OVERRIDE        dx_get_tngencad ( 14 )
#define CP_FEATURE_CONFIRM      dx_get_tngencad ( 15 )
#define CP_MSG_WAIT_DIAL        dx_get_tngencad ( 16 ) // Same as CP_STUTTER_DIAL
#define CP_STUTTER_DIAL         dx_get_tngencad ( 16 ) // Same as CP_MSG_WAIT_DIAL
#define MAX_CP_TONES            16


/*
 * Tone Generation Template
 */
typedef struct {
   unsigned short tg_dflag;   /* Dual Tone - 1, Single Tone - 0 */
   unsigned short tg_freq1;   /* Frequency for Tone 1 (HZ) */
   unsigned short tg_freq2;   /* Frequency for Tone 2 (HZ) */
   short          tg_ampl1;   /* Amplitude for Tone 1 (db) */
   short          tg_ampl2;   /* Amplitude for Tone 2 (db) */
   short          tg_dur;     /* Duration of the Generated Tone */
                              /* Units = 10ms */
} TN_GEN;

/*
 * Cadenced Tone Generation Template
 */
typedef struct {
   unsigned char cycles;      /* Number of cycles */
   unsigned char numsegs;     /* Number of tones */
   short         offtime[4];  /* Array of durations, one for each tone */
   TN_GEN        tone[4];     /* Array of tone templates */
} TN_GENCAD;

/*
 * Tone Template Structure
 */
typedef struct {
   unsigned char  tn_dflag;      /* Dual Tone -1, Single Tone - 0 */
   unsigned char  tn_ampflg;	 /* If set use tone amplitude values  */
   unsigned short tn1_min;       /* Min. Frequency for Tone 1 (in Hz) */
   unsigned short tn1_max;       /* Max. Frequency for Tone 1 (in Hz) */
   unsigned short tn2_min;       /* Min. Frequency for Tone 2 (in Hz) */
   unsigned short tn2_max;       /* Max. Frequency for Tone 2 (in Hz) */
   unsigned short tn_quality;    /* Qualification Template Number */
   unsigned short tn_pquality;   /* Qualification Template Number for */
                                 /*  Playback */
   unsigned short tn_id;         /* Tone Template ID Number */
   unsigned char  tn_ascii;      /* ASCII Digit Value */
   unsigned char  tn_digtype;    /* Digit Type */
   unsigned short tn_rep_cnt;    /* Debounce Rep Count */
   unsigned short tnon_min;      /* Debounce Min. ON Time */
                                 /*  (in 10msec units) */
   unsigned short tnon_max;      /* Debounce Max. ON Time */
                                 /*  (in 10msec units) */
   unsigned short tnoff_min;     /* Debounce Min. OFF Time */
                                 /*  (in 10msec units) */
   unsigned short tnoff_max;     /* Debounce Max. OFF Time */
                                 /*  (in 10msec units) */
   unsigned short tn_minampl1;   /* Minimum amplitude of frequency 1 */
   unsigned short tn_maxampl1;   /* Maximum amplitude of frequency 1 */
   unsigned short tn_minampl2;   /* Minimum amplitude of frequency 2 */
   unsigned short tn_maxampl2;   /* Maximum amplitude of frequency 2 */
} TN_TMPLT;


/*
 * Tone Information Structure
 */
typedef struct {
   unsigned short tn_freq1;   /* Actual Freq of Tone 1 detected (Hz) */
   unsigned short tn_freq2;   /* Actual Freq of Tone 2 detected (Hz) */
   unsigned short tn_on;      /* Actual On Time (in 10msec units) */
   unsigned short tn_off;     /* Actual Off Time (in 10msec units) */
   unsigned short tn_rep_cnt; /* Actual Rep Count */
   unsigned short rfu;        /* Reserved */
} TN_INFO;

/*
 * Transfer parameter block
 */
 typedef struct {
   unsigned short wFileFormat;    /* file format */
   unsigned short wDataFormat;    /* data encoding */
   unsigned long  nSamplesPerSec; /* sampling rate */
   unsigned short wBitsPerSample; /* bits per sample */
} DX_XPB;

/*
 * FEATURE_TABLE structure
 */
typedef struct feature_table {
   unsigned short ft_play;
   unsigned short ft_record;
   unsigned short ft_tone;
   unsigned short ft_e2p_brd_cfg;
   unsigned short ft_fax;
   unsigned short ft_front_end;
   unsigned short ft_misc;
   unsigned short ft_send;
   unsigned short ft_receive;
   unsigned short ft_rfu[6];
} FEATURE_TABLE;

/*
 * Defines for features supported on a device.
 * Use with the feature table obtained from dx_getfeaturelist.
 */
/* Play and Record features */
#define FT_ADPCM           0x0001
#define FT_PCM             0x0002
#define FT_ALAW            0x0004
#define FT_ULAW            0x0008
#define FT_LINEAR          0x0010
#define FT_ITU_G_726       0x0020
#define FT_ADSI            0x0040
#define FT_RAW64KBIT       0x0080
#define FT_DRT6KHZ         0x0100
#define FT_DRT8KHZ         0x0200
#define FT_DRT11KHZ        0x0400
//07-07-1999[cjl] added these defines ******************************************
#define FT_FFT					0x0800
#define FT_FSK_OH				0x1000
#define FT_G729A				0x2000
#define FT_MSGSM				0x4000
//******************************************************************************

/* GTD and GTD features */
#define FT_GTDENABLED      0x0001
#define FT_GTGENABLED      0x0002
#define FT_CADENCE_TONE    0x0004

/* E2P features */
#define FT_CALLP           0x0002
#define FT_MF_TONE_DETECT  0x0004
#define FT_DPD             0x0020
#define FT_SYNTELLECT      0x0040
#define FT_ECR					0x0080
#define FT_CSP					0x0100
#define FT_CONFERENCE			0x0200

/* FAX features */
#define FT_FAX             0x0001
#define FT_VFX40           0x0002
#define FT_VFX40E          0x0004
#define FT_VFX40E_PLUS     0x0008
#define FT_FAX_EXT_TBL	   0x10
#define FT_SENDFAX_TXFILE_ASCII	0x02
#define FT_RS_SHARE        0x20
#define RSC_FAX            0x34
#define RSC_ASSIGNED       1
#define RSC_NOTASSIGNED    0

/* FrontEnd features */
#define FT_ANALOG          0x0001
#define FT_EARTH_RECALL    0x0002
#define  FT_ROUTEABLE      0x0004
#define  FT_ISDN           0x0008
#define  FT_CAS            0x0010
#define  FT_R2MF           0x0020


/* Feature Options */
#define FT_CALLERID        0x0001
#define FT_PROMPTEDREC     0x0002     /* Prompted Record (triggered by VAD) */
#define FT_GAIN_AND_LAW    0x0004     /* TDM ASIC is Gain/Law conversion capable */
#define FT_VAD             0x0008     /* Voice Activity Detection */
#define FT_RECFLOWCONTROL  0x0010     /* Flow control on recording channels */
#define FT_CSPEXTRATSLOT   0x0020     /* Reserve extra tx tslot for CSP */


/*
 * Type definition for Channel/Timeslot device info structure and its values
 */
#ifndef __CT_DEVINFO__
#define __CT_DEVINFO__

/*
 * CT_DEVINFO structure
 */
typedef struct ct_devinfo {
   unsigned long  ct_prodid;
   unsigned char  ct_devfamily;
   unsigned char  ct_devmode;
   unsigned char  ct_nettype;
   unsigned char  ct_busmode;
   unsigned char  ct_busencoding;
   unsigned char  ct_rfu[7];
} CT_DEVINFO;

/*
 * Value defines
 */
/* device family */
#define CT_DFD41D			  0x01
#define CT_DFD41E         0x02
#define CT_DFSPAN         0x03
#define CT_DFMSI          0x04
#define CT_DFDM3          0x05

/* device mode */
#define CT_DMNETWORK      0x00
#define CT_DMRESOURCE     0x01

/* network type */
#define CT_NTNONE         0x00
#define CT_NTT1           0x01
#define CT_NTE1           0x02
#define CT_NTANALOG       0x03
#define CT_NTMSI          0x04
#define CT_NTIPT          0x05

/* bus mode */
#define CT_BMPEB          0x00
#define CT_BMSCBUS        0x01
#define CT_BMH100			  0x06
#define CT_BMH110			  0x07

/* bus encoding */
#define CT_BEULAW         0x00
#define CT_BEALAW         0x01

/*
 * DATA TRANSFER API
 */
#define DT_ADSI		0x0001
#define DT_RAWDATA	0x0002

/*
 * ADSI data transfer modes
 */
#define ADSI_ALERT		0x000A
#define ADSI_NOALERT		0x0005
#define ADSI_ONHOOK_SEIZURE	0x0009
#define ADSI_ONHOOK_NOSEIZURE	0x000B

/*
 * ADSI data transfer structure
 */
typedef struct _ADSI_XFERSTRUC {
   UINT		cbSize;
   DWORD	dwTxDataMode;
   DWORD	dwRxDataMode;
} ADSI_XFERSTRUC;
 
/*
 * RAW data transfer modes
 */
#define RAW_64KBIT		0x0006

/*
 * RAW data transfer structure
 */
typedef struct _RAWDATA_XFERSTRUC {
   UINT		cbSize;
   DWORD	dwTxDataMode;
   DWORD	dwRxDataMode;
} RAWDATA_XFERSTRUC;

#endif


/*
 * Type definition for SCBus Timeslots information structure.
 */
#ifndef __SC_TSINFO__
#define __SC_TSINFO__
typedef struct sc_tsinfo {
   unsigned long  sc_numts;
   long          *sc_tsarrayp;
} SC_TSINFO;
#endif

/*
 * Type definition for ECR Characteristic Table structure.
 */
#ifndef __DX_ECRCT__
#define __DX_ECRCT__
typedef struct dx_ecrct {
   int  ct_length;		/* Sizeof this structure */
   unsigned char ct_NLPflag;	/* NLP required during echo-cancellation? */
} DX_ECRCT;

#define SIZE_OF_ECR_CT sizeof(DX_ECRCT)
#define ECR_CT_ENABLE  0
#define ECR_CT_DISABLE 1
#endif

/*
 * Definition for Read/Write Callback Routine
 */
typedef void (*DXRWROUTINE)(DWORD, PCHAR, DWORD);
/***********************************************************************
 *        FILE: srllib.h
 * DESCRIPTION: Header File for DIALOGIC Standard Runtime Windows
 *              NT/95 library
 *
 *   Copyright (c) Dialogic Corp. All Rights Reserved
 *
 *   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF Dialogic Corp.
 *   The copyright notice above does not evidence any actual or
 *   intended publication of such source code.
 ********************************************************************/


#ifndef __SRLLIB_H__
#define __SRLLIB_H__


#include <windows.h>


/*
 * Included header files
 */
#include "srl_eblk.h"
#include "srltpt.h"


/* Define NULL if it hasn't been defined already */
#ifndef NULL
#define NULL        0L
#endif

/**
 ** Defines used for standard attributes 
 **/
/*
 * Undefined attribute or Failed to get attribute
 */
#define AT_FAILURE   -1
#define AT_FAILUREP  NULL

#define EDV_BADDESC  -1
#define EDV_NOERROR  0

/* Open Flags for devices */
#define OF_DEFAULT   0x00  /* Open device without automatic notification */
#define O_NOTIFY     0x01  /* Open device with automatic notification */


/*
 * General Defines
 */
#define EV_ANYEVT          0xFFFFFFFF  /* Matches Any Event Type */
#define EV_ANYDEV          -1          /* Matches Any Device */
#define SR_DFLT_DATASIZE   48          /* Max size for SRl's statically allocated
                                          event data area */

/* 
 * EVENT MANAGEMENT
 */
#define SR_INTERPOLLID  0x01  /* Parameter id for inter-poll delay */
#define SR_MODEID       0x02  /* Set SRL to run in SIGNAL/POLL mode */
#define SR_DATASZID     0x03  /* Parameter id for getting/setting SRL's
                                 preallocated event data memory size */
#define SR_QSIZEID      0X04  /* Maximum size of SRL's internal event queue */
#define SR_MODELTYPE    0x05  /* Set SRL model type (for NT only) */
#define SR_USERCONTEXT  0x06  /* Allows user to set per device context */
#define SR_WIN32INFO	   0x07  /* Set Win32 Notification mechanism */     
#define SR_STATISTICS   0x08  /* Set statistics monitoring */
#define SR_PARMHIPRIMODE 0x09 /* High Priority handler mode */

#define SR_POLLMODE     0     /* Run SRL in polling mode */
#define SR_SIGMODE      1     /* Run SRL in signalling/interrupt mode */
#define SRL_DEVICE      0     /* The SRL device */
#define SR_TMOUTEVT     0     /* Timeout event - occurs on the SRL DEVICE */

#define SR_STASYNC      0     /* Single threaded async model */
#define SR_MTASYNC      1     /* Multithreaded asynchronous model */
#define SR_MTSYNC       2     /* Multithreaded synchronous model */

#define SR_NOTIFY_ON    0     /* Turn on message notification */
#define SR_NOTIFY_OFF   1     /* Turn off message notification */

#define SR_HIPRIDEFAULT 0        
#define SR_HIPRISYNC    1


/* SRL errors */
#define ESR_NOERR       0     /* No SRL errors */
#define ESR_SCAN        1     /* SRL scanning function returned an error */
#define ESR_PARMID      2     /* Unknown parameter id */
#define ESR_TMOUT       3     /* Returned by ATDV_LASTERR(SRL_DEVICE) when an
                                 SRL function times out */
#define ESR_SYS         4     /* System error - consult errno */
#define ESR_DATASZ      5     /* Invalid size for default event data memory */
#define ESR_QSIZE       6     /* Illegal event queue size */
#define ESR_NOHDLR      7     /* No such handler */
#define ESR_MODE        8     /* Illegal mode for this operation */
#define ESR_NOTIMP      9     /* Function not implemented */

#define SR_TMOUT        -1    /* Returned by event scanning functions
                                 (e.g. sr_waitevt()) when they time out */

/*
 * Defines for DLL modes (to be passed to the xx_libinit functions)
 */
#define DLGC_ST         0     /* Single threaded operation */
#define DLGC_MT         1     /* Multithreaded operation */

/*
 * SRL Win/32 Synchronization Structure (use sr_setparm to set)
 */
typedef struct srlwin32info_tag {
   DWORD		dwTotalSize;	/* Structure size */
   HANDLE		ObjectHandle;	/* Object Handle */
   DWORD		dwHandleType;   /* Handle type */
   DWORD		UserKey;        /* User supplied key */
   LPOVERLAPPED	lpOverlapped;   /* pointer to an overlapped */
} SRLWIN32INFO, *LPSRLWIN32INFO;

/*
 * Flags for dwHandleType
 */
#define  SR_IOCOMPLETIONPORT	1	/* I/O Completion Port */
#define  SR_RESETEVENT			2	/* Reset Event */
#define  SR_WINDOWHANDLE        3   /* Window Handle */

/**
 ** Define Event Types
 **/
#define TEC_STREAM	0xE0					//termination event for ec_stream/ec_reciottdata
#define TEC_VAD		0xE1					//event returned when VAD sees energy

/* Event mask id (internal) */
#define DE_CONVERGED       22    /* EC converged */


/* Event mask values */
#define DM_CONVERGED ( 1 << (DE_CONVERGED - 1) )


/* Event Types */
#define TEC_CONVERGED      0xE2  /* event returned when echo canceller has converged */


/*
 * Error codes returned by ATDV_LASTERR()
 */
#define EEC_UNSUPPORTED	EDX_BADPROD

/* parameters */
#define ECCH_XFERBUFFERSIZE ((PM_SHORT|PM_LIB|PM_DXXX|PM_CH) | 0x0005L)
#define ECCH_NLP			((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x021CL)
#define ECCH_VADINITIATED   ((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x021FL)
#define DXCH_BARGEIN		((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x021DL)
#define ECCH_ADAPTMODE      ((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x021EL)
#define ECCH_ECHOCANCELLER  ((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x0220L)
#define ECCH_SVAD           ((PM_SHORT|PM_FW |PM_DXXX|PM_CH) | 0x0225L)

#define DXCH_SPEECHTRIGG        DXCH_SPEECHPLAYTRIGG
#define DXCH_SPEECHWINDOW       DXCH_SPEECHPLAYWINDOW

//stop codes
#define SENDING		0x0001
#define RECEIVING		0x0002
#define FULLDUPLEX	(SENDING | RECEIVING)

#endif

/***********************************************************************
 *        FILE: faxlib.h
 * DESCRIPTION: Header File for DIALOGIC Windows NT library
 *
 *   Copyright (c) 1996 Dialogic Corp. All Rights Reserved
 *
 *   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF Dialogic Corp.
 *   The copyright notice above does not evidence any actual or
 *   intended publication of such source code.
 **********************************************************************/

#ifndef __FAXLIB_H__
#define __FAXLIB_H__


/*
 * Fax channel parameters
 */

#define	PM_FXXX      	0x03000000	/* Identify as a FAX parameter */

/* 
 * Defines to indicate source and type of parameter (in dxxxlib.h)
 */
#define	FX_LBCPRM_SHT   (PM_LIB|PM_CH|PM_FXXX|PM_SHORT) 

/* Retry count (default=0, max=DF_RETRY3). The DF_RETRYx define can be
 * ORed with DF_RETRYDCN to cause a disconnect when max retries are reached.
 * ex:  DF_RETRY3|DF_RETRYDCN
 */
#define FC_RETRYCNT (FX_LBCPRM_SHT|0x0001) 

/* Defines for retransmission capabilities */
#define  DF_RETRYDCN    0x8000   /* Disconnect on max retries */
#define  DF_NORETRY     0x0      /* (default) */
#define  DF_RETRY1      0x1      /* retry once */
#define  DF_RETRY2      0x2      /* retry twice */
#define  DF_RETRY3      0x3      /* retry three times */

/* 
 * Inter-page D cmd sent by Transmitter in between pages
 * for multi-page TIFF documents.
 * Values: DFC_AUTO, DFC_MPS, DFC_EOM. Default: DFC_EOM 
 * NOTE: The default is maintained at DFC_EOM for backward compatibility.
 *       It is recommended that this parameter be set to DFC_AUTO.
 *       DFC_AUTO allows the fax library to automatically determine the 
 *       inter-page phase D value during a fax transmission.
 */
#define FC_SENDCONT (FX_LBCPRM_SHT|0x0002) 

/*
 * Delimiter for fx_rcvfax() for reception of TIFF documents. 
 * Allows the application to store each received page in seperate TIFF files.
 * Values: DFS_MPS, DFS_EOM, DFS_ALL (for both MPS & EOM).
 * Default: DFC_EOP -- store all received pages in single TIFF file and 
 * complete fx_rcvfax()  only after all pages have been received.
 */
#define FC_ENDDOC  (FX_LBCPRM_SHT|0x0003)

/* 
 * Local and Remote Id parameters.  The NULL terminated id string can 
 * have a maximum length of 20 characters plus NULL termination.
 */
#define FC_LOCALID   (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x010)
#define FC_REMOTEID  (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x011)

/* 
 * Parmeters for controlling percentage of acceptable bad scan lines received.
 * FC_RTN - default 15 - 15% bad scan lines before RTN sent in Phase D.
 * FC_RTP - default  5 -  5% bad scan lines before RTP sent in Phase D.
 */
#define FC_RTN       (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x012)
#define FC_RTP       (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x013)
#define FC_T1               (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x003)
#define FC_CNG              (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x00B)
#define FC_BCNG             (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x00C)
/* 
 * Parameter for selecting the preferred baud rate for transmission.
 */
#define FC_TXBAUDRATE   (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x014)

/* Valid values for Transmission baud rate */
#define   DF_MAXBAUD     0xFFFF       /* Set to maximum supported rate */
#define   DF_14400BAUD   14400   
#define   DF_12200BAUD   12200   
#define   DF_9600BAUD    9600 
#define   DF_7200BAUD    7200
#define   DF_4800BAUD    4800
#define   DF_2400BAUD    2400

/* 
 * Parameter for selecting the baud rate for reception.
 * Valid values for FC_RXBAUDRATE are DF_14400BAUD, DF_9600BAUD,
 * DF_7200BAUD, DF_4800BAUD.
 */
#define FC_RXBAUDRATE   (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x018)

/*
 * Firmware parameter to select preferred transmit line encoding scheme:
 * Default value - DF_MMR. Other supported values - DF_MH, DF_MR
 * OR with DF_ECM to use ECM (Error Correcting Mode).
 */
#define FC_TXCODING   (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x01F)

#define DF_ECM     0x8000  /* OR with FC_TXCODING value to use ECM */

/*
 * Firmware parameter to specify the desired subaddress(es).
 */
#define FC_TXSUBADDR  (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x027)

/*
 * Firmware parameter to read the remote station subaddress string.
 */
#define FC_REMOTESUBADDR  (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x028)

/*
 * Firmware parameter to select Receive storage encoding scheme:
 * Default value - DF_MH. Other supported values - DF_MMR
 */
#define FC_RXCODING   (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x020)

/* 
 * Parameter to set zero- or one- based page numbering for TIFF/F files
 * read by fx_sendfax().  Default is zero based (TF_BASE0) as defined by
 * TIFF/F specifications.  Some applications may create TIFF/F files that
 * do not adhere to zero based page numbering specifiaction. For such
 * cases, this parameter must be set to TF_AUTOPG so that the fax library
 * may automatically determine the correct page numbering scheme.
 * NOTE: Applications must always use zero based page numbering (i.e first page
 * is page 0, second page is page 1 etc.) when specifying pages in the DF_IOTT.
 * The fax library will internally adjust the page number based on the 
 * value of the FC_TFPGBASE parameter.
 */
#define FC_TFPGBASE  (FX_LBCPRM_SHT|0x0010)

/*
 * Values for the TIFF/F page base parameter
 */
#define     TF_BASE0    0    /* Zero base TIFF/F file (default) */
#define     TF_BASE1    1    /* One base TIFF/F file */
#define     TF_AUTOPG   2    /* Automatic page scheme handling */

/* Parameter to set TIFF/F tag checking level */
#define FC_TFTAGCHECK (FX_LBCPRM_SHT|0x0011)

/* Font parameters for SoftFax rendering of ASCII documents */
#define FC_FONT0			(PM_LIB|PM_CH|PM_FXXX|PM_INT|0x0007)
#define FC_FONT3			(PM_LIB|PM_CH|PM_FXXX|PM_INT|0x0008)

/* Parameter for enabling ASCII to MH conversion in host host software or firmware */
#define  FC_SOFTFAX     (PM_LIB|PM_CH|PM_FXXX|PM_INT|0x0009)

/*
 * TIFF/F tag checking level values
 */
#define    TF_MAXTAGS   0    /* check all mandatory tags (default) */
#define    TF_MINTAGS   1    /* check only essential tags */

/*
 * Fax Page Header Parameters: The parameters control the information
 * that is displayed at the top of every transmitted fax page (FAX/4x).
 */
 
/* Fax Header attributes parameter */
#define FC_HDRATTRIB     (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x017)

/* values for header attributes */
#define DF_HDRINSERT     0x00  /* Hdr is inserted before image (default) */
#define DF_HDRDISABLE    0x01  /* Hdr is disabled */
#define DF_HDRUNDERLINE  0x04  /* Hdr is underlined */
#define DF_HDRBOLD       0x08  /* Hdr is displayed in bold typeface */
#define DF_HDRFMT1       0x00  /* Hdr format 1 (default) */
#define DF_HDRFMT2       0x10  /* Hdr format 2 (use FC_HDRUSER2) */

/* Starting page number parameter: (default = 1) */
#define FC_HDRSTARTPAGE   (PM_FW|PM_CH|PM_FXXX|PM_SHORT|0x021)


/*
 * Parameters for Header Format 1.
 */
#define DF_SF_DISABLED	0  /* Disable host base ASCII to MH conversion */
#define DF_SF_ENABLED  1   /* Enable  host base ASCII to MH conversion */

/* Date/Time field parameters */

/* Date format parameter for internal date field generation */
#define  FC_HDRDATEFMT     (FX_LBCPRM_SHT|0x0004) 

/* Values for date format */
#define DF_HDRDATEFMT_0  0  /* disable internal date/time generation */
#define DF_HDRDATEFMT_1  1  /* Date appears as "MM-DD-YYYY"  (US) */
#define DF_HDRDATEFMT_2  2  /* Date appears as "MM/DD/YYYY"  (US) */
#define DF_HDRDATEFMT_3  3  /* Date appears as "DD-MM-YYYY"  (Europe) */
#define DF_HDRDATEFMT_4  4  /* Date appears as "DD/MM/YYYY"  (Europe) */
#define DF_HDRDATEFMT_5  5  /* Date appears as "YYYY-DD-MM"  (Japan) */
#define DF_HDRDATEFMT_6  6  /* Date appears as "YYYY/DD/MM"  (Japan) */
#define DF_HDRDATEFMT_15 15 /* Date appears as "Fri Sep 13 1986" */

/* Time format parameter for internal time field generation */
#define  FC_HDRTIMEFMT     (FX_LBCPRM_SHT|0x0005)

/* Values for date format */
#define DF_HDRTIMEFMT_0  0  /* disable internal date/time generation */
#define DF_HDRTIMEFMT_1  1  /* Time appears as "HH:MM am/pm" (12hr format) */
#define DF_HDRTIMEFMT_2  2  /* Time appears as "HH:MM" (24hr format) */

/* 
 * User formatted Date/Time string parameter - application provides a 
 * string (max 27 chars + null termination) which is directly used in 
 * Date/Time field.  Disable internal generation by setting one or both
 * of the Date/Time format parameters (above) to format 0.
 */
#define FC_HDRDATETIME   (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x015)

/*
 * User string for fax header (max 32 chars + null):
 * Appears between the date/time and page number fields.
 */
#define FC_HDRUSER       (PM_FW|PM_CH|PM_FXXX|PM_VLSTR|0x016)

/*
 * Parameters for Header format 2. 
 * If the application wishes to configure the entire page header string
 * the FC_HDRATTRIB parameter must be set to DF_HDRFMT2 and the 
 * FC_HDRUSER2 parameter set to the string to be displayed.
 * The FC_HDRUSER2 may contain %R and %P to display the remote id and
 * page number.
 */

/* User string for entire Fax Header (128 bytes max) */
#define FC_HDRUSER2      (PM_LIB|PM_CH|PM_FXXX|PM_VLSTR|0x06)

/* End of Fax Page Header parameters */ 

/*
 * Defines for Phase D status values
 */
/* Command's from transmitter - returned by ATFX_PHDCMD() */
#define   DFS_EOP       0     /* End FAX session            */
#define   DFS_MPS       1     /* More pages to follow       */
#define   DFS_EOM       2     /* End of msg, more pgs to follow */
#define   DFS_POLL      3     /* A poll request was sent */
#define   DFS_PRI_EOP   16    /* Request for Operator intervention (PRI-EOP) */
#define   DFS_PRI_MPS   17    /* Request for Operator intervention (PRI-MPS) */
#define   DFS_PRI_EOM   18    /* Request for Operator intervention (PRI-EOM) */

/* Replies from receiver - returned by ATFX_PHDRPY() */
#define   DFS_MCF     1     /* Message Confirmation       */        
#define   DFS_RTN     2     /* Retrain negative           */
#define   DFS_RTP     3     /* Retrain positive           */
#define   DFS_PIP     4     /* Procedure interrupt positive */
#define   DFS_PIN     5     /* Procedure interrupt negative */

/* 
 * Values for FC_ENDDOC parameter
 *  DFS_MPS, DFS_EOM, DFS_ALL, default DFS_EOP 
 */
#define   DFS_ALL     5

/* Phase B status bitmap - returned by ATFX_BSTAT() */
#define  DFS_REMOTEID   0x0100     /* Remote id is available */
#define  DFS_NSF        0x0200     /* NSF is available */
#define  DFS_DCS        0x0400     /* DCS information is available */
#define  DFS_DIS        0x0400     /* DIS information is available */
#define  DFS_REMOTESUBADDR 0x0800  /* subaddress info is available */

/* FAX channel base hardware type - returned by ATFX_CHTYPE() */
#define  DFS_FAX120 0x0000        /* FAX/120 channel */
#define  DFS_FAXDM3 0X0001        /* Dm3 fax channel */
#define  DFS_FAX40  0x3400        /* VFX/40 channel */
#define  DFS_FAX40E 0x3401        /* VFX/40E channel */
#define  DFS_FAX40EPLUS 0x3402    /* VFX/40ESC+ channel */
#define  DFS_FAX40EPLUSREX 0x3403 /* VFX/40ESC+REX channel */
#define  DFS_D41JCT 0x3404        /* D41JCT channel, Basic SoftFax with resource sharing */
#define  DFS_FAX41JCT 0x3405 /* VFX/41JCT channel, Enhanced SoftFax with resource sharing */

/* Line enconding sheme - returned by ATFX_CODING() */
#define   DFS_MH         0      /* 1-D Group 3 Modified Huffmann encoding */
#define   DFS_MR         1      /* 2-D Group 3, T.4 Modified Read encoding */
#define   DFS_MMR        2      /* T.6 Modified Modified Read encoding */

/* Phase B ECM status - returned by ATFX_ECM() */
#define  DFS_ECM_UNAVAILABLE    0       /* ECM unavailable enabled */
#define  DFS_ECM		        1       /* ECM enabled */
#define  DFS_NOECM              2       /* ECM not enabled */

/*
 *  Bits for the rcvflag/sndflag arguments to fx_rcvfax()/fx_sendfax()
 */

/* Enable polling during receive (rcvflag) */
#define   DF_NOPOLL     0x0000     /* Reject a poll */
#define   DF_POLL       0x0002     /* Accept a poll */

/* Enable Remote Terminal Verification (sndflag) */
#define   DF_ENABLE_RTV 0x1000     /* Enable RTV */

/* Enable phase B & D events (rcvflag/sndflag) */
#define   DF_PHASEB     0x0004     /* Generate Phase B event */
#define   DF_PHASED     0x0008     /* Generate Phase D event */

/* Enable/Issue operator intervention (rcvflag/sndflag) */
#define  DF_ISSUE_VRQ   0x0100     /* Issue a voice request */
#define  DF_ACCEPT_VRQ  0x0200     /* Accept a voice request */

/* Receive width selection - set maximum width for reception (rcvflag) */
#define  DF_1728MAX     0x0020     /* Maximum receive width is 1728 pels */
#define  DF_2048MAX     0x0040     /* Maximum receive width is 2048 pels */
                                   /* can recv 1728/2048 */
#define  DF_2432MAX     0x0000     /* Maximum receive width is 2432 pels */
                                   /* can recv 1728/2048/2432 */
                                   /* default */

/* Receive length selection - set maximum length of page (rcvflag) */
#define  DF_A4MAXLEN    0x10000    /* Maximum receive length is A4 size */
#define  DF_B4MAXLEN    0x20000    /* Maximum receive length is B4 size */
#define  DF_NOMAXLEN    0x40000    /* Unlimited receive length */

/* Enable/Disable of T.30 subaddressing information (rcvflag) */
#define  DF_NOSUBADDRDEL 0x0        /* Do not delimit with Phase B msg. */
#define  DF_SUBADDRDEL   0x400000   /* Delimit with T.30 SUB Pase B msg. */

/* 
 * Transmission Resolution Selection (sndflag).
 * If neither of these bits is set, the DF_IOTTs are transmitted at
 * the resolutions at which the documents are stored.
 */
#define  DF_TXRESLO    0x080000   /* Transmit all data in coarse resln */
#define  DF_TXRESHI    0x100000   /* Transmit all data in fine resln */

/* 
 * Storage Resolution Selection during receive (rcvflag).
 * If neither of these bits are set, the received file
 * is stored at the resolution at which the data is received.
 */
#define  DF_RXRESLO    0x080000   /* Store all received data in coarse resln */
#define  DF_RXRESHI    0x100000   /* Store all received data in fine resln */

/*
 * T.30 Subaddress Fax routing.
 */
#define  DF_TXSUBADDR    0x200000   /* Send a fax with subaddress info. */

/* 
 *  Fax Library error codes returned by ATDV_LASTERR( )
 */
#define   EFX_NOTIMP	  0x0100   /* Function not implemented */
#define   EFX_POLLED      0x0101   /* Received poll from remote */
#define   EFX_NOPOLL      0x0102   /* Remote did not accept poll */
#define   EFX_COMPAT      0x0103   /* Hardware incapable of transmitting at
                                    * specified width and resolution
                                    */
#define   EFX_BADTIF      0x0104    /* Incorrect TIFF/F format */
#define   EFX_BADTAG      0x0105    /* Incorrect values for TIFF/F tags */
#define   EFX_NOPAGE      0x0106    /* Specified page missing in TIFF/F file */
#define   EFX_DISCONNECT  0x0107    /* Remote has disconnected */
#define   EFX_RETRYDCN    0x0108    /* Disconnected after specifed retries */
#define   EFX_BADIOTT     0x0109    /* DF_IOTT has incorrect entries */
#define   EFX_BADPAGE     0x010A    /* Not a valid page in TIFF/F file */
#define	  EFX_NOSTATE     0x010B    /* Initial state not set */
#define   EFX_BADSTATE    0x010C    /* Incorrect value for initial state */
#define   EFX_MAXCHAN     0x010D  /* async case: max chan capacity reached */
#define   EFX_NOMEM       0x010E  /* cannot allocate memory for more pages */
#define   EFX_INVALARG    0x010f   /* illegal argument to function */
#define   EFX_INVALFUNC   0x0110   /* illegal call to function - calling
				    *  fx_initstat() when fax in progress or
				    * ATFX_xxx() before a fax session
				    */
#define   EFX_NOFAX       0x0111    /* no fax capability on this board */
#define   EFX_NOTIDLE     0x0112    /* channel is not idle */
#define   EFX_BADPARM     0x0113    /* Invalid value for fax parameter */
#define   EFX_BADTFHDR    0x0114    /* Bad TIFF/F header */
#define   EFX_UNSUPPORTED 0x0115    /* Unsupported feature */
#define   EFX_RDFWVER     0x0116    /* Error reading firmware version */
#define   EFX_NSFBUFF     0x0118    /* NSF buffer less than 2 bytes long */
#define   EFX_NODATA      0x0119    /* Requested data not available */
#define   EFX_NOTIMESLOT  0x011A    /* No timeslot assigned to Fax channel */
#define	  EFX_INVALID_FONT 0x011B   /* Invalid font in font file */

#define   EFX_CMDDATA     0x01fb   /* Invalid cmd/data sent to Firmware */
#define   EFX_FWERROR     0x01fc   /* Firmware Error */
#define   EFX_BADPHASE    0x01fd   /* unexpected phase transition */
#define   EFX_DRVERROR    0x01fe   /* Error in Driver */
#define   EFX_LIBERROR    0x01ff   /* Error in library state machine */

/*
 * Initial protocol states - set with fx_initstat()
 */
#define     DF_RX       0      /* Receiver    */
#define     DF_TX       1      /* Transmitter */

/* 
 * The DF_ASCIIDATA structure - for use with transmission of ASCII data
 * A pointer to this structure may be passed in the DF_IOTT structure for
 * transmitting an ASCII file. Default values are assumed if no DF_ASCIIDATA
 * is specified.
 */

typedef struct {
   unsigned short pagelength;     /* Page length */
   unsigned short pagepad;        /* Pad with blank scan lines to page end */
   unsigned short topmargin;      /* Top margin */
   unsigned short botmargin;      /* Bottom margin */
   unsigned short leftmargin;     /* Left margin */
   unsigned short rightmargin;    /* Right margin */
   unsigned short linespace;       /* Spacing between Ascii lines */
   unsigned short font;            /* Font selection */
   unsigned short tabstops;        /* Number of tab stops on line */
   unsigned char  units;           /* Units for specifying margins/lengths */
   unsigned char  flags;          /* Reserved for future use */
} DF_ASCIIDATA;

/* Defines for the DF_ASCIIDATA structure */

/* Line spacing */
/* Font dependent line spacing */

#define DF_SINGLESPACE  2  /* Single spacing (default) */
#define DF_DOUBLESPACE  4  /* Double spacing */
#define DF_TRIPLESPACE  6  /* Triple spacing */
#define DF_HALFSPACE    1  /* 1/2 spacing - add (+) to DF_SINGLESPACE
                            *  or DF_DOUBLESPACE
                            */

/* Alternate line spacing equates */
/* Font independent line spacing */

#define DF_6LPI       0x8000  /* 6 lines per inch */
#define DF_4LPI       0x8001  /* 4 lines per inch */
#define DF_3LPI       0x8002  /* 3 lines per inch */
#define DF_2_4LPI     0x8003  /* 2.4 lines per inch */
#define DF_8LPI       0x8004  /* 8 lines per inch */

/* font */
#define  DF_FONT_0   0   /* Normal 10 pitch, 6 lines/inch (default) */
#define  DF_FONT_3   3   /* Compressed 17 pitch, 8 lines/inch */


/* pagepad */
#define  DF_PAD      1   /* Pad to end of page with blank lines (default) */
#define  DF_NOPAD    0   /* No padding */

/* Units.   1/10th inch default */
#define  DF_UNITS_IN10   0  /* Margins and page length in 1/10th inch units */
#define  DF_UNITS_MM     1  /* Margins and page length in millimeter units  */
#define  DF_PELS         2  /* Vertical - coarse resolution scanlines */
                            /* Horizontal - pixels */

/*
 * The DF_IOTT structure 
 */
typedef struct df_iott DF_IOTT;

struct df_iott {
   unsigned long  io_offset;      /* Start page or file offset */
   unsigned long  io_length;      /* Number of pages or length of data */
   char          *io_bufferp;     /* Memory transfer start location */
   DF_IOTT       *io_prevp;       /* Pointer to the previous iott entry */
   DF_IOTT       *io_nextp;       /* Pointer to the next iott entry */
   void          *io_datap;       /* Pointer to additional data associated
				     with io_datatype */
   int            io_fhandle;     /* File descriptor */
   unsigned short io_type;        /* Entry type */
   unsigned short io_datatype;    /* Transmit data type */
   unsigned short io_phdcont;     /* Phase D TX value for last page */
   unsigned short io_width;       /* Image width (raw/ascii mode only) */
   unsigned char  io_resln;       /* Image data resolution (raw mode only) */
   unsigned char  io_coding;      /* Image encoding used (raw mode only) */
   unsigned char  rfu[2];         /* Reserved for future use */
};

/* defines for offset and length as first_page and page_count */
#define   io_firstpg     io_offset
#define   io_pgcount     io_length

/* 
 * Defines for DF_IOTT data structure
 */
/* 
 * Phase D Commands to transmit -- io_phdcont field 
 * Note: Old equates DFC_MPS/DFC_EOM are maintained for backward 
 * compatibility. These equates are obsoleted by DFC_AUTO.
 * Applications are recommended to use DFC_AUTO.
 */
#define   DFC_EOP     0x0      /* End of Procedure - no more pages */
#define   DFC_MPG     0x6      /* Merge page data from next IOTT */
#define   DFC_AUTO    0xFF     /* Automatic phase D determination */


/* Defines for io_datatype */
#define   DF_TIFF      0x0
#define   DF_RAW       0x1
#define   DF_ASCII     0x3     

/* 
 * The fields given below are relevant only for transmission of 
 * RAW image files (io_datatype = DF_RAW) and ASCII files 
 * (io_datatype = DF_ASCII).  For TIFF/F files, this
 * information is embedded in the TIFF/F file itself.
 * For ASCII files, the io_coding field is ignored.
 */

/* 1.  Defines for io_width (also returned by ATFX_WIDTH()) */
#define   DF_WID1728   1728      /* 1728 pels per line */
#define   DF_WID2048   2048      /* 2048 pels per line */
#define   DF_WID2432   2432      /* 2432 pels per line */

/* 2.  Defines for io_resln field (also returned by ATFX_RESLN()) */
#define   DF_RESHI      196      /* Hi (fine) resolution   */
#define   DF_RESLO      98       /* Lo (coarse) resolution */

/* 3.  Defines for io_coding field (also returned by ATFX_CODING()) */
#define   DF_MH         0      /* 1-D Group 3 Modified Huffmann encoding */
#define   DF_MR         1      /* 2-D Group 3, T.4 Modified Read encoding */
#define   DF_MMR        2      /* T.6 Modified Modified Read encoding */

/*
 * Phase E status values for ATFX_ESTAT()
 */

/* Status values returned to transmitter */

#define EFX_T1EXPTX	  100  /* Timer T1 expired waiting for message */  
#define EFX_NODISTX       101  /* Got other than DIS while waiting for DIS */  
#define EFX_GOTDCNTX      102  /* Got DCN while waiting for DIS */  
#define EFX_BADDCSTX      103  /* Bad response to DCS, training */  
#define EFX_PHBDEADTX     104  /* No response to DCS, training or TCF */  
#define EFX_NOISETX       105  /* Too much noise training at 2400 bps */  
#define EFX_BADPGTX       106  /* DCN response after sending page */  
#define EFX_PHDDEADTX     107  /* No response after sending page */  
#define EFX_RXCOMP        109  /* Remote site is not receive compatible */  
#define EFX_INVALRSPTX    110  /* No valid response after sending page */  
#define EFX_NOFINERECTX   111  /* Remote cannot receive fine resln documents */
#define EFX_COMMERRTX     190  /* Transmit communication error */
#define EFX_NXTCMDTX      197  /* Timeout waiting for next send page cmd */  
#define EFX_NOWIDTHTX     202  /* Remote cannot receive at specified width */
#define EFX_ECMRNRTX      210  /* Timer T5 expired, receiver not ready */
#define EFX_ECMPHDTX      211  /* Invalid ECM response from receiver */
#define EFX_INVALMMRTX    213    /* Invalid input MMR data */


/* Status values returned to receiver */

#define EFX_TXCOMP        108  /* Remote site is not transmit compatible */  
#define EFX_T2EXPRX       112  /* Timer T2 expired waiting for NSS/DCS/MCF */
#define EFX_T2EXPMPSRX    113  /* Timer T2 expired waiting for next Fax page */
#define EFX_T2EXPDCNRX    114  /* Timer T2 expired waiting for DCN */
#define EFX_T2EXPDRX      115  /* Timer T2 expired waiting for Phase D */
#define EFX_INVALCMDRX    116  /* Unexpected command after page received */
#define EFX_T2EXPFAXRX    117  /* Timer T2 expired waiting for fax page */
#define EFX_T2EXPRRRX     118  /* Timer T2 expired waiting for RR command */
#define EFX_T1EXPRX	  120  /* Timer T1 expired waiting for message */  
#define EFX_GOTDCSRX	  121  /* DCS received while waiting for DTC */
#define EFX_WHYDCNRX	  127  /* Unexpected DCN while waiting for DCS/DIS */  
#define EFX_DCNDATARX	  128  /* Unexpected DCN while wtng for Fax data */  
#define EFX_DCNFAXRX      129  /* Unexpected DCN while wtng for EOM/EOP/MPS */
#define EFX_DCNPHDRX      130  /* Unexpected DCN after EOM/MPS sequence */  
#define EFX_DCNNORTNRX    131  /* DCN after requested retransmission */  
#define EFX_DCNRRDRX      132  /* Unexpected DCN after RR/RNR sequence */
#define EFX_COMMERRRX     191  /* Receive communication error */
#define EFX_NOFAXRX	  193  /* Timed out waiting for first line */  
#define EFX_NOEOLRX	  194  /* Timed out waiting for EOL */  
#define EFX_NOCARRIERRX	  195  /* Lost carrier during Fax receive */  
#define EFX_NXTCMDRX	  198  /* Timed out wtng for next receive page cmd */
#define EFX_PNSUCRX	  205  /* No PN_SUCCESS returned by modem during rcv */
#define EFX_ECMPHDRX      212  /* Invalid ECM response from transmitter */


/* General status values returned to receiver or transmitter */
#define EFX_BUSYCHN        140  /* Request to start Fax while channel busy */  
#define EFX_ABORTCMD       199  /* Stop Fax command received */  
#define EFX_CHIPNORESP     200  /* Fax modem not responding */  
#define EFX_CEDTONE        201  /* Remote CED tone is longer than 5 secs */  
#define EFX_OPINTFAIL      203  /* Operator intervention failed */  
#define EFX_HDLCCARR       204  /* Excessive HDLC carrier */  


/* 
 * Fax events returned to the application 
 */
#define  TFX_FAXSEND   0x0A1      /* Send fax complete */
#define  TFX_FAXRECV   0x0A2      /* Receive fax complete */
#define  TFX_FAXERROR  0x0A3      /* Error event for Fax */
#define  TFX_PHASEB    0x0A4      /* Phase B event */
#define  TFX_PHASED    0x0A5      /* Phase D event */
#define  TFX_LOADFONT  0x0A6      /* Font loading complete */

/* 
 * Fax termination reasons returned as a bitmap by ATFX_TERMMSK() 
 */
#define  TM_FXTERM     0x01       /* Normal termination */
#define  TM_POLLED     0x02       /* Poll received from remote */
#define  TM_VOICEREQ   0x04       /* Voice request issued/received */


/*
 * The DF_DIS and DF_DCS structures for returning T.30 DCS and DIS
 * messages. Refer T.30 specifications for details. 
 */
typedef struct {
    char dis_data[10];     /* DIS information in LSB format */
} DF_DIS;

typedef struct {
    char dcs_data[10];     /* DCS information in LSB format */
} DF_DCS;

/* 
 * User defined IO functions - read()/write()/seek() 
 */
#if (defined (__cplusplus) || defined( __STDC__ ) || defined (__BORLANDC__))

typedef struct df_uio {
   /* User Defined replacement for read()	*/
   int (* u_read)(int fd, char *bufferp, unsigned count);

   /* User Defined replacement for write()	*/
   int (* u_write)(int fd, char *bufferp, unsigned count);

   /* User Defined replacement for lseek()	*/
   int (* u_seek)(int fd, long offset, int mode);

} DF_UIO;

#else

typedef struct df_uio {
   int (* u_read)();		/* User Defined replacement for read()	*/
   int (* u_write)();		/* User Defined replacement for write()	*/
   int (* u_seek)();		/* User Defined replacement for lseek()	*/
} DF_UIO;

#endif


/* Parameter to cause fax session to be aborted on certain events */
#define FC_STOPCH  (FX_LBCPRM_SHT|0x0001f)


/* 
 * Events on which a session is stopped. Set FC_STOPCH to a bitmap of the 
 * values given below.  Note: dx_setevtmsk() must be used
 * to enable the occurrence of these events.  The events will be intercepted
 * by the fax library and a stop issued to the channel depending on FC_STOPCH.
 */
#define DF_LCOFF   1   /* stop the fax on a loop current drop */



/* Undocumented feature for pre-version 2.0 fax applications ONLY:
 * Backward compatability parameter for old method of indicating a poll.
 * Pre-version 2.0 fax library applications already using the polling feature
 * will need to set this parameter to DF_OLDMODE to activate the old mechanism
 * (fx_rcvfax() returns an error and the error code is set to EFX_POLLED).
 *  By default, a poll is now indicated via the ATFX_TERMMSK() which returns
 * a bitmap of termination reasons.
 */
#define FC_BACKCOMPAT  ((PM_LIB|PM_CH|PM_FXXX|PM_SHORT)|0x000F)

#define DF_NEWMODE   0  /* default */
#define DF_OLDMODE   1  /* Activate pre-version 2.0 poll mechanism */

#define TFX_ORIGINATE	0x0A8	// Dis event was received. Dcs on hold
#define DF_JPEG_GREY		3	// set ECM and T6
#define DF_JPEG_COLOR	4	// set ECM and T6


int  dx_open( const char *namep, int oflags );
int  dx_listen( int chDev, SC_TSINFO *sc_tsinfop );
/*************************************************/
 int  ag_getctinfo( int chDev, CT_DEVINFO *ct_devinfop);
 int  ag_getxmitslot( int chDev, SC_TSINFO *sc_tsinfop);
 int  ag_listen( int chDev, SC_TSINFO *sc_tsinfop );
 int  ag_unlisten( int chDev );
 int  dx_addspddig( int chdev, char digit, short adjval );
 int  dx_addtone( int chdev, unsigned char digit, unsigned char digtype );
 int  dx_addvoldig( int chdev, char digit, short adjval );
 int  dx_adjsv( int chdev, unsigned short tabletype, 
                        unsigned short action, unsigned short adjsize );
 int  dx_blddt( unsigned int id,   unsigned freq1, unsigned int fq1dev, 
                                        unsigned int freq2, unsigned int fq2dev,
                                        unsigned int mode );
 int  dx_blddtcad( unsigned int ToneID, 
                        unsigned int freq1,   unsigned int fq1dev, 
                        unsigned int freq2,   unsigned int fq2dev, 
                        unsigned int OnTime,  unsigned int OnTimeDev, 
                        unsigned int OffTime, unsigned int OffTimeDev, 
                        unsigned int repcnt );
 int  dx_bldst( unsigned int ToneID, unsigned int freq, unsigned int fqdev,
                     unsigned int mode );
 int  dx_bldstcad( unsigned int ToneID, 
                        unsigned int freq, unsigned int fqdev,
                        unsigned int OnTime,  unsigned int OnTimeDev, 
                        unsigned int OffTime, unsigned int OffTimeDev, 
                        unsigned int repcnt );
 void  dx_bldtngen( TN_GEN *tngenp, 
                        unsigned short freq1, unsigned short freq2,
                        short amplitude1,    short amplitude2, short duration );
 int  dx_chgfreq( int tonetype, int fq1, int dv1, int fq2, int dv2 );
 int  dx_chgdur( int typetype, int on, int ondv, int off, int offdv );
 int  dx_chgrepcnt( int tonetype, int repcount );
 int  dx_chgqualid( int qualid );
 int  dx_close( int dev );
 void  dx_clrcap( DX_CAP *capp );
 int  dx_clrdigbuf( int chdev );
 int  dx_clrsvcond( int chdev );
 int  dx_clrtpt( DV_TPT *tptp, int size );
 int  dx_comtest( int chdev );
 int  dx_deltones( int chdev );
 int  dx_dial( int chdev, char *dialstrp, const DX_CAP *capp, unsigned short mode );
 int  dx_distone( int chdev, int toneID, int evtMask );
 int  dx_enbtone( int chdev, int ToneID, int evtMask );
 int  dx_getcursv( int chdev, int *curvolp, int *curspeedp );
 int  dx_getctinfo( int chDev, CT_DEVINFO *ct_devinfop);
 int  dx_getdig( int chdev, const DV_TPT *tptp, DV_DIGIT *digitp, 
                        unsigned short mode );
 int  dx_getevt( int chdev, DX_EBLK *eblkp, int timeout );
 int  dx_getfeaturelist( int chDev, FEATURE_TABLE *feature_tablep);
 int  dx_getparm( int dev, unsigned long parm, void * valuep );
 int  dx_getsvmt( int ChDev, unsigned short tableType, DX_SVMT *svmtp );
 TN_GENCAD *  dx_get_tngencad( unsigned int toneid );
 int  dx_getuio(DX_UIO *appuiop);
 int  dx_getxmitslot( int chDev, SC_TSINFO *sc_tsinfop);
 int  dx_initcallp( int chdev );
 int  dx_listen( int chDev, SC_TSINFO *sc_tsinfop );
// int  dx_open( const char *namep, int oflags );
extern int dx_open( const char *namep, int oflags );
 int  dx_pause( int chDev);
 int  dx_play( int ChDev, DX_IOTT *iottp, const DV_TPT *tptp, 
                        unsigned short mode );
 int  dx_playf(int ChDev, const char *fNamep, const DV_TPT *tptp, unsigned short mode);
 int  dx_playtone( int ChDev, const TN_GEN *tngenp, const DV_TPT *tptp, int mode );
 int  dx_playtoneEx( int ddd, const TN_GENCAD *tngencadp, const DV_TPT *tptp, int mode );
 int  dx_readsram(int ChDev, PUCHAR pBuffer, int BufferSize, int Offset, PCHAR pFileName );
 int  dx_rec(int ChDev, DX_IOTT *iottp, const DV_TPT *tptp, unsigned short mode);
 int  dx_recf( int ChDev, const char *fNamep, const DV_TPT *tptp, unsigned short mode);
 int  dx_resume( int chDev);
 int  dx_route( int BdDev, int Chan, int TimeSlot );
 int  dx_routerxtx( int ddd, int channel, int rxslot, int txslot );
 int  dx_sendevt( int devd, unsigned long evttype, void *evtdatap, short evtlen, unsigned short flags);
 int  dx_setchxfercnt(int chDev, int bufnum);
 int  dx_setdevuio(int chDev, DX_UIO *devuiop, DX_UIO **retuiop);
 int  dx_setdigtyp( int ChDev, unsigned short DigitMask );
 int  dx_setdigbuf( int ChDev, int Mode );
 int  dx_setevtmsk( int ChDev, unsigned int mask );
 void  dx_setgtdamp( short Min1, short Max1, short Min2, short Max2 );
 int  dx_sethook( int ChDev, int HookState, unsigned short mode );
 int  dx_setiostatus(INT SrlDevice, INT Status);
 int  dx_setparm( int Dev, unsigned long parm, const void * valuep );
 int  dx_setrings( int devd, unsigned int nrings );
//weihsin
 int  dx_GetRscStatus (int Dev, unsigned long resourceid, int *);
 int  dx_assignresource (int Dev, unsigned long resourceid);
 int  dx_unassignresource (int Dev, unsigned long resourceid);
 int  dx_getdsprs (int Dev, unsigned long resourceid, char* ApplicationBuffer, long *lpTotalResources, long *NumDSP);

//end
 int  dx_setsvcond( int ChDev, unsigned short numBlks, const DX_SVCB *svcbp );
 int  dx_setsvmt(int ChDev, unsigned short TableType, const DX_SVMT *svmtp,
                      unsigned short flag  );
 int  dx_settonelen( int tonelength );
 int  dx_setuio( DX_UIO );
 int  dx_stopch( int ChDev, unsigned short mode );
 int  dx_unlisten( int chDev );
 int  dx_wink( int ChDev, unsigned short mode );
 int  dx_wtring( int ChDev, int numRings, int HookState, int timeout );
#if defined (__BORLANDC__) || defined (DLGC_CLIB)
 int  dx_fileopen ( const char * filep, int flags, int pmode);
 int  dx_filesopen ( const char * filep, int oflag, int shflag, int pmode);
#else
 int  dx_fileopen ( const char * filep, int flags, ...);
 int  dx_filesopen ( const char * filep, int oflag, int shflag, ...);
#endif
 int  dx_fileclose ( int handle );
 long  dx_fileseek ( int handle, long offset, int origin );
 int  dx_fileread ( int handle, void * buffer, unsigned int count );
 int  dx_filewrite ( int handle, void * buffer, unsigned int count );
 int  dx_filelocking ( int handle, int mode, long bytes );
 int  dx_filechsize ( int handle, long size );
 int  dx_filecommit ( int handle );
 int  dx_filedup ( int handle );
 int  dx_filedup2 ( int handle1, int handle2 );
 int  dx_fileumask ( int pmode );
 long  dx_filetell ( int handle );
 int  dx_filestat ( const char * path, struct _stat * buffer );
 int  dx_filefstat ( int handle, struct _stat * buffer );
 long  dx_filefilelength( int handle );
 int  dx_fileisatty( int handle );
 int  dx_filesetmode( int handle, int mode );
 int  dx_fileopen_osfhandle( long osfhandle, int flags );
 int  dx_fileerrno( void );
 int  dx_playiottdata( int ChDev,DX_IOTT * iottp,const DV_TPT * tptp, 
                                     const DX_XPB * xpbp,unsigned short mode);
 int  dx_playwav( int ChDev, const char * fNamep, const DV_TPT *tptp, 
                                                         unsigned short mode);
 int  dx_playvox( int ChDev, const char * fNamep, const DV_TPT *tptp, 
                                     const DX_XPB * xpbp,unsigned short mode);
 int  dx_reciottdata( int ChDev,DX_IOTT * iottp, const DV_TPT *tptp, 
                                     DX_XPB * xpbp,unsigned short mode);
 int  dx_recwav( int ChDev, const char * fNamep, const DV_TPT *tptp, 
                                     DX_XPB * xpbp,unsigned short mode);
 int  dx_recvox( int ChDev, const char * fNamep, const DV_TPT *tptp, 
                                     DX_XPB * xpbp,unsigned short mode);
 int  dx_mreciottdata( int ChDev,DX_IOTT * iottp, const DV_TPT *tptp, 
                               DX_XPB * xpbp,unsigned short mode, SC_TSINFO *lpTimeSlot);
 int  dx_getr2mf( int Chdev, const char *src1_ptr, unsigned short src1_len,
                        const char *src2_ptr, unsigned short src2_len,
              char *dest_ptr, unsigned short dest_len, unsigned short mode);

 int  dx_set_lasterr(int Chdev, long error);
 int  dx_gtcallid( int Chdev, unsigned char *bufp);
 int  dx_gtextcallid( int Chdev, int infotype, unsigned char *bufp);
 int  dx_gtromsig ( int Chdev, char *bufp );
 int  dx_wtcallid( int Chdev, int nrings, int timeout,unsigned char *bufp);
 int  dx_SendReadRequest( INT SrlDevice, PCHAR Buffer,
                                   DWORD DataLength, DXRWROUTINE ReadCompletionRoutine );
 int  dx_SendWriteRequest( INT SrlDevice, PCHAR Buffer, DWORD DataLength,
                                    DWORD BulkFlags, DXRWROUTINE WriteCompletionRoutine   );
 int  dx_InitializeBargeIn( int Chdev, const DV_TPT * tptp,
				    DX_XPB *xpbp, USHORT RecordMode);
 int  dx_gtsernum( int dev, int subfcn, void *buffp);
 int  dx_TSFStatus( void );
 int  dx_listenecr( int chDev, SC_TSINFO *sc_tsinfop );
 int  dx_listenecrex( int chDev, SC_TSINFO *sc_tsinfop, void *dx_ecrctp );
 int  dx_unlistenecr( int chDev );
 int  dx_getxmitslotecr( int chDev, SC_TSINFO *sc_tsinfop);
 int  r2_creatfsig(int chDev, int toneid);
 int  r2_playbsig(int chDev, int backwardsig, int forwardsig, int mode);
 int  dx_BargeIn( int chDev, DX_IOTT *lpPlayIott,
			DX_IOTT *lpRecordIott,
			const DV_TPT *lpPlayTerminations,
			const DV_TPT *lpRecordTerminations,
			DX_XPB *lpPlayParams, 
			USHORT Mode);
 int  dx_TxIottData( int chDev, DX_IOTT *iottp, const DV_TPT *lpTerminations, int wType, 
LPVOID lpParams, USHORT mode);
 int  dx_RxIottData( int chDev, DX_IOTT *iottp, const DV_TPT *lpTerminations, int wType, 
LPVOID lpParams, USHORT mode);
 int  dx_TxRxIottData( int chDev, DX_IOTT *lpTxIott, const DV_TPT *lpTxTerminations, DX_IOTT 
*lpRxIott, const DV_TPT *lpRxTerminations, int wType, LPVOID lpParams, USHORT mode);
 int  dx_cspstopch( int Chdev, unsigned short mode);

 int  ai_open(const char* namep);
 int  ai_close(int devh);
 int  ai_getxmitslot(int devh, SC_TSINFO* sc_tsinfop);

/* Fax Library Function Prototypes - ANSI C & C++ */

const char * __cdecl fx_getversion ( int dev, int flag );
int fx_getcopyright ( int dev, char *buffer );
int fx_loadfontfile ( int dev, char *fontfilename, unsigned long ulMode );
int fx_open(const char * name, int oflags);
int fx_close(int dev);
int fx_stopch(int dev, int mode);
int fx_initstat(int dev, int state);
int fx_sendfax(int dev, DF_IOTT * iotp, unsigned long sndflag);
int fx_rcvfax(int dev, const char * faxname, unsigned long rcvflag);
int fx_rcvfax2(int dev, int fd, unsigned long rcvflag);
int fx_setparm(int dev, unsigned long parm, const void * valuep);
int fx_getparm(int dev, unsigned long parm, void * valuep);
void fx_setuio(DF_UIO df_uio);
void fx_setiott(DF_IOTT *iotp, int fhandle, unsigned short dtype,
                         unsigned short cont);
int fx_getDIS(int, DF_DIS *);
int fx_getDCS(int, DF_DCS *);
int fx_getNSF(int, unsigned short, char *);
int fx_loadfont(int devd, int fontfh, unsigned long mode);
int fx_rtvContinue(int iDev, int iContinue);
int fx_getctinfo(int iDev, CT_DEVINFO* ctinfo);
int fx_originate(int dev, int mode);

#ifdef _WIN32
long fx_libinit(unsigned short flag);
long fx_GetDLLVersion(LPDWORD fileverp, LPDWORD prodverp);
#endif

/* Fax convenience functions */

int fx_sendtiff(const char * faxname, unsigned long firstpg,
                        unsigned long pgcount, unsigned short phdcont);
int fx_sendraw(const char * faxname, unsigned short width,
                        unsigned char resln, unsigned short phdcont);
int fx_sendascii(const char * faxname, unsigned short phdcont);

/* Fax Extended Attributes */

long ATFX_SPEED(int dev);
long ATFX_WIDTH(int dev);
long ATFX_RESLN(int dev);
long ATFX_PGXFER(int dev);
DF_IOTT * ATFX_LASTIOTT(int dev);
DF_IOTT * ATFX_BADIOTT(int dev);
long ATFX_BADPAGE(int dev);
long ATFX_ESTAT(int dev);
long ATFX_BSTAT(int dev);
long ATFX_PHDCMD(int dev);
long ATFX_PHDRPY(int dev);
long ATFX_TERMMSK(int dev);
long ATFX_BSTAT(int dev);
const char * ATFX_FXVERSION(int dev);
long ATFX_TFBADTAG(int dev);
long ATFX_TFPGBASE(int dev);
long ATFX_TFNOTAG(int dev);
long ATFX_RTNPAGES(int dev);
long ATFX_SCANLINES(int dev);
long ATFX_BADSCANLINES(int dev);
long ATFX_CODING(int dev);
long ATFX_CHTYPE(int dev);
long ATFX_TRCOUNT(int dev);
long ATFX_STATE(int dev);
long ATFX_ECM(int dev);

#ifdef _WIN32
long _faxGetDllVersion(char *szFileName,PDWORD pdwFileVerMajor,
				                    PDWORD pdwFileVerMinor, PDWORD pdwProductVerMajor,
				                    PDWORD pdwProductVerMinor);
#endif
                                                            
/* Fax SCBus functions */
int fx_listen(int dev, SC_TSINFO * sc_tsinfop);
int fx_unlisten(int dev);
int fx_getxmitslot(int dev, SC_TSINFO * sc_tsinfop);

#endif

/*
 * Extended Attributes
 */
 char *  ATDX_BDNAMEP(  INT SrlDevice );
 char **  ATDX_CHNAMES( INT SrlDevice );
 long  ATDX_BDTYPE(     INT SrlDevice );
 long  ATDX_BUFDIGS(    INT SrlDevice );
 long  ATDX_CHNUM(      INT SrlDevice );
 long  ATDX_DEVTYPE(    INT SrlDevice );
 long  ATDX_DBMASK(     INT SrlDevice );
 long  ATDX_EVTCNT(     INT SrlDevice );
 long  ATDX_FWVER(      INT SrlDevice );
 long  ATDX_HOOKST(     INT SrlDevice );
 long  ATDX_LINEST(     INT SrlDevice );
 long  ATDX_NUMCHAN(    INT SrlDevice );
 long  ATDX_PHYADDR(    INT SrlDevice );
 long  ATDX_PRODUCT(    INT SrlDevice );
 long  ATDX_RINGCNT(    INT SrlDevice );
 long  ATDX_DIGBUFMODE( INT SrlDevice );
 long  ATDX_STATE(      INT SrlDevice );
 long  ATDX_TERMMSK(    INT SrlDevice );
 long  ATDX_TONEID(     INT SrlDevice );
 long  ATDX_TRCOUNT(    INT SrlDevice );
 long  ATDX_XFERBUFSIZE(INT SrlDevice );
 long  ATDX_RXDATABUFSIZE(INT SrlDevice );

/*
 * Call Analysis Extended Attributes
 */
 long  ATDX_ANSRSIZ(  INT SrlDevice );
 long  ATDX_CONNTYPE( INT SrlDevice );
 long  ATDX_CPERROR(  INT SrlDevice );
 long  ATDX_CPTERM(   INT SrlDevice );
 long  ATDX_FRQDUR(   INT SrlDevice );
 long  ATDX_FRQDUR2(  INT SrlDevice );
 long  ATDX_FRQDUR3(  INT SrlDevice );
 long  ATDX_FRQHZ(    INT SrlDevice );
 long  ATDX_FRQHZ2(   INT SrlDevice );
 long  ATDX_FRQHZ3(   INT SrlDevice );
 long  ATDX_FRQOUT(   INT SrlDevice );
 long  ATDX_LONGLOW(  INT SrlDevice );
 long  ATDX_SHORTLOW( INT SrlDevice );
 long  ATDX_SIZEHI(   INT SrlDevice );
 long  ATDX_DTNFAIL( INT SrlDevice );
 long  ATDX_CRTNID( INT SrlDevice );
 int   dx_callp (int chdev, UINT SignalWaitTime, UINT AnswerWaitTime, UINT PVDWaitTime, 
											 UINT PVD_Id, UINT PAMD_Id, USHORT Mode);
 int   dx_rearm (int chdev);

/*
 * 'C' language interface functions
 */
 long  dx_libinit( unsigned short flags );
 long  dx_GetDllVersion( LPDWORD fileverp, LPDWORD prodverp );
// my add 
   char *  ATDV_ERRMSGP(long ddd);
  long    ATDV_IOPORT(long ddd);
  long    ATDV_IRQNUM(long ddd);
  long    ATDV_LASTERR(long ddd);
  char *  ATDV_NAMEP(long ddd);
  long    ATDV_SUBDEVS(long ddd);
  long  sr_waitevt(long tmout);
  long  sr_waitevtEx(long *handlep, int count, long tmout, long *evthp);
  long  sr_enbhdlr(long ddd, unsigned long event_type,long (*hdlr)(unsigned long parm));
  long  sr_dishdlr(long ddd, unsigned long event_type,long (*hdlr)(unsigned long parm));
  long  sr_getboardcnt(char *brdname, int *brdcnt);
  long  sr_getevtdev(...);
  long  sr_getevttype(...);
  long  sr_getevtlen(unsigned long evt_handle);
  void *  sr_getevtdatap(...);
  long  sr_hold(void);
  long  sr_release(void);
  long  sr_getparm(long ddd, long parmid, void* valuep);
  long  sr_setparm(long ddd, long parmid, void* valuep);
  void  sr_NotifyEvent(HWND handle, unsigned int message, unsigned int flag);
  long  sr_libinit(unsigned short flag);
  long  sr_GetVersion(char *libnamep, LPDWORD fileverp, LPDWORD prodverp);
  long  sr_GetDllVersion(LPDWORD fileverp, LPDWORD prodverp);
  void  sr_cleanup(void);
  long  sr_putevt(long dev, unsigned long evt, long len, void  *datap, long err);
 int	ec_getxmitslot (int hDev, SC_TSINFO *lpSlot);
 int	ec_getparm (int hDev, ULONG ParmNo, void *lpValue);
 int	ec_listen (int hDev, SC_TSINFO *lpSlot);
 int	ec_rearm (int hDev);
 int	ec_reciottdata (int hDev, DX_IOTT *iottp, DV_TPT *tptp,DX_XPB *xpbp,USHORT mode);
 int	ec_setparm (int hDev, ULONG ParmNo, void *lpValue);
 int	ec_stopch (int hDev, ULONG StopType, USHORT mode);
 int	ec_stream (int hDev, DV_TPT *tptp, DX_XPB *xpbp,
											 int (*callback) (int, char *, UINT), USHORT mode);
 int	ec_unlisten (int hDev);

#endif