// Win32
#if defined ( WIN32 ) || defined ( _WIN32 )
    #include "allegro5/platform/alplatf_win32_msvc.h"

// Linux
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #include "allegro5/platform/alplatf_linux.h"

// Mac
#elif defined(__APPLE__) 
    // iPhone
    #if TARGET_OS_IPHONE
        #include "allegro5/platform/alplatf_iphone.h"

    // OSX
    #else
        #include "allegro5/platform/alplatf_macosx.h"

    #endif

// Android
#elif defined(__ANDROID)
    #include "allegro5/platform/alplatf_android.h"

#endif
