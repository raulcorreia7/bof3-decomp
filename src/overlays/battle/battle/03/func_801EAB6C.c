#include "battle_03.h"

MATCH u8 func_801EAB6C(u8* message) {
    u8  count;
    u32 value;

    count = 0;
    value = *message;
    while (value != 0u) {
        if (((value - 0x12u) < 2u) || (value == 0x15u)) {
            message += 1;
        }
        message += 1;
        count += 1;
        value = *message;
    }
    return count;
}
