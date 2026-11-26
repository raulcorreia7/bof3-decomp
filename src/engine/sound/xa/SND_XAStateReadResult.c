#include "engine/slus/slus.h"

/* Retries the pending read, then converts the stored position.
 */
MATCH void SND_XAStateReadResult(void) {
    s32  value;
    u16  count;
    u16* counter;

    counter  = &g_SndXAStateFrame;
    count    = *counter + 1;
    *counter = count;
    if (count & 0x1) {
        if (g_SndXASyncResult <= 0) {
            g_SndXASyncResult = 0;
            CdControlF(CdlGetlocL, 0);
            return;
        }
        g_SndXASyncResult = 0;
        g_SndXAWaitFrames = 0;
        if (CdLastCom() == CdlGetlocL) {
            value                = CdPosToInt((CdlLOC*)((u8*)counter + 6));
            g_SndXACurrentSector = value;
            if (value >= g_SndXAEndSector) {
                g_EmiServiceState = SND_XA_STATE_PAUSE;
                g_SndXASyncResult = 0;
            }
        }
    }
}
