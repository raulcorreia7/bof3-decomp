#include "area030_04.h"

/* Maps a 0xFFFF-scaled value onto the 0x24-byte stride entry selected by the row byte, returning the entry's pair when the value exceeds its limit and otherwise the limit pair scaled by value * 10 / limit / 10. */
/* func_801E0ABC */
MATCH s32 Fishing_CatchScore(u8 row_index, u16 value) {
    s32 limit;
    s32 q;

    limit = D_801E2AD7[row_index * 0x24];
    if (value >= (u32)limit) {
        return *(u16*)(D_801E2ADA + row_index * 0x24);
    }
    q = (value * 10) / limit;
    return (u16)(*(u16*)(D_801E2ADA + row_index * 0x24) * q / 10);
}
