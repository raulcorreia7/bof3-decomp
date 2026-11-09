#include "area030_04.h"
/* Sequences two argument-free subsystem helpers: calls
 * Actor_StepAnimLoop() then func_8014D4E0(), then returns. A void, argument-free
 * thunk. */

/* Declared file-locally: this module's shared header omits the callee; its
 * real signature (sibling modules' area030_04.h) is u8 Actor_StepAnimLoop(void). */

MATCH void func_801D5B48(void) {
    Actor_StepAnimLoop();
    Area_AddActor();
}
