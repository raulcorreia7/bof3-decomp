#include "area167_13.h"

MATCH void func_801F3CE0(void) {
    s8 variant;

    g_MessageRequest = 0xFFFF;
    if (D_801490C7 != 2) {
        variant = 2;
        if (D_801490C7 == 0) {
            variant = 1;
        }
        D_80146866 = variant;
        Game_SetScriptActive();
        D_80146867 = 0x40;
        D_801448EB = 0x20;
        D_801448EC = 0x15;
    }
}
