#include "game_00.h"

MATCH void func_8019C910(void) {
    if (Script_AnimStepOnce() != 0u) {
        Actor_Clear();
        return;
    }
    Area_AddGridActor();
}
