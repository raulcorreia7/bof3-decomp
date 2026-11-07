#include "battle_15.h"

MATCH void func_8009A254(void) {
    u16 slot_data;
    s32 input;

    /* First word of the record of the slot that owns the message panel. */
    slot_data = D_80145FAA[BATTLE_ACTIVE_ROW->slot * 0xA0];
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        g_BattleUIState = 4;
        return;
    }
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        g_BattleUIState = 3;
        return;
    }
    input = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if (input & (PADLup | PADLdown)) {
        if (Item_GetFlags(slot_data >> 8, slot_data & BYTE_MASK) & 0x80) {
            g_BattleMessageTurn->command.target = Battle_FindSelectableSlotForward(3);
            {
                u8* state = (u8*)&g_BattleUIState;

                *state -= 1;
            }
            SND_PlayCue(EMI_CUE_ID(1, 1));
            return;
        }
    }
    if (input & PADLright) {
        if (func_8009AF7C() & BYTE_MASK) {
            g_BattleMessageTurn->command.target =
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)g_BattleMessageTurn->command.target + 1);
        } else {
            g_BattleMessageTurn->command.target = Battle_FindSelectableSlotForward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)g_BattleMessageTurn->command.target + 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if (input & PADLleft) {
        if (func_8009AF7C() & BYTE_MASK) {
            g_BattleMessageTurn->command.target =
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)g_BattleMessageTurn->command.target - 1);
        } else {
            g_BattleMessageTurn->command.target = Battle_FindSelectableSlotBackward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)g_BattleMessageTurn->command.target - 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
