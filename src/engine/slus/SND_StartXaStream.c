#include "engine/slus/slus.h"

/* resets the loader request block for the given position, latches
 * the request, runs the entry lookup, converts the target LBA, and installs
 * the CD sync callback.
 */
MATCH void SND_StartXaStream(s32 key, s32 unused) {
    s16* req;

    req               = &D_80146818;
    *req              = 0;
    g_EmiServiceState = 1;
    D_8014681A        = key;
    D_8014682F        = 0;
    D_8014682C        = 0;
    D_80146832        = 0;
    D_80146820        = 0;
    D_8014681C        = 0;
    g_EmiServiceMode  = 2;
    g_EmiStreamState  = 0;
    SND_ResolveXaStream(key);
    CdIntToPos(D_8014680C, (CdlLOC*)((u8*)req + 0x20));
    CdSyncCallback((CdlCB)SND_StoreXaSyncResult);
}
