#include "plp567_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D078C[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptMomo.h"
