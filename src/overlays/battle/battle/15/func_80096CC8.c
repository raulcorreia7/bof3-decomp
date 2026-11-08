#include "battle_15.h"

MATCH void func_80096CC8(void) {
    u16 held;
    s32 trigger;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_state = 4u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_state = 3u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & (PADLup | PADLdown)) != 0) {
        g_BattleActorTurn->command.target = Battle_FindNextTarget(3);
        *(u8*)&g_Battle.ui_state -= 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target =
            Battle_FindNextTarget(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target =
            Battle_FindPrevTarget(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
