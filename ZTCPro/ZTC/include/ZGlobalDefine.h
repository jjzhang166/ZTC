#ifndef ZTC__INCLUDE__ZGLOBALDEFINE_H    
#define ZTC__INCLUDE__ZGLOBALDEFINE_H    
/*   
   The operating system, must be one of: (Z_OS_x)   
         
     MACX   - Mac OS X   
     MAC9   - Mac OS 9   
     MSDOS  - MS-DOS and Windows   
     OS2    - OS/2   
     OS2EMX - XFree86 on OS/2 (not PM)   
     WIN32  - Win32 (Windows 95/98/ME and Windows NT/2000/XP)   
     CYGWIN - Cygwin   
     SOLARIS    - Sun Solaris   
     HPUX   - HP-UX   
     ULTRIX - DEC Ultrix   
     LINUX  - Linux   
     FREEBSD    - FreeBSD   
     NETBSD - NetBSD   
     OPENBSD    - OpenBSD   
     BSDI   - BSD/OS   
     IRIX   - SGI Irix   
     OSF    - HP Tru64 UNIX   
     SCO    - SCO OpenServer 5   
     UNIXWARE   - UnixWare 7, Open UNIX 8   
     AIX    - AIX   
     HURD   - GNU Hurd   
     DGUX   - DG/UX   
     RELIANT    - Reliant UNIX   
     DYNIX  - DYNIX/ptx   
     QNX    - QNX   
     QNX6   - QNX RTP 6.1   
     LYNX   - LynxOS   
     BSD4   - Any BSD 4.4 system   
     UNIX   - Any UNIX BSD/SYSV system   
*/
          
#if defined(__APPLE__) && defined(__GNUC__)    
#  define Z_OS_MACX    
#elif defined(__MACOSX__)    
#  define Z_OS_MACX    
#elif defined(macintosh)    
#  define Z_OS_MAC9    
#elif defined(__CYGWIN__)    
#  define Z_OS_CYGWIN    
#elif defined(MSDOS) || defined(_MSDOS)    
#  define Z_OS_MSDOS    
#elif defined(__OS2__)    
#  if defined(__EMX__)    
#    define Z_OS_OS2EMX    
#  else    
#    define Z_OS_OS2    
#  endif    
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))    
#  define Z_OS_WIN32    
#  define Z_OS_WIN64    
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))    
#  define Z_OS_WIN32    
#elif defined(__MWERKS__) && defined(__INTEL__)    
#  define Z_OS_WIN32    
#elif defined(__sun) || defined(sun)    
#  define Z_OS_SOLARIS    
#elif defined(hpux) || defined(__hpux)    
#  define Z_OS_HPUX    
#elif defined(__ultrix) || defined(ultrix)    
#  define Z_OS_ULTRIX    
#elif defined(sinix)    
#  define Z_OS_RELIANT    
#elif defined(__linux__) || defined(__linux)    
#  define Z_OS_LINUX    
#elif defined(__FreeBSD__)    
#  define Z_OS_FREEBSD    
#  define Z_OS_BSD4    
#elif defined(__NetBSD__)    
#  define Z_OS_NETBSD    
#  define Z_OS_BSD4    
#elif defined(__OpenBSD__)    
#  define Z_OS_OPENBSD    
#  define Z_OS_BSD4    
#elif defined(__bsdi__)    
#  define Z_OS_BSDI    
#  define Z_OS_BSD4    
#elif defined(__sgi)    
#  define Z_OS_IRIX    
#elif defined(__osf__)    
#  define Z_OS_OSF    
#elif defined(_AIX)    
#  define Z_OS_AIX    
#elif defined(__Lynx__)    
#  define Z_OS_LYNX    
#elif defined(__GNU_HURD__)    
#  define Z_OS_HURD    
#elif defined(__DGUX__)    
#  define Z_OS_DGUX    
#elif defined(__QNXNTO__)    
#  define Z_OS_QNX6    
#elif defined(__QNX__)    
#  define Z_OS_QNX    
#elif defined(_SEQUENT_)    
#  define Z_OS_DYNIX    
#elif defined(_SCO_DS)                   /* SCO OpenServer 5 + GCC */    
#  define Z_OS_SCO    
#elif defined(__USLC__)                  /* all SCO platforms + UDK or OUDK */    
#  define Z_OS_UNIXWARE    
#  define Z_OS_UNIXWARE7    
#elif defined(__svr4__) && defined(i386) /* Open UNIX 8 + GCC */    
#  define Z_OS_UNIXWARE    
#  define Z_OS_UNIXWARE7    
#else    
#  error "ZTC has not been ported to this OS!"    
#endif    
          
#if defined(Z_OS_MAC9) || defined(Z_OS_MACX)    
#  define Z_OS_MAC    
#endif    
          
#if defined(Z_OS_MAC9) || defined(Z_OS_MSDOS) || defined(Z_OS_OS2) || defined(Z_OS_WIN32) || defined(Z_OS_WIN64)    
#  undef Z_OS_UNIX    
#elif !defined(Z_OS_UNIX)    
#  define Z_OS_UNIX    
#endif


//---@±‡“Î∆˜-----begin
#ifdef _WIN32

	#if defined(ZTC_EXPORT) && defined(_WINDLL)
		#define  ZTC_API __declspec(dllexport)
		#define EXPIMP_TEMPLATE
	#elif !defined(ZTC_STATIC)
		#define ZTC_API __declspec(dllimport)
		#define EXPIMP_TEMPLATE extern
	#else
		#define ZTC_API
		#define EXPIMP_TEMPLATE
	#endif

#elif defined(__linux__)

	#if defined(ZTC_EXPORT)
		#define ZTC_API __attribute__((visibility("default")))
		#define EXPIMP_TEMPLATE
	#else
		#define ZTC_API
		#define EXPIMP_TEMPLATE extern
	#endif

#else

	#define ZTC_API
	#define EXPIMP_TEMPLATE
#endif
//---@±‡“Î∆˜-----end

#endif //ZTC__INCLUDE__ZGLOBALDEFINE_H