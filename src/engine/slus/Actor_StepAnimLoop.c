#include "engine/slus/slus.h"

/* Loops the sprite animation: counts the step delay (+0x4A) down and, at zero, wraps to step 0 at the end of the
 * stream (step count at +0x49) or follows a jump step (delay >= 0x80), returning 1 on a wrap or jump, then stages the step.
 */
/* func_8014D978 */
MATCH u8 Actor_StepAnimLoop(void) {
    Actor* first_work;
    Actor* work;
    u8*    entry;
    u16    index;
    u8     result;

    first_work = g_Task;
    result     = 0;
    if (--first_work->unk_4A == 0) {
        work  = g_Task;
        index = work->script_pc;
        if ((index >> 1) == work->unk_49) {
            work->script_pc = 0;
            result          = 1;
        } else {
            entry = work->script + index;
            if (entry[0] >= 0x80U) {
                work->script_pc = (entry[1] * 2);
                result          = 1;
            }
        }
        Actor_StageAnimStep();
    }
    return result;
}
