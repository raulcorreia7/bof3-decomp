#include "battle_15.h"

/* applies battle-selection cursor input: a held confirm/cancel pair jumps to a selection phase, a flagged
 * secondary-panel entry consumes the 0x5000 triggers, and the D-pad scrolls the active slot with the move cue.
 */
MATCH void func_80098DC4(void) {
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
        if ((Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]) & 0x80u) != 0u) {
            D_801EB4D8->command.target = Battle_FindSelectableSlotForward(3);
            *(u8*)&g_BattleUIState -= 1u;
            SND_PlayCue(EMI_CUE_ID(1, 1));
            return;
        }
    }
    if ((trigger & PADLright) != 0) {
        if ((func_8009AF7C() & BYTE_MASK) != 0u) {
            D_801EB4D8->command.target = func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target + 1);
        } else {
            D_801EB4D8->command.target = Battle_FindSelectableSlotForward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target + 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        if ((func_8009AF7C() & BYTE_MASK) != 0u) {
            D_801EB4D8->command.target = func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target - 1);
        } else {
            D_801EB4D8->command.target = Battle_FindSelectableSlotBackward(
                func_801DD7D8(g_BattlePartyCount - 1, 0, (s8)D_801EB4D8->command.target - 1) & BYTE_MASK);
        }
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
