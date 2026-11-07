#include "battle_15.h"

MATCH void func_80097DC0(void) {
    u16 held;
    u8* message;
    u8* entry;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleUIState = 3u;
    } else if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_BattleUIState = 2u;
    } else if ((INPUT_REPEATED(held, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) != 0) {
        /* FAKE: plain read of the message-slot selector: the volatile qualifier
         * makes the scheduler fill the branch delay slot and shifts the call. */
        message = (u8*)&D_80148656;
        entry   = Party_GetAbilities(message[0], D_8014857B, 1);
        if ((D_801CA718[entry[D_8014857C] * 0x14] & ABILITY_TARGET_BOTH_SIDES) != 0u) {
            g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
            SND_PlayCue(EMI_CUE_ID(1, 1));
        }
    }
}
