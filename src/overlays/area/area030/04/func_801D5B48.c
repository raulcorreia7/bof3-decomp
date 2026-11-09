#include "area030_04.h"
/* Sequences two argument-free subsystem helpers: calls Actor_StepAnimLoop() then func_8014D4E0(), then returns. */

/* Declared file-locally: this module's shared header omits the callee. */

MATCH void func_801D5B48(void) {
    Actor_StepAnimLoop();
    Area_AddActor();
}
