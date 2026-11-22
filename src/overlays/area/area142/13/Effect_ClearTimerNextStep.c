#include "area142_13.h"

/* Clears the effect timer and advances to the next step. */
/* func_801F2C60 */
MATCH void Effect_ClearTimerNextStep(void) {
    TASK(Actor)->timer = 0;
    TASK(Actor)->header.step += 1;
}
