#include "battle_15.h"

MATCH void func_80096CC8(void) {
    u16 held;
    s32 trigger;

    held = g_InputPressed;
    if ((held & D_80145AC4) != 0u) {
        g_BattleUIState = 4u;
        return;
    }
    if ((held & D_80145AC2) != 0u) {
        g_BattleUIState = 3u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & (PADLup | PADLdown)) != 0) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(3);
        *(u8*)&g_BattleUIState -= 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(
            func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target + 1) & 0xFF);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotBackward(
            func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target - 1) & 0xFF);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
