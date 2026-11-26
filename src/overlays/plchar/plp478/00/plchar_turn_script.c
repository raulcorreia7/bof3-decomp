#include "plp478_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF6D8[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF6E4, 2, g_Self);
}
