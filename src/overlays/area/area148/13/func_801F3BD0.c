#include "area148_13.h"

MATCH void func_801F3BD0(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 5;
        SYS_SetFlag(g_SaveData.scene_event_flags, 0x59);
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
