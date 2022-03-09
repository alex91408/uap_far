#define         L_BTOMEXT       511
#define         L_DATNAME       128
#define         FILE_UTOB       "unisys.dat"
#define         FILE_ITOB       "ibm.dat"
#define         FILE_BTOM       "big5mess.dat"
#define         FILE_BTOMEXT    "big5ext.txt"
#define         FILE_B2UNI      "big5unic.dat"
#define         WCODE_FIRSTBYTE         0x20
#define         WCODE_SECONDBYTE        0x20
#define         WCODE_MESSNO            (-1)
#define         WCODE_UNICODE           0x0000

enum    {
        WCODE_TABLE_USERDEF,
        WCODE_TABLE_DEFAULT,
        WCODE_TABLE_AS400,
        WCODE_TABLE_MS
};

typedef struct  _WCODE_TWOBYTE  {
        char    c[2];
}       WCODE_TWOBYTE;

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      int     wcode_inpytbl(int no);
GINNIMPORT      int     wcode_inystbl(int no);
GINNIMPORT      int     wcode_utob_datfile(char *fname);
GINNIMPORT      int     wcode_itob_datfile(char *fname);
GINNIMPORT      int     wcode_btom_datfile(char *fname);
GINNIMPORT      int     wcode_btom_extfile(char *fname);
GINNIMPORT      int     wcode_b2uni_datfile(char *fname);
GINNIMPORT      int     wcode_ascii2ebcdic_table(int table, unsigned char *userdef);
GINNIMPORT      int     wcode_ebcdic2ascii_table(int table, unsigned char *userdef);
GINNIMPORT      unsigned        char    wcode_ascii2ebcdic(unsigned char code);
GINNIMPORT      unsigned        char    wcode_ebcdic2ascii(unsigned char code);
GINNIMPORT      int     wcode_utob(char *unisys, char *big5, int size);
GINNIMPORT      int     wcode_itob(char *ibm, char *big5, int size);
GINNIMPORT      int     wcode_btom(char *big5, short *mess, int size);
GINNIMPORT      int     wcode_b2uni(char *big5, short *unic, int size);
GINNIMPORT      int     wcode_utob9e9f(char *unisys, char *big5, int size);
GINNIMPORT      int     wcode_itob0e0f(char *ibm, char *big5, int size);
GINNIMPORT      int     wcode_unisys2big5(char *unisys, char *big5, int size);
GINNIMPORT      int     wcode_ibm2big5(char *ibm, char *big5, int size);
GINNIMPORT      int     wcode_big5IImess(char *big5, short *mess, int size);
GINNIMPORT      int     wcode_big5IIunicode(char *big5, short *unic, int size);

__END_DECLS
