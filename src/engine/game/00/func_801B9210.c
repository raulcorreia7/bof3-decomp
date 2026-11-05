#include "game_00.h"

MATCH void func_801B9210(void) {
    u8  saved;
    u8  mode;
    s32 v;

    if (g_Task->tint.bytes.flags != 0) {
        GFX_StagePalette((GAME_PALETTE_STAGE + (g_Task->unk_05 << 6)), 0);
        g_Task->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->tint.bytes.flags = 0;
        ACTOR_CLEAR_TINT();
    }
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    if ((g_Task->x.fixed & 0x7FFF) != 0 || (g_Task->y.fixed & 0x7FFF) != 0) {
        g_Task->x.fixed      = (g_Task->x.fixed + 0x4800) & ~0x7FFF;
        g_Task->y.fixed      = (g_Task->y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(g_Task->z) = Area_ReadStepHeight(g_Task->x.fixed, g_Task->y.fixed, g_Task->direction_08);
        if (g_Task->unk_05 == 0) {
            v                   = g_Task->x.fixed;
            g_AreaScrollTargetX = v;
            v                   = g_Task->y.fixed;
            g_AreaScrollTargetY = v;
            func_80153DE8();
        }
    }
    saved                = g_Task->direction_08;
    g_Task->direction_08 = saved ^ 4;
    mode                 = func_801B9598();
    if (mode == 1 || mode == 3) {
        if ((func_801BDF08() << 24) != 0) {
            g_Task->unk_09 = 0;
            Actor_ClearVelocity();
        } else {
            func_801C24D0();
            g_Task->unk_09--;
            func_801C57B4();
        }
    } else {
        Actor_ClearVelocity();
    }
    func_801C2E34(g_Task->unk_0B);
    g_Task->direction_08 = saved;
    g_Task->unk_0A       = 8;
    Actor_RequestScript(g_Task->direction_08);
    SND_PlayCue(EMI_CUE_ID(1, 8));
    g_Task->unk_03++;
}
