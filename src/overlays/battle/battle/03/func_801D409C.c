#include "battle_03.h"

/* scans the first three battle action slots and, per kind mask bit 0x200, clears the slot's 0x8 flag and appends a selection-ring record (the 0x24 ability name for the flagged kind, else the 0x23 resource). */
MATCH void func_801D409C(void) {
    u8*                     state;
    u8*                     battler;
    const volatile Ability* ability;
    BattleAction*           action_ref;
    u16                     mask;
    u8                      index;
    int                     clear_flag;
    u8*                     phase_byte;

    if (D_801EC2E4 != 0) {
        return;
    }

    state = &g_Battle.row_cursor;
    if (*state < 3) {
        clear_flag = ~8;
        battler    = state + 0x8F;
        ability    = g_Abilities;
        do {
            (*state)++;
            action_ref = g_Battle.action;
            mask       = D_801CA71C[action_ref->unk_02].mask;
            if (mask & 0x200) {
                if (!(g_Game.members[*state - 1].u.turn.damage_flags.value & COMBATANT_FLAG_UNK_3)) {
                    continue;
                }
                g_Game.members[*state - 1].u.turn.damage_flags.value &= clear_flag;
                Battle_SetTextPartyName((u8)(*state - 1));
                for (index = 0; index < 32; index++) {
                    D_801490F8[index] = 0;
                }
                for (index = 0; index < 12; index++) {
                    D_801490F8[index] = ability[ENEMY_COMBATANT(*battler).turn.command.id].name[index];
                }
                Battle_AddMessage(1, 0, Message_GetText(BATTLE_TEXT_LEARNED));
                return;
            }
            if (g_Game.members[*state - 1].u.turn.damage_flags.value & COMBATANT_FLAG_UNK_3) {
                g_Game.members[*state - 1].u.turn.damage_flags.value &= clear_flag;
                Battle_AddMessage(1, 0, Message_GetText(BATTLE_TEXT_CANT_LEARN));
                return;
            }
        } while (g_Battle.row_cursor < 3);
    }
    phase_byte  = &g_Battle.phase.sub_step;
    *phase_byte = *phase_byte + 1;
}
