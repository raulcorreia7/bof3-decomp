#include "start_08.h"

MATCH void func_801E77F0(void) {
    MenuListRow* row;
    u8*          first;
    u8           i;
    u8           j;
    s32          offset;

    first                       = &g_SaveSlots[0].source_index;
    g_SaveSlots[2].source_index = GAME_NONE;
    g_SaveSlots[1].source_index = GAME_NONE;
    *first                      = 0xFF;
    row                         = (MenuListRow*)((u8*)&g_SaveSlots[0].source_index - 0x15);
    for (j = 0; j < BATTLE_PARTY_CHARACTERS_COUNT; j++) {
        i = 0;
        if (g_SaveSlotCount != 0) {
            do {
                offset = i * 24;
                if ((&D_8018E9A1)[offset] - '0' == j) {
                    SAVE_AccessFile(1, &g_SaveCardDirectory[offset], 1, 0x1C, 0xEA0);
                    *(MenuListRowWords*)row = *(MenuListRowWords*)0x800C26A0;
                    row->source_index       = i;
                }
                i++;
            } while (i < g_SaveSlotCount);
        }
        row++;
    }
}
