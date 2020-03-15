
#ifndef POOL_EXPORT_H
#define POOL_EXPORT_H

#ifdef POOL_STATIC_DEFINE
#  define POOL_EXPORT
#  define POOL_NO_EXPORT
#else
#  ifndef POOL_EXPORT
#    ifdef pool_EXPORTS
        /* We are building this library */
#      define POOL_EXPORT 
#    else
        /* We are using this library */
#      define POOL_EXPORT 
#    endif
#  endif

#  ifndef POOL_NO_EXPORT
#    define POOL_NO_EXPORT 
#  endif
#endif

#ifndef POOL_DEPRECATED
#  define POOL_DEPRECATED __declspec(deprecated)
#endif

#ifndef POOL_DEPRECATED_EXPORT
#  define POOL_DEPRECATED_EXPORT POOL_EXPORT POOL_DEPRECATED
#endif

#ifndef POOL_DEPRECATED_NO_EXPORT
#  define POOL_DEPRECATED_NO_EXPORT POOL_NO_EXPORT POOL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef POOL_NO_DEPRECATED
#    define POOL_NO_DEPRECATED
#  endif
#endif

#endif /* POOL_EXPORT_H */
