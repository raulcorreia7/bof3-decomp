#include "game_00.h"

MATCH void func_8019C664(void) {
    Actor* work;
    void*  flags;
    Actor* state;

    g_Task->direction_08 = (u8)g_Game.members[0].facing;
    func_8019EE10();
    g_Task->unk_27 = 0x7B;
    Actor_SelectScript(((u8)g_Task->direction_08 >> 1) + 0x4A);
    GFX_LoadPalette(GAME_PALETTE_STAGE + 0xC0, 1);
    work                    = g_Task;
    work->pos.x.fixed       = g_Game.members[0].pos.x.fixed;
    work->pos.y.fixed       = g_Game.members[0].pos.y.fixed;
    COORD_INT(work->pos.z)  = (s16)((u16)COORD_INT(g_Game.members[0].pos.z) + 0xC0);
    work->vx                = (s32)(g_FacingOffsets[work->direction_08].x * 0x10);
    FIELD(s32, work, 0x10u) = (s32)(g_FacingOffsets[work->direction_08].y * 0x10);
    if (g_Game.members[0].chr.character_id == CHAR_ID_NINA_YOUNG) {
        work->unk_0A = 0xA;
    } else {
        work->unk_0A = 0x12;
    }
    flags              = g_Task;
    *(u8*)(flags)      = (u8)(*(u8*)(flags) | ACTOR_FLAG_SKIP_PALETTE_STAGE);
    state              = g_Task;
    state->header.mode = (u8)(state->header.mode + 1);
}
