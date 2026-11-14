#include "battle_15.h"

/* Semantic view of the shared battle-selection scratch band
 * (g_BattleChoicePanel, 0x80148570): word-sized cursor coordinates and
 * ring state sit beside byte-sized panel fields. */
typedef struct BattleSelectionInit {
    volatile u8  selection_kind;  /* +0x00 */
    volatile u8  panel_rows;      /* +0x01 */
    volatile u8  primary_kind;    /* +0x02 */
    volatile u8  primary_state;   /* +0x03 */
    volatile u16 scroll_base_x;   /* +0x04 */
    volatile u16 scroll_base_y;   /* +0x06 */
    volatile u8  panel_kind;      /* +0x08 */
    volatile u8  panel_row_count; /* +0x09 */
    volatile u8  group_index;     /* +0x0A */
    volatile u8  page_base;       /* +0x0B */
    volatile u8  cursor_index;    /* +0x0C */
    volatile u8  cursor_limit;    /* +0x0D */
    volatile u16 ring_cursor;     /* +0x0E */
    volatile u16 ring_handle;     /* +0x10 */
} BattleSelectionInit;

/* FAKE: retail reads D_801454F4 as flat bytes; the owner declares rows. */
MATCH void func_80097EC0(void) {
    BattleSelectionInit* init_work;
    volatile BattleTurn* actor_turn;
    u32                  source_slot_offset;
    u32                  active_selection_flags;
    u32                  flag_mask;
    u8                   entry_index;
    u8                   entry_value;
    u8                   tail_byte;

    init_work                           = (BattleSelectionInit*)g_BattleChoicePanel;
    init_work->selection_kind           = 1u;
    g_BattleChoicePanel[1]              = 8u;
    g_BattleChoicePanel[2]              = 2u;
    g_BattleChoicePanel[3]              = 2u;
    entry_index                         = g_BattleMessageSlot[5];
    actor_turn                          = g_BattleActorTurn;
    source_slot_offset                  = entry_index * 3u;
    g_BattleChoicePanel[0xA]            = entry_index;
    g_BattleChoicePanel[0xB]            = ((u8*)D_801454F4)[source_slot_offset];
    VOL(u16, g_BattleChoicePanel[0x10]) = ((u8*)D_801454F4)[source_slot_offset + 1];
    entry_value                         = ((u8*)D_801454F4)[source_slot_offset + 2];
    g_BattleChoicePanel[0xD]            = 0xFFu;
    g_BattleChoicePanel[8]              = 2u;
    g_BattleChoicePanel[9]              = 0u;
    g_BattleChoicePanel[0xC]            = entry_value;
    active_selection_flags              = actor_turn->action_flags.value;
    flag_mask                           = active_selection_flags & 0x20002u;
    if (flag_mask != 2u) {
        VOL(u16, g_BattleChoicePanel[0x14]) = 0u;
    } else {
        VOL(u16, g_BattleChoicePanel[0x14]) = (active_selection_flags & 0x2u);
    }
    init_work->scroll_base_x = 0x140u;
    init_work->scroll_base_y = 0x3Fu;
    tail_byte                = g_BattleMessageSlot[5];
    D_801485DC               = 0u;
    D_801485DD               = 8u;
    D_801485DE               = 0u;
    D_80148656               = tail_byte;
}
