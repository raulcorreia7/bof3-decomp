#include "area121_14.h"

MATCH u8 func_801F5028(s32 x, s32 y, u8 dir) {
    s32 tries;

    if (dir != 0xFF) {
        tries                  = 0;
        SELF(Actor)->direction = CALL_AS(s32 (*)(), Actor_FacingToward)();
        do {
            if (func_801B0E44() == 0 && Actor_FindInRange(x, y, 0) == -1) {
                break;
            }
            SELF(Actor)->direction = (SELF(Actor)->direction + 1) & 0x7;
            tries++;
        } while (tries < 8);
        if (tries < 8) {
            return 1;
        }
    }
    return 0;
}
