#include "boss018_16.h"

/* func_800C1ADC */
MATCH void Boss_EndEntrance2(void) {
    if (Actor_StepAnimOnce() != 0) {
        ACTOR_SET_MODE(2);
    }
}
