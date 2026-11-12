#include "battle_15.h"

extern u8 D_80145F20[];

/* Each battler row is 0x140 bytes; each colour cell inside a row is 0xA4. */
#define BATTLE_CELL_STRIDE      0xA4
/* The active battler index selects one of three rows. */
#define BATTLE_ACTIVE_ROW_COUNT 3
/* The timer counts up to this value before it stops. */
#define BATTLE_TIMER_MAX        9

/* A sixteen-byte block the retail copies with four unaligned word pairs, so the
 * block is moved as a byte group and never as machine words. */
typedef struct BattleBlock {
    u8 bytes[16];
} BattleBlock;

/* Advances the player battler: bumps its timer and mirrored work row, copies the battler work rows and effect
 * vectors, and mirrors the active row value into the selection slot.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800A1D84(void) {
    s32          record_index;
    s32          row_offset;
    u8           i;
    u8           row_index;
    volatile u8* active;
    u8*          cell;
    u8*          dest;
    u8*          src;
    u8*          dst;
    u8           timer;

    active    = &g_Battle.target;
    row_index = *active;
    if (row_index < BATTLE_ACTIVE_ROW_COUNT) {
        row_offset   = row_index * BATTLE_PARTY_STRIDE;
        record_index = (&g_Game.members[0].character_index)[row_offset];
        timer        = g_Characters[record_index].fatigue;
        if (timer < BATTLE_TIMER_MAX) {
            g_Characters[record_index].fatigue = timer + 1;
            row_offset                         = *active * BATTLE_PARTY_STRIDE;
            D_80145F1E[row_offset]             = D_80145F1E[row_offset] + 1;
        }
        Char_RebuildStats(&g_Characters[g_Game.members[*active].character_index]);
        i = 0;
        if (g_Battle.party_count != 0) {
            do {
                cell       = &g_Characters[g_Game.members[i].character_index];
                dest       = i * BATTLE_PARTY_STRIDE + D_80145F04;
                dest[0x0E] = cell[0x0E];
                dest[0x0F] = cell[0x0F];
                dest[0x10] = cell[0x10];
                dest[0x11] = cell[0x11];
                dest[0x12] = cell[0x12];
                i += 1;
                dest[0x13]                   = cell[0x13];
                *(BattleBlock*)(dest + 0x3C) = *(BattleBlock*)(cell + 0x1C);
                *(BattleBlock*)(dest + 0x4C) = *(BattleBlock*)(cell + 0x2C);
            } while ((u32)(i & BYTE_MASK) < (u8)g_Battle.party_count);
        }
        i = 0;
        Battle_ApplyFormationStats();
        if (g_Battle.party_count != 0) {
            do {
                dst                         = i * BATTLE_PARTY_STRIDE + D_80145F20;
                src                         = i * BATTLE_PARTY_STRIDE + (D_80145F20 + 0x20);
                *(BattleBlock*)(dst + 0x00) = *(BattleBlock*)(src + 0x00);
                *(BattleBlock*)(dst + 0x10) = *(BattleBlock*)(src + 0x10);
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
        g_Battle.target_record->hp_change = (s16) - (s16) * (D_80145F20 + (*active * BATTLE_PARTY_STRIDE));
    }
}
#else
INCLUDE_ASM(func_800A1D84);
#endif
