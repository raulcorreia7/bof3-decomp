#include "battle_03.h"

MATCH void func_801E16B4(void) {
    u8           state;
    PartyMember* work;

    if (EMI_IsReady() != 0) {
        work  = g_Game.current;
        state = work->u.turn.command.type;
        if (state == 4) {
            if (!(work->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
                if (!(func_801DDF50(work->chr.character_id, g_Battle.unk_EA[3]) & BYTE_MASK)) {
                    TASK(PartyMember)->unk_09 = 0x1E;
                } else {
                    goto block_8;
                }
            } else if (((g_Battle.dragon_form == state) || ((g_Battle.dragon_form - 7) < 2U)) && (func_801DDF50(work->chr.character_id, g_Battle.unk_EA[3]) & BYTE_MASK)) {
                goto block_8;
            }
        } else {
        block_8:
            TASK(PartyMember)->unk_09 = 0;
        }
        if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            work = g_Game.current;
            if (work->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) {
                TASK(PartyMember)->unk_09 = D_801EB23C[g_Battle.dragon_form];
            } else {
                TASK(PartyMember)->unk_09 = g_BattleCharacterStepIds[work->chr.character_id];
            }
            Script_Request((TASK(PartyMember)->facing + 0x2C) & BYTE_MASK);
            TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
        } else {
            TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
        }
        Battle_IsPartyMemberBlocked();
    }
}
