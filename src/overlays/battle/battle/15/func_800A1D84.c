#include "battle_15.h"

/* The active battler index selects one of three party members. */
#define BATTLE_ACTIVE_MEMBER_COUNT 3
/* The timer counts up to this value before it stops. */
#define BATTLE_TIMER_MAX           9

/* Advances the player battler: bumps its timer and mirrored work record, copies the battler work records and effect
 * vectors, and mirrors the active member value into the selection slot.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800A1D84(void) {
    Character* member_chr;
    s32        record_index;
    u8         i;
    u32        battler_slot;
    u8*        active;
    Character* cell;
    u8*        src;
    u8*        dst;
    u8         timer;

    active       = (u8*)&g_Battle.target;
    battler_slot = *active;
    if (battler_slot < BATTLE_ACTIVE_MEMBER_COUNT) {
        record_index = g_Game.members[battler_slot].character_index;
        timer        = g_Characters[record_index].fatigue;
        if (timer < BATTLE_TIMER_MAX) {
            g_Characters[record_index].fatigue = timer + 1;
            g_Game.members[*active].chr.fatigue += 1;
        }
        Char_RebuildStats(&g_Characters[g_Game.members[*active].character_index]);
        i = 0;
        if (g_Battle.party_count != 0) {
            do {
                member_chr                       = &g_Game.members[i].chr;
                cell                             = &g_Characters[g_Game.members[i].character_index];
                member_chr->equip.weapon         = cell->equip.weapon;
                member_chr->equip.shield         = cell->equip.shield;
                member_chr->equip.helmet         = cell->equip.helmet;
                member_chr->equip.armor          = cell->equip.armor;
                member_chr->equip.accessories[0] = cell->equip.accessories[0];
                i += 1;
                member_chr->equip.accessories[1] = cell->equip.accessories[1];
                memcpy((u8*)&member_chr->base, (u8*)&cell->stats, 16);
                memcpy((u8*)&member_chr->base + 16, (u8*)&cell->stats + 16, 16);
            } while ((u32)(i & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        i = 0;
        Battle_ApplyFormationStats();
        if (g_Battle.party_count != 0) {
            do {
                dst                    = (u8*)&g_Game.members[i].chr.stats;
                src                    = (u8*)&g_Game.members[i].chr.base;
                *(Cpy16u*)(dst + 0x00) = *(Cpy16u*)(src + 0x00);
                *(Cpy16u*)(dst + 0x10) = *(Cpy16u*)(src + 0x10);
                i += 1;
            } while ((u32)(i & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        i = 0;
        func_800A4458();
        if (g_Battle.party_count != 0) {
            do {
                Battle_RescaleStats(i & BYTE_MASK);
                i += 1;
            } while ((u32)(i & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        g_Battle.target_record->hp_change = -(s16)g_Game.members[*active].chr.stats.max_hp;
    }
}
#else
INCLUDE_ASM(func_800A1D84);
#endif
