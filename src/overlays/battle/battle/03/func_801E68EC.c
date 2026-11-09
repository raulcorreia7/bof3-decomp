#include "battle_03.h"

MATCH void func_801E68EC(void) {
    if (Actor_StepAnimLoop() & BYTE_MASK) {
        func_801E5988();
        return;
    }
    Area_AddActor();
}
