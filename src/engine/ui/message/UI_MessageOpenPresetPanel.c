#include "engine/slus/slus.h"

/* sets the menu panel's position from the D_8017F944/D_8017F946
 * lookup keyed by the g_UiPanelPlacement byte, packs the panel's window fields and
 * advances its state byte.
 */
/* func_80159A90 */
MATCH void UI_MessageOpenPresetPanel(void) {
    /* FAKE: pins panel to v1. */
    FAKE_REG(MenuPanelTask*, panel, "v1");
    u8* mode;
    u16 x;
    u16 y;

    mode  = &g_UiPanelPlacement;
    panel = g_UiPanelCurrent;

    x             = *(u16*)((u8*)&D_8017F944 + (*mode * 4));
    panel->pos.vx = ((x + 35) << 4);

    y                          = *(u16*)((u8*)&D_8017F946 + (FAKE_VOLATILE(u8, *mode) * 4));
    panel->u.grow.width_delta  = 0xE3;
    panel->u.grow.height_delta = 0x66;
    panel->u.grow.w            = 0;
    panel->u.grow.h            = 0;
    panel->unk_0A              = 0x47;
    panel->pos.vy              = ((y + 16) << 4);

    panel         = g_UiPanelCurrent;
    panel->unk_0B = 0x20;

    panel = g_UiPanelCurrent;
    panel->state++;
}
