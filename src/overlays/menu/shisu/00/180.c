#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The shisu overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D80(void) {
    SYS_DISPATCH_BYTE(D_801D96DC, D_80148650);
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
        u8* step = &D_80148650;
        u8  cur  = *step;

        D_80148651 = 0;
        D_80148652 = 0;
        *step      = cur + 1;
    }
}

MATCH void func_801D0E4C(void) {
    SYS_DISPATCH_BYTE(D_801D96F0, D_80148651);
}

MATCH void func_801D0E88(void) {
    u8* counter;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    func_801D1D1C();
    counter = &D_80148651;
    *counter += 1;
}

MATCH void func_801D0EC4(void) {
    func_801D7224(D_80144953);
    if (g_UiWindowEffectBusy == 0) {
        u8* step = &D_80148650;

        D_80148651 = 0;
        D_80148364 = 0x2B;
        *step += 1;
    }
}

MATCH void func_801D0F24(void) {
    SYS_DISPATCH_BYTE(D_801D96F8, D_80148651);
}

MATCH void func_801D0F60(void) {
    func_801D7224(D_80144953);
    UI_SetMode(2U);
    func_801D1E34();
    {
        u8* step = &D_80148651;

        *step += 1;
    }
}

MATCH void func_801D0FAC(void) {
    if (g_UiWindowEffectBusy == 0) {
        u8* step = &D_80148650;

        D_80148651  = 0;
        D_80148354  = 0;
        *D_80148378 = 0;
        D_8014839C  = 0;
        *step += 1;
        return;
    }
    func_801D7224(D_80144953);
}

MATCH void func_801D1018(void) {
    if (g_MenuStatusItems.unk_08 != 0) {
        Item_Remove(ITEM_CAT_ITEM, 0x4DU, g_MenuStatusItems.used[0], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x23U, g_MenuStatusItems.used[1], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x24U, g_MenuStatusItems.used[2], 0);
        Item_Remove(ITEM_CAT_ITEM, 0x56U, g_MenuStatusItems.used[3], 0);
        D_80146875 = 0x14;
        func_801D1EE8();
        if (D_801DA044 >= 0x33) {
            D_80146867 = 2;
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
            D_80146867 = 1;
        }
    } else {
        D_80146875 = 5;
    }
    Menu_ResetPanelTasks();
    {
        u16* sub = &g_GameEntrySubstate;

        *sub += 1;
    }
}

MATCH void func_801D11A4(void) {
    func_801D7224(D_80144953);
    D_801D9700[D_80148651]();
}

INCLUDE_ASM(func_801D11F4);

INCLUDE_ASM(func_801D14C0);

MATCH void func_801D1898(void) {
    Callback handler;

    handler = D_801D970C[D_80148652];
    handler();
    func_801D2C0C();
    func_801D2DA8();
}

MATCH void func_801D18E4(void) {
    u8* count;
    u8  value;

    count      = &D_80148652;
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
            u8* step = &D_80148652;

            *step += 1;
        }
    }
}

/* blocker: late loads of D_80148652 and D_801DA0A7 sources. */
INCLUDE_ASM(func_801D1964);

INCLUDE_ASM(func_801D1A20);

INCLUDE_ASM(func_801D1B58);

MATCH void func_801D1CA4(void) {
    g_MenuStatusItems.held[0] = Item_Count(ITEM_CAT_ITEM, ITEM_MACKEREL, 0);
    g_MenuStatusItems.held[1] = Item_Count(ITEM_CAT_ITEM, ITEM_SHALY_SEED, 0);
    g_MenuStatusItems.held[2] = Item_Count(ITEM_CAT_ITEM, ITEM_VINEGAR, 0);
    g_MenuStatusItems.held[3] = Item_Count(ITEM_CAT_ITEM, ITEM_HORSERADISH, 0);
}

/* blocker: store constant order; first diff: +0x00 li v0,20. */
INCLUDE_ASM(func_801D1D1C);

MATCH void func_801D1E34(void) {
    FIELD(u8, g_MenuPanelTasks, 0) = 0;
    D_80148357                     = 1;
    D_8014837B                     = 1;
    D_8014839F                     = 1;
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
