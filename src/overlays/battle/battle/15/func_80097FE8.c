#include "battle_15.h"

/* Opens the battle choice panel (panel task 16) and its cursor frame (panel task 19). */
MATCH void func_80097FE8(void) {
    MenuPanelTask* panel;
    u8*            message_slot;
    BattleTurn*    actor_turn;
    u32            flags;
    u8             entry_index;
    u8             eight;

    panel                = &g_UiPanelTasks[16];
    panel->active        = 1;
    eight                = 8;
    panel->panel         = eight;
    panel->mode          = 2;
    panel->state         = 2;
    message_slot         = g_BattleMessageSlot;
    panel->unk_0B        = 2;
    entry_index          = message_slot[5];
    actor_turn           = g_BattleActorTurn;
    panel->flags         = 0xFF;
    panel->unk_08        = 2;
    panel->unk_09        = 0;
    panel->unk_0A        = entry_index;
    flags                = actor_turn->action_flags.value;
    panel->pos.vx        = 0x140;
    panel->pos.vy        = 0x3F;
    panel->u.addr.unk_14 = flags & 2;
    D_80148656           = message_slot[5];
    panel += 3;
    panel->active = 0;
    panel->panel  = eight;
    panel->mode   = 0;
}
