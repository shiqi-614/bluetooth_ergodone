#include "print.h"
#include "tmk/xprintf.h"

template <typename... T>
void print(const char* str, T... args)
{
    int len = snprintf(NULL, 0, str, args...);
    if (len) {
        char buff[len];
        sprintf(buff, str, args...);
        Serial.println(buff);
    }
}
