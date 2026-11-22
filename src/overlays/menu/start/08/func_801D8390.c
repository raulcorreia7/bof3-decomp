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

    Menu_DrawClutStrip(g_WindowClut);
    base                      = (u8*)&D_801484CC;
    *(s16*)base               = 0x17;
    base[0x110]               = 1;
    g_UiPanelTasks[19].unk_0B = 1;
    g_UiPanelTasks[21].active = 1;
    D_801485E0                = g_UiPanelTasks[4].pos.x;
    D_801485E2                = g_UiPanelTasks[4].pos.y + g_UiPanelTasks[16].unk_0A * 0x36;
    D_80148628                = D_80148574 + 0x2A;
    D_8014862A                = D_80148576 + 7;
    slot                      = (u8*)base + 0xA4;
    pad                       = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL);
    g_UiPanelTasks[16].flags  = 0xFF;
    count                     = Party_CountOrder(PARTY_ORDER_FIELD);
    if (pad & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[16].unk_0A--;
        if ((s8)g_UiPanelTasks[16].unk_0A < 0) {
            g_UiPanelTasks[16].unk_0A = count - 1;
        }
    } else if (pad & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[16].unk_0A++;
        if ((s32)(count & 0xFF) - 1 < (s32)(u8)g_UiPanelTasks[16].unk_0A) {
            g_UiPanelTasks[16].unk_0A = 0;
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
        D_801485DC                = 0;
        D_801485B9                = 6;
        D_801485BA                = 0xF;
        D_801485B8                = 1;
        D_801485BC                = 0x28;
        D_801485BE                = 0x3C;
        g_BattleEquipSlot         = (slot[0xB] == 3) ? 6 : 5;
        g_UiPanelTasks[18].unk_0B = 0;
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
