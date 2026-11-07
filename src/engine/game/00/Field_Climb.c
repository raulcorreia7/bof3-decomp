#include "game_00.h"

/* func_801B3260 */
MATCH void Field_Climb(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = g_FieldClimbSteps[work[2]];
    handler();
}
