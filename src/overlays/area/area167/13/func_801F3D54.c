#include "area167_13.h"

MATCH void func_801F3D54(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice != 2) {
        if (g_MessageChoice == 0) {
            D_80146866 = 0;
        } else {
            D_80146866 = 2;
        }
        Game_SetScriptActive();
        D_80146867 = 0x40;
        D_801448EB = 0x20;
        D_801448EC = 0x14;
    }
}
