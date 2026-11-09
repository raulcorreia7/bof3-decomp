#include "engine/slus/slus.h"

/* Modifies a bounded byte counter by a signed delta. */
MATCH s32 Char_AddResistance(u8* counter, s32 delta) {
    s32 signed_delta;

    signed_delta = (s8)delta;

    if (signed_delta > 0) {
        if (*counter >= 6) {
            return 0;
        }
        *counter = (*counter + delta);
        if (*counter >= 7) {
            *counter = 6;
        }
        return 1;
    }

    if (signed_delta < 0) {
        if (*counter >= 6) {
            return 0;
        }
        *counter = (*counter + delta);
        if ((s8)*counter < 0) {
            *counter = 0;
        }
        return 1;
    }

    if (*counter >= 7) {
        return 0;
    }
    *counter = 7;
    return 1;
}
