#include "boss052_16.h"

MATCH void func_800C1E7C(void) {
    Actor* work;
    u8     delay;

    work  = (Actor*)g_Task;
    delay = work->timer;
    if (delay != 0xFF) {
        if (delay == 0) {
            SND_PlayCue(0x603);
            ((Actor*)g_Task)->timer = 0xFF;
        } else {
            work->timer = delay - 1;
        }
    }
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        ((Actor*)g_Task)->header.step++;
    }
}
