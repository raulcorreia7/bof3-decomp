#include "battle_15.h"

MATCH void func_8009FE10(void) {
    func_800A31E0(g_Battle.target, 0x40);
    g_Battle.target_record->target_flags |= BATTLE_HIT_AP;
    g_Battle.target_record->hp_change = -0x14;
    g_Battle.target_record->ap_change = -4;
}
