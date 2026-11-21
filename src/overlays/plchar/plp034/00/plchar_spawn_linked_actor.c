#include "plp034_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH s32 func_801CF940(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CFB4C */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CFC38(void) {
    SYS_DISPATCH_TASK(D_801D0334, 3, g_Task);
}

MATCH void func_801CFC7C(void) {
    /* FAKE: retail reads SND_PlaySE as void(s32). */
    ((void (*)(s32))SND_PlaySE)(g_Task->unk_2C + 0x100);
    Actor_RequestScript((((s32)(g_Task->direction - 1) / 2) + 0x42) & 0xFF);
    g_Task->unk_0A = 8;
    g_Task->unk_03 = 1;
}

#include "overlays/plchar/shared/PlChar_UpdateLinkedFacing.h"

#include "overlays/plchar/shared/PlChar_ClearPanelModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CFEAC);

MATCH void func_801D0050(void) {
    SYS_DISPATCH_TASK(D_801D0340, 2, g_Task);
}

MATCH void PlChar_StartTurnRei(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/shared/PlChar_RunStepScript.h"
