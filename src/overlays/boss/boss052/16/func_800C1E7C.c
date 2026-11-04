#include "boss052_16.h"

MATCH void func_800C1E7C(void) {
    Actor* work;
    u8     delay;

    work  = (Actor*)g_SpadWork;
    delay = work->unk_09;
    if (delay != 0xFF) {
        if (delay == 0) {
            SND_PlayCue(0x603);
            ((Actor*)g_SpadWork)->unk_09 = 0xFF;
        } else {
            work->unk_09 = delay - 1;
        }
    }
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        ((Actor*)g_SpadWork)->state_02++;
    }
}
