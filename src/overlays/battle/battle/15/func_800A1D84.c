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
/* nonmatching unmeasured: tried the first draft with pointer locals and FIELD views (35.93%); the 16-byte packed block copies
 * (39.51%); the active index read once into a local (40.25%); the u8 loop counter (45.38%); the packed block copies
 * with the u8 counter (48.50%); the second loop's source base computed from the table base (62.55%). residual: the
 * frame - the candidate saves one register too many (s3) and keeps the loop count address in a callee-saved register
 * where retail rematerialises it in t0/t1, and the retail re-materialises the D_80145FCC base inside the loop while the
 * candidate holds it in t2. resume: a source shape with one long-lived value less, so the loop count address is
 * rematerialised per loop and the frame drops from 0x30 to the retail 0x20. */
#ifdef NON_MATCHING
NON_MATCHING void func_800A1D84(void) {
    s32 record_index;
    s32 row_offset;
    u8  i;
    u8  row_index;
    /* FAKE: pin keeps the active index address in the retail s2 home. */
    MATCH_FAKE_PIN(volatile u8*, active, "s2");
    u8* cell;
    u8* dest;
    u8* src;
    u8* dst;
    u8  timer;

    active    = &g_BattleTarget;
    row_index = *active;
    if (row_index < BATTLE_ACTIVE_ROW_COUNT) {
        row_offset   = row_index * BATTLE_PARTY_STRIDE;
        record_index = D_80145FCC[row_offset];
        timer        = g_Characters[record_index].fatigue;
        if (timer < BATTLE_TIMER_MAX) {
            g_Characters[record_index].fatigue = timer + 1;
            row_offset                         = *active * BATTLE_PARTY_STRIDE;
            D_80145F1E[row_offset]             = D_80145F1E[row_offset] + 1;
        }
        Char_RebuildStats(&g_Characters[g_BattlePartyBattlers[*active].record_slot]);
        i = 0;
        if (g_BattlePartyCount != 0) {
            do {
                cell       = &g_Characters[g_BattlePartyBattlers[i].record_slot];
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
            } while ((u32)(i & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
        i = 0;
        func_800AAA74();
        if (g_BattlePartyCount != 0) {
            do {
                dst                         = i * BATTLE_PARTY_STRIDE + D_80145F20;
                src                         = i * BATTLE_PARTY_STRIDE + (D_80145F20 + 0x20);
                *(BattleBlock*)(dst + 0x00) = *(BattleBlock*)(src + 0x00);
                *(BattleBlock*)(dst + 0x10) = *(BattleBlock*)(src + 0x10);
                i += 1;
            } while ((u32)(i & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
        i = 0;
        func_800A4458();
        if (g_BattlePartyCount != 0) {
            do {
                func_800A9BD8(i & BYTE_MASK);
                i += 1;
            } while ((u32)(i & BYTE_MASK) < (u8)g_BattlePartyCount);
        }
        g_BattleTargetRecord[2] = (s16) - (s16) * (D_80145F20 + (*active * BATTLE_PARTY_STRIDE));
    }
}
#else
INCLUDE_ASM(func_800A1D84);
#endif
