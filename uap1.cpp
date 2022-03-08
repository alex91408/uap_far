//----------------------------------------------------------------------------------------------
// 每次更改請在此區註解    最新放最上面 CHING2  p400()  
// ver 要改   #define VERSION XXXX   每次異動版本需要修改
//
//----------------------------------------------------------------------------------------------

//#define VERSION   "20220210  V6.00 vs2019 "


//20220210 V6.0 ching2  modify uap for VS2019  及弱掃



#include "uapVar.h"
#include  <stdlib.h>
#include  <io.h>
#include <stdio.h>
#include  <string.h>

int   init_get_funcpt();
int   init_set_funcpt();
ex myExp;

char dt_d_c_callid[128];   // 按鍵式callid first_char(d)+callid+end_char(c)
int  dt_d_c_callidcnt = 0;   // 所接收 callid 長度
char dl_Line[64][10];  // for dialline.par
char dl_LineLocal[64][10]; // for dialline.par


int recdt(int c)
{

	if (vxp->hook == '1' && (char)c == 'd') 
	{
		dt_d_c_callidcnt = 0;
		dt_d_c_callid[dt_d_c_callidcnt++] = '0';
	}
	else if (vxp->hook == '1' && (char)c == 'c') 
	{
		dt_d_c_callid[dt_d_c_callidcnt] = 0;
	}
	else if (vxp->hook == '1') {
		dt_d_c_callid[dt_d_c_callidcnt++] = (char)c;
	}

	fdbprintf("---rec=(%c)---hook=(%c)\n\r", c, vxp->hook);
	return 0;
}
int uap_end()
{
	fdbprintf("uap_end \n");
	return 0;
}
int ap_end()
{
	ginn_outofservice();
	return 0;
}
int init_set_funcpt()
{
	setFuncPointToKer("_uap_check_play", NULL); //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_check_dial", NULL); //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_check_rec", NULL);  //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_check_wtring", NULL); //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_check_tone", NULL);  //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_check_dtmf", NULL); //(NFUNCPTR)aa);
	setFuncPointToKer("_uap_play_end", NULL);  //(NFUNCPTR)aa1);
	setFuncPointToKer("_uap_receive_dtmf", (NFUNCPTR)recdt); //(NFUNCPTR)aa);
	return 0;
}
int init_uap()
{
	init_get_funcpt();
	init_set_funcpt();
	myExp = exVar;
	return 0;
}






UAP uap1[] = { {"", NULL},
};


//20220210 
extern int uap4_select(char*);


/*****************************************************************************/
int uap1_select(char *str)
{
    int i, k;
    for (i=0; uap1[i].name[0]!=0; i++)
	{
        if (strcmp(str, uap1[i].name) == 0)
		{
           k=(*uap1[i].func)(/*uap1[i].parm*/);
           return k;
        }
    }
    return -1;
}    
int uap_select(char *str)
{
	int k;
	if (str[1] == '.')
	{
		switch (str[0])
		{	
		case '1': k = uap1_select(&str[2]);
			break;
		case '4': k = uap4_select(&str[2]);
			break;
		default: k = uap1_select(&str[2]);
			break;
		}
		return k;
	}
	k = uap1_select(str);
	return k;
}
