#include "battle_15.h"

/* Opens the equipment panel (panel task 18) and its list panel (panel task 17), keeping the choice panel's position. */
/* func_8009B03C */
MATCH void Battle_InitEquipChangePanel(void) {
    MenuPanelTask* panel;
    u8*            slot;
    u16            saved_x;
    u16            saved_y;

    panel         = &g_UIPanelTasks[18];
    panel->active = 1;
    slot          = g_BattleMessageSlot;
    panel->panel  = 8;
    panel->mode   = 3;
    panel->state  = 2;
    panel->unk_0A = 0;
    panel->unk_0B = 0xFF;
    panel->unk_0C = slot[5];
    D_801485D8    = &s_BattleEquipment[0];
    panel->pos.vx = -0xAA;
    panel->flags  = 1;
    panel->pos.vy = 0x3F;
    panel--;
    panel->active                    = 1;
    saved_x                          = g_UIPanelTasks[16].pos.vx;
    panel->state                     = 1;
    saved_y                          = g_UIPanelTasks[16].pos.vy;
    panel->mode                      = 4;
    panel->panel                     = 8;
    panel->unk_0C                    = 0;
    panel->unk_0A                    = 0;
    panel->unk_0B                    = 0;
    panel->unk_08                    = 0;
    panel->flags                     = 0;
    panel->unk_09                    = 0;
    g_BattleChoicePanel.items.active = 0;
    g_BattleChoicePanel.items.pos.vx = SCREEN_WIDTH;
    panel->pos.vx                    = saved_x;
    panel->pos.vy                    = saved_y;
    D_80148656                       = slot[5];
}
