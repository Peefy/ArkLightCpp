
#include <string>
#include "../core/basic.h"

enum class Platform
{
    Unknown = 0,
    Windows = 1,
    Linux = 2,
    MacOS = 3,
    Android = 4,
    iOS = 5
};

inline Platform GetPlatfom() {
    #if defined ARK_MSVC
    return Platform::Windows;
    #elif defined ARK_GCC
    return Platform::Linux;
    #elif defined ARK_APPLE
    return Platform::MacOS;
    #else
    return Platform::Unknown;
    #endif
}
