#include "engine/game/00/game_00.h"

/* func_801A246C */
/* Pace of step 6: adds one move to the move counter when bit 1 of the party step count changed. */
MATCH s32 Actor_PaceByPartyStepBit1(s32 value_a, s32 value_b, s32 flag_bits) {
    /* FAKE: retail keeps the original flag_bits in a3 across the bit-0 test; the
     * allocator coalesces the copy without the pin. */
    u16 saved;
    /* FAKE: retail computes the merged bit-1 test into v0 so both branch delay
     * slots carry it; the allocator otherwise places it in a3. */
    s32 flags;
    u8  value;
    u8* work;

    saved = flag_bits;
    flag_bits &= 1;
    if (flag_bits != 0) {
        if ((g_ScenarioState.unk_08 & 0x2) != (g_EncounterSteps & 0x2)) {
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
            work      = TASK(u8);
            work[9]   = (0x20 / (value_b & BYTE_MASK));
            work      = TASK(u8);
            work[0xA] = (work[9] >> 1);
        }
    }
    return 0;
}
