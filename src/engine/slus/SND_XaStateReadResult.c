#include "engine/slus/slus.h"

/* Retries the pending read, then converts the stored position.
 */
MATCH void SND_XaStateReadResult(void) {
    s32  value;
    u16  count;
    u16* counter;

    counter  = &D_8014681E;
    count    = *counter + 1;
    *counter = count;
    if (count & 0x1) {
        if (D_8014682E <= 0) {
            D_8014682E = 0;
            CdControlF(CdlGetlocL, 0);
            return;
        }
        D_8014682E = 0;
        D_8014681C = 0;
        if (CdLastCom() == CdlGetlocL) {
            value      = CdPosToInt((CdlLOC*)((u8*)counter + 6));
            D_80146814 = value;
            if (value >= D_80146810) {
                g_EmiServiceState = SND_XA_STATE_PAUSE;
                D_8014682E        = 0;
            }
        }
    }
}
