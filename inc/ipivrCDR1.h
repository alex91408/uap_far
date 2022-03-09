
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
  char callerName[32];			// incoming
  char callerNo[32];			// incoming
  char callerAddr[32];			// incoming
  char calledName[32];			// incoming
  char calledNo[32];			// incoming
  char result[2];				// transfer
  char errCode[4];				// transfer
  char callID[64];				// incoming caller's
  long incomingTime;			// incoming
  long connectTime;				// transfer
  long disconnectTime;			// release
  int  cost;
} IVRCDR, *ivrcdr;

// This class is exported from the ipivrCDR.dll
class IPIVRCDR_API CIpivrCDR {
public:

	CIpivrCDR(void);
  int incomingCall( IVRCDR );
  int transferCall( IVRCDR );
  int releaseCall( IVRCDR );
	// TODO: add your methods here.
};

extern IPIVRCDR_API int nIpivrCDR;

IPIVRCDR_API int fnIpivrCDR(void);

