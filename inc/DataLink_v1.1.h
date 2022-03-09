// DataLink.h: interface for the CDataLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATALINK_H__19726B6A_0E18_4557_ABA2_85C763E66C2B__INCLUDED_)
#define AFX_DATALINK_H__19726B6A_0E18_4557_ABA2_85C763E66C2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DB_OPEN_OPENEXCLUSIVE   0x0001; // Not implemented
#define DB_OPEN_OPENREADONLY    0x0002; // Open database read only
#define DB_OPEN_USECURSORLIB    0x0004; // Use ODBC cursor lib
#define DB_OPEN_NOODBCDIALOG    0x0008; // Don't display ODBC Connect dialog
#define DB_OPEN_FORCEODBCDIALOG 0x0010; // Always display ODBC connect dialog

#define OPEN_TYPE_DYNASET     1;
#define OPEN_TYPE_SNAPSHOT    2;
#define OPEN_TYPE_FORWARDONLY 3;
#define OPEN_TYPE_DYNAMIC     4;
	
#define OPEN_OPTIONS_NONE                     0x0;
#define OPEN_OPTIONS_READONLY                 0x0004;
#define OPEN_OPTIONS_APPENDONLY               0x0008;
#define OPEN_OPTIONS_SKIPDELETEDRECORDS       0x0010;
#define OPEN_OPTIONS_NODIRTYFIELDCHECK        0x0020;
#define OPEN_OPTIONS_USEBOOKS                 0x0100;
#define OPEN_OPTIONS_USEMULTIROWFETCH         0x0200;
#define OPEN_OPTIONS_USERALLOCMULTIROWBUFFERS 0x0400;
#define OPEN_OPTIONS_USEEXTENDEDFETCH         0x0800;
#define OPEN_OPTIONS_EXECUTEDIRECT            0x2000;
#define OPEN_OPTIONS_OPTIMIZEBULKADD          0x4000;
#define OPEN_OPTIONS_FIRSTBULKADD             0x8000;



//##ModelId=3C20364B037D
class AFX_EXT_CLASS CDataLink  
{
public:
	//##ModelId=3C20364B038F
	int GetDataType(char * field_name);
	//##ModelId=3C20364B039A
	int GetDataType(short index);
	//##ModelId=3C20364B03AE
	HDBC hdbc;
	//##ModelId=3C20364B03B7
	BOOL Requery();
	//##ModelId=3C20364B03C1
	void SetOpenDbOptions(DWORD options);
	//##ModelId=3C20364B03CB
	BOOL Rollback();
	//##ModelId=3C20364B03D5
	BOOL CommitTrans();
	//##ModelId=3C20364B03DF
	BOOL BeginTrans();
	//##ModelId=3C20364B03E0
	BOOL CanTransact();
	//##ModelId=3C20364C0001
	BOOL CanUpdate();
	//##ModelId=3C20364C000B
	BOOL IsConnected();
	//##ModelId=3C20364C0015
	void SetLoginTimeOut(unsigned int seconds);
	//##ModelId=3C20364C001F
	BOOL OpenDatabase(char * lpConnectString);
	//##ModelId=3C20364C0033
	BOOL ExecuteSQL(char * sqlstr);
	//##ModelId=3C20364C003D
	BOOL SelectRecorder(CString lpFileds, CString lpTableName, CString lpWhere, CString lpSort);
	//##ModelId=3C20364C0065
	BOOL ExecuteSQL(CString sqlstr);
	//##ModelId=3C20364C0079
	CString GetSQL();
	//##ModelId=3C20364C0083
	BOOL mConnected;
	//##ModelId=3C20364C0097
	BOOL Requery(char *lpWhere, char *lpSort);
	//##ModelId=3C20364C00AB
	BOOL OpenDatabase();
	//##ModelId=3C20364C00BF
	CString GetErrMsg();
	//##ModelId=3C20364C00C9
	BOOL IsOpen();
	//##ModelId=3C20364C00DD
	BOOL IsEOF();
	//##ModelId=3C20364C00E7
	BOOL IsBOF();
	//##ModelId=3C20364C00F1
	BOOL GetDataEx(short mIndex, void *buff, unsigned long bufflen);
	//##ModelId=3C20364C010F
	BOOL GetDataEx(char * lpFieldName,void * buff, unsigned long bufflen);
	//##ModelId=3C20364C0124
	BOOL GetData(short nIndex, CString* strValue);
	//##ModelId=3C20364C0141
	BOOL GetData(LPCTSTR lpszName, CString* strValue);
	//##ModelId=3C20364C0156
	BOOL GetData(short mIndex ,void * buff, int bufflen);
	//##ModelId=3C20364C0174
	BOOL GetData(char * lpFieldName,void * buff, int bufflen);
	//##ModelId=3C20364C019C
	CString GetODBCFieldName(short nIndex);
	//##ModelId=3C20364C01B0
	short GetODBCFieldCount();
	//##ModelId=3C20364C01C4
	long GetRecordCount();
	//##ModelId=3C20364C01CE
	BOOL Move( long nRows, WORD wFetchType = SQL_FETCH_RELATIVE );
	//##ModelId=3C20364C01EC
	BOOL MovePrev();
	//##ModelId=3C20364C0200
	BOOL MoveNext();
	//##ModelId=3C20364C0214
	BOOL MoveLast();
	//##ModelId=3C20364C0228
	BOOL MoveFirst();
	//##ModelId=3C20364C023C
	void CleanSelectResult();
	//##ModelId=3C20364C0250
	BOOL SelectRecorder(UINT nOpenType , DWORD dwOption , LPCTSTR lpFileds , LPCTSTR lpTableName , LPCTSTR lpWhere , LPCTSTR lpSort);
	//##ModelId=3C20364C0282
	BOOL SelectRecorder(char * lpFileds , char * lpTableName , char * lpWhere , char * lpSort);
	//##ModelId=3C20364C02B4
	BOOL DeleteRecorder(char * lpTableName , char * lpWhere);
	//##ModelId=3C20364C02DC
	BOOL UpdateRecorder(char * lpTableName , char * lpData , char * lpWhere);
	BOOL UpdateRecorder(char * lpTableName , char * lpData , char * lpWhere, long *count);
	//##ModelId=3C20364C0304
	BOOL AddNewRecorder(char * lpTableName , char * lpFields , char * lpValue);
	//##ModelId=3C20364C032C
	void CloseDatabase();
	//##ModelId=3C20364C034A
	BOOL OpenDatabase(char * lpDsn ,char * lpUID, char * lpPWD);
	//##ModelId=3C20364C0372
	CDataLink();
	//##ModelId=3C20364C0390
	virtual ~CDataLink();



private :
	//##ModelId=3C20364C03A4
	DWORD dwOptions;
	//##ModelId=3C20364C03B8
	CString mErrMsg;
	//##ModelId=3C20364C03CD
	CDatabase mConn;
	//##ModelId=3C20364C03E1
	CRecordset * mRs;
};

#endif // !defined(AFX_DATALINK_H__19726B6A_0E18_4557_ABA2_85C763E66C2B__INCLUDED_)
