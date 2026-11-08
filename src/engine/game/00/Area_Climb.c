#include "game_00.h"

/* func_801B3260 */
MATCH void Area_Climb(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = g_AreaClimbSteps[work[2]];
    handler();
}
