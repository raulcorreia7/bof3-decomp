#include "area135_14.h"

MATCH u8 func_801F5D1C(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        if (func_801F5C60(2129920, (i << 17) + 0xC8000) == 0xFF) {
            break;
        }
    }
    return i;
}
