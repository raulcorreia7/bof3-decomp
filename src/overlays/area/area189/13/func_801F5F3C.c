#include "area189_13.h"

/* Turns the task by the held pad direction and stores the turn step the script
 * reads: up only arms step 1 and returns 2, right and left arm steps 2 and 3,
 * step the facing and set the turn parameter. */
MATCH s32 func_801F5F3C(void) {
    if (g_PadStates[0].held & PADLup) {
        g_Task->script_record = 1;
        return 2;
    }
    if (g_PadStates[0].held & PADLright) {
        g_Task->script_record = 2;
        g_Task->direction     = g_Task->direction + 1;
        g_Task->param.unk_0B  = 0xF0;
    } else if (g_PadStates[0].held & PADLleft) {
        g_Task->script_record = 3;
        g_Task->direction     = g_Task->direction - 1;
        g_Task->param.unk_0B  = 0x10;
    } else {
        return 0;
    }
    g_Task->direction &= 0xF;
    return 1;
}
