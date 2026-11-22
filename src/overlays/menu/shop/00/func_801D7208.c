#include "shop_00.h"

/* Source record block of the slot copy. */

MATCH void func_801D7208(void) {
    SaveSlotRow* slot;
    u8*          first;
    u8           i;
    u8           j;
    s32          offset;

    first                           = &g_SaveSlots[0].bytes.card_index;
    g_SaveSlots[2].bytes.card_index = GAME_NONE;
    g_SaveSlots[1].bytes.card_index = GAME_NONE;
    *first                          = 0xFF;
    slot                            = g_SaveSlots;
    for (j = 0; j < BATTLE_PARTY_CHARACTERS_COUNT; j++) {
        i = 0;
        if (g_SaveSlotCount != 0) {
            do {
                offset = i * 24;
                if ((&D_8018E9A1)[offset] - '0' == j) {
                    SAVE_AccessFile(1, &g_SaveCardDirectory[offset], 1, 0x1C, 0xEA0);
                    *slot                  = *(SaveSlotRow*)0x800C26A0;
                    slot->bytes.card_index = i;
                }
                i++;
            } while (i < g_SaveSlotCount);
        }
        slot++;
    }
}
