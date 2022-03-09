#define         WRIFF_WAVE_ALAW         0x0006
#define         WRIFF_WAVE_ULAW         0x0007

typedef
        struct  _WRIFF_WAVEINFO {
        int     format;
        long    offset;
        long    length;
}       WRIFF_WAVEINFO;

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      int     wriff_waveinfo(int fd, WRIFF_WAVEINFO *p);
GINNIMPORT      int     wriff_writeheader(int fd, int format);

__END_DECLS
