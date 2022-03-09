// jfax.h: 
//
//////////////////////////////////////////////////////////////////////


class AFX_EXT_CLASS CJFax
{
public:
	CJFax();
	virtual ~CJFax();
	int InitialFaxVar(int);
	int InitFax();
	int NeedFax(char sdfile[][50], int, int *);
	int RecvFax(char *, int *);
	int RecvFaxC(char *, int *);
};


