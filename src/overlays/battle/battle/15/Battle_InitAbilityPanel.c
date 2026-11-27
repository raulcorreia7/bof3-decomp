#include "battle_15.h"

/* func_80097EC0 */
MATCH void Battle_InitAbilityPanel(void) {
    MenuPanelTask* panel;
    BattleTurn*    actor_turn;
    u32            flags;
    u8             entry_index;
    u8             cursor;
    u8             tail;

    panel                = &g_UiPanelTasks[16];
    panel->active        = 1;
    panel->panel         = 8;
    panel->mode          = 2;
    panel->state         = 2;
    entry_index          = g_BattleMessageSlot[5];
    actor_turn           = g_BattleActorTurn;
    panel->unk_0A        = entry_index;
    panel->unk_0B        = D_801454F4[entry_index][0];
    panel->u.addr.unk_10 = D_801454F4[entry_index][1];
    cursor               = D_801454F4[entry_index][2];
    panel->flags         = 0xFF;
    panel->unk_08        = 2;
    panel->unk_09        = 0;
    panel->unk_0C        = cursor;
    flags                = actor_turn->action_flags.value;
    if ((flags & 0x20002) != 2) {
        panel->u.addr.unk_14 = 0;
    } else {
        panel->u.addr.unk_14 = flags & 2;
    }
    panel->pos.vx             = 0x140;
    panel->pos.vy             = 0x3F;
    tail                      = g_BattleMessageSlot[5];
    g_UiPanelTasks[19].active = 0;
    g_UiPanelTasks[19].panel  = 8;
    g_UiPanelTasks[19].mode   = 0;
    D_80148656                = tail;
}
