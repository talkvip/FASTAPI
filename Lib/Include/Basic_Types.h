#ifndef HUNDSUN_PUBLIC_BASIC_TYPES_H
#define HUNDSUN_PUBLIC_BASIC_TYPES_H

#if defined(__linux__)
#include <unistd.h>
#include <pthread.h>
#endif
#include <errno.h>
#include <cstdarg>
#include <string>
#include <time.h>
#include <limits>

/***
 * SIZE OF SHORT
 */
#if !defined (SIZEOF_SHORT)
#  if (USHRT_MAX) == 255U
#    define SIZEOF_SHORT 1
#  elif (USHRT_MAX) == 65535U
#    define SIZEOF_SHORT 2
#  elif (USHRT_MAX) == 4294967295U
#    define SIZEOF_SHORT 4
#  elif (USHRT_MAX) == 18446744073709551615U
#    define SIZEOF_SHORT 8
#  else
#    error: unsupported short size, must be updated for this platform!
#  endif
#endif 
/* !defined (SIZEOF_SHORT) */

/***
 * SIZE OF INT 
 */
#if !defined (SIZEOF_INT)
#  if (UINT_MAX) == 65535U
#    define SIZEOF_INT   2
#  elif (UINT_MAX) == 4294967295U
#    define SIZEOF_INT   4
#  elif (UINT_MAX) == 18446744073709551615U
#    define SIZEOF_INT   8
#  else
#    error: unsupported int size, must be updated for this platform!
#  endif
#endif /* !defined (SIZEOF_INT) */

/***
 * SIZE OF LONG 
 */
#if !defined (SIZEOF_LONG)
#  if (ULONG_MAX) == 65535UL
#    define SIZEOF_LONG   2
#  elif (ULONG_MAX) == 4294967295UL
#    define SIZEOF_LONG   4
#  elif (ULONG_MAX) == 18446744073709551615UL
#    define SIZEOF_LONG   8
#  else
#    error: unsupported long size, must be updated for this platform!
#  endif
#endif /* !defined (SIZEOF_LONG) */

/***
 * SIZE OF LONG LONG 
 */
#if !defined (SIZEOF_LONG_LONG)
#  if defined (ULLONG_MAX)
#    if ((ULLONG_MAX) == 4294967295ULL)
#      define SIZEOF_LONG_LONG   4
#    elif ((ULONG_MAX) == 18446744073709551615ULL)
#      define SIZEOF_LONG_LONG   8
#    endif
#  endif
#  if !defined (SIZEOF_LONG_LONG)
#    define SIZEOF_LONG_LONG     8
#  endif
#endif /* !defined (SIZEOF_LONG_LONG) */


/*8-bits Integer*/
     typedef char                 int8 ;
     typedef unsigned char               uint8 ;

/*16-bits Interger*/
#  if SIZEOF_SHORT == 2
     typedef short                       int16 ;
     typedef unsigned short              uint16 ;
#  elif SIZEOF_INT == 2
     typedef int                         int16 ;
     typedef unsigned int                uint16 ;
#  else
#    error Have to add to the int16 type setting.
#  endif

/*32-bits Interger*/
#  if SIZEOF_INT == 4
     typedef int                        int32 ;
     typedef unsigned int               uint32 ;
#  elif SIZEOF_LONG == 4
     typedef int                        int32 ;
     typedef signed int                 uint32 ;
#  else
#    error Have to add to the int32 type setting.
#  endif

/*64-bits Integer*/
#  if SIZEOF_LONG == 8  
     typedef long                       int64 ;
     typedef signed long                uint64 ;
#  elif SIZEOF_LONG_LONG == 8  
     typedef long long                  int64 ;  
     typedef unsigned long long         uint64 ;
#  else
#    error Have to add to the int64 type setting.
#  endif


/*FUNCTION_CALL_MODE*/
#ifdef _WIN32
# if !defined (FUNCTION_CALL_MODE)
#   define FUNCTION_CALL_MODE         __stdcall
# endif
# else
#   define FUNCTION_CALL_MODE
#endif

/*EXPORT*/
#ifdef _WIN32
#  ifdef _DLL_EXPORT
#    define MY_EXPORT __declspec(dllexport)
#  else
#    define MY_EXPORT __declspec(dllimport)
#endif
#else
#  define MY_EXPORT
#endif

	 // fast type
	 typedef enum 
	 {
		 emFAST_SHLEVEL2 ,
		 emFAST_SZLEVEL2
	 } FAST_TYPE ;

#endif
