#include "battle_15.h"

/* Semantic view of the shared battle-selection scratch band
 * (g_BattleChoicePanel, 0x80148570): word-sized cursor coordinates and
 * ring state sit beside byte-sized panel fields. */
typedef struct BattleSelectionInit {
    volatile u8  selection_type;  /* +0x00 */
    volatile u8  panel_rows;      /* +0x01 */
    volatile u8  primary_type;    /* +0x02 */
    volatile u8  primary_state;   /* +0x03 */
    volatile u16 scroll_base_x;   /* +0x04 */
    volatile u16 scroll_base_y;   /* +0x06 */
    volatile u8  panel_type;      /* +0x08 */
    volatile u8  panel_row_count; /* +0x09 */
    volatile u8  group_index;     /* +0x0A */
    volatile u8  page_base;       /* +0x0B */
    volatile u8  cursor_index;    /* +0x0C */
    volatile u8  cursor_limit;    /* +0x0D */
    volatile u16 ring_cursor;     /* +0x0E */
    volatile u16 ring_handle;     /* +0x10 */
} BattleSelectionInit;

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
    g_UiPanelTasks[19].active = 0;
    g_UiPanelTasks[19].panel  = 8;
    g_UiPanelTasks[19].mode   = 0;
    D_80148656                = tail;
}
