#include "area082_13.h"

MATCH void func_801F3470(void) {
    if (Area_StepSparks() == 0) {
        TASK(Actor)->unk_32 = 0x10;
        TASK(Actor)->header.mode++;
    }
}
