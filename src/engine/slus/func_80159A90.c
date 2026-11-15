#include "engine/slus/slus.h"

/* sets the menu panel's position from the D_8017F944/D_8017F946
 * lookup keyed by the D_801490CE byte, packs the panel's window fields and
 * advances its state byte.
 */
MATCH void func_80159A90(void) {
    /* FAKE: pins panel to v1. */
    FAKE_REG(MenuPanelTask*, panel, "v1");
    u8* mode;
    u16 x;
    u16 y;

    mode  = &D_801490CE;
    panel = g_MenuCurrentPanel;

    x            = *(u16*)((u8*)&D_8017F944 + (VOL(u8, *mode) * 4));
    panel->pos.x = ((x + 35) << 4);

    y                    = *(u16*)((u8*)&D_8017F946 + (VOL(u8, *mode) * 4));
    panel->u.grow.step_x = 0xE3;
    panel->u.grow.step_y = 0x66;
    panel->u.grow.width  = 0;
    panel->u.grow.height = 0;
    panel->unk_0A        = 0x47;
    panel->pos.y         = ((y + 16) << 4);

    panel         = g_MenuCurrentPanel;
    panel->unk_0B = 0x20;

    panel = g_MenuCurrentPanel;
    panel->state++;
}
