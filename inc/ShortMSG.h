
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SHORTMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SHORTMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SHORTMSG_EXPORTS
#define SHORTMSG_API __declspec(dllexport)
#else
#define SHORTMSG_API __declspec(dllimport)
#endif

typedef int (* dbgprint)(char *); 

// This class is exported from the ShortMSG.dll
class SHORTMSG_API CShortMSG {
public:
	CShortMSG(dbgprint, char *);
	~CShortMSG(void);
	SendShortMSG(void);
	SendShortMSG1(void);
	SendShortMSG2(void);
	// TODO: add your methods here.
};

extern SHORTMSG_API int nShortMSG;

SHORTMSG_API int fnShortMSG(void);

