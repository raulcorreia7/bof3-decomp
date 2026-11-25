#include "engine/slus/slus.h"

/* resets the loader request block for the given position, latches
 * the request, runs the entry lookup, converts the target LBA, and installs
 * the CD sync callback.
 */
MATCH void SND_XAStartStream(s32 key, s32 unused) {
    s16* req;

    req               = &D_80146818;
    *req              = 0;
    g_EmiServiceState = SND_XA_STATE_SEEK;
    g_XAStreamKey     = key;
    D_8014682F        = 0;
    g_XAStopRequested = 0;
    D_80146832        = 0;
    g_XARetryCount    = 0;
    g_XAWaitFrames    = 0;
    g_EmiStreamMode   = 2;
    g_EmiStreamState  = 0;
    SND_XAResolveStream(key);
    CdIntToPos(g_XAStartSector, (CdlLOC*)((u8*)req + 0x20));
    CdSyncCallback((CdlCB)SND_XASetSyncResult);
}
