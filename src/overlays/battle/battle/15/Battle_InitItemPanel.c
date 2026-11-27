#include "battle_15.h"

/* func_8009AF84 */
MATCH void Battle_InitItemPanel(void) {
    MenuChoicePanel* panel;

    panel               = &g_BattleChoicePanel.items;
    panel->active       = 1;
    panel->panel        = 8;
    panel->state        = 2;
    panel->mode         = 1;
    panel->unk_09       = 0;
    panel->drawn_cursor = 0xFF;
    panel->type         = 2;
    panel->pos.vx       = -0xAA;
    panel->group        = D_801454FD;
    panel->message_id   = 0;
    panel->pos.vy       = 0x3F;
    panel->group_first  = D_801454FE;
    panel->group_cursor = D_801454FF;
    panel += 3;
    panel->active = 0;
    panel->panel  = 8;
    panel->mode   = 0;
}
