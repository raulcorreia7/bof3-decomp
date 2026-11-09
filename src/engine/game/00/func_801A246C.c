#include "game_00.h"

MATCH s32 func_801A246C(s32 value_a, s32 value_b, s32 flag_bits) {
    /* FAKE: retail keeps the original flag_bits in a3 across the bit-0 test; the
     * allocator coalesces the copy without the pin. */
    FAKE_REG(s32, saved, "a3");
    /* FAKE: retail computes the merged bit-1 test into v0 so both branch delay
     * slots carry it; the allocator otherwise places it in a3. */
    FAKE_REG(s32, flags, "v0");
    u8  value;
    u8* work;

    saved = flag_bits;
    flag_bits &= 1;
    if (flag_bits != 0) {
        if ((D_80146878 & 0x2) != (g_EncounterSteps & 0x2)) {
            value = FIELD(u8, value_a, 0x7Bu);
            if (value < 0xFAu) {
                FIELD(u8, value_a, 0x7Bu) = (value + 1u);
            }
            return 1;
        }
    }
    flags = saved & 0x2;
    if (flags != 0) {
        if (FIELD(u8, value_a, 0x7Bu) != 0u) {
            work      = (u8*)g_Task;
            work[9]   = (0x20 / (value_b & BYTE_MASK));
            work      = (u8*)g_Task;
            work[0xA] = (work[9] >> 1);
        }
    }
    return 0;
}
