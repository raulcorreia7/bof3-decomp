#include "battle_15.h"

extern u8 D_80145F20[];
extern u8 D_801EB6D0[];

/* Advances the battle party: bumps the active battler's timer, copies
 * the character cells into the battle rows and drains the enemy rows.
 */
/* nonmatching unmeasured: the active-battler byte is reached through a pointer the retail homes in s2; candidate
 * 40.59%. resume: a source shape that reproduces the retail's cell, row and enemy-row address forms and its register
 * allocation. */
#ifdef NON_MATCHING
NON_MATCHING void func_800A0EC4(void) {
    Character* cell;
    Character* dest;
    s32        cell_offset;
    s32        record_index;
    s32        row_offset;
    s32        timer;
    s32        index;
    s32        member;
    u16        value;
    u32        rate;
    u8*        state;

    state = &g_BattleActiveBattler;
    if (*state < 3U) {
        record_index = *(D_80145FCC + (*state * BATTLE_PARTY_STRIDE));
        timer        = g_SaveData.characters[record_index].fatigue;
        if (timer < 5U) {
            g_SaveData.characters[record_index].fatigue = timer + 1;
            row_offset                                  = *state * BATTLE_PARTY_STRIDE;
            D_80145F1E[row_offset]                      = D_80145F1E[row_offset] + 1;
        }
        Char_RebuildStats((*(D_80145FCC + (*state * BATTLE_PARTY_STRIDE)) * 0xA4) + (u8*)&g_SaveData.characters);
        index = 0;
        if (g_BattlePartyCount != 0) {
            do {
                row_offset         = index * BATTLE_PARTY_STRIDE;
                cell               = (Character*)((*(D_80145FCC + row_offset) * 0xA4) + (u8*)&g_SaveData.characters);
                dest               = (Character*)(row_offset + D_80145F04);
                dest->equip.weapon = cell->equip.weapon;
                dest->equip.shield = cell->equip.shield;
                dest->equip.helmet = cell->equip.helmet;
                dest->equip.armor  = cell->equip.armor;
                dest->equip.accessories[0] = cell->equip.accessories[0];
                index++;
                dest->equip.accessories[1]    = cell->equip.accessories[1];
                ((s32*)&dest->base.max_hp)[0] = ((s32*)&cell->stats.max_hp)[0];
                ((s32*)&dest->base.max_hp)[1] = ((s32*)&cell->stats.max_hp)[1];
                ((s32*)&dest->base.max_hp)[2] = ((s32*)&cell->stats.max_hp)[2];
                ((s32*)&dest->base.max_hp)[3] = ((s32*)&cell->stats.max_hp)[3];
                ((s32*)&dest->base.max_hp)[4] = ((s32*)&cell->stats.max_hp)[4];
                ((s32*)&dest->base.max_hp)[5] = ((s32*)&cell->stats.max_hp)[5];
                ((s32*)&dest->base.max_hp)[6] = ((s32*)&cell->stats.max_hp)[6];
                ((s32*)&dest->base.max_hp)[7] = ((s32*)&cell->stats.max_hp)[7];
            } while ((u32)(index & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
        index = 0;
        func_800AAA74();
        if (g_BattlePartyCount != 0) {
            do {
                row_offset                           = index * BATTLE_PARTY_STRIDE;
                dest                                 = (Character*)(row_offset + D_80145F20);
                *(BattleStatBlockPart*)(dest + 0)    = *(BattleStatBlockPart*)(row_offset + (D_80145F20 + 0x20));
                *(BattleStatBlockPart*)(dest + 0x10) = *(BattleStatBlockPart*)(row_offset + (D_80145F20 + 0x30));
                index++;
            } while ((u32)(index & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
        index = 0;
        func_800A4458();
        if (g_BattlePartyCount != 0) {
            do {
                func_800A9BD8(index & BYTE_MASK);
                index++;
            } while ((u32)(index & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
    } else {
        cell_offset = (*state - 3) * 0x118;
        value       = D_801EB6D0[cell_offset];
        if (value != 0xFFFF) {
            rate = ((u16*)&D_800E4068)[D_801EB710[cell_offset] * 68] / 10;
            if ((u32)(rate & HALF_MASK) < value) {
                D_801EB6D0[cell_offset] = value - rate;
                row_offset              = (*state - 3) * 0x118;
                D_801EB6F0[row_offset] =
                    D_801EB6F0[row_offset] - (((u16*)&D_800E4068)[D_801EB710[row_offset] * 68] / 10);
                member = *state - 3;
                value  = D_801EB6D0[member * 0x118];
                if (value < D_801EB6C4[member][0]) {
                    D_801EB6C4[member][0] = value;
                }
            }
        }
    }
    if (!(func_800A3A10(*(u8*)&g_BattleActiveBattler, g_BattleTarget) & BYTE_MASK)) {
        if ((u8)g_BattleTarget < 3U) {
            value = D_80145F18[g_BattleTarget][0];
        } else {
            value = D_801EB6C4[g_BattleTarget - 3][0];
        }
        g_BattleTargetRecord->hp_change = (s16)(value - 1);
    }
}
#else
INCLUDE_ASM(func_800A0EC4);
#endif
