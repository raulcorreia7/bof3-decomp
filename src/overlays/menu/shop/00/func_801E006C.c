#include "shop_00.h"

MATCH void func_801E006C(void) {
    s32 input;
    /* FAKE: pin keeps the shared 0xFF constant in a0, so its load schedules before the other constants. */
    FAKE_REG(s32, ff, "a0");

    TEXT_SetVariable(0, 5, g_Characters[D_801E6264[D_801E625C]].name);
    D_80148340 = 0x75;
    if (D_8014839F == 0) {
        D_80148624 = 1;
        D_80148628 = D_801483A0;
        D_80148628 = D_80148628 + 0x2A;
        D_8014862A = D_801483A2 + 7;
    } else {
        D_80148624 = 0;
    }
    input = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if (input & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_801483A9 = 0x32;
        D_801E625C = D_801E625C - 1;
        if (((s8)D_801E625C) < 0) {
            D_801E625C = D_801E6258 - 1;
        }
    } else if (input & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_801483A9 = 0x31;
        D_801E625C += 1;
        if ((D_801E625C) > (D_801E6258 - 1)) {
            D_801E625C = 0;
        }
    }
    D_80148382 = D_801E6264[D_801E625C];
    D_801483A6 = D_801E6264[D_801E625C];
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        SND_PlayCue(EMI_CUE_ID(1, 2));
        input                = 1;
        D_8014839F           = 3;
        D_801483C1           = 7;
        D_801483C2           = 0xB;
        g_BattleMessageState = 2;
        ff                   = 0xFF;
        D_801483A8           = ff;
        D_801483CC           = ff;
        D_8014837B           = input;
        D_801483C0           = input;
        D_801483CA           = 0;
        D_801483CB           = 0;
        D_801483C4           = BATTLE_PARTY_STRIDE;
        D_801483C6           = 0x3E;
        D_801483CD           = 0;
        (*((s8*)(&D_80148652)))++;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_8014837B = 1;
        D_8014839F = 1;
        (*((s8*)(&D_80148651)))--;
    }
}
