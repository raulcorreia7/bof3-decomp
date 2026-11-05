#include "boss051_16.h"

MATCH void func_800C1BF0(void) {
    PartyBattler* battler;
    s32           value;
    u8            value2;
    u8            value3;

    battler = g_Task;
    g_Task  = D_801EB4E0;
    func_8014DAEC();
    g_Task = battler;
    value2 = battler->word_08.byte.unk_09;
    value  = value2 & 0xFF;
    if (value != 0xFF) {
        if (value == 0) {
            SND_PlayCue(0x601U);
            g_Task->word_08.byte.unk_09 = 0xFF;
        } else {
            battler->word_08.byte.unk_09 = value2 - 1;
        }
    }
    value3 = g_Task->word_08.byte.timer_0A;
    if (value3 == 0) {
        D_801EB4E0->mode = 5;
        D_801EB4E0->step = 0;
        func_800A9820(g_BattleTargetSelector);
        g_Task->mode += 1;
        return;
    }
    g_Task->word_08.byte.timer_0A = value3 - 1;
}
