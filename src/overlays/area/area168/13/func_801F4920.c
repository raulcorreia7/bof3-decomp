#include "area168_13.h"

/* Draft matches; adjacent scene globals need a shared type. */
MATCH void func_801F4920(void) {
    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 0) {
        SYS_SetFlag(g_SaveData.scene_event_flags, 0x8FU);
        Game_SetScriptActive();
        D_801448EB = 0x3B;
        D_801448EC = 0;
    }
}
