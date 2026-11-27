#include "shop_00.h"

/* File-local declarations: shop panel configuration bytes and halfwords. */

MATCH void func_801D2828(void) {
    u8* state;

    g_UiPanelTasks[7].pos.vx   = BATTLE_PARTY_STRIDE;
    g_UiPanelTasks[7].pos.vy   = 0x3E;
    g_UiPanelTasks[7].active   = 1;
    g_UiPanelTasks[7].panel    = 7;
    g_UiPanelTasks[7].mode     = 9;
    g_UiPanelTasks[7].state    = 2;
    /* Pointer form: retail keeps one base register across the counter load and
     * the store, which a symbol access would re-materialize. */
    state                      = &g_MenuStep.state;
    g_UiPanelTasks[7].unk_0A   = 0;
    g_UiPanelTasks[7].unk_0B   = 0;
    g_UiPanelTasks[7].unk_0C   = 0;
    g_UiPanelTasks[7].flags    = 0xFF;
    g_UiPanelTasks[7].unk_08   = 3;
    g_UiPanelTasks[7].unk_09   = 0;
    g_UiPanelTasks[7].u.grow.w = 0;
    g_UiPanelTasks[7].u.grow.h = 0;
    *state += 1;
}
