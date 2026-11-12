#include "area104_14.h"

/* The probe loop matches area121 func_801F5028 but keeps a separate body: the functions have different names, addresses and parameter forms. */
MATCH u8 func_801F4AE4(s32 x, s32 y, s32 dir) {
    s32 tries;

    if ((u8)dir != 0xFF) {
        tries                = 0;
        g_Task->direction_08 = Actor_FacingToward();
        do {
            if (func_801B0E44() == 0 && func_801BDE14(x, y, 0) == -1) {
                break;
            }
            g_Task->direction_08 = (g_Task->direction_08 + 1) & 0x7;
            tries++;
        } while (tries < 8);
        if (tries < 8) {
            return 1;
        }
    }
    return 0;
}
