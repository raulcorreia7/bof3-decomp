#include "battle_15.h"

/* Opens the battle choice panel (panel task 16) on its first entry and its cursor frame (panel task 19). */
MATCH void func_800A8360(void) {
    MenuPanelTask* panel;

    panel               = &g_UiPanelTasks[16];
    panel->active       = 1;
    panel->mode         = 1;
    panel->panel        = 8;
    panel->state        = 2;
    panel->flags        = 0xFF;
    panel->pos.vx       = -0xAA;
    panel->unk_0A       = 0;
    panel->unk_0B       = 0;
    panel->unk_0C       = 0;
    panel->unk_09       = 0;
    panel->u.message.id = 0;
    panel->pos.vy       = 0x3F;
    panel += 3;
    panel->active = 0;
    panel->panel  = 8;
    panel->mode   = 0;
}
