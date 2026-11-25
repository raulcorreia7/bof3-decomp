#include "engine/slus/slus.h"

/* Sends the next chunk of the pending sound bank body to the SPU; when the body is in, opens the bank's sequence set
 * and plays the queued sequence. */
MATCH void EMI_VabUploadBody(void) {
    s32*          state;
    s32*          sizes;
    s8*           slot;
    volatile u32* ring;
    u8*           bank;
    s32           result;
    s8            voice;
    s32           index;

    slot  = &g_EmiRingIndex;
    index = *slot;
    slot += 0x30;
    state = (s32*)slot + index;
    if (*state != -1) {
        while ((s16)SsVabTransCompleted(SS_IMMEDIATE) == 0) {
        }
    } else {
        g_EmiUploadBank      = g_EmiEntryBank;
        g_EmiUploadBytesLeft = D_80146478;
        *state               = 0;
    }
    ring   = &g_EmiRingBase;
    sizes  = (s32*)&ring[45];
    result = SsVabTransBodyPartly((u8*)(*ring + (g_EmiRingIndex << 11)), sizes[g_EmiRingIndex], g_EmiBanks[g_EmiUploadBank].vab_id);
    g_EmiUploadBytesLeft -= sizes[g_EmiRingIndex];
    if ((g_EmiUploadBytesLeft == 0) && (result == g_EmiBanks[g_EmiUploadBank].vab_id)) {
        D_80146486 = 0;
        while ((s16)SsVabTransCompleted(SS_IMMEDIATE) == 0) {
        }
    }
    if (result == -1) {
        g_EmiReadStatus = 2;
    }
    if (result < 0) {
        return;
    }
    bank = &g_EmiUploadBank;
    if (g_EmiBanks[*bank].flags & 2) {
        voice                          = SsSepOpenJ((u32*)g_EmiBanks[*bank].sequence_buffer, g_EmiBanks[*bank].vab_id, 4);
        g_SelectionEffectVoices[*bank] = voice;
        if ((s8)voice == -1) {
            g_EmiReadStatus = 2;
            return;
        }
        g_EmiBanks[*bank].flags &= ~2;
    }
    if ((g_EmiStreamFlags & 0x40) && (g_EmiUploadBank == D_80146855)) {
        SND_SeqPlay(g_EmiUploadBank, D_80146856, 100, 100);
    }
}
