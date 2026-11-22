#include "area189_13.h"

/* Turns the task by the held pad direction and stores the turn step the script
 * reads: up only arms step 1 and returns 2, right and left arm steps 2 and 3,
 * step the facing and set the turn parameter. */
MATCH s32 func_801F5F3C(void) {
    if (g_PadStates[0].held & PADLup) {
        TASK(Actor)->script_record = 1;
        return 2;
    }
    if (g_PadStates[0].held & PADLright) {
        TASK(Actor)->script_record = 2;
        TASK(Actor)->direction     = TASK(Actor)->direction + 1;
        TASK(Actor)->param.unk_0B  = 0xF0;
    } else if (g_PadStates[0].held & PADLleft) {
        TASK(Actor)->script_record = 3;
        TASK(Actor)->direction     = TASK(Actor)->direction - 1;
        TASK(Actor)->param.unk_0B  = 0x10;
    } else {
        return 0;
    }
    TASK(Actor)->direction &= 0xF;
    return 1;
}
