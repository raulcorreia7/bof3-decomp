#include "game_00.h"

/* D_80195ED4 */
FieldActionSteps g_FieldActionSteps = {
    FieldAction_RollStep, FieldAction_FindSmall, FieldAction_FindLarge, FieldAction_End, FieldAction_WaitMessage,
};

static u8 s_gap_80195EE8[4] = {0};
