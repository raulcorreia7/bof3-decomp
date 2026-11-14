#include "battle_03.h"

MATCH void func_801E16B4(void) {
    u8           state;
    PartyMember* work;

    if (EMI_IsReady() != 0) {
        work  = g_Game.current;
        state = work->u.turn.command.type;
        if (state == 4) {
            if (!(work->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM)) {
                if (!(func_801DDF50(work->chr.character_id, D_801463CD) & BYTE_MASK)) {
                    g_Task->unk_09 = 0x1E;
                } else {
                    /* shared exit: the armed step clears the phase byte */
                    goto block_8;
                }
            } else if (((g_Battle.dragon_form == state) || ((g_Battle.dragon_form - 7) < 2U)) && (func_801DDF50(work->chr.character_id, D_801463CD) & BYTE_MASK)) {
                /* shared exit: the armed step clears the phase byte */
                goto block_8;
            }
        } else {
        block_8:
            g_Task->unk_09 = 0;
        }
        if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            work = g_Game.current;
            if (work->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) {
                g_Task->unk_09 = D_801EB23C[g_Battle.dragon_form];
            } else {
                g_Task->unk_09 = s_BattleCharacterStepIds[work->chr.character_id];
            }
            Actor_RequestScript((g_Task->facing + 0x2C) & BYTE_MASK);
            g_Task->header.step = g_Task->header.step + 1;
        } else {
            g_Task->header.mode = g_Task->header.mode + 1;
        }
        Battle_IsPartyMemberBlocked();
    }
}
