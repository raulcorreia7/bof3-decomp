#include "plp349_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH s32 func_801CEC18(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CEE24 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CEF10(void) {
    SYS_DISPATCH_TASK(D_801CF614, 3, g_Task);
}

MATCH void func_801CEF54(void) {
    /* FAKE: retail reads SND_PlaySE as void(s32). */
    ((void (*)(s32))SND_PlaySE)(g_Task->unk_2C + 0x100);
    Actor_RequestScript(((g_Task->direction - 1) / 2) + 0x42);
    g_Task->unk_0A = 8;
    g_Task->unk_03 = 1;
}

#include "overlays/plchar/shared/PlChar_UpdateLinkedFacing.h"

#include "overlays/plchar/shared/PlChar_ClearPanelModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF184);

MATCH void func_801CF328(void) {
    SYS_DISPATCH_TASK(D_801CF620, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CF534(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF544(void) {
    g_Game.current->u.field.mode.value = 0;
}
