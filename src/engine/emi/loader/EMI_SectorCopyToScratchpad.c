#include "engine/slus/slus.h"

/* copies two 0x400-byte halves of the active CD sector to scratchpad.
 */
MATCH void EMI_SectorCopyToScratchpad(void) {
    /* FAKE: retail keeps the CD-sector base in a0. */
    FAKE_REG(u32, base, "a0");
    u32 i;

    {
        s8*  slot;
        u32* scratch;

        scratch    = (u32*)SCRATCH_PAD;
        slot       = &g_EmiRingIndex;
        D_8018B4B0 = 0;
        do {
            i          = D_8018B4B0;
            base       = g_EmiRingBase;
            D_8018B4B0 = i + 1;
            scratch[i] = *(u32*)((*slot << 11) + base + i * 4);
        } while (i + 1 < 256U);
    }
    LZ77_DecodeStep();
    {
        s8*  slot;
        s8*  guard;
        u32* scratch;

        guard = &g_EmiRingIndex;
        if (*(u32*)(*guard * 4 + (u8*)&g_EmiRingIndex + 0x90) >= 0x401U) {
            scratch    = (u32*)SCRATCH_PAD;
            D_8018B4B0 = 0;
            slot       = guard;
            do {
                i          = D_8018B4B0;
                base       = g_EmiRingBase;
                D_8018B4B0 = i + 1;
                scratch[i] = *(u32*)((*slot << 11) + base + i * 4 + 0x400);
            } while (i + 1 < 256U);
            LZ77_DecodeStep();
        }
    }
}
