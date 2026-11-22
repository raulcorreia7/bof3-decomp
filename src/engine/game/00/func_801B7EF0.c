#include "game_00.h"

MATCH void func_801B7EF0(void) {
    s32 value;

    COORD_INT(g_Task->pos.z) = Area_HeightRead(g_Task->pos.x.fixed, g_Task->pos.y.fixed) + 0x200;
    value                    = 0x3D;
    if (g_Task->direction == FACING_RIGHT) {
        value = 0x3C;
    }
    Script_Request(value);
    if (g_Task->unk_05 != 0) {
        Actor_SetSemiTransparent();
        g_Task->tint.steps.delta.r = -0x80;
        g_Task->tint.steps.delta.g = -0x80;
        g_Task->tint.steps.delta.b = -0x80;
        g_Task->tint.bytes.flags   = 1;
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->unk_04 = 7;
    } else {
        g_Task->unk_04 = 8;
    }
}
