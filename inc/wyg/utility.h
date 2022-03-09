#ifndef         _UTILITY_
#define         _UTILITY_               1
#include        <time.h>
//#if	!defined(EC_WIN32)
//#include        <sys/time.h>
//#endif
#include        <errno.h>
#define         MON_PER_YEAR            12
#define         HOUR_PER_DAY            24
#define         MIN_PER_HOUR            60
#define         SEC_PER_MIN             60
#define         ENDL                    "\r\n"

#define         WCFG_BUFSIZE            511
typedef int     (*WCFGFUNCPTR)(char *);

typedef
        struct  {
        long    x[2];
}       GINN_TB;

enum    {
        P_CHAR, P_SPACE, P_HEX, P_DEC
};

enum    {
        F_RESET, F_COUNT
};

enum    {
        PT_STR, PT_LONG,
        PT_MAX
};

enum	{
	W_BO_LITTLEENDIAN, W_BO_BIGENDIAN,
	W_BO_MAX
};

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      FILE    *wygfp;
GINNIMPORT      int     xshowtime;
GINNIMPORT      struct  tm      *xtm;
GINNIMPORT      struct  timeval *xtimeval;
//extern  int     errno;

GINNIMPORT      int     wbyteorder(void);
GINNIMPORT      int     xfprintime(FILE *fp);
GINNIMPORT      int     xfprintf(FILE *fp, char *fmt, ...);
GINNIMPORT      int     is_digit(char c);
GINNIMPORT      int     is_xdigit(char c);
GINNIMPORT      int     is_upper(char c);
GINNIMPORT      int     is_lower(char c);
GINNIMPORT      int     is_alpha(char c);
GINNIMPORT      int     to_upper(char c);
GINNIMPORT      int     to_lower(char c);
GINNIMPORT      int     xstricmp(char *, char *, int);
GINNIMPORT      int     wstricmp(char *, char *);
GINNIMPORT      char    *wstrlwr(char *);
GINNIMPORT      char    *wstrupr(char *);
GINNIMPORT      int     is_long(char *buf, int n, long *value);
GINNIMPORT      int     is_digit_spc(char *, char *);
GINNIMPORT      int     is_digit_spc_t(char *, char *, char *);
GINNIMPORT      int     is_alpha_spc(char *, char *);
GINNIMPORT      long    wtime(long *t);
GINNIMPORT      long    elapsed_time(int flag, long *t);
GINNIMPORT      int     reset_ginn_tb(GINN_TB *t);
GINNIMPORT      long    elapsed_10ms(int flag, GINN_TB *t);
GINNIMPORT      long    elapsed_utime(int flag, GINN_TB *t);
GINNIMPORT      void    xfclose(FILE **fp);
GINNIMPORT      const   char    *xperror(int err);
GINNIMPORT      int     xstat(char *filename, long *size);
GINNIMPORT      long    xfilelength(char *filename);
GINNIMPORT      int     xrandom(int max);
GINNIMPORT      void    xstrncpy(char *dst, char *src, int n);
GINNIMPORT      void    xmempcpy(char *dst, char *src, int n);
GINNIMPORT      int     xfprintptr(FILE *fp, char *ptr, int n, int mode);
GINNIMPORT      int     make_feb(int year);
GINNIMPORT      int     days_of_month(int year, int month);
GINNIMPORT      long    xlocaltime(int days);
GINNIMPORT      int     wsplitpath(char *path);
GINNIMPORT      int     wcfggetlcnt(void);
GINNIMPORT      int     wcfggets(char *cfg, int chan, WCFGFUNCPTR funcp);
GINNIMPORT      char    *wgetcfgparm(char *cfg, int chan, char *token, int type, void *dest);
GINNIMPORT      char    *wgetcfgstr(char *cfg, int chan, char *token, char *dest);

__END_DECLS

#endif
