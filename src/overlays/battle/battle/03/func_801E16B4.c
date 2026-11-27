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
                    SELF(PartyMember)->unk_09 = 0x1E;
                } else {
                    goto block_8;
                }
            } else if (((g_Battle.dragon_form == state) || ((g_Battle.dragon_form - 7) < 2U)) && (func_801DDF50(work->chr.character_id, g_Battle.unk_EA[3]) & BYTE_MASK)) {
                goto block_8;
            }
        } else {
        block_8:
            SELF(PartyMember)->unk_09 = 0;
        }
        if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            work = g_Game.current;
            if (work->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) {
                SELF(PartyMember)->unk_09 = D_801EB23C[g_Battle.dragon_form];
            } else {
                SELF(PartyMember)->unk_09 = g_BattleCharacterStepIds[work->chr.character_id];
            }
            Script_Request((SELF(PartyMember)->facing + 0x2C) & BYTE_MASK);
            SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
        } else {
            SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
        }
        Battle_IsPartyMemberBlocked();
    }
}
