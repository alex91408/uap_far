#define MAX_AUDIO_BUF_LEN 512
#define NUM_AUDIO_BUFS 300
#define MAX_AUDIO_BUFFER_LENGTH  (MAX_AUDIO_BUF_LEN*NUM_AUDIO_BUFS)

#define   CTRL_SHM_FILE      "ctrlBuf.shm"
#define   LOCK_FILE          "shmUse.lock"


enum	asrStatus{
  ASR_ST_NONE,
  ASR_ST_SUCCESS, ASR_ST_NOCSHM, ASR_ST_NORESOURCE, ASR_ST_SERVERDEAD,
  ASR_ST_RESBUSY, ASR_ST_TIMEOUT, ASR_ST_RESOK,
  ASR_ST_RECOGNIZING, ASR_ST_BARGEIN, ASR_ST_ASRSUCC, ASR_ST_ASRFAIL, 
  ASR_ST_ASRSTAERR,
  ASR_ST_CSPPARMERR, ASR_ST_FUNCNULL, ASR_ST_ECSTREAMERR,ASR_ST_GRASETERR
};


// share memory map file name is "ctrlBuf.shm"
typedef struct ctrlStruc {
  int  asrTotalNumbers;
  long asrActiveCnt;
} ctrlStruc;
 
// share memory map file name is "tmpBufX.shm", X is 0, 1, 2, ...
typedef struct shmStruc {
  int serverState;  // 0: asr ready
                    // 1: answer client's request
                    // 2: bargein
                    // 3: asr generate result
  int clientState;  // 0: initial
                    // n: client request ,n-->lineno(1,---)
                    // -1: client get result
  int  current;
  char vData[MAX_AUDIO_BUFFER_LENGTH];
  char grammar[128];   // grammar file name
  char voiceType[16];  // "ulaw" or "alaw"
  int  bargein;        //software or hardware bargein
 
  int  rc;              //asr errorcode
  int  nBest;           
  char result[128];
  char rcMessage[512];  // if rc != 0, error message
} shmStruc;

extern "C" __declspec(dllexport) FUNCPTR getAsrFunc(int);
extern "C" __declspec(dllexport) int setAsrFunc(int,FUNCPTR);
//--------------------------------------------
