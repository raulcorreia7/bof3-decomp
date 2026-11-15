#include "battle_03.h"

MATCH void func_801E3B04(void) {
    if (Battle_IsEnemyBlocked() != 0u) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_TriggerCritical();
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E567C();
    }
}
