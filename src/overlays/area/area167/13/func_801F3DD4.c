#include "area167_13.h"

MATCH void func_801F3DD4(void) {
    g_MessageRequest = 0xFFFF;
    if (D_801490C7 != 2) {
        if (D_801490C7 == 0) {
            D_80146866 = 0;
        } else {
            D_80146866 = 1;
        }
        Game_SetScriptActive();
        D_80146867 = 0x40;
        D_801448EB = 0x20;
        D_801448EC = 0x14;
    }
}
