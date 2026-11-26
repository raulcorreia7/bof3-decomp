#include "boss033_16.h"

MATCH void func_800C1F38(void) {
    if (Script_AnimStepOnce() != 0) {
        Script_Select(3);
        SELF(Actor)->header.step++;
    }
}
