#include "battle_03.h"

/* Non-volatile view of the battle mode word (0x801463C0): ram.h declares it
 * volatile, and a volatile 16-bit load cannot be narrowed to the byte the
 * slot-selection call takes. */

/* starts a battle: clears the 0x20 setup flag, records the battle
 * mode, resolves the battler record of the random type (party records for types
 * 0-2, enemy records for 3+) and copies its position words into the 0x80146386
 * pair.
 */
MATCH void func_801D3624(void) {
    u16* setup_flags;
    /* FAKE: allocator tie, record pointer in a1. */
    FAKE_REG(PartyMember*, work, "a1");
    u32 enemy_offset;
    u8  type_index;
    u16 mode;
    s32 type;

    setup_flags = &g_Battle.flags;
    if ((*setup_flags & 0x20) == 0) {
        return;
    }

    *setup_flags &= ~0x20;
    g_BattleActiveActor->header.mode = 7;
    g_BattleActiveActor->header.step = 0;
    Battle_SetSlotPending(g_Battle.active_battler);
    mode               = g_Battle.action_id;
    g_Battle.unk_EA[3] = mode;
    if ((u16)(mode - 0x24) < 2 || mode == 0x8C) {
        type                     = Battle_PickTarget();
        type_index               = type;
        g_Battle.target_selector = type;
        if (type_index < 3) {
            work                    = &g_Game.members[type_index];
            g_Battle.selected_actor = work;
            /* Retail builds this pointer as base + 0x118 + row * 0x140. */
            D_80146390              = &g_Game.members[type_index].u.turn.command;
            D_80146386              = work->screen_x.value + g_BattlePanelOffsets[g_Game.members[type_index].chr.character_id * 8 + work->facing * 2];
            D_80146388              = work->screen_y.value + D_801EB0B1[g_Game.members[type_index].chr.character_id * 8 + work->facing * 2];
        } else {
            enemy_offset            = type_index * 0x118;
            work                    = (PartyMember*)(g_BattleEnemies + enemy_offset);
            D_80146390              = g_BattleEnemies + 0xF4 + enemy_offset;
            g_Battle.selected_actor = work;
            D_80146386              = work->screen_x.value + ENEMY_COMBATANT(type_index).panel_offset_x;
            D_80146388              = work->screen_y.value + ENEMY_COMBATANT(type_index).panel_offset_y;
        }
        D_8014638A = work->depth;
    }
    Battle_LoadSelectionEffect((*(u8*)&g_Battle.action_id));
    g_Battle.ui_step += 1;
}
