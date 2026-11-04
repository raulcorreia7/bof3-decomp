#include "boss022_13.h"

MATCH void Boss_EndEntrance(void) {
    if (func_8014DAEC() != 0) {
        ACTOR_SET_STEP(2);
    }
}
