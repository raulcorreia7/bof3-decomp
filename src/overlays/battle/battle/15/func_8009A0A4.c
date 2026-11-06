#include "battle_15.h"

MATCH void func_8009A0A4(void) {
    s32          buttons;
    u16          kind_index;
    volatile u8* dest;
    u8           value;

    kind_index = D_80145FAA[BATTLE_ACTIVE_ROW->slot * (BATTLE_PARTY_STRIDE / 2)];
    if (g_InputPressed & D_80145AC4) {
        g_BattleUIState = 4;
        return;
    }
    if (g_InputPressed & D_80145AC2) {
        g_BattleUIState = 3;
        return;
    }
    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if (buttons & (PADLup | PADLdown)) {
        if (Item_GetFlags(kind_index >> 8, kind_index & BYTE_MASK) & 0x80) {
            if (func_8009AF7C() & BYTE_MASK) {
                *D_801EB4D8 = 0;
            } else {
                *D_801EB4D8 = Battle_FindSelectableSlotForward(0);
            }
            dest  = &g_BattleUIState;
            value = *dest + 1;
            *dest = value;
            SND_PlayCue(EMI_CUE_ID(1, 1));
            return;
        }
    }
    if ((buttons & PADLright) != 0) {
        *D_801EB4D8 =
            Battle_FindSelectableSlotForward(func_801DD7D8(g_BattleEnemyCount + 2, 3, (s8)*D_801EB4D8 + 1) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if (buttons & PADLleft) {
        *D_801EB4D8 = Battle_FindSelectableSlotBackward(func_801DD7D8(g_BattleEnemyCount + 2, 3, (s8)*D_801EB4D8 - 1) &
                                                        BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
