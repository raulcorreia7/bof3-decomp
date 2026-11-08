#include "battle_15.h"

/* Builds the active battler's queued action list: copies up to three gene bytes, appends the combo ids
 * enabled by the gene flags, then terminates with 0xD9 and clears the rest. */
MATCH void func_800A78B8(void) {
    u8* dst;
    u8  count;
    u8  i;
    u8  value;

    dst   = &D_80145F04[g_BattleActiveBattler * BATTLE_PARTY_STRIDE];
    count = 0;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        value = D_800B4EA4[D_800B6F58][i];
        if (value == 0) {
            break;
        }
        FIELD(u8, dst + count, 0x70u) = value;
        count++;
    }
    if (D_800B6F60 > 0) {
        count = func_800A7B40(0, count);
        if (D_800B6F69 > 0) {
            count = func_800A7B40(5, count);
        }
        if (D_800B6F63 > 0) {
            count = func_800A7B40(0xE, count);
        }
    }
    if (D_800B6F61 > 0) {
        count = func_800A7B40(1, count);
        if (D_800B6F69 > 0) {
            count = func_800A7B40(6, count);
        }
    }
    if (D_800B6F62 > 0) {
        count = func_800A7B40(2, count);
        if (D_800B6F69 > 0) {
            count = func_800A7B40(7, count);
        }
    }
    if (D_800B6F63 > 0) {
        count = func_800A7B40(3, count);
        if (D_800B6F69 > 0) {
            count = func_800A7B40(8, count);
        }
    }
    if (D_800B6F64 > 0) {
        count = func_800A7B40(4, count);
        if (D_800B6F69 > 0) {
            count = func_800A7B40(9, count);
        }
    }
    if (D_800B6F6C > 0) {
        count = func_800A7B40(0xC, count);
    }
    if (D_800B6F6B > 0) {
        count = func_800A7B40(0xB, count);
    }
    if (D_800B6F69 > 0) {
        count = func_800A7B40(0xD, count);
    }
    FIELD(u8, dst + count, 0x70u) = 0xD9;
    for (count++; count < 10; count++) {
        FIELD(u8, dst + count, 0x70u) = 0;
    }
}
