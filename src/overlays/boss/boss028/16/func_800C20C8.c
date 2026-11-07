#include "boss028_16.h"

MATCH void func_800C20C8(void) {
    if (!ACTOR_IN_USE(*g_BattleEffectBattler)) {
        TASK_BYTES[2]++;
    }
    func_8014D978();
}
