#include "game_00.h"

/* func_801B3540 */
MATCH void Area_ClimbDismount(void) {
    Callback handler = g_AreaClimbDismountSteps[g_Task->unk_03];
    handler();
}
