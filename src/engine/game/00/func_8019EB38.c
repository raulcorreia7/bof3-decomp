#include "game_00.h"

MATCH void func_8019EB38(void) {
    Actor* work;
    Actor* flags;
    Actor* state;
    s32    step;

    g_Task->direction_08    = (u8)g_BattlePartyBattlers[0].facing;
    work                    = g_Task;
    FIELD(s32, work, 0x34u) = D_80145EC4 + g_FacingSteps[work->direction_08].x;
    work->pos.y.fixed       = D_80145EC8 + D_80181B98[work->direction_08 * 2];
    COORD_INT(work->pos.z)  = (s16)((u16)D_80145ECE + 0xC0);
    work->vx                = g_FacingOffsets[work->direction_08].x * 0x10;
    step                    = g_FacingOffsets[work->direction_08].y * 0x10;
    work->unk_0A            = 0xE;
    flags                   = g_Task;
    work->vy                = step;
    flags->unk_0B           = 0;
    state                   = g_Task;
    state->header.mode      = (u8)(state->header.mode + 1);
}
