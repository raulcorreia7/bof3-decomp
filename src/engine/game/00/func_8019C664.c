#include "game_00.h"

MATCH void func_8019C664(void) {
    Actor* work;
    void*  flags;
    Actor* state;

    g_Task->direction_08 = (u8)D_80145E98;
    func_8019EE10();
    g_Task->unk_27 = 0x7B;
    Actor_SelectScript(((u8)g_Task->direction_08 >> 1) + 0x4A);
    GFX_StagePalette(GAME_PALETTE_STAGE + 0xC0, 1);
    work                    = g_Task;
    FIELD(s32, work, 0x34u) = (s32)D_80145EC4;
    work->y.fixed           = (s32)D_80145EC8;
    COORD_INT(work->z)    = (s16)((u16)D_80145ECE + 0xC0);
    work->vx                = (s32)(g_FacingOffsets[work->direction_08].x * 0x10);
    FIELD(s32, work, 0x10u) = (s32)(g_FacingOffsets[work->direction_08].y * 0x10);
    if (D_80145F09 == 1) {
        work->unk_0A = 0xA;
    } else {
        work->unk_0A = 0x12;
    }
    flags         = g_Task;
    *(u8*)(flags) = (u8)(*(u8*)(flags) | ACTOR_FLAG_SKIP_PALETTE_STAGE);
    state         = g_Task;
    state->mode   = (u8)(state->mode + 1);
}
