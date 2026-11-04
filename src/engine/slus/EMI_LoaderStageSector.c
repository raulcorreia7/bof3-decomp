#include "engine/slus/slus.h"

/* copies two 0x400-byte halves of the active CD sector to scratchpad.
 */
MATCH void EMI_LoaderStageSector(void) {
    /* FAKE: retail keeps the CD-sector base in a0. */
    MATCH_REG(u32, base, "a0");
    u32 i;

    {
        s8*  slot;
        u32* scratch;

        scratch    = (u32*)SCRATCH_PAD;
        slot       = &D_80146488;
        D_8018B4B0 = 0;
        do {
            i                             = D_8018B4B0;
            base                          = g_EmiRingBase;
            D_8018B4B0                    = i + 1;
            *(u32*)((u32)scratch + i * 4) = *(u32*)((*slot << 11) + base + i * 4);
        } while (i + 1 < 256U);
    }
    EMI_DecodeStep();
    {
        s8*  slot;
        s8*  guard;
        u32* scratch;

        guard = &D_80146488;
        if (*(u32*)(*guard * 4 + (u8*)&D_80146488 + 0x90) >= 0x401U) {
            scratch    = (u32*)SCRATCH_PAD;
            D_8018B4B0 = 0;
            slot       = guard;
            do {
                i                             = D_8018B4B0;
                base                          = g_EmiRingBase;
                D_8018B4B0                    = i + 1;
                *(u32*)((u32)scratch + i * 4) = *(u32*)((*slot << 11) + base + i * 4 + 0x400);
            } while (i + 1 < 256U);
            EMI_DecodeStep();
        }
    }
}
