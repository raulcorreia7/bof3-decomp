#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The bate overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D9C(void) {
    SYS_DISPATCH_BYTE(g_MenuBateSteps, g_MenuStep.step);
}

MATCH void func_801D0DD8(void) {
    g_MenuStep.sub_step = 0;
    g_MenuStep.state    = 0;
    g_MenuStep.step     = D_8018E244 + 2;
}

/* func_801D0E04 */
MATCH void Menu_ResetPanels(void) {
    u16* count;

    UI_PanelResetTasks();
    count = &g_GameEntrySubstate;
    *count += 1;
}

MATCH void func_801D0E38(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Steps, g_MenuStep.sub_step);
}

MATCH void func_801D0E74(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub0Steps, g_MenuStep.state);
}

/* func_801D0EB0 */
MATCH void Menu_StartFadeIn(void) {
    u8* count;

    UI_ModeSet(UI_MODE_FAST_FADE_IN);
    count = &g_MenuStep.state;
    *count += 1;
}

MATCH void func_801D0EE4(void) {
    u8* base = &g_WindowClut;
    Menu_DrawClutStrip(*base);
    if (g_SysThreads[2].state != 0) {
        return;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    func_801D1C90();
    D_80148654 = 4;
    D_80148652++;
    strncpy((char*)(base + 0x491), (char*)D_801D86F8, 5);
}

MATCH void func_801D0F70(void) {
    u8* timer;

    Menu_DrawClutStrip(g_WindowClut);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        D_801D8ED4.unk_00 = 0;
        D_801D8ED4.unk_04 = 1;
        D_801D8ED4.unk_08 = 0;
        g_MenuStep.state  = 0;
        D_80148659        = 0;
        g_MenuStep.sub_step += 1;
    }
}

MATCH void func_801D0FF8(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub1Steps, g_MenuStep.state);
    Menu_DrawClutStrip(g_WindowClut);
}

MATCH void func_801D1044(void) {
    s32 pressed;
    u8* item;
    u8* step;
    s32 category;

    g_UiPanelTasks[4].active = 1;
    g_UiPanelTasks[4].pos.vx = D_80148358 + 6;
    g_UiPanelTasks[4].pos.vy = (u16)(D_8014835A + (g_UiPanelTasks[1].unk_0A * 13 + 0x57));
    pressed                  = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL) & (PADLup | PADLdown);
    g_UiPanelTasks[1].unk_0B = 0xFF;
    g_UiPanelTasks[1].flags  = 1;
    if (pressed != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x01));
        g_UiPanelTasks[1].unk_0A ^= 3;
    }
    g_UiPanelTasks[0].unk_09 = g_UiPanelTasks[1].unk_0A;
    if (g_UiPanelTasks[1].unk_0A == 0 || g_UiPanelTasks[1].unk_0A != 3) {
        item     = &g_Characters[7].equip.weapon;
        category = 1;
    } else {
        item     = &g_Characters[7].equip.armor;
        category = 2;
    }
    D_80148388 = Item_GetDescription(category, *item);
    D_801483AC = 0xDC;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x03));
        step                     = &g_MenuStep.state;
        g_UiPanelTasks[0].unk_0B = D_8014833A->type;
        g_UiPanelTasks[1].unk_0B = g_UiPanelTasks[1].unk_0A;
        (*step)++;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x06));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x02));
        g_UiPanelTasks[0].state   = 1;
        g_UiPanelTasks[1].state   = 1;
        g_UiPanelTasks[2].state   = 1;
        g_UiPanelTasks[3].state   = 1;
        g_UiPanelTasks[4].active  = 0;
        g_UiPanelTasks[21].active = 0;
        D_80148654                = 5;
        g_MenuStep.state          = 0;
        g_MenuStep.sub_step += 1;
    }
}
