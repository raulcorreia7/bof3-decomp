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

    UI_ModeSet(UI_MODE_FAST_FADE_IN);
    func_801D1D1C();
    counter = &g_MenuStep.sub_step;
    *counter += 1;
}

MATCH void func_801D0EC4(void) {
    Menu_DrawClutStrip(g_WindowClut);
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
    Menu_DrawClutStrip(g_WindowClut);
    UI_ModeSet(2U);
    func_801D1E34();
    {
        u8* step = &g_MenuStep.sub_step;

        *step += 1;
    }
}

MATCH void func_801D0FAC(void) {
    if (g_UiWindowEffectBusy == 0) {
        u8* step = &g_MenuStep.step;

        g_MenuStep.sub_step      = 0;
        g_UiPanelTasks[1].active = 0;
        *D_80148378              = 0;
        g_UiPanelTasks[3].active = 0;
        *step += 1;
        return;
    }
    Menu_DrawClutStrip(g_WindowClut);
}

MATCH void func_801D1018(void) {
    if (g_ShisuIngredients.rounds != 0) {
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_MACKEREL, g_ShisuIngredients.used[0], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_SHALY_SEED, g_ShisuIngredients.used[1], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_VINEGAR, g_ShisuIngredients.used[2], 0);
        Item_Remove(ITEM_CATEGORY_ITEM, ITEM_HORSERADISH, g_ShisuIngredients.used[3], 0);
        g_ScenarioState.step = 0x14;
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
        g_ScenarioState.step = 5;
    }
    UI_PanelResetTasks();
    {
        u16* sub = &g_GameEntrySubstate;

        *sub += 1;
    }
}

MATCH void func_801D11A4(void) {
    Menu_DrawClutStrip(g_WindowClut);
    g_ShisuStep2Steps[g_MenuStep.sub_step]();
}

/* Reads the command row input: left and right flip mix or leave, up and down open the ingredient list. */
MATCH void func_801D11F4(void) {
    u16* input;
    u8*  step;
    u8   cur;
    u16  buttons;

    input   = &g_PadStates[0].pressed;
    buttons = INPUT_REPEATED(*input, INPUT_DIRECTIONAL);
    if (buttons & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_ShisuIngredients.command ^= 1;
        D_80148364 = g_ShisuIngredients.command + 0x2B;
    } else if (buttons & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        D_80148364                = 0x2A;
        g_ShisuIngredients.cursor = 3;
        g_MenuStep.sub_step++;
    } else if (buttons & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
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
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    g_MenuStep.sub_step += 2;
                    g_MenuStep.state = g_MenuStep.state; /* FAKE: retail reloads and stores state. */
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    D_80148364 = 0x31;
                }
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                g_ShisuIngredients.rounds++;
            }
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    } else if (*input & g_InputMasks[MENU_INPUT_CANCEL]) {
    advance:
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        step                     = &g_MenuStep.step;
        cur                      = *step;
        g_UiPanelTasks[0].active = 0;
        g_MenuStep.sub_step      = 0;
        *step                    = cur + 1;
    }

    g_UiPanelTasks[0].active = 1;
    D_80148334               = D_8014837C + g_ShisuIngredients.command * 48;
    g_UiPanelTasks[0].pos.y  = D_8014837E + 4;
    if (g_ShisuIngredients.rounds != 0) {
        D_801DA0FC = D_801DA084 + g_ShisuBaseScale * 0xA00;
    }
    func_801D2C0C();
    func_801D2DA8();
}

#ifdef NON_MATCHING
/* Reads the ingredient list and updates the selected amounts. */
NON_MATCHING void func_801D14C0(void) {
    volatile u16* input;
    u16           buttons;
    u16           pressed;

    input   = &g_PadStates[0].pressed;
    buttons = INPUT_REPEATED(*input, PADLup | PADLdown);
    if (*input != 0) {
        D_80148364 = 0x2A;
    }
    if (buttons & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_ShisuIngredients.cursor--;
        if ((s8)g_ShisuIngredients.cursor < 0) {
            g_ShisuIngredients.cursor = 0xFF;
            g_MenuStep.sub_step--;
            D_80148364 = g_ShisuIngredients.command + 0x2B;
        }
    } else if (buttons & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_ShisuIngredients.cursor++;
        if (g_ShisuIngredients.cursor >= 4) {
            g_ShisuIngredients.cursor = 0xFF;
            g_MenuStep.sub_step--;
            D_80148364 = g_ShisuIngredients.command + 0x2B;
        }
    } else {
        pressed = *input;
        if ((pressed & g_InputMasks[MENU_INPUT_CANCEL]) || !(pressed & g_InputMasks[MENU_INPUT_CONFIRM])) {
            goto update;
        }
        switch (g_ShisuIngredients.cursor) {
            case 0:
                if (g_ShisuIngredients.held[0] == 0) {
                    goto empty;
                }
                if (g_ShisuIngredients.used[0] != 0) {
                    goto full;
                }
                D_801DA0C1 = 1;
                g_ShisuIngredients.used[0]++;
                g_ShisuIngredients.held[0]--;
                goto selected;
            case 1:
                if (g_ShisuIngredients.held[1] == 0) {
                    goto empty;
                }
                if (g_ShisuIngredients.used[1] >= 20) {
                    goto full;
                }
                if (g_ShisuIngredients.used[1] == 0) {
                    D_801DA049 = 1;
                }
                g_ShisuIngredients.used[1]++;
                g_ShisuIngredients.held[1]--;
                goto selected;
            case 2:
                if (g_ShisuIngredients.used[1] == 0) {
                    D_80148364 = 0x2F;
                    goto rejected;
                }
                if (g_ShisuIngredients.held[2] == 0) {
                    goto empty;
                }
                if (g_ShisuIngredients.used[2] >= 20) {
                    goto full;
                }
                g_ShisuIngredients.used[2]++;
                g_ShisuIngredients.held[2]--;
                goto selected;
            case 3:
                if (g_ShisuIngredients.used[0] == 0) {
                    D_80148364 = 0x30;
                    goto rejected;
                }
                if (g_ShisuIngredients.held[3] == 0) {
                    goto empty;
                }
                if (g_ShisuIngredients.used[3] >= 20) {
                    goto full;
                }
                g_ShisuIngredients.used[3]++;
                g_ShisuIngredients.held[3]--;
            selected:
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                break;
            empty:
                D_80148364 = 0x2E;
                goto rejected;
            full:
                D_80148364 = 0x2D;
            rejected:
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                break;
        }
    }
update:
    g_UiPanelTasks[0].active = 1;
    D_80148334               = g_UiPanelTasks[3].pos.x + 7;
    g_UiPanelTasks[0].pos.y  = g_UiPanelTasks[3].pos.y + g_ShisuIngredients.cursor * 13 + 26;
    g_UiPanelTasks[0].unk_0A = g_ShisuIngredients.cursor;
    g_UiPanelTasks[3].unk_0A = g_ShisuIngredients.cursor;
    if (g_ShisuIngredients.rounds != 0) {
        D_801DA0FC = D_801DA084 + g_ShisuBaseScale * 0xA00;
    }
    func_801D2C0C();
    func_801D2DA8();
}
#else
INCLUDE_ASM(func_801D14C0);
#endif

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
        D_801D9EF0[0] = g_ShisuTopping[0];
        D_801D9EF0[1] = g_ShisuTopping[1];
        D_801D9EF0[2] = g_ShisuTopping[2];
        D_801D9EF4[0] = g_ShisuBase[0];
        D_801D9EF4[1] = g_ShisuBase[1];
        D_801D9EF4[2] = g_ShisuBase[2];
        D_801DA0C1    = 4;
        D_801DA049    = 4;
        D_80148654    = 0;
        D_80148652 += 1;
    }
}
#else
INCLUDE_ASM(func_801D1964);
#endif

/* Fades the six tint channels up to the fade level. */
MATCH void func_801D1A20(void) {
    u8  base2;
    u8  base1;
    u8  base0;
    u8  topping2;
    u8  topping1;
    u8  topping0;
    u8  level;
    u8* fade;

    fade     = &D_80148654;
    level    = *fade;
    topping0 = D_801D9EF0[0];
    if (topping0 < level) {
        topping0 = level;
    }
    g_ShisuTopping[0] = topping0;
    topping1          = D_801D9EF0[1];
    if (topping1 < level) {
        topping1 = level;
    }
    g_ShisuTopping[1] = topping1;
    topping2          = D_801D9EF0[2];
    if (topping2 < level) {
        topping2 = level;
    }
    g_ShisuTopping[2] = topping2;
    base0             = D_801D9EF4[0];
    if (base0 < level) {
        base0 = level;
    }
    g_ShisuBase[0] = base0;
    base1          = D_801D9EF4[1];
    if (base1 < level) {
        base1 = level;
    }
    g_ShisuBase[1] = base1;
    base2          = D_801D9EF4[2];
    if (base2 < level) {
        base2 = level;
    }
    g_ShisuBase[2] = base2;
    if (level == 0x80) {
        SND_SEPlay(0x200);
    }
    *fade = *fade + 8;
    if (*fade == 0) {
        *fade = 0xF8;
        D_80148652 += 1;
    }
}

/* Fades the topping and base tints down to their own colours, 8 levels a frame, then opens the next round. */
MATCH void func_801D1B58(void) {
    u8* fade;
    u8  level;

    fade              = &D_80148654;
    level             = *fade;
    g_ShisuTopping[0] = (D_801D9EF0[0] < level) ? level : D_801D9EF0[0];
    g_ShisuTopping[1] = (D_801D9EF0[1] < level) ? level : D_801D9EF0[1];
    g_ShisuTopping[2] = (D_801D9EF0[2] < level) ? level : D_801D9EF0[2];
    g_ShisuBase[0]    = (D_801D9EF4[0] < level) ? level : D_801D9EF4[0];
    g_ShisuBase[1]    = (D_801D9EF4[1] < level) ? level : D_801D9EF4[1];
    g_ShisuBase[2]    = (D_801D9EF4[2] < level) ? level : D_801D9EF4[2];
    *fade             = level - 8;
    if (*fade == 0) {
        D_801DA0C1        = 5;
        D_801DA049        = 1;
        D_80148652        = 0;
        g_ShisuTopping[0] = D_801D9EF0[0];
        g_ShisuTopping[1] = D_801D9EF0[1];
        g_ShisuTopping[2] = D_801D9EF0[2];
        g_ShisuBase[0]    = D_801D9EF4[0];
        g_ShisuBase[1]    = D_801D9EF4[1];
        g_ShisuBase[2]    = D_801D9EF4[2];
        g_ShisuIngredients.rounds++;
        D_80148651 -= 2;
    }
}

MATCH void func_801D1CA4(void) {
    g_ShisuIngredients.held[0] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_MACKEREL, 0);
    g_ShisuIngredients.held[1] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_SHALY_SEED, 0);
    g_ShisuIngredients.held[2] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_VINEGAR, 0);
    g_ShisuIngredients.held[3] = Item_Count(ITEM_CATEGORY_ITEM, ITEM_HORSERADISH, 0);
}

#ifdef NON_MATCHING
/* Places the four shisu panels and points the ingredient list at the item counts. */
NON_MATCHING void func_801D1D1C(void) {
    g_UiPanelTasks[1].pos.x      = 0x14;
    g_UiPanelTasks[2].pos.x      = 0x70;
    LOH(g_UiPanelTasks[1].pos.y) = -0x64;
    LOH(g_UiPanelTasks[2].pos.y) = -0x64;
    g_UiPanelTasks[2].unk_0A     = 8;
    g_UiPanelTasks[3].mode       = 3;
    LOH(g_UiPanelTasks[3].pos.x) = -0x78;
    g_UiPanelTasks[3].pos.y      = 0x3F;
    g_UiPanelTasks[0].active     = 0;
    g_UiPanelTasks[0].panel      = 1;
    g_UiPanelTasks[0].mode       = 0;
    g_UiPanelTasks[0].state      = 2;
    g_UiPanelTasks[0].pos.x      = 0;
    g_UiPanelTasks[0].pos.y      = 0;
    g_UiPanelTasks[1].active     = 1;
    g_UiPanelTasks[1].panel      = 1;
    g_UiPanelTasks[1].mode       = 1;
    g_UiPanelTasks[1].state      = 2;
    g_UiPanelTasks[2].active     = 1;
    g_UiPanelTasks[2].panel      = 1;
    g_UiPanelTasks[2].mode       = 2;
    g_UiPanelTasks[2].state      = 2;
    g_UiPanelTasks[2].unk_0B     = 0xFF;
    g_UiPanelTasks[3].active     = 1;
    g_UiPanelTasks[3].panel      = 1;
    g_UiPanelTasks[3].state      = 2;
    g_UiPanelTasks[3].unk_0A     = 0xFF;
    g_UiPanelTasks[3].item_table = (s32)&g_ShisuIngredients;
}
#else
INCLUDE_ASM(func_801D1D1C);
#endif

MATCH void func_801D1E34(void) {
    FIELD(u8, g_UiPanelTasks, 0x0) = 0;
    g_UiPanelTasks[1].state        = 1;
    g_UiPanelTasks[2].state        = 1;
    g_UiPanelTasks[3].state        = 1;
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
    g_ShisuBase[0]   = initial;
    g_ShisuBase[1]   = initial;
    g_ShisuBase[2]   = initial;
    D_801DA07C       = *scroll_x;
    D_801DA080       = y;
    height           = Area_HeightSample(x, y);
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
    g_ShisuTopping[0]   = initial;
    g_ShisuTopping[1]   = initial;
    g_ShisuTopping[2]   = initial;
    D_801DA0F4          = *scroll_x;
    D_801DA0F8          = *scroll_y;
    D_801DA110          = next_record[1];
    height              = Area_HeightSample(*scroll_x, *scroll_y);
    D_801DA0FC          = (height << 16) + SHISU_HEIGHT_BIAS;
}
#else
INCLUDE_ASM(func_801D27BC);
#endif

#ifdef NON_MATCHING
NON_MATCHING s32 func_801D2978(void) {
    s8 amount;
    u8 saved[3];
    s8 v;

    amount = g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds;
    if (amount <= 0) {
        amount = 1;
    }
    if (amount > 20) {
        amount = 20;
    }
    g_ShisuBaseScale = g_ShisuScales[amount];
    saved[0]         = g_ShisuBase[0];
    saved[1]         = g_ShisuBase[1];
    saved[2]         = g_ShisuBase[2];
    if (g_ShisuIngredients.used[2] * 3 >= 0xFF - saved[0]) {
        v = -1;
    } else {
        v = saved[0] + g_ShisuIngredients.used[2] * 3;
    }
    g_ShisuBase[0] = v;
    if (g_ShisuIngredients.used[2] * 3 >= 0xFF - g_ShisuBase[1]) {
        v = -1;
    } else {
        v = g_ShisuBase[1] + g_ShisuIngredients.used[2] * 3;
    }
    g_ShisuBase[1] = v;
    if (g_ShisuIngredients.used[2] * 3 < g_ShisuBase[2]) {
        g_ShisuBase[2] -= g_ShisuIngredients.used[2] * 3;
    } else {
        g_ShisuBase[2] = 0;
    }
    func_801D2308(&D_801DA044 + 1);
    g_ShisuBase[0] = saved[0];
    g_ShisuBase[1] = saved[1];
    g_ShisuBase[2] = saved[2];
}
#else
INCLUDE_ASM(func_801D2978);
#endif
