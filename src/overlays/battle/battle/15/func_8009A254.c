#include "battle_15.h"

MATCH void func_8009A254(void) {
    u16 slot_data;
    s32 input;

    /* First word of the record of the slot that owns the message panel. */
    slot_data = g_Game.members[BATTLE_ACTIVE_ROW->slot].u.turn.command.id;
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        g_Battle.ui_mode = 4;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        g_Battle.ui_mode = 3;
        return;
    }
    input = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if (input & (PADLup | PADLdown)) {
        if (Item_GetFlags(slot_data >> 8, slot_data & BYTE_MASK) & ITEM_USABLE_MENU) {
            g_BattleActorTurn->command.target = Battle_TargetNext(3);
            {
                u8* state = (u8*)&g_Battle.ui_mode;

                *state -= 1;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            return;
        }
    }
    if (input & PADLright) {
        if (func_8009AF7C() & BYTE_MASK) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1));
        } else {
            g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (input & PADLleft) {
        if (func_8009AF7C() & BYTE_MASK) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1));
        } else {
            g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
