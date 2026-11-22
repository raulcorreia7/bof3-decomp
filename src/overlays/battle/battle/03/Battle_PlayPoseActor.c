#include "battle_03.h"

/* func_801E68EC */
MATCH void Battle_PlayPoseActor(void) {
    if (Script_AnimStepLoop() & BYTE_MASK) {
        Effect_Reset();
        return;
    }
    Area_AddActor();
}
