/* Returns the entry of ENTRIES at base plus the ROWS offset of row, or at base + 8 when mode is 5 or more. A statement macro shared by the area overlays; every change here must verify every member. */
/* AREA_INDEXED_ENTRY (area191 0x801F3924, area192 0x801F33E4) */
#define AREA_INDEXED_ENTRY(ROWS, ENTRIES) \
    u32 index;                            \
    if ((u8)mode < 5) {                   \
        index = ROWS[(u8)row] + base;     \
    } else {                              \
        index = base + 8;                 \
    }                                     \
    return ENTRIES[(u8)index];
