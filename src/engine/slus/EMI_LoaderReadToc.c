#include "engine/slus/slus.h"

/* validates the active EMI header tag and builds cumulative sector
 * offsets for its entries; invalid tags disable the active load.
 */
MATCH void EMI_LoaderReadToc(void) {
    u8*           header;
    u8*           tag;
    s32           tag_count;
    s32           tag_index;
    u32*          entry;
    u32*          offsets;
    u32*          sector_offsets;
    s32*          entry_count;
    u32           next_offset;
    u32           header_address;
    u8*           loader_state;
    volatile u32* loader_word;
    s32           next_count;

    tag_index        = 7;
    loader_word      = &g_EmiRingBase;
    loader_state     = (u8*)loader_word + 0x30;
    header_address   = *loader_word;
    tag_count        = 7;
    header           = (u8*)header_address;
    D_80146848       = (u32*)header;
    D_80146844.bytes = header;

    do {
        tag = header + tag_index;
        if (tag[8] != g_EmiHeaderTag[tag_count]) {
            loader_state[0]     = 0;
            loader_state[-0x14] = 1;
            return;
        }
        next_count = tag_count--;
        tag_index--;
    } while (next_count != 0);

    sector_offsets    = g_EmiSlotSectors;
    next_offset       = sector_offsets[0] + 1;
    sector_offsets[1] = next_offset;
    entry_count       = (s32*)D_80146848;
    tag_index         = 2;
    if (*entry_count < 2) {
        return;
    }

    entry   = (u32*)(D_80146844.bytes + 0x20);
    offsets = sector_offsets + 2;
    do {
        next_offset += (entry[-4] + 0x7FFu) >> 11;
        *offsets = next_offset;
        entry += 4;
        tag_index++;
        offsets++;
    } while (tag_index <= *entry_count);
}
