#include "battle_15.h"

/* func_80097844 */
MATCH void Battle_SelectAbilityEnemyTarget(void) {
    u16 held;
    s32 trigger;
    u8* message;
    u8* entry;

    held = g_PadStates[0].pressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_mode = 4u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_mode = 3u;
        return;
    }
    /* FAKE: plain read of the message-slot selector: the volatile qualifier
     * makes the scheduler fill the branch delay slot and shifts the call. */
    message = (u8*)&D_80148656;
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    entry   = Party_GetAbilities(message[0], g_UIPanelTasks[16].unk_0B, 1);
    if ((g_Abilities[entry[g_UIPanelTasks[16].unk_0C]].targeting_flags & ABILITY_TARGET_FLAG_BOTH_SIDES) != 0u && (trigger & (PADLup | PADLdown)) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(0);
        g_Battle.ui_mode += 1u;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
