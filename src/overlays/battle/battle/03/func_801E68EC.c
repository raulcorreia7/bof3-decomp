#include "battle_03.h"

MATCH void func_801E68EC(void) {
    if (Actor_StepAnimLoop() & BYTE_MASK) {
        Effect_Reset();
        return;
    }
    Area_AddActor();
}
