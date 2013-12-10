// ======================================================================================
// File         : expat_config.h
// Author       : Wu Jie 
// Last Change  : 12/10/2013 | 02:27:47 AM | Tuesday,December
// Description  : 
// ======================================================================================

// windows 32-bit 
#if defined ( WIN32 ) || defined ( _WIN32 )
    #include <winconfig.h>
// linux
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #include <expat_linux_config.h>
// apple
#elif defined(__APPLE__)
// ios
    #if TARGET_OS_IPHONE
        #include <expat_ios_config.h>
// mac osx
    #else
        #include <expat_mac_config.h>
    #endif
// android
#elif defined(__ANDROID)
    #include <expat_android_config.h>
// unknown
#else
    #include <expat_config.h>
#endif
