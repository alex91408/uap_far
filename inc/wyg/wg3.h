enum    {
        WG3_BO_MSB2LSB, WG3_BO_LSB2MSB,
        WG3_BO_MAX
};

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      void    wg3_setbytealign(int flag);
GINNIMPORT      void    wg3_setbitsorder(int flag);
GINNIMPORT      void    wg3_settiffflag(int flag);
GINNIMPORT      int     wg3_pbm2g3(char *fpbm, int fg3);

__END_DECLS
