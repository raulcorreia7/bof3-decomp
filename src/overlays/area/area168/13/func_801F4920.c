#include "area168_13.h"

/* Draft matches; adjacent scene globals need a shared type. */
MATCH void func_801F4920(void) {
    g_MessageRequest = 0xFFFF;
    if (D_801490C7 == 0) {
        SYS_SetFlag(g_SceneEventFlags, 0x8FU);
        Game_SetScriptActive();
        D_801448EB = 0x3B;
        D_801448EC = 0;
    }
}
