#include "battle_15.h"

/* func_8009AF84 */
MATCH void Battle_InitItemPanel(void) {
    MenuPanelTask* panel;

    panel               = &g_UiPanelTasks[16];
    panel->active       = 1;
    panel->panel        = 8;
    panel->state        = 2;
    panel->mode         = 1;
    panel->unk_09       = 0;
    panel->flags        = 0xFF;
    panel->unk_08       = 2;
    panel->pos.vx       = -0xAA;
    panel->unk_0A       = D_801454FD;
    panel->u.message.id = 0;
    panel->pos.vy       = 0x3F;
    panel->unk_0B       = D_801454FE;
    panel->unk_0C       = D_801454FF;
    panel += 3;
    panel->active = 0;
    panel->panel  = 8;
    panel->mode   = 0;
}
