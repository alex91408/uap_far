enum    {
        TCP_C_ERROR = -1, TCP_C_NONE, TCP_C_SERVER, TCP_C_DATA, TCP_C_CONNECTED,
        TCP_C_CONNFAILED, TCP_C_CONNECTING,
        TCP_C_MAXSTATE
};

enum    {
        TCP_E_NONE, TCP_E_NOUSE, TCP_E_ACCEPT, TCP_E_MAXHANDLE,
        TCP_E_MAXERROR
};

enum    {
        TCP_M_BLOCKING, TCP_M_NONBLOCKING,
        TCP_M_MAXSTATE
};

typedef
        struct  _TCP_SOCKADDR {
        long    addr;
        unsigned        int     port;
}       TCP_SOCKADDR;

typedef
        struct  _TCP_HD {
        int     handle;
        int     inprogress;
        TCP_SOCKADDR    l;
        TCP_SOCKADDR    r;
}       TCP_HD;

//extern  int     tcptimeout;
//extern  int     tcpremoteinfo;
//extern  FILE    *tcpfp;
//extern  TCP_HD  *thd;
//extern  int     *hda;

//      2003.07.14
//      tcp_check_nh() now return TCP_C_NONE for unused handle,
//              TCP_C_CONNECTED for used and connected handle
//              TCP_C_CONNECTING for used and connection in progress handle
//

#include        "cdefs.h"
__BEGIN_DECLS

#ifdef  _GINN_SCO_
extern  int     h_errno;
#endif

GINNIMPORT      void    tcp_blockingmode(int mode);
GINNIMPORT      void    tcp_timeout(int microsec);
GINNIMPORT      void    tcp_logfp(FILE *fp);
GINNIMPORT      void    tcp_keepalive(int flag);
GINNIMPORT      void    tcp_reuseaddr(int flag);
GINNIMPORT      int     tcp_server_getsockname(int no, char *addr, char *port);
GINNIMPORT      int     tcp_getsockname(int no, char *laddr, char *lport, char *raddr, char *rport);
GINNIMPORT      int     tcp_handle_count(void);
GINNIMPORT      int     tcp_nuse(void);
GINNIMPORT      int     tcp_check_nh(int no);
GINNIMPORT      int     tcp_handle_init(int cnt);
GINNIMPORT      int     tcp_server_handle_count(void);
GINNIMPORT      int     tcp_server_nuse(void);
GINNIMPORT      int     tcp_server_check_nh(int no);
GINNIMPORT      int     tcp_server_handle_init(int cnt);
GINNIMPORT      int     tcp_remote_addr(int no, char *p);
GINNIMPORT      int     tcp_server_close(int no);
GINNIMPORT      int     tcp_close(int no);
GINNIMPORT      int     tcp_server_open(char *serv_name);
GINNIMPORT      int     tcp_server_xopen(char *lif, char *serv_name);
GINNIMPORT      int     tcp_server_ready(int no);
GINNIMPORT      int     tcp_connect(char *host, char *serv_name);
GINNIMPORT      int     tcp_xconnect(char *host, char *serv_name, char *localif, char *localport);
GINNIMPORT      int     tcp_connect_icmp(char *host, char *serv_name);
GINNIMPORT      int     tcp_xconnect_icmp(char *host, char *serv_name, char *localif, char *localport);
GINNIMPORT      int     tcp_send(int no, char *p, int len);
GINNIMPORT      int     tcp_data_ready(int no);
GINNIMPORT      int     tcp_ready(int *no);
GINNIMPORT      int     tcp_receive(int no, char *p, int len);
GINNIMPORT      int     tcp_xreceive(int no, char *p, int len);
GINNIMPORT      int     tcp_icmp_check(char *host);
GINNIMPORT      int     tcp_nbytes_inq(int no);
GINNIMPORT      int     tcp_nbytes_outq(int no);

__END_DECLS
