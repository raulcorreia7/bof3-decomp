#include "area052_13.h"

MATCH void func_801F37A8(void) {
    s32 x;
    s32 y;

    if ((u8)func_801F3980(&x, &y) != 0) {
        if (D_80146867 == 10) {
            if (g_Task->pos.x.fixed != TO_COORD_HALF(104)) {
                func_801F3BA0(x, y);
                g_ScriptState->cursor += 6;
            }
        } else if (D_80146867 == 20) {
            func_801F3A14(x, y);
            if (g_Task->pos.x.fixed == TO_COORD_HALF(133)) {
                g_ScriptState->cursor += 3;
                /* FAKE: keeps the step store after the cursor store. */
                FAKE_BARRIER();
                g_SceneEventStep = 45;
            }
        }
    }
}
