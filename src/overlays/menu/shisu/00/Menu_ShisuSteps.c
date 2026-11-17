#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The shisu overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D80(void) {
    SYS_DISPATCH_BYTE(g_ShisuSteps, g_MenuStep.step);
}

MATCH void func_801D0DBC(void) {
    func_801D1CA4();
    g_ShisuIngredients.command      = 0;
    g_ShisuIngredients.cursor       = 0;
    g_ShisuIngredients.rounds       = 0;
    g_ShisuIngredients.used[0]      = 0;
    g_ShisuIngredients.used[1]      = 0;
    g_ShisuIngredients.used[2]      = 0;
    g_ShisuIngredients.used[3]      = 0;
    g_ShisuIngredients.topping_size = func_801D1E60();
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
    SYS_DISPATCH_BYTE(g_ShisuStep1Steps, g_MenuStep.sub_step);
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
    SYS_DISPATCH_BYTE(g_ShisuStep3Steps, g_MenuStep.sub_step);
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
    if (g_ShisuIngredients.rounds != 0) {
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_MACKEREL, g_ShisuIngredients.used[0], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_SHALY_SEED, g_ShisuIngredients.used[1], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_VINEGAR, g_ShisuIngredients.used[2], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_HORSERADISH, g_ShisuIngredients.used[3], 0);
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
    g_ShisuStep2Steps[g_MenuStep.sub_step]();
}

/* Reads the command row input: left and right flip mix or leave, up and down open the ingredient list. */
MATCH void func_801D11F4(void) {
    u16* input;
    u8*  step;
    u8   cur;
    u16  buttons;

    input   = &g_InputPressed;
    buttons = INPUT_REPEATED(*input, INPUT_DIRECTIONAL);
    if (buttons & (PADLright | PADLleft)) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
        g_ShisuIngredients.command ^= 1;
        D_80148364 = g_ShisuIngredients.command + 0x2B;
    } else if (buttons & PADLup) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148364                = 0x2A;
        g_ShisuIngredients.cursor = 3;
        g_MenuStep.sub_step++;
    } else if (buttons & PADLdown) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148364                = 0x2A;
        g_ShisuIngredients.cursor = 0;
        g_MenuStep.sub_step++;
    } else if (*input & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_ShisuIngredients.command != 0) {
            goto advance;
        }
        if (g_ShisuIngredients.rounds < 8) {
            if (g_ShisuIngredients.rounds == 0) {
                if (g_ShisuIngredients.used[0] != 0 && g_ShisuIngredients.used[1] != 0) {
                    SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 3));
                    g_MenuStep.sub_step += 2;
                    g_MenuStep.state = g_MenuStep.state; /* FAKE: retail reloads and stores state. */
                } else {
                    SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 7));
                    D_80148364 = 0x31;
                }
            } else {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 3));
                g_ShisuIngredients.rounds++;
            }
        } else {
            SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
    } else if (*input & g_InputMasks[MENU_INPUT_CANCEL]) {
    advance:
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 3));
        step                       = &g_MenuStep.step;
        cur                        = *step;
        g_MenuPanelTasks[0].active = 0;
        g_MenuStep.sub_step        = 0;
        *step                      = cur + 1;
    }

    g_MenuPanelTasks[0].active = 1;
    D_80148334                 = D_8014837C + g_ShisuIngredients.command * 48;
    D_80148336                 = D_8014837E + 4;
    if (g_ShisuIngredients.rounds != 0) {
        D_801DA0FC = D_801DA084 + g_ShisuBaseScale * 0xA00;
    }
    func_801D2C0C();
    func_801D2DA8();
}

INCLUDE_ASM(func_801D14C0);

MATCH void func_801D1898(void) {
    Callback handler;

    handler = g_ShisuStep2Sub2Steps[g_MenuStep.state];
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

#ifdef NON_MATCHING
/* Copies the equipped item's status values onto the equip list's title row. */
NON_MATCHING void func_801D1964(void) {
    if ((D_801DA0C6 != 0) && (D_801DA04E != 0)) {
        D_801D9EF0[0] = g_ShisuToppingR;
        D_801D9EF0[1] = g_ShisuToppingG;
        D_801D9EF0[2] = g_ShisuToppingB;
        D_801D9EF0[4] = g_ShisuBaseR;
        D_801D9EF0[5] = g_ShisuBaseG;
        D_801D9EF0[6] = g_ShisuBaseB;
        D_801DA0C1    = 4;
        D_801DA049    = 4;
        D_80148654    = 0;
        D_80148652 += 1;
    }
}
#else
INCLUDE_ASM(func_801D1964);
#endif

#ifdef NON_MATCHING
/* Fades the six tint channels up to the fade level. */
NON_MATCHING void func_801D1A20(void) {
    u8* fade;
    s32 level;
    u16 value0;
    u16 value1;
    u16 value2;
    u16 value3;
    u16 value4;
    u16 value5;

    fade   = &D_80148654;
    level  = *fade;
    value0 = D_801D9EF0[0];
    if (value0 < (u8)level) {
        value0 = level;
    }
    g_ShisuToppingR = value0;
    value1          = D_801D9EF0[1];
    if (value1 < (u8)level) {
        value1 = level;
    }
    g_ShisuToppingG = value1;
    value2          = D_801D9EF0[2];
    if (value2 < (u8)level) {
        value2 = level;
    }
    g_ShisuToppingB = value2;
    value3          = D_801D9EF0[4];
    if (value3 < (u8)level) {
        value3 = level;
    }
    g_ShisuBaseR = value3;
    value4       = D_801D9EF0[5];
    if (value4 < (u8)level) {
        value4 = level;
    }
    g_ShisuBaseG = value4;
    value5       = D_801D9EF0[6];
    if (value5 < (u8)level) {
        value5 = level;
    }
    g_ShisuBaseB = value5;
    if ((u8)level == 0x80) {
        SND_PlaySE(0x200);
    }
    *fade = *fade + 8;
    if (*fade == 0) {
        *fade = 0xF8;
        D_80148652 += 1;
    }
}
#else
INCLUDE_ASM(func_801D1A20);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D1B58(void) {
    u8* fade;
    u8  level;
    u8  value0;
    u8  value1;
    u8  value2;
    u8  value3;
    u8  value4;
    u8  value5;

    fade  = &D_80148654;
    level = *fade;

    value0 = D_801D9EF0[0];
    if (value0 < level) {
        value0 = level;
    }
    g_ShisuToppingR = value0;
    value1          = D_801D9EF0[1];
    if (value1 < level) {
        value1 = level;
    }
    g_ShisuToppingG = value1;
    value2          = D_801D9EF0[2];
    if (value2 < level) {
        value2 = level;
    }
    g_ShisuToppingB = value2;
    value3          = D_801D9EF0[4];
    if (value3 < level) {
        value3 = level;
    }
    g_ShisuBaseR = value3;
    value4       = D_801D9EF0[5];
    if (value4 < level) {
        value4 = level;
    }
    g_ShisuBaseG = value4;
    value5       = D_801D9EF0[6];
    if (value5 < level) {
        value5 = level;
    }
    g_ShisuBaseB = value5;

    level -= 8;
    *fade = level;
    if ((u8)level == 0) {
        D_801DA0C1      = 5;
        D_801DA049      = 1;
        D_80148652      = 0;
        g_ShisuToppingR = D_801D9EF0[0];
        g_ShisuToppingG = D_801D9EF0[1];
        g_ShisuToppingB = D_801D9EF0[2];
        g_ShisuBaseR    = D_801D9EF0[4];
        g_ShisuBaseG    = D_801D9EF0[5];
        g_ShisuBaseB    = D_801D9EF0[6];
        g_ShisuIngredients.rounds += 1;
        D_80148651 -= 2;
    }
}
#else
INCLUDE_ASM(func_801D1B58);
#endif

MATCH void func_801D1CA4(void) {
    g_ShisuIngredients.held[0] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_MACKEREL, 0);
    g_ShisuIngredients.held[1] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_SHALY_SEED, 0);
    g_ShisuIngredients.held[2] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_VINEGAR, 0);
    g_ShisuIngredients.held[3] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_HORSERADISH, 0);
}

#ifdef NON_MATCHING
/* Places the four shisu panels and points the ingredient list at the item counts. */
NON_MATCHING void func_801D1D1C(void) {
    g_MenuPanelTasks[1].pos.x      = 0x14;
    g_MenuPanelTasks[2].pos.x      = 0x70;
    LOH(g_MenuPanelTasks[1].pos.y) = -0x64;
    LOH(g_MenuPanelTasks[2].pos.y) = -0x64;
    g_MenuPanelTasks[2].unk_0A     = 8;
    g_MenuPanelTasks[3].mode       = 3;
    LOH(g_MenuPanelTasks[3].pos.x) = -0x78;
    g_MenuPanelTasks[3].pos.y      = 0x3F;
    g_MenuPanelTasks[0].active     = 0;
    g_MenuPanelTasks[0].panel      = 1;
    g_MenuPanelTasks[0].mode       = 0;
    g_MenuPanelTasks[0].state      = 2;
    g_MenuPanelTasks[0].pos.x      = 0;
    g_MenuPanelTasks[0].pos.y      = 0;
    g_MenuPanelTasks[1].active     = 1;
    g_MenuPanelTasks[1].panel      = 1;
    g_MenuPanelTasks[1].mode       = 1;
    g_MenuPanelTasks[1].state      = 2;
    g_MenuPanelTasks[2].active     = 1;
    g_MenuPanelTasks[2].panel      = 1;
    g_MenuPanelTasks[2].mode       = 2;
    g_MenuPanelTasks[2].state      = 2;
    g_MenuPanelTasks[2].unk_0B     = 0xFF;
    g_MenuPanelTasks[3].active     = 1;
    g_MenuPanelTasks[3].panel      = 1;
    g_MenuPanelTasks[3].state      = 2;
    g_MenuPanelTasks[3].unk_0A     = 0xFF;
    g_MenuPanelTasks[3].item_table = (s32)&g_ShisuIngredients;
}
#else
INCLUDE_ASM(func_801D1D1C);
#endif

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

#ifdef NON_MATCHING
NON_MATCHING void func_801D1EE8(void) {
    s32 denominator;
    s32 difference;
    s32 numerator;
    s32 scaled_difference;
    s32 subtotal;
    s32 total;

    denominator       = g_ShisuIngredients.topping_size * 4;
    difference        = g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds;
    scaled_difference = difference * 5;
    if (denominator == 0) {
        D_801DA034 = 0;
    } else if (denominator - scaled_difference > 0) {
        numerator  = scaled_difference * 100;
        D_801DA034 = numerator / denominator;
    } else {
        numerator  = scaled_difference * 100;
        D_801DA034 = 200 - (numerator / denominator);
    }
    if (D_801DA034 < 0) {
        D_801DA034 = 0;
    }

    denominator       = g_ShisuIngredients.used[1];
    scaled_difference = g_ShisuIngredients.used[2] * 4;
    if (denominator == 0) {
        D_801DA038 = 0;
    } else if (denominator - scaled_difference > 0) {
        numerator  = scaled_difference * 100;
        D_801DA038 = numerator / denominator;
    } else {
        numerator  = scaled_difference * 100;
        D_801DA038 = 200 - (numerator / denominator);
    }
    if (D_801DA038 < 0) {
        D_801DA038 = 0;
    }

    if ((2 - g_ShisuIngredients.rounds) > 0) {
        D_801DA03C = (g_ShisuIngredients.rounds * 25) + 50;
    } else {
        D_801DA03C = 150 - (g_ShisuIngredients.rounds * 25);
    }
    if (D_801DA03C < 0) {
        D_801DA03C = 0;
    }

    denominator = g_ShisuIngredients.topping_size + g_ShisuIngredients.used[2];
    difference  = (g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds) + g_ShisuIngredients.used[3];
    if (denominator == 0) {
        D_801DA040 = 0;
    } else if ((denominator - difference) > 0) {
        D_801DA040 = (difference * 100) / denominator;
    } else {
        D_801DA040 = 200 - ((difference * 100) / denominator);
    }
    if (D_801DA040 < 0) {
        D_801DA040 = 0;
    }

    subtotal   = g_ShisuIngredients.topping_size * (D_801DA034 * 10);
    total      = subtotal + (g_ShisuIngredients.rounds * ((D_801DA038 * D_801DA03C) / 100));
    D_801DA044 = 0;
    D_801DA044 = subtotal;
    D_801DA044 = total;
    total      = (total + (D_801DA040 * 0x10)) / 100;
    D_801DA044 = total;
}
#else
INCLUDE_ASM(func_801D1EE8);
#endif

INCLUDE_ASM(func_801D2308);

#ifdef NON_MATCHING
NON_MATCHING void func_801D27BC(void) {
    s32** record_cell;
    s32*  scroll_x;
    s32*  scroll_y;
    s32*  record;
    s32*  next_record;
    s32   x;
    s32   y;
    s32   height;
    s32   bias;
    s8    initial;

    record_cell = &D_801F501C;
    x           = g_AreaScrollTargetX;
    scroll_x    = &g_AreaScrollTargetX;
    scroll_y    = &g_AreaScrollTargetY;
    bias        = 0x1000;
    record      = *record_cell;
    D_801DA09C  = record;
    record      = D_801DA09C;
    y           = *scroll_y;
    D_801DA098  = record[1];

    D_801DA049       = 0;
    D_801DA090       = 0;
    g_ShisuBaseScale = bias;
    D_801DA0AC       = 0;
    D_801DA0B0       = 0;
    g_ShisuBaseAngle = 0;
    initial          = -0x80;
    g_ShisuBaseR     = initial;
    g_ShisuBaseG     = initial;
    g_ShisuBaseB     = initial;
    D_801DA07C       = *scroll_x;
    D_801DA080       = y;
    height           = Area_SampleHeight(x, y);
    D_801DA084       = (height << 16) - SHISU_HEIGHT_BIAS;

    record              = *record_cell;
    D_801DA114          = record + 2;
    next_record         = D_801DA114;
    D_801DA0C1          = 0;
    D_801DA108          = 0;
    g_ShisuToppingScale = bias;
    D_801DA124          = 0;
    D_801DA128          = 0;
    g_ShisuToppingAngle = 0;
    g_ShisuToppingR     = initial;
    g_ShisuToppingG     = initial;
    g_ShisuToppingB     = initial;
    D_801DA0F4          = *scroll_x;
    D_801DA0F8          = *scroll_y;
    D_801DA110          = next_record[1];
    height              = Area_SampleHeight(*scroll_x, *scroll_y);
    D_801DA0FC          = (height << 16) + SHISU_HEIGHT_BIAS;
}
#else
INCLUDE_ASM(func_801D27BC);
#endif

#ifdef NON_MATCHING
NON_MATCHING s32 func_801D2978(void) {
    s8 amount;
    u8 saved[3];

    amount = g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds;
    if (amount <= 0) {
        amount = 1;
    }
    if (amount > 20) {
        amount = 20;
    }
    g_ShisuBaseScale = g_ShisuScales[amount];

    saved[0] = g_ShisuBaseR;
    saved[1] = g_ShisuBaseG;
    saved[2] = g_ShisuBaseB;
    if (g_ShisuIngredients.used[2] * 3 < 0xFF - saved[0]) {
        g_ShisuBaseR = saved[0] + g_ShisuIngredients.used[2] * 3;
    } else {
        g_ShisuBaseR = 0xFF;
    }
    if (g_ShisuIngredients.used[2] * 3 < 0xFF - g_ShisuBaseG) {
        g_ShisuBaseG += g_ShisuIngredients.used[2] * 3;
    } else {
        g_ShisuBaseG = 0xFF;
    }
    if (g_ShisuIngredients.used[2] * 3 < g_ShisuBaseB) {
        g_ShisuBaseB -= g_ShisuIngredients.used[2] * 3;
    } else {
        g_ShisuBaseB = 0;
    }
    func_801D2308(&D_801DA044 + 1);
    g_ShisuBaseR = saved[0];
    g_ShisuBaseG = saved[1];
    g_ShisuBaseB = saved[2];
    return saved[2];
}
#else
INCLUDE_ASM(func_801D2978);
#endif
