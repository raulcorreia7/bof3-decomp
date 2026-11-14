#include "battle_15.h"

MATCH void func_800A0378(void) {
    u32 mode;
    u16 base;
    u8  flag;

    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        mode = *MEM_PTR(u8, &g_Battle.target);
        if (mode < 3u) {
            base = g_Game.members[mode].chr.hp;
        } else {
            base = ENEMY_COMBATANT(mode).hp;
        }
        g_Battle.target_record->hp_change = base;
    } else {
        flag                                 = 1;
        g_Battle.target_record->target_flags = flag;
    }
}
