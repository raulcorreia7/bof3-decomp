#include "shop_00.h"

/* File-local declarations: the shop message panel fields and the pad halfwords
 * are not declared by this target's shop_00.h. */

MATCH void func_801E2474(void) {
    u8* counter;
    u8  count;

    D_80148340               = g_UiPanelTasks[1].flags + 0x122;
    g_UiPanelTasks[1].unk_0C = g_UiPanelTasks[1].unk_0B;

    counter = &D_80148654;
    count   = *counter;
    if (count != 0) {
        *counter = count - 1;
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        g_UiPanelTasks[1].state  = 2;
        g_UiPanelTasks[2].state  = 1;
        g_UiPanelTasks[3].state  = 1;
        g_UiPanelTasks[1].unk_0C = 0x7F;
        *counter                 = 8;
        D_80148652++;
    }
}
