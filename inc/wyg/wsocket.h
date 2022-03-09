#ifdef  EC_WIN32
#define ERRNO           (WSAGetLastError())
#define H_ERRNO         (WSAGetLastError())
#else
#define ERRNO           (errno)
#define H_ERRNO         (h_errno)

#include        <sys/socket.h>
#include        <net/if.h>
#ifdef  _GINN_SCO_
extern  int     h_errno;
#endif
#endif

#ifdef  _GINN_SOLARIS_
#define INADDR_NONE     -1
#endif

#include        "cdefs.h"
__BEGIN_DECLS

GINNIMPORT      long    socket_get_ipaddr(char *host, FILE *fp);
#ifdef  EC_WIN32
GINNIMPORT      int     socket_startup(void);
GINNIMPORT      int     socket_cleanup(void);
#else
GINNIMPORT      long    socket_get_if(char *ifname, FILE *fp);
GINNIMPORT      long    socket_get_ifconf(struct ifreq *ifr, int n, FILE *fp);
#endif

__END_DECLS
