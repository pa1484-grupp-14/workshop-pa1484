#ifdef NATIVE_BUILD
#include "String.h"
bool strstr(const std::string& a, const std::string& b ) {
    return a == b;
}
#endif