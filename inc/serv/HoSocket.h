// HoSocket.h: interface for the HoSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSOCKET_H__69E6357E_5709_11D4_BACA_0050BAADBFF6__INCLUDED_)
#define AFX_HOSOCKET_H__69E6357E_5709_11D4_BACA_0050BAADBFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h>

class __declspec(dllimport) HoSocket  
{
public:
	bool GetSocketOpt(int level, int optname, char FAR *optval, int FAR *optlen);
	bool SetSocketOpt(int level,int optname,const char FAR *optval,int optlen);
	int GetErrorMsg();
	bool Accept(HoSocket &sConnect);
	void CloseNetEvent();
	WSAEVENT hEvent;
	WSANETWORKEVENTS events;
	bool CreateNetEvent(long Events);
	bool WaitNetEvent(DWORD dwTimeout);
	bool Shutdown(int how=SD_BOTH);
	int SendDatagram(const char* pch, const int nSize, LPSOCKADDR_IN psa, const int nSecs);
	int ReceiveDatagram(char* pch, const int nSize, LPSOCKADDR psa, const int nSecs);
	bool GetPeerAddr(char * paddr , unsigned int bufflen);
	bool GetPeerAddr(LPSOCKADDR psa);
	static bool GetHostByName(const char* pchName, LPSOCKADDR_IN psock, const USHORT ushPort=0);
	static bool GetHostByAddr(char * ip , char * hostbuff , int hostbufflen);
	static bool GetHostByAddr(LPSOCKADDR_IN psa , hostent * phost);
	bool Bind(LPSOCKADDR psa);
	int ReceiveEx(char *pch, const int nSize, const int nSecs);
	int Receive(char* pch, const int nSize, const int nSecs);
	bool ReadLine(char *pch , const int nSize , const int nSecs);
	int Send(const char* pch, const int nSize, const int nSecs);
	int SendEx(const char* pch, const int nSize, const int nSecs);
	bool WriteLine(char *pch , const int nSize , const int nSecs);
	bool Connect(const char* pchIP, const USHORT ushPort);
	bool Close();
	bool Accept(HoSocket & sConnect ,LPSOCKADDR sAddr);
	bool Listen(int backlog=5);
	bool Bind(const USHORT ushPort =0);
	bool Bind(const char* pchIP, const USHORT ushPort = 0);
	bool Create(int nType , int nProtocol);
	bool Create(/* default type SOCK_STREAM , protocol IPPROTO_IP */);
	static bool InitSocket();
	int GetErrorMsg(char * msg ,unsigned int bufflen);
	bool Create(int nType /* default protocol IPPROTO_IP */);
	SOCKET mSocket;
	HoSocket();
	virtual ~HoSocket();
	char   UserAccount[16];
	bool   UserLogin;
private:
	
	SOCKADDR_IN SockAddr;

	
};

#endif // !defined(AFX_HOSOCKET_H__69E6357E_5709_11D4_BACA_0050BAADBFF6__INCLUDED_)
