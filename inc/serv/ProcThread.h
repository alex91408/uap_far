#if !defined(AFX_PROCTHREAD_H__E6A34739_7E89_4D79_AAD1_A4F03DBBA7D9__INCLUDED_)
#define AFX_PROCTHREAD_H__E6A34739_7E89_4D79_AAD1_A4F03DBBA7D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CProcThread thread

class CProcThread : public CWinThread
{
	DECLARE_DYNCREATE(CProcThread)
protected:
	CProcThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CString m_FileName;
	CString m_PathName;
	CString m_FileTitle;
  CString m_KerFile; //may
	int m_LineNo;
	int m_StartMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProcThread();

	// Generated message map functions
	//{{AFX_MSG(CProcThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCTHREAD_H__E6A34739_7E89_4D79_AAD1_A4F03DBBA7D9__INCLUDED_)
