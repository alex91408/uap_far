/*
        form file tag description :

        tags must put at begining of line
        !F : Form feed
             !FoverlapPbmfiles.lst
        !Z : End of form
             !ZoverlapPbmfiles.lst
        !x : set horizontal gap size for 1 byte code
             !x0
        !X : set horizontal gap size fro 2 byte code
             !X4
        !Y : set vertical gap size
             !Y4
        !M : variable with multiple loop
             put !V as value of first variable to terminate loop

        tags can put at any position
        !P : put pbmfile
             !Plogo.pbm
        !E : Exclamation mark (!)
        !N : line feed
        !V : put variable
*/

typedef enum    {
        WFT_UNKNOWN,
        WFT_PBM,
        WFT_PGM,
        WFT_PPM,
        WFT_PBM_RAW,
        WFT_PGM_RAW,
        WFT_PPM_RAW
}       WPBM_FILE_TYPES;

typedef struct  pbm_header      {
        WPBM_FILE_TYPES ftype;
        int             xsize;
        int             ysize;
        long            offset;
        long            length;
}       WPBM_HEADER;

enum    {
        WPBM_TXT2PBM,   WPBM_TXT2G3,    WPBM_TXT2TIFF
};

enum    {
        ASCFONT,        STDFONT,        SPCFONT,        SPCFSUPP
};

enum    {
        FI_ASCII,       FI_UNICODE,     FI_MAX
};

enum    {
        WPBM_KEEPTMPOFF,         WPBM_KEEPTMPON
};

#define         DOT_LINE        1728
#define         BYTE_LINE       (DOT_LINE/8)
#define         L_MARGIN        0
#define         R_MARGIN        0
#define         MAX_FONTWIDTH   64
#define         MAX_FONTHEIGHT  64
#define         MAX_XGAP        MAX_FONTWIDTH
#define         MAX_YGAP        MAX_FONTHEIGHT
#define         DEF_X1GAP       0
#define         DEF_X2GAP       4
#define         DEF_YGAP        4

#if	defined(EC_WIN32) || defined (_GINN_WIN32_)
#define         DEFAULT_FONTPATH        ".\\pbm\\unicode"
#define         DEFAULT_BIG5UNIC        ".\\pbm\\unicode\\big5unic.dat"
#define         DEFAULT_PBM2G3          ".\\pbm\\bin\\pbm2g3.exe"
#define         DEFAULT_FAX2TIFF        ".\\pbm\\bin\\g32tiff.exe"
#else
#define         DEFAULT_FONTPATH        "./pbm/unicode"
#define         DEFAULT_BIG5UNIC        "./pbm/unicode/big5unic.dat"
#define         DEFAULT_PBM2G3          "./pbm/bin/pbm2g3"
#define         DEFAULT_FAX2TIFF        "./pbm/bin/g32tiff"
#endif
//#define         DEFAULT_ASCFONT         "mingliu36x20.pbm"
//#define         DEFAULT_UNICFONT        "mingliu36u.pbm"
#define         DEFAULT_ASCFONT         "ascii.pbm"
#define         DEFAULT_UNICFONT        "unicode.pbm"
#define         DEFAULT_FAX2TIFFOPT     "-M -1 -m"
#define         DEFAULT_ESCCHAR         '!'

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      int     wpbm_getheader(char *name, WPBM_HEADER *p);
GINNIMPORT      int     wpbm_xbyte(int xsize);
GINNIMPORT      int     wpbm_validrawpbm(char *name, WPBM_HEADER *p);
GINNIMPORT      void    wpbm_logfp(FILE *fp);
GINNIMPORT      void    wpbm_fontpath(char *p);
GINNIMPORT      void    wpbm_ascfont(char *p);
GINNIMPORT      void    wpbm_unicfont(char *p);
GINNIMPORT      void    wpbm_big5unic(char *p);
GINNIMPORT      void    wpbm_pbm2g3(char *p);
GINNIMPORT      void    wpbm_fax2tiff(char *p);
GINNIMPORT      void    wpbm_fax2tiffopt(char *p);
GINNIMPORT      void    wpbm_x1gap(int x);
GINNIMPORT      void    wpbm_x2gap(int x);
GINNIMPORT      void    wpbm_ygap(int y);
GINNIMPORT      void    wpbm_esc_char(char c);
GINNIMPORT      void    wpbm_keeptmpfile(int flag);
GINNIMPORT      int     wpbm_overlaplist(char *fpbm, char *flist);
GINNIMPORT      int     wpbm_txt2pbm(char *srcfile, char *varfile, char *datfile, int action);

__END_DECLS
