#include "area037_13.h"

MATCH void func_801F3854(void) {
    s8 choice = D_801490C7;

    if (choice == 0) {
        Game_SetScriptActive();
        D_801448EB = AREA_ORIGIN_OFFSET;
        MESSAGE_REQUEST_CLEAR();
    } else if (choice == 1) {
        MESSAGE_REQUEST_CLEAR();
        D_80146867 = 0x64;
    } else if (choice == 2) {
        MESSAGE_REQUEST_CLEAR();
        D_80146867 = 0x5F;
    }
}
