#include "game_00.h"

MATCH void func_801B79F8(void) {
    COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) - 0x200;
    g_Task->pos.x.fixed -= g_FacingOffsets[g_Task->direction].x * ((g_Task->voice_flags.scene_flag + 1) << 5);
    g_Task->pos.y.fixed -= g_FacingOffsets[g_Task->direction].y * ((g_Task->voice_flags.scene_flag + 1) << 5);
    if (g_Task->direction == FACING_LEFT) {
        Actor_RequestScript(0x3C);
    } else {
        Actor_RequestScript(0x3D);
    }
    if (g_Task->unk_05 != 0) {
        func_801C2438();
        g_Task->tint.steps.delta.r = -0x80;
        g_Task->tint.steps.delta.g = -0x80;
        g_Task->tint.steps.delta.b = -0x80;
        g_Task->tint.bytes.flags   = 1;
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->unk_04 = 3;
    } else {
        g_Task->unk_04 = 4;
    }
}
