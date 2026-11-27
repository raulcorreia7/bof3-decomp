#include "plp567_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801D07A4, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurnPeco.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"
