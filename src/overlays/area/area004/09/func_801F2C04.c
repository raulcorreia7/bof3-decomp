#include "area004_09.h"

MATCH void func_801F2C04(void) {
    /* FAKE: retail reaches g_SceneEventFlags as D_801448EB + 0x63D, so the step byte address is kept in a register. */
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (D_801490C7) {
    case 0:
        D_801448ED = 0;
        break;
    case 1:
        D_801448ED = 1;
        break;
    default:
        return;
    }
    step  = &D_801448EB;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 0x1F);
}
