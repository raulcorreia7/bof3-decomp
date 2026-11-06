#include "battle_15.h"

MATCH void func_80098C18(void) {
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
            if (func_8009AF7C() != 0u) {
                D_801EB4D8[0] = 0u;
            } else {
                D_801EB4D8[0] = Battle_FindSelectableSlotForward(0);
            }
            /* FAKE: byte pointer access keeps the address in a register so the
             * store merges into the shared SND_PlayCue delay slot. */
            *(u8*)&g_BattleUIState += 1;
            SND_PlayCue(EMI_CUE_ID(1, 1));
            return;
        }
    }
    if ((trigger & PADLright) != 0) {
        D_801EB4D8[0] = Battle_FindSelectableSlotForward(
            func_801DD7D8(g_BattleEnemyCount + 2, 3, ((s8*)D_801EB4D8)[0] + 1) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if ((trigger & PADLleft) != 0) {
        D_801EB4D8[0] = Battle_FindSelectableSlotBackward(
            func_801DD7D8(g_BattleEnemyCount + 2, 3, ((s8*)D_801EB4D8)[0] - 1) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
