#include "engine/slus/slus.h"

/* sets the menu panel's position from the D_8017F944/D_8017F946
 * lookup keyed by the D_801490CE byte, packs the panel's window fields and
 * advances its state byte.
 */
MATCH void func_80159A90(void) {
    /* FAKE: pins panel to v1. */
    MATCH_FAKE_PIN(MenuPanelTask*, panel, "v1");
    u8* mode;
    u16 x;
    u16 y;

    mode  = &D_801490CE;
    panel = g_MenuPanelTaskCurrent;

    x        = *(u16*)((u8*)&D_8017F944 + (VOL(u8, *mode) * 4));
    panel->x = (u16)((x + 35) << 4);

    y                          = *(u16*)((u8*)&D_8017F946 + (VOL(u8, *mode) * 4));
    *(u16*)((u8*)panel + 0x14) = 0xE3;
    *(u16*)((u8*)panel + 0x16) = 0x66;
    *(u16*)((u8*)panel + 0x10) = 0;
    *(u16*)((u8*)panel + 0x12) = 0;
    *(u8*)((u8*)panel + 0xA)   = 0x47;
    panel->y                   = (u16)((y + 16) << 4);

    panel                    = g_MenuPanelTaskCurrent;
    *(u8*)((u8*)panel + 0xB) = 0x20;

    panel = g_MenuPanelTaskCurrent;
    panel->state++;
}
