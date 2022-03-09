// otsMutex.h: interface for the otsMutex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTSMUTEX_H__DDF27C2D_0B93_4A0E_A98D_AD6138A34DE0__INCLUDED_)
#define AFX_OTSMUTEX_H__DDF27C2D_0B93_4A0E_A98D_AD6138A34DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=3C203665006B
//class OTS_UTIL_API otsMutex  
class  otsMutex  

{
public:
	//##ModelId=3C203665007F
	BOOL initMutex(char * name);
	//##ModelId=3C2036650089
	void releaseMutex();
	//##ModelId=3C2036650093
	BOOL getMutex(long timeout);
	//##ModelId=3C203665009D
	otsMutex();
	//##ModelId=3C203665009E
	virtual ~otsMutex();

private:
	//##ModelId=3C20366500A8
	HANDLE hMutex;
};

#endif // !defined(AFX_OTSMUTEX_H__DDF27C2D_0B93_4A0E_A98D_AD6138A34DE0__INCLUDED_)
