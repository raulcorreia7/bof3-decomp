#include "boss022_13.h"

MATCH void Boss_EndEntrance(void) {
    if (Actor_StepAnimOnce() != 0) {
        ACTOR_SET_MODE(2);
    }
}
