#include "battle_15.h"

/* func_80097EC0 */
MATCH void Battle_InitAbilityPanel(void) {
    BattleAbilityPanel* panel;
    BattleTurn*         actor_turn;
    u32                 flags;
    u8                  entry_index;
    u8                  cursor;
    u8                  tail;

    panel               = &g_BattleChoicePanel.abilities;
    panel->active       = 1;
    panel->panel        = 8;
    panel->mode         = 2;
    panel->state        = 2;
    entry_index         = g_BattleMessageSlot[5];
    actor_turn          = g_BattleActorTurn;
    panel->member       = entry_index;
    panel->ability_type = D_801454F4[entry_index][0];
    panel->first_row    = D_801454F4[entry_index][1];
    cursor              = D_801454F4[entry_index][2];
    panel->drawn_cursor = 0xFF;
    panel->type         = 2;
    panel->unk_09       = 0;
    panel->cursor       = cursor;
    flags               = actor_turn->action_flags.value;
    if ((flags & 0x20002) != 2) {
        panel->unk_14 = 0;
    } else {
        panel->unk_14 = flags & 2;
    }
    panel->pos.vx             = 0x140;
    panel->pos.vy             = 0x3F;
    tail                      = g_BattleMessageSlot[5];
    g_UIPanelTasks[19].active = 0;
    g_UIPanelTasks[19].panel  = 8;
    g_UIPanelTasks[19].mode   = 0;
    D_80148656                = tail;
}
