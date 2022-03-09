enum    {
        DH_NONE,
        OPEN_HEADER_ERROR,
        OPEN_NUMBER_ERROR,
        NOT_IN_TIME,
        END_OF_DIAL,
        END_OF_CYCLE,
        NOT_DIALABLE
};

typedef struct dialheader {
 	char name[32];  //20
  	char locode[8];   	/* local code */
	char telseq[5][4];	/* [5]:dialout time slice, [4]:telpos[3] */
	int  stime[5];		/* time to dial */
  	int  etime[5];       
  	int  reclen;
 	int  telpos[3];
  	int  tellen[3];
	int  result_pos;
 	int  maxcyc;
	int  interval;		/* delay before starting next cycle(minutes) */
  	int  maxrec;
	int  curcyc;
  	int  currec;
	long cyctime;		/* starting time for a new cycle */
	char telno[3][32];  //16--32
} DH, *dh;

extern  DH      *ginn_dhp;
