#include "engine/slus/slus.h"

/* opens and enables the boot-side event set used after the logo path
 * hands back to the disc/runtime layer.
 */
MATCH void SYS_InitCard(void) {
    EnterCriticalSection();
    g_SysCardSoftwareIoEvent      = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_SysCardSoftwareTimeoutEvent = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_SysCardSoftwareNewEvent     = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    g_SysCardSoftwareErrorEvent   = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_SysCardHardwareIoEvent      = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_SysCardHardwareTimeoutEvent = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_SysCardHardwareErrorEvent   = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(g_SysCardSoftwareIoEvent);
    EnableEvent(g_SysCardSoftwareTimeoutEvent);
    EnableEvent(g_SysCardSoftwareNewEvent);
    EnableEvent(g_SysCardSoftwareErrorEvent);
    EnableEvent(g_SysCardHardwareIoEvent);
    EnableEvent(g_SysCardHardwareTimeoutEvent);
    EnableEvent(g_SysCardHardwareErrorEvent);
    InitCARD(1);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}
