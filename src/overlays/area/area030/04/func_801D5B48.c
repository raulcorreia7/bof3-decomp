#include "area030_04.h"
/* Sequences two argument-free subsystem helpers: calls
 * Script_AnimStepLoop() then func_8014D4E0(), then returns. A void, argument-free
 * thunk. */

/* Declared file-locally: this module's shared header omits the callee; its
 * real signature (sibling modules' area030_04.h) is u8 Script_AnimStepLoop(void). */

MATCH void func_801D5B48(void) {
    Script_AnimStepLoop();
    Area_AddActor();
}
