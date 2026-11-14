#include "battle_15.h"

MATCH void func_800A1978(void) {
    u32 mode;
    u16 base;

    if RANDOM_MASK (1) {
        if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
            mode = *MEM_PTR(u8, &g_Battle.target);
            if (mode < 3u) {
                base = g_Game.members[mode].chr.hp;
            } else {
                base = ENEMY_COMBATANT(mode).hp;
            }
            g_Battle.target_record->hp_change = base - 1;
        }
    }
}
