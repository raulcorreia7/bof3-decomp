#include "area059_13.h"

#include "overlays/area/Area_CheckStepTrigger.h"

/* func_801F2E80 */
MATCH s32 Area_CheckStepTrigger(s32 x, s32 y) {
    return Area_StepIntoTrigger(x, y, 0x29);
}
