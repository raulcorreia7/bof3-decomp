#include "boss036_16.h"

MATCH void func_800C1F44(void) {
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->timer        = 0;
    Script_Select(1);
    Script_AnimStepLoop();
    Area_AddActor();
    SELF(Actor)->header.step++;
}
