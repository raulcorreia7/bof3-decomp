#include "area002_09.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            D_801448ED = 5;
            break;
        case 1:
            D_801448ED = 4;
            break;
        default:
            return;
    }
    step  = &D_801448EB;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 0x1E);
}
