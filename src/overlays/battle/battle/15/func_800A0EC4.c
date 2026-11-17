#include "battle_15.h"

/* Advances the battle party: bumps the active battler's timer, copies
 * the character cells into the battle rows and drains the enemy rows.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800A0EC4(void) {
    Character* character;
    Character* row;
    s32        cell_offset;
    s32        record_index;
    s32        row_offset;
    s32        timer;
    s32        index;
    s32        member;
    u16        value;
    u32        rate;
    u8*        state;
    u8*        dest;

    state = &g_Battle.active_battler;
    if (*state < 3U) {
        record_index = g_Game.members[*state].character_index;
        timer        = g_Characters[record_index].fatigue;
        if (timer < 5U) {
            g_Characters[record_index].fatigue = timer + 1;
            row_offset                         = *state * BATTLE_PARTY_STRIDE;
            D_80145F1E[row_offset]             = D_80145F1E[row_offset] + 1;
        }
        Char_RebuildStats(&g_Characters[g_Game.members[*state].character_index]);
        index = 0;
        if (g_Battle.party_count != 0) {
            do {
                row_offset                = index * BATTLE_PARTY_STRIDE;
                character                 = &g_Characters[g_Game.members[index].character_index];
                row                       = &g_Game.members[index].chr;
                row->equip.weapon         = character->equip.weapon;
                row->equip.shield         = character->equip.shield;
                row->equip.helmet         = character->equip.helmet;
                row->equip.armor          = character->equip.armor;
                row->equip.accessories[0] = character->equip.accessories[0];
                row->equip.accessories[1] = character->equip.accessories[1];
                index++;
                __builtin_memcpy(&row->base, &character->stats, sizeof(Stats));
            } while ((u32)(index & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        index = 0;
        Battle_ApplyFormationStats();
        if (g_Battle.party_count != 0) {
            do {
                row_offset = index * BATTLE_PARTY_STRIDE;
                dest       = (u8*)D_80145F20 + row_offset;
                __builtin_memcpy(dest, dest + 0x20, sizeof(Cpy16u));
                __builtin_memcpy(dest + 0x10, dest + 0x30, sizeof(Cpy16u));
                index++;
            } while ((u32)(index & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        index = 0;
        func_800A4458();
        if (g_Battle.party_count != 0) {
            do {
                Battle_RescaleStats(index & BYTE_MASK);
                index++;
            } while ((u32)(index & BYTE_MASK) < (u8)g_Battle.party_count);
        }
    } else {
        member = *state - 3;
        value  = g_BattleEnemyBattlers[member].stats.max_hp;
        if (value != 0xFFFF) {
            rate = ((u16*)&D_800E4068)[g_BattleEnemyBattlers[member].type * 68] / 10;
            if ((u32)(rate & HALF_MASK) < value) {
                g_BattleEnemyBattlers[member].stats.max_hp = value - rate;
                g_BattleEnemyBattlers[member].base.max_hp -= ((u16*)&D_800E4068)[g_BattleEnemyBattlers[member].type * 68] / 10;
                value = g_BattleEnemyBattlers[member].stats.max_hp;
                if (value < g_BattleEnemyBattlers[member].hp) {
                    g_BattleEnemyBattlers[member].hp = value;
                }
            }
        }
    }
    if (!(Battle_PickAbility(*(u8*)&g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if ((u8)g_Battle.target < 3U) {
            value = g_Game.members[g_Battle.target].chr.hp;
        } else {
            value = ENEMY_COMBATANT(g_Battle.target).hp;
        }
        g_Battle.target_record->hp_change = (s16)(value - 1);
    }
}
#else
INCLUDE_ASM(func_800A0EC4);
#endif
