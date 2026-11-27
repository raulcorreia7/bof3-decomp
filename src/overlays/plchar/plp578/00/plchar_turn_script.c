#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFAB8[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurnMomo.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptMomo.h"
