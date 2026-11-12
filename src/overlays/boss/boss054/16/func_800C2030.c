#include "boss054_16.h"

MATCH void func_800C2030(void) {
    Battle_MarkDamaged(g_Battle.target_selector);
    g_BattleEffectBattler->timer--;
    func_801E5988();
}
