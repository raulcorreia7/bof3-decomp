#include "battle_03.h"

/* Non-volatile view of the battle mode word (0x801463C0): ram.h declares it
 * volatile, and a volatile 16-bit load cannot be narrowed to the byte the
 * slot-selection call takes. */

/* starts a battle: clears the 0x20 setup flag, records the battle
 * mode, resolves the battler row of the random kind (local rows for kinds
 * 0-2, enemy rows for 3+) and copies its position words into the 0x80146386
 * pair.
 */
MATCH void func_801D3624(void) {
    u16* setup_flags;
    /* FAKE: allocator tie, row pointer in a1. */
    FAKE_REG(PartyMember*, work, "a1");
    u32 row_offset;
    u8  kind_index;
    u16 mode;
    s32 kind;

    setup_flags = &g_Battle.state;
    if ((*setup_flags & 0x20) == 0) {
        return;
    }

    *setup_flags &= ~0x20;
    D_8014637C[1] = 7;
    D_8014637C[2] = 0;
    Battle_SetSlotPending(g_Battle.active_battler);
    mode       = g_Battle.action_id;
    D_801463CD = mode;
    if ((u16)(mode - 0x24) < 2 || mode == 0x8C) {
        kind                     = Battle_PickTarget();
        kind_index               = kind;
        g_Battle.target_selector = kind;
        if (kind_index < 3) {
            work                    = &g_Game.members[kind_index];
            g_Battle.selected_actor = work;
            /* Retail builds this pointer as base + 0x118 + row * 0x140. */
            D_80146390              = &g_Game.members[kind_index].u.turn.command;
            D_80146386              = work->unk_2E.half + g_BattlePanelOffsets[g_Game.members[kind_index].chr.character_id * 8 + work->facing * 2];
            D_80146388              = work->unk_30.half + D_801EB0B1[g_Game.members[kind_index].chr.character_id * 8 + work->facing * 2];
        } else {
            row_offset              = kind_index * 0x118;
            work                    = (PartyMember*)(g_BattleEnemies + row_offset);
            D_80146390              = g_BattleEnemies + 0xF4 + row_offset;
            g_Battle.selected_actor = work;
            D_80146386              = work->unk_2E.half + ENEMY_COMBATANT(kind_index).panel_offset_x;
            D_80146388              = work->unk_30.half + ENEMY_COMBATANT(kind_index).panel_offset_y;
        }
        D_8014638A = work->depth;
    }
    Battle_LoadSelectionEffect((*(u8*)&g_Battle.action_id));
    g_Battle.ui_step += 1;
}
