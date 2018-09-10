#ifndef CCACHE_CONFIG_H
#define CCACHE_CONFIG_H

#define WINVER          0x0600
#define _WIN32_WINNT    0x0600

// #define HAVE_COMPAR_FN_T
// #define HAVE_EXTERN_INLINE
#define HAVE_GETFINALPATHNAMEBYHANDLEW
#define HAVE_GETHOSTNAME                    0
// #define HAVE_GETOPT_LONG
// #define HAVE_GETPWUID
// #define HAVE_GETTIMEOFDAY
// #define HAVE_HIDDEN
#define HAVE_LCONV_DECIMAL_POINT            0
#define HAVE_LCONV_THOUSANDS_SEP            0
#define HAVE_LOCALECONV                     0
#define HAVE_MEMCPY                         1
// #define HAVE_MKSTEMP
#define HAVE_REALPATH                       0
// #define HAVE_STRNDUP
// #define HAVE_STRTOK_R
// #define HAVE_UNSETENV

#define HAVE_PTRDIFF_T                      1
#define HAVE_INTMAX_T                       1
#define HAVE_UINTMAX_T                      1
#define HAVE_UINTPTR_T                      1
#define HAVE_LONG_DOUBLE                    0
#define HAVE_LONG_LONG_INT                  1
#define HAVE_UNSIGNED_LONG_LONG_INT         1
// #define HAVE_UTIMES
#define HAVE_VA_COPY                        1
#define HAVE___VA_COPY                      0
#define HAVE_ASPRINTF                       0
#define HAVE_SNPRINTF                       1
#define HAVE_VASPRINTF                      0
#define HAVE_VSNPRINTF                      1

#define HAVE_INTTYPES_H 1
#define HAVE_LOCALE_H 1
//#define HAVE_PWD_H
#define HAVE_STDARG_H 1
#define HAVE_STDDEF_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
//#define HAVE_SYS_MMAN_H
//#define HAVE_SYS_TIME_H
//#define HAVE_SYS_WAIT_H
#define HAVE_UNISTD_H

#endif