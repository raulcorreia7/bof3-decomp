#include "area002_09.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (D_801490C7) {
        case 0:
            g_SaveData.scene_event.selection = 5;
            break;
        case 1:
            g_SaveData.scene_event.selection = 4;
            break;
        default:
            return;
    }
    step  = &g_SaveData.scene_event.mode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 0x1E);
}
