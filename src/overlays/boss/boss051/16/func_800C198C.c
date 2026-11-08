#include "boss051_16.h"

MATCH void func_800C198C(void) {
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        Battle_TriggerCritical();
        func_801E567C();
    }
}
