#include "game_00.h"

/* func_801C6A7C */
MATCH s32 Area_PickEncounter(void) {
    s32 sum;
    u8* base;
    s32 index;
    u8  limit;
    s32 masked;

    limit  = (RANDOM_MASK(0xF)) + 1;
    sum    = 0;
    base   = MEM_PTR(u8, 0x800E4000u);
    index  = 0;
    masked = limit & BYTE_MASK;
loop:
    sum += base[8];
    if ((sum & BYTE_MASK) < (u32)masked) {
        index += 1;
        base += 9;
        if ((index & BYTE_MASK) < 8U) {
            goto loop; /* try the next weight record */
        }
        return 0;
    }
    return (index & BYTE_MASK);
}
