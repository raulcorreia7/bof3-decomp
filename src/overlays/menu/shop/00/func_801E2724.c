#include "shop_00.h"

/* File-local declarations: shop panel slot flags, type/count/source bytes and
 * frame halfwords are not declared by this target's shop_00.h. */

MATCH void func_801E2724(void) {
    u8* flags = D_80148378;

    g_UiPanelTasks[2].panel  = 7;
    g_UiPanelTasks[2].mode   = 0x10;
    g_UiPanelTasks[2].state  = 2;
    D_8014837C               = BATTLE_PARTY_STRIDE;
    D_8014837E               = 0x3F;
    g_UiPanelTasks[2].unk_0A = g_UiPanelTasks[1].flags;
    *flags                   = 1;
    g_UiPanelTasks[3].mode   = 0x11;
    g_UiPanelTasks[3].pos.vx = 0xB4;
    g_UiPanelTasks[3].panel  = 7;
    g_UiPanelTasks[3].state  = 2;
    g_UiPanelTasks[3].pos.vy = 0xF0;
    flags += 0x24;
    *flags = 1;
}
