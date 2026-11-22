#include "boss022_13.h"

MATCH void Boss_EndEntrance(void) {
    if (Script_AnimStepOnce() != 0) {
        ACTOR_SET_MODE(2);
    }
}
