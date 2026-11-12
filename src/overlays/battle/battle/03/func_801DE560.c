#include "battle_03.h"

MATCH void func_801DE560(u8 event_kind, u8 event_value, u8 group, u8 timer, u8* payload) {
    u8 index;
    u8 value;

    index = 2u;
    while (index < 8u) {
        value = D_801EB4F0[index][0];
        if (value == 0u) {
            D_801EB4F0[index][0]  = value | 1u;
            D_801EB4F1[index][0]  = event_kind;
            /* slot+2 byte; battle_03.h declares D_801EB4F2 as a scalar, so reach it
             * as the last byte of the previous stride row */
            D_801EB4F3[index][-1] = event_value;
            D_801EB4F3[index][0]  = group;
            D_801EB4F8[index][0]  = timer;
            D_801EB4F4[index][0]  = payload;
            D_801EB4FA[index][0]  = 0u;
            return;
        }
        index += 1u;
    }
}
