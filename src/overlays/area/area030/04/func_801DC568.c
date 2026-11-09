#include "area030_04.h"

/* Gates the shared state mask 0x50 then refreshes display state. */

MATCH void func_801DC568(void) {
    func_801DDF7C(0x50);
    Actor_StepAnimLoop();
}
