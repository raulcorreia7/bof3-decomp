#include "game_00.h"

MATCH void func_801C2710(void) {
    u8* work;
    u8* state;
    s32 product;
    u8  index;

    work = (u8*)SCRATCH_WORK;
    if ((work[0x08] == 2) || (work[0x08] == 6)) {
        g_AreaCameraStep = 4;
    } else {
        g_AreaCameraStep = 8;
    }
    index               = g_GameState->u.field.counter_11C.u8_value;
    product             = g_AreaCameraStep * g_RouteSpeedScale[index];
    state               = (u8*)SCRATCH_WORK;
    g_AreaCameraStep    = product;
    g_AreaScrollTargetX = ((s32*)state)[13] + ((s32*)state)[3] * state[0x09];
    g_AreaScrollTargetY = ((s32*)state)[14] + ((s32*)state)[4] * state[0x09];
    /* FAKE: barrier pins load after store. */
    MATCH_BARRIER();
    g_AreaCameraHeightStep = ((s32*)state)[5];
}
