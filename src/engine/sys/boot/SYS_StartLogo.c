#include "engine/slus/slus.h"

/* loads and transfers control to LOGO.EXE, then restores the boot
 * rendering path after the loaded executable returns.
 */
MATCH void SYS_StartLogo(void) {
    u_long* ordering_table;
    u_long* text_addr;

    SYS_LoadExe(g_LogoExePath);

    text_addr                = &g_LogoHeader.exec.s_addr;
    *text_addr               = 0x801FF000;
    g_LogoHeader.exec.s_size = 0;

    StopCallback();
    PadStop();
    StopCARD();
    EnterCriticalSection();
    Exec(&g_LogoHeader.exec, 0, 0);
    ExitCriticalSection();
    SYS_InitHardware();

    ordering_table = &D_80143DB8;
    ClearOTag(ordering_table, 8);
    DrawOTag(ordering_table);
    ordering_table += 0x24;
    ClearOTag(ordering_table, 8);
    DrawOTag(ordering_table);

    GFX_ClearRect(0, 0, GFX_VRAM_WIDTH, GFX_VRAM_HEIGHT);
    DrawSync(0);
    SetDispMask(1);
}
