#include "engine/slus/slus.h"

/* initializes the post-logo disc/event path and hands control to the
 * first boot-side callback chain.
 */
MATCH void SYS_InitHardware(void) {
    ResetCallback();
    EMI_LoaderInit();

    if (g_SysHardwareInitialized == 0) {
        VSync(0);
        ResetGraph(0);
        SetVideoMode(MODE_NTSC);
        g_SysHardwareInitialized = 1;
        EnterCriticalSection();
        EnableEvent(OpenEvent(HwCPU, EvSpTRAP, EvMdINTR, (long (*)())SYS_ShowException));
        ExitCriticalSection();
    } else {
        VSync(0);
        ResetGraph(3);
    }

    InitGeom();
    SetGeomScreen(1000);
    SetGeomOffset(160, 120);
    PadInit(0);
    SYS_InitCard();
    ChangeClearPAD(0);
}
