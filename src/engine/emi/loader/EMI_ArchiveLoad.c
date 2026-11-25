#include "engine/slus/slus.h"

/* initializes EMI streaming state, refreshes the active LBA, and
 * installs CD callbacks.
 */
MATCH void EMI_ArchiveLoad(u32 emi_id) {
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
    g_EmiUploadBank      = 0;
    D_80146486           = 0;
    g_EmiRingIndex       = 1;
    g_EmiRingSlot        = 0;
    g_EmiRingBase        = cd_base;

    do {
        g_EmiRingStates[ring_index] = 0xFF;
        ring_index += 1;
    } while (ring_index < EMI_CALLBACK_SLOT_COUNT);

    if (g_EmiStreamMode == 2) {
        if (CdSync(1, g_EmiSyncResult) != CdlNoIntr) {
            if ((g_EmiSyncResult[0] & (CdlStatPlay | CdlStatSeek | CdlStatRead)) != 0) {
                D_8014648B = 1;
            }
        }
    }

    max_lba         = D_8014685C;
    current_lba     = D_80146858;
    g_EmiStreamMode = 1;
    if (max_lba < current_lba) {
        D_8014685C = current_lba;
    }

    active_lba          = g_EmiRequestedSlotId;
    D_80146858          = 0;
    new_lba             = EMI_ArchiveGetSector(active_lba);
    slot                = g_EmiNextSlot;
    g_EmiSlotSectors[0] = new_lba;
    g_EmiSectorCursor   = new_lba;
    g_EmiNextSlot       = slot + 1;
    EMI_NextEntry(slot);

    g_EmiBytesLeft   = EMI_SECTOR_SIZE;
    g_EmiStreamState = 0;
    CdReadyCallback(CD_OnReady);
    CdSyncCallback((CdlCB)CD_OnSync);
    EMI_ArchiveStart();
}
