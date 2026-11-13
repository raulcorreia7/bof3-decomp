#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The shisu overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D80(void) {
    SYS_DISPATCH_BYTE(g_MenuStatusStates, g_MenuStep.step);
}

MATCH void func_801D0DBC(void) {
    func_801D1CA4();
    g_MenuStatusItems.unk_09  = 0;
    g_MenuStatusItems.unk_0A  = 0;
    g_MenuStatusItems.unk_08  = 0;
    g_MenuStatusItems.used[0] = 0;
    g_MenuStatusItems.used[1] = 0;
    g_MenuStatusItems.used[2] = 0;
    g_MenuStatusItems.used[3] = 0;
    g_MenuStatusItems.unk_0B  = func_801D1E60();
    func_801D27BC();
    {
        u8* step = &g_MenuStep.step;
        u8  cur  = *step;

        g_MenuStep.sub_step = 0;
        g_MenuStep.state    = 0;
        *step               = cur + 1;
    }
}

MATCH void func_801D0E4C(void) {
    SYS_DISPATCH_BYTE(g_MenuStatusStep1Funcs, g_MenuStep.sub_step);
}

MATCH void func_801D0E88(void) {
    u8* counter;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    func_801D1D1C();
    counter = &g_MenuStep.sub_step;
    *counter += 1;
}

MATCH void func_801D0EC4(void) {
    Menu_DrawClutStrip(D_80144953);
    if (g_UiWindowEffectBusy == 0) {
        u8* step = &g_MenuStep.step;

        g_MenuStep.sub_step = 0;
        D_80148364          = 0x2B;
        *step += 1;
    }
}

MATCH void func_801D0F24(void) {
    SYS_DISPATCH_BYTE(g_MenuStatusStep3Funcs, g_MenuStep.sub_step);
}

MATCH void func_801D0F60(void) {
    Menu_DrawClutStrip(D_80144953);
    UI_SetMode(2U);
    func_801D1E34();
    {
        u8* step = &g_MenuStep.sub_step;

        *step += 1;
    }
}

MATCH void func_801D0FAC(void) {
    if (g_UiWindowEffectBusy == 0) {
        u8* step = &g_MenuStep.step;

        g_MenuStep.sub_step = 0;
        D_80148354          = 0;
        *D_80148378         = 0;
        D_8014839C          = 0;
        *step += 1;
        return;
    }
    Menu_DrawClutStrip(D_80144953);
}

MATCH void func_801D1018(void) {
    if (g_MenuStatusItems.unk_08 != 0) {
        Item_Remove(ITEM_CAT_ITEM, 0x4DU, g_MenuStatusItems.used[0], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x23U, g_MenuStatusItems.used[1], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x24U, g_MenuStatusItems.used[2], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x56U, g_MenuStatusItems.used[3], 0);
        g_SceneState.step_05 = 0x14;
        func_801D1EE8();
        if (D_801DA044 >= 0x33) {
            g_ScriptVars[3] = 2;
            if (D_801DA044 < 0x5A) {
                D_80144E5E = 0;
            } else if (D_801DA044 < 0x78) {
                D_80144E5E = 1;
            } else if (D_801DA044 < 0x96) {
                D_80144E5E = 2;
            } else if (D_801DA044 < 0xAA) {
                D_80144E5E = 3;
            } else if (D_801DA044 < 0xB4) {
                D_80144E5E = 4;
            } else {
                D_80144E5E = 5;
            }
        } else {
            g_ScriptVars[3] = 1;
        }
    } else {
        g_SceneState.step_05 = 5;
    }
    Menu_ResetPanelTasks();
    {
        u16* sub = &g_GameEntrySubstate;

        *sub += 1;
    }
}

MATCH void func_801D11A4(void) {
    Menu_DrawClutStrip(D_80144953);
    g_MenuStatusStep2Funcs[g_MenuStep.sub_step]();
}

INCLUDE_ASM(func_801D11F4);

INCLUDE_ASM(func_801D14C0);

MATCH void func_801D1898(void) {
    Callback handler;

    handler = g_MenuStatusStep2Sub2Funcs[g_MenuStep.state];
    handler();
    func_801D2C0C();
    func_801D2DA8();
}

/* func_801D18E4 */
MATCH void Menu_SetState(void) {
    u8* count;
    u8  value;

    count      = &g_MenuStep.state;
    value      = *count;
    D_801DA0C1 = 2;
    D_801DA049 = 2;
    *count     = value + 1;
}

MATCH void func_801D1910(void) {
    if ((D_801DA0C6 != 0) && (D_801DA04E != 0)) {
        D_801DA0C1 = 3;
        D_801DA049 = 3;
        {
            u8* step = &g_MenuStep.state;

            *step += 1;
        }
    }
}

INCLUDE_ASM(func_801D1964);

INCLUDE_ASM(func_801D1A20);

INCLUDE_ASM(func_801D1B58);

MATCH void func_801D1CA4(void) {
    g_MenuStatusItems.held[0] = Item_Count(ITEM_CAT_ITEM, ITEM_MACKEREL, 0);
    g_MenuStatusItems.held[1] = Item_Count(ITEM_CAT_ITEM, ITEM_SHALY_SEED, 0);
    g_MenuStatusItems.held[2] = Item_Count(ITEM_CAT_ITEM, ITEM_VINEGAR, 0);
    g_MenuStatusItems.held[3] = Item_Count(ITEM_CAT_ITEM, ITEM_HORSERADISH, 0);
}

INCLUDE_ASM(func_801D1D1C);

MATCH void func_801D1E34(void) {
    FIELD(u8, g_MenuPanelTasks, 0x0) = 0;
    D_80148357                       = 1;
    D_8014837B                       = 1;
    D_8014839F                       = 1;
}

MATCH s32 func_801D1E60(void) {
    u32 value = D_80144FF9;

    if (value < 0x26) {
        return 9;
    }
    if (value - 0x26 < 2) {
        return 10;
    }
    if (value - 0x28 < 5) {
        return 11;
    }
    if (value - 0x2D < 5) {
        return 12;
    }
    if (value - 0x32 < 10) {
        return 13;
    }
    if (value - 0x3C < 5) {
        return 14;
    }
    if (value - 0x41 < 3) {
        return 15;
    }
    return 16;
}

INCLUDE_ASM(func_801D1EE8);

INCLUDE_ASM(func_801D2308);

INCLUDE_ASM(func_801D27BC);

INCLUDE_ASM(func_801D2978);
