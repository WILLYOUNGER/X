#include "XString.h"

namespace XSTRINGTOOL {

std::string PUB_strformat(const char *format, ...)
{
    va_list valst;
    va_start(valst, format);

    char _c_buffer_ptr[1024] = {0};

    vsnprintf(_c_buffer_ptr, 1023, format, valst);
    va_end(valst);

    return std::string(_c_buffer_ptr);
}

}
