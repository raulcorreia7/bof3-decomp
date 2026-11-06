#include "boss018_16.h"

/* func_800C1940 */
MATCH void Boss_EndEntrance(void) {
    if (func_8014DAEC() != 0) {
        ACTOR_SET_STEP(2);
    }
}
