#include "area145_14.h"

MATCH void func_801F3E10(void) {
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) + 2000;
    g_Task->gravity          = -8;
    g_Task->vx               = 0;
    g_Task->vy               = 0;
    g_Task->vz               = 0;
    g_Task->unk_04           = 1;
    Actor_SelectScript(0x3B);
    g_ScriptState->flag_00 |= 0x40;
    g_ScriptState->unk_01 = (D_80146250 - g_Game.members) * 20;
    g_ScriptState->cursor -= 2;
}
