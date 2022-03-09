#ifndef         _WES_
#define         _WES_           1

#define WES_MINKEY      1
#define WES_MAXKEY      16

enum    {
        WES_MINFUNC,
        WES_WRITEKEY,
        WES_WRITEMKEY,
        WES_ENCRYPT,
        WES_DECRYPT,
        WES_MAXFUNC
};

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      void    wes_logfp(FILE *fp);
GINNIMPORT      int     wes_open(void);
GINNIMPORT      int     wes_close(void);
GINNIMPORT      int     wes_writemkey(int pos, unsigned char *key);
GINNIMPORT      int     wes_writeppkey(int pos, unsigned char *key);
GINNIMPORT      int     wes_writekey(int pos, unsigned char *key);
GINNIMPORT      int     wes_readppkey(int pos, unsigned char *key);
GINNIMPORT      int     wes_readkey(int pos, unsigned char *key);
GINNIMPORT      int     wes_cryptwmkey(int func, int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_encryptwmkey(int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_decryptwmkey(int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_cryptwppkey(int func, int mkey, int ppkey, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_encryptwppkey(int mkey, int ppkey, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_decryptwppkey(int mkey, int ppkey, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_cryptwkey(int func, int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_encryptwkey(int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_decryptwkey(int pos, unsigned char *src, unsigned char *dst, int size);
GINNIMPORT      int     wes_cipherilen(char *idata, int ilen, int key, char *odata, int mode);
GINNIMPORT      int     wes_cipher(char *idata, int key, char *odata, int mode);
GINNIMPORT      int     wes_xcipherilen(char *idata, int ilen, int mkey, int ppkey, char *odata, int mode);
GINNIMPORT      int     wes_xcipher(char *idata, int mkey, int ppkey, char *odata, int mode);

__END_DECLS

#endif
