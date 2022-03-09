typedef struct fctlf { 
        int  taskid;
        int  kid;
        int  branch;
        int  typedir;
        int  messnum;
        int  nbappel;
        int  voie;
        int  error;

     /* start of logging */

        char command;  	/* 0:normal 3:abort after call 5:abort at once */
        char etatlig;	/* 1:start 2:call in 3:call end 8:abnrmal end */
        char writer;	/* 0:user 1:call end 2:abnormal end 3:system */
    	char drtype;	/* V:voice M:modem H;host ... */
        char hook;      /* ' ' : Unknown, '1' : Onhook, '0' : Offhook */
        char applic[6];
        char datein[6];
        char timein[6];
        char message[32];
        char rcvdig[6];
        char timeout[6];
		char lineno[4];  //2
      
	    char setno[2];		
        char userlog[190];
        char gap[2];			// make size of an entry 300 bytes 
        char dbg;				// Y: dbg N:no debug
        long alive;				// -1 not start line, n(changing):alive , n(no change):dead 
        long alive_tm;			//write time //20040723 
		char pathName[8];		// pathName of Co. shch as ots, cht,... 20060822
		int pendingDial;		// when ringing transfer, dialing will be suspended to dial 2nd one.
		int	codec;				// forced Codec from uap
        char fille[1024-24];	//for future use //20040723
} VX, *vx;


#define vx_size sizeof(VX)         
#define vx_key  41
