#include "engine/slus/slus.h"

/* Plays the sprite animation once. */
/* func_8014DAEC */
MATCH u8 Actor_StepAnimOnce(void) {
    u8  result;
    u8  count;
    u16 index;

    result         = 0;
    count          = g_Task->unk_4A - 1;
    g_Task->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        index = g_Task->script_pc;
        if ((index >> 1) == g_Task->unk_49) {
            g_Task->unk_4A = 1;
            return 1;
        }
        if (*(u8*)(g_Task->script + index) >= 0x80) {
            g_Task->script_pc = *(u8*)(g_Task->script + index + 1) << 1;
            result            = 1;
        }
        Actor_StageAnimStep();
    }
    return result;
}
