#include "game_00.h"

MATCH void func_8019CBD8(void) {
    Actor* other;
    Actor* record;
    Actor* work;
    Actor* counter;

    g_Task->direction = FACING_UP;
    SYS_InitScratchpad((u8*)(FIELD(s32, g_AreaLoads[g_GameAreaId], 0x8u) + (g_Task->param.unk_0B * 8)));
    record                     = g_Task;
    record->tint.steps.delta.r = -0x80;
    other                      = g_Task;
    record->voice_flags.raw    = 1;
    other->tint.steps.delta.g  = -0x80;
    g_Task->tint.steps.delta.b = -0x80;
    work                       = g_Task;
    work->vx                   = 0;
    work->vy                   = 0;
    work->vz                   = 0;
    work->timer                = 0;
    func_8019D270();
    g_Task->param.unk_0B = 0U;
    counter              = g_Task;
    counter->header.mode = (counter->header.mode + 1);
    Actor_ProjectForDraw();
}
