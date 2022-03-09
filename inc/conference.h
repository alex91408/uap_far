typedef struct {
	int		cfrNo;				// 會議室(1~TotalCfrNo)
	int		password;			// 密碼
	int		timeLoc;			// Point back to TTab
	char	year;				// 年
	char	mm;					// 月
	char	dd;					// 日
	char	hh;					// 時
	long    meetingTime;		// meeting time. to calculate
	char	name[64];			// 主持人姓名
	char	extension[8];		// 分機號碼
	char	recFileName[32];	// 會議錄音檔名
	char	handset[32];		// handset to send Short Message
	char	attender[8][32];	// 8個參加者之主叫號
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

