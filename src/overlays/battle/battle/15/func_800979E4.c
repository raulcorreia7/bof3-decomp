#include "battle_15.h"

MATCH void func_800979E4(void) {
    u16 held;
    s32 trigger;
    u8* message;
    u8* entry;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_state = 4u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_state = 3u;
        return;
    }
    /* FAKE: plain read of the message-slot selector: the volatile qualifier
     * makes the scheduler fill the branch delay slot and shifts the call. */
    message = (u8*)&D_80148656;
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    entry   = Party_GetAbilities(message[0], g_MenuPanelTasks[16].unk_0B, 1);
    if ((D_801CA718[entry[g_MenuPanelTasks[16].unk_0C] * 0x14] & ABILITY_TARGET_BOTH_SIDES) != 0u &&
        (trigger & (PADLup | PADLdown)) != 0) {
        g_BattleActorTurn->command.target = Battle_FindNextTarget(3);
        *(u8*)&g_Battle.ui_state -= 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        if (func_80097EB8() != 0u) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1));
        } else {
            g_BattleActorTurn->command.target =
                Battle_FindNextTarget(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        if (func_80097EB8() != 0u) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1));
        } else {
            g_BattleActorTurn->command.target =
                Battle_FindPrevTarget(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
