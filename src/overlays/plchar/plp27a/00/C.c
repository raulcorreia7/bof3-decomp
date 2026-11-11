#include "plp27a_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF900[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CF90C, 2, g_Task);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

#include "overlays/plchar/Plchar_FollowerInReach.h"

MATCH s32 func_801CEAE0(u8 index) {
    PLCHAR_PROBE_FACING_FOLLOWER(index);
}

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CF914, 2, g_Task);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE30(void) {
    SYS_DISPATCH_TASK(D_801CF920, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF1C0);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF858(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CF868(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CF878(void) {
    D_801CF92C[g_Task->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF938[g_Task->unk_2C]();
}
