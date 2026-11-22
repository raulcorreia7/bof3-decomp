#include "boss052_16.h"

MATCH void func_800C1E7C(void) {
    Actor* work;
    u8     delay;

    work  = TASK(Actor);
    delay = work->timer;
    if (delay != 0xFF) {
        if (delay == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 3));
            TASK(Actor)->timer = 255;
        } else {
            work->timer = delay - 1;
        }
    }
    Script_AnimStepLoop();
    Area_AddActor();
    if (g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) {
        TASK(Actor)->header.step++;
    }
}
