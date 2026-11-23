#include "battle_15.h"

/* Advances the battle party: bumps the active battler's timer, copies
 * the character cells into the battle rows and drains the enemy rows.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800A0EC4(void) {
    u8* record;
    u8* cell;
    u8  character_index;
    u32 i;
    u32 party_slot;
    s32 record_index;
    s32 member_offset;
    s32 timer;
    s32 member;
    u16 value;
    u32 rate;
    u8* state;

    state = &g_Battle.active_battler;
    if (*state < 3U) {
        record_index = g_Game.members[*state].character_index;
        timer        = g_Characters[record_index].fatigue;
        if (timer < 5U) {
            g_Characters[record_index].fatigue = timer + 1;
            member_offset                      = *state * BATTLE_PARTY_STRIDE;
            D_80145F1E[member_offset]++;
        }
        Char_RebuildStats(&g_Characters[g_Game.members[*state].character_index]);
        i = 0;
        if (g_Battle.party_count != 0) {
            do {
                party_slot    = (u8)i;
                member_offset = party_slot << 2;
                member_offset += party_slot;
                member_offset <<= 6;
                record                                     = (u8*)g_Game.members[0].chr.name + member_offset;
                character_index                            = g_Game.members[0].chr.name[member_offset + 0xC8];
                cell                                       = (u8*)&g_Characters[character_index];
                ((Character*)record)->equip.weapon         = ((Character*)cell)->equip.weapon;
                ((Character*)record)->equip.shield         = ((Character*)cell)->equip.shield;
                ((Character*)record)->equip.helmet         = ((Character*)cell)->equip.helmet;
                ((Character*)record)->equip.armor          = ((Character*)cell)->equip.armor;
                ((Character*)record)->equip.accessories[0] = ((Character*)cell)->equip.accessories[0];
                ((Character*)record)->equip.accessories[1] = ((Character*)cell)->equip.accessories[1];
                i++;
                memcpy(record + 0x3C, cell + 0x1C, 0x10);
                memcpy(record + 0x4C, cell + 0x2C, 0x10);
            } while ((u8)i < g_Battle.party_count);
        }
        i = 0;
        Battle_ApplyFormationStats();
        {
            u8* count = &g_BattlePartyCount;
            u8* dst_base;
            u8* src_base;

            if (*count != 0) {
                dst_base = D_80145F20;
                src_base = dst_base + 0x20;
                do {
                    u32 member_offset;

                    member_offset = (u8)i * BATTLE_PARTY_STRIDE;
                    memcpy((u8*)(member_offset + (u32)dst_base), (u8*)(member_offset + (u32)src_base), 0x20);
                    i++;
                } while ((u8)i < *count);
            }
        }
        i = 0;
        func_800A4458();
        if (g_BattlePartyCount != 0) {
            do {
                Battle_RescaleStats((u8)i);
                i++;
            } while ((u8)i < g_BattlePartyCount);
        }
    } else {
        value = ENEMY_COMBATANT(*state).stats.max_hp;
        if (value != 0xFFFF) {
            rate = (&D_800E4068)[ENEMY_COMBATANT(*state).type * 68] / 10;
            if ((u16)rate < value) {
                ENEMY_COMBATANT(*state).stats.max_hp = value - rate;
                ENEMY_COMBATANT(*state).base.max_hp -= (&D_800E4068)[ENEMY_COMBATANT(*state).type * 68] / 10;
                if (ENEMY_COMBATANT(*state).stats.max_hp < ENEMY_COMBATANT(*state).hp) {
                    ENEMY_COMBATANT(*state).hp = ENEMY_COMBATANT(*state).stats.max_hp;
                }
            }
        }
    }
    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
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
