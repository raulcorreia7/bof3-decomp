#include "battle_15.h"

MATCH void func_800979E4(void) {
    u16 held;
    s32 trigger;
    u8* message;
    u8* entry;

    held = g_InputPressed;
    if ((held & D_80145AC4) != 0u) {
        g_BattleUIState = 4u;
        return;
    }
    if ((held & D_80145AC2) != 0u) {
        g_BattleUIState = 3u;
        return;
    }
    /* FAKE: plain read of the message-slot selector: the volatile qualifier
     * makes the scheduler fill the branch delay slot and shifts the call. */
    message = (u8*)&D_80148656;
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    entry   = Party_GetAbilities(message[0], D_8014857B, 1);
    if ((D_801CA718[entry[D_8014857C] * 0x14] & 0x80u) != 0u && (trigger & (PADLup | PADLdown)) != 0) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(3);
        *(u8*)&g_BattleUIState -= 1u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        return;
    }
    if ((trigger & PADLright) != 0) {
        if (func_80097EB8() != 0u) {
            D_801EB4D8->command.target = func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target + 1);
        } else {
            D_801EB4D8->command.target = Battle_FindSelectableSlotForward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target + 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        if (func_80097EB8() != 0u) {
            D_801EB4D8->command.target = func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target - 1);
        } else {
            D_801EB4D8->command.target = Battle_FindSelectableSlotBackward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target - 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
