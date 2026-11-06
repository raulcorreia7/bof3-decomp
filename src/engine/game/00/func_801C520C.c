#include "game_00.h"

MATCH s32 func_801C520C(void) {
    s32* route;
    s32  index;
    s32  step;
    s32  sumX;
    s32  sumY;
    s32  targetX;
    s32  targetY;
    s32  done;
    u8   transitionId;

    route   = (s32*)SP_REF(s32, 0x44);
    index   = FIELD(u8, route, 0x8u) * 2;
    step    = FIELD(u8, route, 0x70u) + 2;
    done    = 0;
    sumX    = FIELD(s32, route, 0x34u) + (g_FacingSteps[FIELD(u8, route, 0x8u)].x * step);
    targetX = sumX;
    sumY    = FIELD(s32, route, 0x38u) + (g_FacingStepY[index] * step);
    targetY = sumY;
    if (FIELD(s16, route, 0x3Eu) < Area_ReadHeight(sumX, sumY)) {
        COORD_INT(g_Task->pos.z) = (s16)((u16)COORD_INT(g_Task->pos.z) + D_80181B88[g_GameState->slot_index_79]);
    } else {
        COORD_INT(g_Task->pos.z) = Area_ReadHeight(targetX, targetY);
        transitionId             = 0x3F;
        if (g_Task->direction_08 == FACING_W) {
            transitionId = 0x3E;
        }
        done = 1;
        Actor_RequestScript(transitionId);
    }
    if ((g_Task->unk_05 == 0) &&
        !((g_GameFlags | g_AreaWalkFlags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
    }
    if (!(g_FrameCount & 3)) {
        func_8014DAEC();
    }
    return done;
}
