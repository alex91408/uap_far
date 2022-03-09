#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      int     pattern_match(char *src, int slen, char *ptrn, int plen);
GINNIMPORT      int     init_skip(char *ptrn, int plen);
GINNIMPORT      int     bm_match(char *src, int slen, char *ptrn, int plen);

__END_DECLS
