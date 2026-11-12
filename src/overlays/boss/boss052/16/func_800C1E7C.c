#include "boss052_16.h"

MATCH void func_800C1E7C(void) {
    Actor* work;
    u8     delay;

    work  = (Actor*)g_Task;
    delay = work->timer;
    if (delay != 0xFF) {
        if (delay == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_ENEMY, 3));
            ((Actor*)g_Task)->timer = 255;
        } else {
            work->timer = delay - 1;
        }
    }
    Actor_StepAnimLoop();
    Area_AddActor();
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        ((Actor*)g_Task)->header.step++;
    }
}
