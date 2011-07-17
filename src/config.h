#ifndef SERIALIZER__CONFIG_H
#define SERIALIZER__CONFIG_H

// optional components that can be used
//#define HAVE_BOOST_FILESYSTEM

// define PLATFORM_ directive
#ifdef WIN32
    #define PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM_MACOS
#else
    #define PLATFORM_LINUX
#endif

// logging configuration
#define LOG_DIRECTORY "logs/"

#if defined(HAVE_BOOST_FILESYSTEM)
    #define USE_BOOST_LOG_OPENER
#elif defined(PLATFORM_WINDOWS)
    #define USE_WINDOWS_LOG_OPENER
#else
    #define USE_POSIX_LOG_OPENER
#endif

#endif
