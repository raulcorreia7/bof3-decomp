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

    work    = TASK(Actor);
    step    = work->voice_flags.scene_flag + 2;
    next_x  = work->pos.x.fixed + g_FacingSteps[work->direction].x * step;
    x       = next_x;
    next_y  = work->pos.y.fixed + g_FacingSteps[work->direction].y * step;
    y       = next_y;
    counter = COORD_INT(work->pos.z);
    moved   = 0;

    result = Area_HeightRead(x, y);
    slot   = g_Game.current->chr.character_id;
    if (result - D_80181B70[slot] < counter) {
        COORD_INT(TASK(Actor)->pos.z) -= D_80181B88[slot];
    } else {
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(x, y) - D_80181B70[g_Game.current->chr.character_id];
        if (TASK(Actor)->direction == FACING_LEFT) {
            Script_Request(0x3C);
        } else {
            Script_Request(0x3D);
        }
        moved = 1;
    }

    if (TASK(Actor)->unk_05 == 0 && !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_ScrollAdvance((s16)COORD_INT(TASK(Actor)->pos.z));
    }
    if (!(g_FrameCount & 0x3)) {
        Script_AnimStepOnce();
    }
    return moved;
}
