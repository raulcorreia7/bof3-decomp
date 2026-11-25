#include "engine/slus/slus.h"

/* selects the next EMI entry, transfers its dispatch metadata into
 * loader state, releases any prior owner, and advances the loader step.
 */
MATCH void EMI_VabLoadHeader(void) {
    /* FAKE: unused frame, 64 bytes. */
    FAKE_STACK_PADS(u8, 64);
    volatile u32* table_word;
    u32           word;
    u8            slot;
    u16           index;

    if (g_EmiStep == 0) {
        table_word = &g_EmiLoadArg;
        slot       = g_EmiNextSlot;
        word       = *table_word;
        D_80146484 = slot;

        word           = g_EmiBankLinks[word].index;
        index          = word;
        g_EmiEntryBank = index;
        /* FAKE: barrier pins index store before entry lookup. */
        /* FAKE: barrier reproduces store then reload ordering. */
        FAKE_BARRIER();
        *table_word                     = g_EmiBankLinks[(u8)index].word;
        g_EmiBankLinks[(u8)index].state = 0;
        /* FAKE: keeps the owner-byte reload below both table stores. */
        FAKE_BARRIER();

        if (g_SelectionEffectVoices[g_EmiEntryBank] != -1) {
            SsUtAllKeyOff(0);
            SsSepClose(g_SelectionEffectVoices[g_EmiUploadBank]);
            g_SelectionEffectVoices[g_EmiEntryBank] = -1;
        }
    }

    EMI_SectorCopy();
    {
        u32* loader_step;
        loader_step  = &g_EmiStep;
        *loader_step = *loader_step + 1;
    }
}
