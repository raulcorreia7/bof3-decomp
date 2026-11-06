#include "engine/slus/slus.h"

/* walks the bundle record list g_AreaMapBundle.object_list_28: a header of 0x8001 marks a palette entry whose low flag
 * bit is cleared, and its twelve-byte entries each write their payload word into the map row that the halfword table
 * and the entry's row and bits 14-19 select. */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 81.82%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_80154438(void) {
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);
    u32* record;
    u32* entry;
    s32  record_offset;
    s32  entry_index;
    s32  row_product;
    s32  lookup_product;
    u32  header;
    u32  clean_header;
    u32  value;
    u32  payload;
    u32  table_offset;
    u32  row_offset;
    u32  sum;
    u32  shifted;
    u32  half;
    u32  base_offset;
    u32  lookup;
    u32  destination;
    u16  table;
    u16  map_value;
    u8   width;
    u8   stride;
    u32  entry_row;

    record_offset = g_AreaMapBundle.object_list_28 * 4;
    record        = (u32*)(record_offset + MAP_BUNDLE_BASE);
    if (*record != 0) {
        do {
            header = *record;
            if ((header & HALF_MASK) == 0x8001) {
                clean_header = header & ~1u;
                *record      = clean_header;
                if (((u8*)record)[7] < 2) {
                    entry_index = 0;
                    if ((s32)(clean_header >> 16) > 0) {
                        do {
                            entry              = record + entry_index;
                            value              = entry[1];
                            entry_row          = ((u8*)entry)[5];
                            table              = *(u16*)(MAP_BUNDLE_BASE + 2);
                            width              = *(u8*)MAP_BUNDLE_BASE;
                            stride             = *(u8*)(MAP_BUNDLE_BASE + 1);
                            row_product        = width * stride;
                            lookup_product     = (value & BYTE_MASK) * width;
                            table_offset       = table << 2;
                            row_offset         = entry_row << 1;
                            sum                = table_offset + row_offset;
                            shifted            = (value >> 14) & 0x3C;
                            half               = (row_product + 1) >> 1;
                            base_offset        = MAP_BUNDLE_BASE + (half << 2);
                            lookup             = (lookup_product << 1) + sum + MAP_BUNDLE_BASE;
                            map_value          = *(u16*)lookup;
                            destination        = table_offset + base_offset + (map_value << 2) + shifted;
                            payload            = entry[2];
                            *(u32*)destination = payload;
                        } while ((entry_index += 3) < FIELD(u16, record, 2));
                    }
                }
            }
            record += FIELD(u16, record, 2) + 1;
        } while (*record != 0);
    }
}
#else
INCLUDE_ASM(func_80154438);
#endif
