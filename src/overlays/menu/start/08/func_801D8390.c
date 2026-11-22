#include "start_08.h"

extern u8 D_80148656;

typedef struct Start08Panel {
    s16 unk_00;
    u8  pad_02[0x10E];
    u8  unk_110;
} Start08Panel;

#ifdef NON_MATCHING
NON_MATCHING void func_801D8390(void) {
    u8* base;
    u8* slot;
    s32 pad;
    s32 count;

    Menu_DrawClutStrip(D_80144953);
    base        = (u8*)&D_801484CC;
    *(s16*)base = 0x17;
    base[0x110] = 1;
    D_801485E7  = 1;
    D_80148624  = 1;
    D_801485E0  = D_801483C4;
    D_801485E2  = D_801483C6 + D_8014857A * 0x36;
    D_80148628  = D_80148574 + 0x2A;
    D_8014862A  = D_80148576 + 7;
    slot        = (u8*)base + 0xA4;
    pad         = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL);
    D_8014857D  = 0xFF;
    count       = Party_CountOrder(PARTY_ORDER_FIELD);
    if (pad & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        D_8014857A--;
        if ((s8)D_8014857A < 0) {
            D_8014857A = count - 1;
        }
    } else if (pad & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        D_8014857A++;
        if ((s32)(count & 0xFF) - 1 < (s32)(u8)D_8014857A) {
            D_8014857A = 0;
        }
    }
    if (pad & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        slot[9] = 0x32;
        slot[0xB]--;
        if ((s8)slot[0xB] < 0) {
            slot[0xB] = 3;
        }
    } else if (pad & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        slot[9] = 0x31;
        slot[0xB]++;
        if ((u8)slot[0xB] >= 4) {
            slot[0xB] = 0;
        }
    }
    D_80148656 = slot[0xA];
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        D_801485DC      = 0;
        D_801485B9      = 6;
        D_801485BA      = 0xF;
        D_801485B8      = 1;
        D_801485BC      = 0x28;
        D_801485BE      = 0x3C;
        g_BattleItemRow = (slot[0xB] == 3) ? 6 : 5;
        D_801485C3      = 0;
        D_80148652++;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801485DC = 0;
        D_80148651 -= 5;
    }
}
#else
INCLUDE_ASM(func_801D8390);
#endif
