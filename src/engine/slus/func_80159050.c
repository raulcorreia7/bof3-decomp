#include "engine/slus/slus.h"

/* latches the pending flags into the panel flag byte, arms the two half-centres and 12.4 slide targets from the flag-keyed centre tables, clears both remaining distances, steps the panel state and derives each per-frame step as a fifth of its centre. */
MATCH void func_80159050(void) {
    volatile u8* flags;
    /* FAKE: the merged panel pointer must survive the if/else in v1; the allocator
     * otherwise moves the branch stores off v1 (measured: a0, three sites). */
    FAKE_REG(MenuPanelTask*, task, "v1");
    u8  flag_byte;
    s32 next_y;

    flags = &D_801490CE;

    g_MenuCurrentPanel->flags = 0;
    flag_byte                 = *flags;
    if ((flag_byte & 0x80) != 0) {
        *flags = flag_byte & 0x7F;
        g_MenuCurrentPanel->flags |= 1;
        flag_byte = *flags;
    }
    if ((flag_byte & 0x40) != 0) {
        *flags = flag_byte & 0xBF;
        g_MenuCurrentPanel->flags |= 2;
        g_MenuCurrentPanel->unk_0A = 0x78;
        g_MenuCurrentPanel->unk_0B = 0x36;
        task                       = (MenuPanelTask*)g_MenuCurrentPanel;
        task->pos.x                = (((u8*)&D_8017F91C)[*flags * 2] + 60) * 16;
        next_y                     = ((u8*)&D_8017F91D)[*flags * 2] + 0x1B;
    } else {
        g_MenuCurrentPanel->unk_0A = 0xC8;
        g_MenuCurrentPanel->unk_0B = 0x36;
        task                       = (MenuPanelTask*)g_MenuCurrentPanel;
        task->pos.x                = (((u8*)&g_MenuPanelOrigins)[*flags * 2] + 100) * 16;
        next_y                     = ((u8*)&D_8017F90D)[*flags * 2] + 0x1B;
    }
    task->pos.y = next_y * 16;

    task                = (MenuPanelTask*)g_MenuCurrentPanel;
    task->u.grow.width  = 0;
    task->u.grow.height = 0;
    task->state += 1;
    task->u.grow.step_x = ((task->unk_0A * 0x10) / 5);
    task->u.grow.step_y = ((task->unk_0B * 0x10) / 5);
}
