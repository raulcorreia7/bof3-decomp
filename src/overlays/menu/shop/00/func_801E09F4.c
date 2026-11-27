#include "shop_00.h"

MATCH void func_801E09F4(void) {
    s32 raw;
    s32 buttons;
    u16 sum;
    u8  count;
    u8* flag;
    u8  count2;
    u8* flag2;

    D_80148340                = 0x18;
    g_UiPanelTasks[21].pos.vx = g_UiPanelTasks[5].pos.vx + 5;
    sum                       = (g_UiPanelTasks[5].unk_0A << 4) + 0x1A;
    g_UiPanelTasks[21].pos.vy = g_UiPanelTasks[5].pos.vy + sum;
    buttons                   = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    if (buttons & PADLup) {
        u8 next;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        next                     = g_UiPanelTasks[5].unk_0A - 1;
        g_UiPanelTasks[5].unk_0A = next;
        if ((s8)next < 0) {
            g_UiPanelTasks[5].unk_0A = 2;
        }
    } else if (buttons & PADLdown) {
        u8 next;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        next                     = g_UiPanelTasks[5].unk_0A + 1;
        g_UiPanelTasks[5].unk_0A = next;
        if ((next & BYTE_MASK) >= 3U) {
            g_UiPanelTasks[5].unk_0A = 0;
        }
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        raw = g_UiPanelTasks[5].unk_0A & BYTE_MASK;
        if (raw == 0) {
            flag                     = &g_MenuStep.state;
            count                    = *flag;
            g_UiPanelTasks[5].unk_0B = g_UiPanelTasks[5].unk_0A;
            *flag                    = count + 1;
            return;
        }
        Menu_RunAbilityStockSort(raw);
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        flag2                    = &g_MenuStep.sub_step;
        g_UiPanelTasks[5].active = 0;
        count2                   = *flag2;
        g_BattleMessageState     = 4;
        *flag2                   = count2 - 2;
    }
}
