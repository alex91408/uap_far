typedef struct  {
    char trid[3];                       /* Transaction ID */
    char fill1;
    char trdatein[6];                   /* transation beginning date */
    char trtimein[6];                   /* transaction begining time */
    char trtimeout[6];                   /* transaction ending time  */

    char error[4];                      /* error code  "0000" -> success */
    char stat1;                         /* 0:success 1:failure 2:busy */
    char stat2;                         /* cancel or not   H:host sent */
    char oacnt[20];                     /* transfer out acc */
    char iacnt[20];                     /* transfer in acc */
    char inamt[13];                     /* trans-in amount */
    char amt[13];                       /* use amount */
    char amt1[13];                      /* today amount */
    char idno[11];                      /* id no. R*/
    char lossdate[15];                  /* loss OK time*/
    char sdate[6];                      /* fax starting date */
    char edate[6];                      /* fax ending date */
    char faxn[10];                      /* fax number */
    char lcode[3];                      /* local code 02:tpe 04:txg 07:kh */
    char form[4];                       /* fax form no */
    char faxlno[4];                     /* fax line no */
    char fill2;
    char cury[2];                       /* currency code */
    char fill3[22];
} LOG, *log;
