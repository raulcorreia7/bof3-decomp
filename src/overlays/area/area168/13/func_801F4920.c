#include "area168_13.h"

/* Draft matches; adjacent scene globals need a shared type. */
MATCH void func_801F4920(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 0) {
        SYS_SetFlag(g_SceneEventFlags, 143U);
        Scene_StartEvent(0x3B, 0);
    }
}
