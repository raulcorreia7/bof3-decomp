#include "area097_13.h"

MATCH void func_801F2C04(void) {
    u8* result;
    s8* state = &D_801448EC;

    switch (*state) {
        case 0:
            Game_SetScriptActive();
            *state = 1;
            break;
        case 1:
            result = &D_80146867;
            if (*result == 2) {
                Game_ClearScriptActive();
                *result    = 0;
                D_801448EB = 0;
                *state     = 0;
            }
            break;
    }
}
