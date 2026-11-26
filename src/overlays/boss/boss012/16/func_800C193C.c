#include "boss012_16.h"

MATCH void func_800C193C(void) {
    if (Script_AnimStepLoop() != 0) {
        SELF(Actor)->unk_03 = 1;
    }
}
