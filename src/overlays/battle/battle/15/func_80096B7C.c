#include "battle_15.h"

MATCH void func_80096B7C(void) {
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
        g_BattleActorTurn->command.target = Battle_TargetNext(0);
        *(u8*)&g_Battle.ui_state += 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target =
            Battle_TargetNext(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target =
            Battle_TargetPrev(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
