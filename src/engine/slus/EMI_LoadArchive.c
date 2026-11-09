#include "engine/slus/slus.h"

/* initializes EMI streaming state, refreshes the active LBA, and installs CD callbacks. */
MATCH void EMI_LoadArchive(u32 emi_id) {
    u32 cd_base;
    u32 active_lba;
    u32 current_lba;
    u32 max_lba;
    u32 ring_index;
    u32 new_lba;
    u8  slot;

    cd_base              = AREA_WORK;
    ring_index           = 0;
    g_EmiRequestedSlotId = emi_id;
    g_EmiNextSlot        = 0;
    D_80146482           = 0;
    D_80146486           = 0;
    D_80146488           = 1;
    g_EmiRingSlot        = 0;
    g_EmiRingBase        = cd_base;

    do {
        g_EmiRingStates[ring_index] = 0xFF;
        ring_index += 1;
    } while (ring_index < EMI_CALLBACK_SLOT_COUNT);

    if (g_EmiServiceMode == 2) {
        if (CdSync(1, D_80146498) != CdlNoIntr) {
            if ((D_80146498[0] & 0xE0) != 0) {
                D_8014648B = 1;
            }
        }
    }

    max_lba          = D_8014685C;
    current_lba      = D_80146858;
    g_EmiServiceMode = 1;
    if (max_lba < current_lba) {
        D_8014685C = current_lba;
    }

    active_lba          = g_EmiRequestedSlotId;
    D_80146858          = 0;
    new_lba             = EMI_GetArchiveSector(active_lba);
    slot                = g_EmiNextSlot;
    g_EmiSlotSectors[0] = new_lba;
    g_EmiSectorCursor   = new_lba;
    g_EmiNextSlot       = slot + 1;
    EMI_NextEntry(slot);

    g_EmiBytesLeft   = 0x800;
    g_EmiStreamState = 0;
    CdReadyCallback(EMI_CdOnReady);
    CdSyncCallback((CdlCB)EMI_CdOnSync);
    EMI_StartArchive();
}
