#include "area144_13.h"

MATCH void func_801F3C78(void) {
    Actor* work;
    u8     mode;

    work     = g_Task;
    g_PartyX = work->pos.x.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the x store before the y load. */
    g_PartyY = work->pos.y.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the y store before the z load. */
    D_80143F84 = work->pos.z.fixed;
    mode       = g_ScriptState->unk_04;
    D_80143FC3 = 1;
    D_80143FC0 = mode;
    Area_SetFacingOffsetX(3);
}
