#include "shop_00.h"

MATCH void func_801E006C(void) {
    s32 input;
    /* FAKE: pin keeps the shared 0xFF constant in a0, so its load schedules before the other constants. */
    FAKE_REG(s32, ff, "a0");

    UI_MessageSetVariable(0, 5, g_Characters[D_801E6264[D_801E625C]].name);
    D_80148340 = 0x75;
    if (g_UIPanelTasks[3].state == 0) {
        g_UIPanelTasks[21].active = 1;
        g_UIPanelTasks[21].pos.vx = g_UIPanelTasks[3].pos.vx;
        g_UIPanelTasks[21].pos.vx = g_UIPanelTasks[21].pos.vx + 0x2A;
        g_UIPanelTasks[21].pos.vy = g_UIPanelTasks[3].pos.vy + 7;
    } else {
        g_UIPanelTasks[21].active = 0;
    }
    input = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if (input & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[3].flags = 0x32;
        D_801E625C              = D_801E625C - 1;
        if (((s8)D_801E625C) < 0) {
            D_801E625C = D_801E6258 - 1;
        }
    } else if (input & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[3].flags = 0x31;
        D_801E625C += 1;
        if ((D_801E625C) > (D_801E6258 - 1)) {
            D_801E625C = 0;
        }
    }
    g_UIPanelTasks[2].unk_0A = D_801E6264[D_801E625C];
    g_UIPanelTasks[3].unk_0A = D_801E6264[D_801E625C];
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        input                    = 1;
        g_UIPanelTasks[3].state  = 3;
        g_UIPanelTasks[4].panel  = 7;
        g_UIPanelTasks[4].mode   = 0xB;
        g_BattleMessageState     = 2;
        ff                       = 0xFF;
        g_UIPanelTasks[3].unk_0C = ff;
        g_UIPanelTasks[4].unk_0C = ff;
        g_UIPanelTasks[2].state  = input;
        g_UIPanelTasks[4].active = input;
        g_UIPanelTasks[4].unk_0A = 0;
        g_UIPanelTasks[4].unk_0B = 0;
        g_UIPanelTasks[4].pos.vx = BATTLE_PARTY_STRIDE;
        g_UIPanelTasks[4].pos.vy = 0x3E;
        g_UIPanelTasks[4].flags  = 0;
        (*((s8*)(&g_MenuStep.state)))++;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UIPanelTasks[2].state = 1;
        g_UIPanelTasks[3].state = 1;
        (*((s8*)(&g_MenuStep.sub_step)))--;
    }
}
