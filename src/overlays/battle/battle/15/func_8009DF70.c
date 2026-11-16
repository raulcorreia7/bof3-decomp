#include "battle_15.h"

MATCH void func_8009DF70(void) {
    g_Battle.target_record->hp_change = -5;
    if (RANDOM_MASK(0x7F) < 0x27) {
        Battle_CureStatus(g_Battle.target, 0x68);
    }
}
