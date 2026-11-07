#include "battle_15.h"

MATCH void func_80098144(void) {
    u16 held;
    s32 trigger;

    held = g_InputPressed;
    if ((held & g_InputMasks[INPUT_SLOT_CANCEL]) != 0u) {
        g_BattleUIStep = 3u;
        return;
    }
    if ((held & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0u) {
        g_BattleUIStep = 2u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
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
