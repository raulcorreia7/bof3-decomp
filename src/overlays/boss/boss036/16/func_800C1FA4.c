#include "boss036_16.h"

MATCH void func_800C1FA4(void) {
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        SPAD_WORK_BYTES[2]++;
    }
}
