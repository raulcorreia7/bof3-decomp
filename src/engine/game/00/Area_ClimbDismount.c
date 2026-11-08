#include "game_00.h"

/* func_801B3540 */
MATCH void Area_ClimbDismount(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = g_AreaClimbDismountSteps[work[3]];
    handler();
}
