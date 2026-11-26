#include "area144_13.h"

MATCH void func_801F3C78(void) {
    Actor* work;
    u8     mode;

    work               = TASK(Actor);
    g_PartyPos.x.fixed = work->pos.x.fixed;
    g_PartyPos.y.fixed = work->pos.y.fixed;
    g_PartyPos.z.fixed = work->pos.z.fixed;
    mode               = g_ScriptState->move_mode;
    D_80143FC3         = 1;
    D_80143FC0         = mode;
    Area_SetFacingOffsetX(3);
}
