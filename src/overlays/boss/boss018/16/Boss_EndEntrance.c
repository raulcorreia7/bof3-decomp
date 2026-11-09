#include "boss018_16.h"

/* func_800C1940 */
MATCH void Boss_EndEntrance(void) {
    if (Actor_StepAnimOnce() != 0) {
        ACTOR_SET_MODE(2);
    }
}
