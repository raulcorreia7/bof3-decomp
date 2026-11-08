#include "battle_15.h"

MATCH void func_8009DF70(void) {
    g_Battle.target_record->hp_change = -5;
    if (RANDOM_MASK(0x7F) < 0x27) {
        func_800A36F0(g_Battle.target, 0x68);
    }
}
