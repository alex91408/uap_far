
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IPIVRCDR_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IPIVRCDR_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef IPIVRCDR_EXPORTS
#define IPIVRCDR_API __declspec(dllexport)
#else
#define IPIVRCDR_API __declspec(dllimport)
#endif


typedef struct ivrCDR
{
  int  seqID;
  char callerID[32];
  char accountID[32];
  char callerAddr[32];
  char calledID[32];
  char calledAddr[32];
  char rtpRelay[2];
  char result[2];
  char statusCode[8];
  char callID[64];
  long incomingTime;
  long connectTime;
  long disconnectTime;
  int  cost;
  int  codec;
  char fromURI[64];
  char toURI[64];
  char contactURI[64];
  char requestURI[64];
  char origRequestURI[64];
  char fromPrivateIP[32];
  char toPrivateIP[32];
} IVRCDR, *ivrcdr;

typedef int (* dbgprint)(char *);

// This class is exported from the ipivrCDR.dll
class IPIVRCDR_API CIpivrCDR {
public:

	CIpivrCDR(dbgprint);
	~CIpivrCDR(void);
  //int incomingCall( IVRCDR );
  //int transferCall( IVRCDR );
  //int releaseCall( IVRCDR );
  int incomingCall(ivrcdr);
  int connectCall(ivrcdr);
  int releaseCall(ivrcdr);
  int ringCall(ivrcdr);
  int closeDB();
	// TODO: add your methods here.
};

extern IPIVRCDR_API int nIpivrCDR;

IPIVRCDR_API int fnIpivrCDR(void);

