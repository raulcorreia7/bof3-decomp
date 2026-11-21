#include "battle_15.h"

/* func_80098144 */
MATCH void Battle_SelectExamineEnemyTarget(void) {
    u16 held;
    s32 trigger;

    held = g_PadStates[0].pressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_step = 3u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_step = 2u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
