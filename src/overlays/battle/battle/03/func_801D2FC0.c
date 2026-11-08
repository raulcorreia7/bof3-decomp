#include "battle_03.h"

MATCH void func_801D2FC0(void) {
    if (BATTLE_IS_SCRIPTED()) {
        g_Battle.boss_event_hook(BOSS_EVENT_ACTION_START);
    }
    g_Battle.phase.step     = 1;
    g_Battle.phase.sub_step = g_Battle.action_type;
}
