#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The bate overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D9C(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStates, D_80148650);
}

MATCH void func_801D0DD8(void) {
    D_80148651 = 0;
    D_80148652 = 0;
    D_80148650 = D_8018E244 + 2;
}

MATCH void func_801D0E04(void) {
    u16* count;

    Menu_ResetPanelTasks();
    count = &g_GameEntrySubstate;
    *count += 1;
}

MATCH void func_801D0E38(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Funcs, D_80148651);
}

MATCH void func_801D0E74(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub0Funcs, D_80148652);
}

MATCH void func_801D0EB0(void) {
    u8* count;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    count = &D_80148652;
    *count += 1;
}

INCLUDE_ASM(func_801D0EE4);

MATCH void func_801D0F70(void) {
    u8* timer;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        D_801D8ED4.unk_00 = 0;
        D_801D8ED4.unk_04 = 1;
        D_801D8ED4.unk_08 = 0;
        D_80148652        = 0;
        D_80148659        = 0;
        D_80148651 += 1;
    }
}

MATCH void func_801D0FF8(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub1Funcs, D_80148652);
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
    pressed    = PAD_GetRepeatedButtons(g_InputPressed & 0xF000) & 0x5000;
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
        step       = &D_80148652;
        D_8014833B = D_8014833A->kind_00;
        D_8014835F = D_8014835E;
        (*step)++;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        *D_80148333 = 1;
        D_80148357  = 1;
        D_8014837B  = 1;
        D_8014839F  = 1;
        D_801483C0  = 0;
        D_80148624  = 0;
        D_80148654  = 5;
        D_80148652  = 0;
        D_80148651 += 1;
    }
}
