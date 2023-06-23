#include "include/to_camel_case.h"

void to_camel_case(const char *text, char *camel) {
    do {
        *camel = *text;
        if (*text == '-' || *text == '_') {
            char head = *(text + 1);
            *camel = (char)(head - ((head >= 'a' && head <= 'z') ? 32 : 0));
            // *camel = (char)((head >= 'a' && head <= 'z') ? toupper(head) : head);
            text++;
        }
        camel++;
        text++;
    } while (*text != '\0');
    *camel = '\0';
}
