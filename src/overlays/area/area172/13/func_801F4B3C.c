#include "area172_13.h"

MATCH void func_801F4B3C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        if (SYS_TestFlag(D_80144EF8, 0x12)) {
            D_801448EB = 0x23;
            D_801448EC = 5;
        } else {
            D_80146874 = 6;
            D_80146875 = 0;
        }
    }
}
