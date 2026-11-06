#include "game_00.h"

MATCH s32 func_801C6A7C(void) {
    s32 sum;
    u8* base;
    s32 index;
    /* FAKE: limit pinned to v0; keeps the masked copy from folding. */
    MATCH_REG(s32, limit, "v0");
    s32 masked;

    limit = rand();
    limit &= 0xF;
    limit += 1;
    sum    = 0;
    base   = MEM_PTR(u8, 0x800E4000u);
    index  = 0;
    masked = limit & 0xFF;
loop:
    sum += base[8];
    if ((sum & 0xFF) < (u32)masked) {
        index += 1;
        base += 9;
        if ((index & 0xFF) < 8U) {
            goto loop; /* try the next weight record */
        }
        return 0;
    }
    return (index & 0xFF);
}
