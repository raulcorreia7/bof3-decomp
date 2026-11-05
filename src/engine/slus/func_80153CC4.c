#include "engine/slus/slus.h"

/* TODO
 */
MATCH void func_80153CC4(u32 unused) {
    u32 base_t0;
    u32 level_t1;
    s32 count_a3;
    s32 offset_a2;
    s32 count_a1;
    u32 step_a0;
    u32 v0;
    u32 v1;

    count_a3  = 0;
    level_t1  = g_FrameBufferIndex & BYTE_MASK;
    base_t0   = (u32)(u8*)&D_80142CC0;
    offset_a2 = 0;
    do {
        count_a1 = 0;
        step_a0  = level_t1;
        do {
            v0 = step_a0 << 3;
            count_a1++;
            v1                       = v0 + offset_a2;
            v0                       = v0 + base_t0;
            *(u32*)(D_80142CC4 + v1) = offset_a2 + v0;
            *(u32*)(D_80142CC0 + v1) = 0;
            step_a0 += 2;
        } while (count_a1 < 2);
        count_a3++;
        offset_a2 += 0x30;
    } while (count_a3 < 56);
    (void)unused;
}
