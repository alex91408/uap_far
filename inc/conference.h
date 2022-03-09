typedef struct {
	int		cfrNo;				// �|ĳ��(1~TotalCfrNo)
	int		password;			// �K�X
	int		timeLoc;			// Point back to TTab
	char	year;				// �~
	char	mm;					// ��
	char	dd;					// ��
	char	hh;					// ��
	long    meetingTime;		// meeting time. to calculate
	char	name[64];			// �D���H�m�W
	char	extension[8];		// �������X
	char	recFileName[32];	// �|ĳ�����ɦW
	char	handset[32];		// handset to send Short Message
	char	attender[8][32];	// 8�Ӱѥ[�̤��D�s��
	long	inTime[8];			// attend Time
	long	outTime[8];			// Leave time
	char	status[8];			// 1: leave room
	long    registerTime;		// If registerTime > meetingTime, expire will be 15 minutes after registerTime
	char	filler[24];			// Make 512
} CfrR;

typedef struct {
	int		year;
	int		cfrNo;
	int		password;
	char	filler[116];
} TTab;

typedef struct {
	char	extensionNo[16];
	char	name[32];
	char	password[16];
	char	deleted[2];
	char	handset[32];
	char    emailAddress[64];
} EXTS;

