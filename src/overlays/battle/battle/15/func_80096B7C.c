#include "battle_15.h"

MATCH void func_80096B7C(void) {
    u16 held;
    s32 trigger;

    held = g_InputPressed;
    if ((held & g_InputMasks[INPUT_SLOT_CANCEL]) != 0u) {
        g_BattleUIState = 4u;
        return;
    }
    if ((held & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0u) {
        g_BattleUIState = 3u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & (PADLup | PADLdown)) != 0) {
        g_BattleMessageTurn->command.target = Battle_FindSelectableSlotForward(0);
        *(u8*)&g_BattleUIState += 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        g_BattleMessageTurn->command.target = Battle_FindSelectableSlotForward(
            func_801DD7D8(g_BattleEnemyCount + 2, 3, (s8)g_BattleMessageTurn->command.target + 1) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleMessageTurn->command.target = Battle_FindSelectableSlotBackward(
            func_801DD7D8(g_BattleEnemyCount + 2, 3, (s8)g_BattleMessageTurn->command.target - 1) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
