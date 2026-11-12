#include "game_00.h"

MATCH s32 func_801C4FE0(void) {
    Actor* work;
    s32    step;
    s32    next_x;
    s32    next_y;
    s32    x;
    s32    y;
    s16    result;
    s32    counter;
    u8     slot;
    s32    moved;

    work    = g_Task;
    step    = work->state_70.byte + 2;
    next_x  = work->pos.x.fixed + g_FacingSteps[work->direction_08].x * step;
    x       = next_x;
    next_y  = work->pos.y.fixed + g_FacingSteps[work->direction_08].y * step;
    y       = next_y;
    counter = COORD_INT(work->pos.z);
    moved   = 0;

    result = Area_ReadHeight(x, y);
    slot   = g_Game.current->chr.character_id;
    if (result - D_80181B70[slot] < counter) {
        COORD_INT(g_Task->pos.z) -= D_80181B88[slot];
    } else {
        COORD_INT(g_Task->pos.z) = Area_ReadHeight(x, y) - D_80181B70[g_Game.current->chr.character_id];
        if (g_Task->direction_08 == FACING_LEFT) {
            Actor_RequestScript(0x3C);
        } else {
            Actor_RequestScript(0x3D);
        }
        moved = 1;
    }

    if (g_Task->unk_05 == 0 && !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_AdvanceScroll((s16)COORD_INT(g_Task->pos.z));
    }
    if (!(g_FrameCount & 0x3)) {
        Actor_StepAnimOnce();
    }
    return moved;
}
