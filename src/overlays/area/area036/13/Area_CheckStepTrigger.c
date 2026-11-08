#include "area036_13.h"

#include "overlays/area/Area_CheckStepTrigger.h"

/* func_801F2C64 */
MATCH s32 Area_CheckStepTrigger(s32 x, s32 y) {
    return Area_StepIntoTrigger(x, y, 0x23);
}
