#include "engine/slus/slus.h"

/* loads and transfers control to LOGO.EXE, then restores the boot
 * rendering path after the loaded executable returns.
 */
MATCH void SYS_RunLogo(void) {
    u_long* ordering_table;
    u32*    exec_state;

    SYS_LoadExec(s__LOGO_LOGO_EXE_1_80149800);

    exec_state  = &D_80143EA0;
    *exec_state = 0x801FF000;
    D_80143EA4  = 0;

    StopCallback();
    PadStop();
    StopCARD();
    EnterCriticalSection();
    Exec((struct EXEC*)(exec_state - 8), 0, 0);
    ExitCriticalSection();
    SYS_InitHardware();

    ordering_table = &D_80143DB8;
    ClearOTag(ordering_table, 8);
    DrawOTag(ordering_table);
    ordering_table += 0x24;
    ClearOTag(ordering_table, 8);
    DrawOTag(ordering_table);

    GFX_ClearRect(0, 0, 1024, 512);
    DrawSync(0);
    SetDispMask(1);
}
