#include "engine/slus/slus.h"

/* advances the current loader slot through its transfer, retunes
 * the remaining byte count, and re-arms the slot state machine.
 */
/* Typed bank fields and a cached bank pointer leave a 0x30 frame versus retail 0x20. */
#ifdef NON_MATCHING
NON_MATCHING void EMI_UploadVabBody(void) {
    u8*  vab;
    s32* slot;
    s32  off;
    s32  result;
    u8   index;

    /* The table rows are 0x14 bytes; the retail body reaches each field with
     * byte offsets from the table base (the bank records + field). */
    vab = (u8*)&g_EmiBanks[0].sequence_buffer;

    slot = (s32*)((u8*)&D_80146488 + 48) + D_80146488;
    if (*slot != -1) {
        do {
        } while ((SsVabTransCompleted(SS_IMMEDIATE) << 16) == 0);
    } else {
        D_80146482 = D_80146483;
        D_80146474 = D_80146478;
        *slot      = 0;
    }

    off    = D_80146488 << 11;
    result = (s16)SsVabTransBodyPartly((u8*)(g_EmiRingBase + off), D_80146518[D_80146488], *(s16*)(vab + 4 + D_80146482 * 0x14));
    D_80146474 -= D_80146518[D_80146488];
    if (D_80146474 == 0) {
        if (result == *(s16*)(vab + 4 + D_80146482 * 0x14)) {
            D_80146486 = 0;
            do {
            } while ((SsVabTransCompleted(SS_IMMEDIATE) << 16) == 0);
        }
    }
    if (result == -1) {
        g_EmiReadStatus = 2;
    }
    if (result < 0) {
        return;
    }

    index = D_80146482;
    if (*(u16*)(vab + 6 + index * 0x14) & 2) {
        result                         = SsSepOpenJ(*(u32*)(vab + index * 0x14), *(s16*)(vab + 4 + index * 0x14), 4);
        g_SelectionEffectVoices[index] = (u8)result;
        if ((s8)result == -1) {
            g_EmiReadStatus = 2;
            return;
        }
        *(u16*)(vab + 6 + index * 0x14) &= 0xFFFD;
    }
    if ((g_EmiStreamFlags & 0x40) && (index == D_80146855)) {
        SND_PlaySequence(index, D_80146856, 100, 100);
    }
}
#else
INCLUDE_ASM(EMI_UploadVabBody);
#endif
