typedef struct parms {
        int   version;
        int   card_timeout;
        int   play_vol;
        int   rec_vol;
        char  dbport[24];
        int   dbg_iniflag ;
        int   flash_time;
        int   pause_time;
        int   dtmf_ontime;
        int   dtmf_offtime;
        char  dial_zero[8];
        char  lo_code[6];
        char  exlo_code[10][6];
        int   siloff;
        int   sr1;
        int   sr2;
        int   filler[10];
        char  telhead[40][20];
        int   len[40];
        char  pmfile[40][20];
        int   deft;                     // default position
        int   pos;
} TEL, *tel;

