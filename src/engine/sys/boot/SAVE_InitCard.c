#include "engine/slus/slus.h"

/* opens and enables the boot-side event set used after the logo path
 * hands back to the disc/runtime layer.
 */
MATCH void SAVE_InitCard(void) {
    EnterCriticalSection();
    g_SaveCardSoftwareIoEvent      = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_SaveCardSoftwareTimeoutEvent = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_SaveCardSoftwareNewEvent     = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    g_SaveCardSoftwareErrorEvent   = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_SaveCardHardwareIoEvent      = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_SaveCardHardwareTimeoutEvent = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_SaveCardHardwareErrorEvent   = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(g_SaveCardSoftwareIoEvent);
    EnableEvent(g_SaveCardSoftwareTimeoutEvent);
    EnableEvent(g_SaveCardSoftwareNewEvent);
    EnableEvent(g_SaveCardSoftwareErrorEvent);
    EnableEvent(g_SaveCardHardwareIoEvent);
    EnableEvent(g_SaveCardHardwareTimeoutEvent);
    EnableEvent(g_SaveCardHardwareErrorEvent);
    InitCARD(1);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}
