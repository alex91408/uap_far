#if     defined(EC_WIN32) && defined(GINN_DLL)
#ifdef  GINN_EXPORTS
#define GINNIMPORT      __declspec (dllexport)
#else
#define GINNIMPORT      __declspec (dllimport)
#endif
#else
#define GINNIMPORT      extern
#endif

#if defined(EC_WIN32) || defined(WIN32) || defined(_GINN_WIN32_) || defined(_GINN_SOLARIS_) || defined(_GINN_SCOUNIX_)
#if defined(__cplusplus)
#define __BEGIN_DECLS   extern "C" {
#define __END_DECLS     };
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif
#else
#include        <sys/cdefs.h>
#endif

#ifdef  EC_WIN32
#define         wopen           _open
#define         wclose          _close
#define         wlseek          _lseek
#define         wread           _read
#define         wwrite          _write
#else
#ifndef O_BINARY
#define         O_BINARY        0
#endif
#define         wopen           open
#define         wclose          close
#define         wlseek          lseek
#define         wread           read
#define         wwrite          write
#endif

