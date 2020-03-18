#ifndef API_EXPORTS_H
#define API_EXPORTS_H

#ifdef _WIN32
    #ifdef osco_od_gen_EXPORTS
        #define API_EXPORT __declspec(dllexport)
    #else
        #define API_EXPORT __declspec(dllimport)
    #endif
#else
    #define API_EXPORT
#endif

#endif /* API_EXPORTS_H */