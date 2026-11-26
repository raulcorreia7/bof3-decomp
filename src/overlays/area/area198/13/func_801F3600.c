#include "area198_13.h"

MATCH void func_801F3600(void) {
    /* FAKE: the best unpinned form differs in two instructions; retail reserves eight more frame bytes. */
    FAKE_STACK_PADS(u8, 8);

    if ((g_FrameCount & 7) == 0) {
        if (g_ScriptVars[0] >= 3) {
            /* FAKE: the best unpinned form differs in two instructions; retail loads the task byte into v1. */
            FAKE_REG(u8, task_step, "v1")    = SELF(Actor)->param.unk_0B;
            /* FAKE: the best unpinned form differs in two instructions; retail masks the byte into v0. */
            FAKE_REG(s32, masked_step, "v0") = task_step & 7;
            if (masked_step == 0) {
                /* FAKE: the best unpinned form differs in two instructions; retail passes zero in a0. */
                FAKE_REG(s32, sound_arg, "a0") = 0;
                SND_SEPlay(sound_arg);
            }
            func_801F36B4();
            if (g_ScriptVars[0] >= 4) {
                func_801F36B4();
            }
        }
    }
    g_ScriptState->cursor -= 2;
}
