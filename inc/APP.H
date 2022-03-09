#define         MSGFORM         "%s/mess%04d"
#define         VOXFORM         "%s/voxx%04d"
#define         ULAWFORM        "%s/ulaw%04d"
#define         ALAWFORM        "%s/alaw%04d"
#define         WAVEFORM        "%s/wave%04d"
#define         MSXFORM         "%s/mexx%04d"
#ifndef TX0400D
#define         VAPFORM         "%s/synth%01d"
#else
#define         VAPFORM         "%s/synth%01d.telsyn"
#endif
#define         TOP_OF_STACK    20
#define         BOTTOM_OF_STACK 0
#define         BVAP            1
#define         EVAP            9
#define         BVAR            1
#define         EVAR            25
#define         BMESS           1
#define         EMESS           9999
#define         ONHOOK          0
#define         OFFHOOK         1
#define         BUSYHOOK        2
#define         SQUIT           0
#define         READY           64
#define         OK              0
#define         SYNC_TM         33
#define         SENTINEL_PROMPT 65535
#define         DET_ONHOOK      2
#define         DET_TIMEOUT     3
#define         DET_EOD         4
#define         DET_HRETURN     5
#define         DET_ERROR       6
#define         DET_DIGIT       7
#define         DET_ASRERR      8    //may
#define         DET_ASRBARGEIN  9
#define         DET_ASRSUCC     10
#define         DET_ASRTMOUT    11
#define         DET_CSPRETURN   12


#define         ACTIVE          1
#define         TERMINATE       0
#define         YEAH            1021
#define         vap_key         43
#define         vap_size        sizeof(VTAB)

//may for asr
#define         MAX_ASR_RESULTNUM   5
#define         MAX_ASR_WAITTM      60
#define         RECORD_ASR_PATH     "asrVoice%03d"

typedef
        struct  {
        int     sp;
        int     stack[TOP_OF_STACK-BOTTOM_OF_STACK];
        char    apsav[TOP_OF_STACK-BOTTOM_OF_STACK][10];
        char    termd[4];
        int     clrdig;
        long    lgitime;
        long    lgotime;
        char    apname[8];
        char    mpa[128];    //20-->128
        char    buff[256];
        int     hook;
        int     ohbranch;       /* onhook branch , -1 no special branch */
}       CHANNEL, *channel;

typedef
        struct  {
        long    o;
        long    s;
}       VTAB, *vtab;



typedef
        struct  {
        int     no;
        int     tdev;
        int     waittm;
        int     i_f;
        int     type;
}       VOICE;


typedef struct {
    int   RxBufSize	;
    int   TxBufSize	;

    int   XferBufferSize ;
    int   VADInitiated		;
    int   EchoCanceller  ;
    int   BargeIn        ;
    int   BargeInOnly		;
    int   EC_Tap_Length	;
    int   AdaptMode      ;
    int   Nlp			;
    int   SpeechPlayThresh  ;
    int   SpeechNonPlayThresh  ;
    int   SpeechPlayTrigg    ;
    int   SpeechNonPlayTrigg ;
    int   SpeechPlayWindow		;
    int   SpeechNonPlayWindow;
    int   SpeechSNR	;
    int   Voice_Data_Format;

}CSP_SET_DATA;

int     hang_up(void);
int     makemsgfile(int, char *, char *);