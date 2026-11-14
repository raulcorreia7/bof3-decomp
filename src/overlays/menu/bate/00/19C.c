#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The bate overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D9C(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStates, g_MenuStep.step);
}

MATCH void func_801D0DD8(void) {
    g_MenuStep.sub_step = 0;
    g_MenuStep.state    = 0;
    g_MenuStep.step     = D_8018E244 + 2;
}

/* func_801D0E04 */
MATCH void Menu_ResetPanels(void) {
    u16* count;

    Menu_ResetPanelTasks();
    count = &g_GameEntrySubstate;
    *count += 1;
}

MATCH void func_801D0E38(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Funcs, g_MenuStep.sub_step);
}

MATCH void func_801D0E74(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub0Funcs, g_MenuStep.state);
}

/* func_801D0EB0 */
MATCH void Menu_StartFadeIn(void) {
    u8* count;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    count = &g_MenuStep.state;
    *count += 1;
}

MATCH void func_801D0EE4(void) {
    u8* base = &D_80144953;
    Menu_DrawClutStrip(*base);
    if (g_UiWindowEffectBusy != 0) {
        return;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    func_801D1C90();
    D_80148654 = 4;
    D_80148652++;
    strncpy((char*)(base + 0x491), (char*)D_801D86F8, 5);
}

MATCH void func_801D0F70(void) {
    u8* timer;

    Menu_DrawClutStrip(D_80144953);
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
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub1Funcs, g_MenuStep.state);
    Menu_DrawClutStrip(D_80144953);
}

MATCH void func_801D1044(void) {
    s32 pressed;
    u8* item;
    u8* step;
    s32 category;

    D_801483C0 = 1;
    D_801483C4 = D_80148358 + 6;
    D_801483C6 = D_8014835A + (D_8014835E * 13 + 0x57);
    pressed    = INPUT_GetRepeatedButtons(g_InputPressed & 0xF000) & 0x5000;
    D_8014835F = 0xFF;
    D_80148361 = 1;
    if (pressed != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
        D_8014835E ^= 3;
    }
    D_80148339 = D_8014835E;
    if (D_8014835E == 0 || D_8014835E != 3) {
        item     = &D_80144DF2;
        category = 1;
    } else {
        item     = &D_80144DF5;
        category = 2;
    }
    D_80148388 = Item_GetDescription(category, *item);
    D_801483AC = 0xDC;
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x03));
        step       = &g_MenuStep.state;
        D_8014833B = D_8014833A->kind_00;
        D_8014835F = D_8014835E;
        (*step)++;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        *D_80148333      = 1;
        D_80148357       = 1;
        D_8014837B       = 1;
        D_8014839F       = 1;
        D_801483C0       = 0;
        D_80148624       = 0;
        D_80148654       = 5;
        g_MenuStep.state = 0;
        g_MenuStep.sub_step += 1;
    }
}
