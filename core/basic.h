
#ifndef __BASIC_H_
#define __BASIC_H_

#define ARK_LIGHT_VERSION  L"0.0.1"

#if defined _WIN64 || __x86_64 || __LP64__
#define ARK_64
#endif

#if defined _MSC_VER
#define ARK_MSVC
#else
#define ARK_GCC
#if defined(__APPLE__)
#define ARK_APPLE
#endif
#endif

#endif
