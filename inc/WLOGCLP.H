typedef struct  {
    short trid;                          // Transaction ID
                                         // 001: voice in
    short error;                         // 0:success else Error
    char  accno[20];                     // Account No. to receive price
    long  seqno;                         // Transaction Sequence No.
    char  telno[20];                     /* tel. No. to dial */
    long  time;                          /* transation beginning time */
    short durc[2];                       /* duration time For cus_cost */
    short durs[2];                       /* duration time For svr_cost */
    short unitc1[2];                     /* unit(ex. 10 sec.) For Cus_cost */
    short unitc2[2];                     /* unit(ex. 10 sec.) For Cus_cost */
    short units1[2];                     /* unit(ex. 10 sec.) For svr_cost */
    short units2[2];                     /* unit(ex. 10 sec.) For svr_cost */
    short cus_cost[2];                   /* customer rate(ex. 20 yen) */
    short svr_cost[2];                   /* isp rate(ex. 10 yen) */
    long  cus_price;                     /* Total price for customer */
    long  svr_price;                     /* Total price for isp */
    long  roam_price;                    // Total roaming fee
    short roam_rate;                     // % rate for cus_cost
    short center_rate;                   // % rate for accounting center
    long  cus_ip;                        // dial in server IP
    long  roams_ip;                       // roaming server IP
    long  rcv_ip;                        // receiving IP
    long  pay_ip;                        // transmitting IP
    long  dial_ip;                       // dial center ip
    long  roamg_ip;                       // roaming server IP
    long  introducer;                    // Introducer code for the account
    float inwardrate;                    // to transfer to USD by caller
    float openerrate;                    // to transfer to USD by opener
} LOG, *log;

