#include "shop_00.h"

/* One 0x18-byte shop filter record: the 0x10-byte key and the packed count word. */
typedef struct ShopFilter {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 count;
} ShopFilter;

MATCH void func_801D6F00(void) {
    ShopFilter* record;
    s32         count;
    u8          i;
    u32         value;
    s32         masked;
    u32         shift;
    s32         bumped;
    s32         offset;
    u32*        count_word;

    g_SaveSlotFirst = SAVE_ScanDirectory((char*)D_801D0C94, 0x10);
    D_801E610C      = 0;
    count           = 0;
    i               = 0;
    if (g_SaveSlotFirst != 0) {
        do {
            offset     = i * 0x18;
            count_word = (u32*)((u8*)&D_8018E9A4 + offset);
            value      = *count_word;
            shift      = value >> 13;
            masked     = count & BYTE_MASK;
            if ((value & 0x1FFF) != 0) {
                bumped = masked + 1;
                count  = bumped + shift;
            } else {
                count = masked + shift;
            }
            record = (ShopFilter*)g_SaveCardDirectory + i;
            if (strncmp((char*)record, (char*)D_801D0C20, 0x10) == 0) {
                ((ShopFilter*)g_SaveCardDirectory)[D_801E610C] = *record;
                D_801E610C += 1;
            }
            i += 1;
        } while (i < g_SaveSlotFirst);
    }
    D_801E60FC      = 0xF - count;
    g_SaveSlotCount = D_801E610C;
}
