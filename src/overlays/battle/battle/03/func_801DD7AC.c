#include "battle_03.h"

MATCH u8 func_801DD7AC(s32 selector) {
    u8 var = g_CharSlot[selector & 0xFF];

    if ((var & 0xFF) == 7) {
        var = 0;
    }
    return var;
}
