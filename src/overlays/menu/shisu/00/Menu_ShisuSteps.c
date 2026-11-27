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
    if (g_SysThreads[2].state == 0) {
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
    if (g_SysThreads[2].state == 0) {
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
    g_UiPanelTasks[0].pos.vy = D_8014837E + 4;
    if (g_ShisuIngredients.rounds != 0) {
        D_801DA0FC = D_801DA084 + g_ShisuBaseScale * 0xA00;
    }
    func_801D2C0C();
    func_801D2DA8();
}

/* Reads the ingredient list and updates the selected amounts. */
MATCH void func_801D14C0(void) {
    volatile u16* input;
    s32           buttons;
    u8            cursor;

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
            D_80148364                = g_ShisuIngredients.command + 0x2B;
            g_MenuStep.sub_step--;
        }
    } else if (buttons & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_ShisuIngredients.cursor++;
        if (g_ShisuIngredients.cursor >= 4) {
            g_ShisuIngredients.cursor = 0xFF;
            D_80148364                = g_ShisuIngredients.command + 0x2B;
            g_MenuStep.sub_step--;
        }
    } else {
        buttons = g_PadStates[0].pressed;
        if (!(g_InputMasks[MENU_INPUT_CANCEL] & buttons) && (g_InputMasks[MENU_INPUT_CONFIRM] & buttons)) {
            switch (g_ShisuIngredients.cursor) {
                case 0:
                    if (g_ShisuIngredients.held[0] == 0) {
                        D_80148364 = 0x2E;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    } else if (g_ShisuIngredients.used[0] == 0) {
                        D_801DA0C0.header.mode = 1;
                        g_ShisuIngredients.used[0]++;
                        g_ShisuIngredients.held[0]--;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    } else {
                        D_80148364 = 0x2D;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    }
                    break;
                case 1:
                    if (g_ShisuIngredients.held[1] == 0) {
                        D_80148364 = 0x2E;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    } else if (g_ShisuIngredients.used[1] < 20) {
                        if (g_ShisuIngredients.used[1] == 0) {
                            D_801DA048.header.mode = 1;
                        }
                        g_ShisuIngredients.used[1]++;
                        g_ShisuIngredients.held[1]--;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    } else {
                        D_80148364 = 0x2D;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    }
                    break;
                case 2:
                    if (g_ShisuIngredients.used[1] != 0) {
                        if (g_ShisuIngredients.held[2] == 0) {
                            D_80148364 = 0x2E;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                        } else if (g_ShisuIngredients.used[2] < 20) {
                            g_ShisuIngredients.used[2]++;
                            g_ShisuIngredients.held[2]--;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                        } else {
                            D_80148364 = 0x2D;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                        }
                    } else {
                        D_80148364 = 0x2F;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    }
                    break;
                case 3:
                    if (g_ShisuIngredients.used[0] != 0) {
                        if (g_ShisuIngredients.held[3] == 0) {
                            D_80148364 = 0x2E;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                        } else if (g_ShisuIngredients.used[3] < 20) {
                            g_ShisuIngredients.used[3]++;
                            g_ShisuIngredients.held[3]--;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                        } else {
                            D_80148364 = 0x2D;
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                        }
                    } else {
                        D_80148364 = 0x30;
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    }
                    break;
            }
        }
    }
    cursor                   = g_ShisuIngredients.cursor;
    g_UiPanelTasks[0].active = 1;
    g_UiPanelTasks[0].unk_0A = cursor;
    g_UiPanelTasks[0].pos.vx = g_UiPanelTasks[3].pos.vx + 7;
    g_UiPanelTasks[0].pos.vy = g_UiPanelTasks[3].pos.vy + cursor * 13 + 26;
    g_UiPanelTasks[3].unk_0A = cursor;
    if (g_ShisuIngredients.rounds != 0) {
        D_801DA0FC = D_801DA084 + g_ShisuBaseScale * 0xA00;
    }
    func_801D2C0C();
    func_801D2DA8();
}

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

    count                  = &g_MenuStep.state;
    value                  = *count;
    D_801DA0C0.header.mode = 2;
    D_801DA048.header.mode = 2;
    *count                 = value + 1;
}

MATCH void func_801D1910(void) {
    if ((D_801DA0C6 != 0) && (D_801DA04E != 0)) {
        D_801DA0C0.header.mode = 3;
        D_801DA048.header.mode = 3;
        {
            u8* step = &g_MenuStep.state;

            *step += 1;
        }
    }
}

/* Copies the equipped item's status values onto the equip list's title row. */
MATCH void func_801D1964(void) {
    if ((D_801DA0C6 != 0) && (D_801DA04E != 0)) {
        D_801DA0C0.header.mode = 4;
        D_801DA048.header.mode = 4;
        D_80148654             = 0;
        D_801D9EF0[0]          = g_ShisuTopping[0];
        D_801D9EF0[1]          = g_ShisuTopping[1];
        D_801D9EF0[2]          = g_ShisuTopping[2];
        D_801D9EF4[0]          = g_ShisuBase[0];
        D_801D9EF4[1]          = g_ShisuBase[1];
        D_801D9EF4[2]          = g_ShisuBase[2];
        D_80148652++;
    }
}

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
        D_801DA0C0.header.mode = 5;
        D_801DA048.header.mode = 1;
        D_80148652             = 0;
        g_ShisuTopping[0]      = D_801D9EF0[0];
        g_ShisuTopping[1]      = D_801D9EF0[1];
        g_ShisuTopping[2]      = D_801D9EF0[2];
        g_ShisuBase[0]         = D_801D9EF4[0];
        g_ShisuBase[1]         = D_801D9EF4[1];
        g_ShisuBase[2]         = D_801D9EF4[2];
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

/* Places the four shisu panels and points the ingredient list at the item counts. */
MATCH void func_801D1D1C(void) {
    g_UiPanelTasks[0].active     = 0;
    g_UiPanelTasks[0].panel      = 1;
    g_UiPanelTasks[0].mode       = 0;
    g_UiPanelTasks[0].state      = 2;
    g_UiPanelTasks[0].pos.vx     = 0;
    g_UiPanelTasks[0].pos.vy     = 0;
    g_UiPanelTasks[1].active     = 1;
    g_UiPanelTasks[1].panel      = 1;
    g_UiPanelTasks[1].mode       = 1;
    g_UiPanelTasks[1].state      = 2;
    g_UiPanelTasks[1].pos.vx     = 0x14;
    g_UiPanelTasks[1].pos.vy     = -0x64;
    g_UiPanelTasks[2].active     = 1;
    g_UiPanelTasks[2].panel      = 1;
    g_UiPanelTasks[2].mode       = 2;
    g_UiPanelTasks[2].state      = 2;
    g_UiPanelTasks[2].pos.vx     = 0x70;
    g_UiPanelTasks[2].pos.vy     = -0x64;
    g_UiPanelTasks[2].unk_0A     = 8;
    g_UiPanelTasks[2].unk_0B     = 0xFF;
    g_UiPanelTasks[3].active     = 1;
    g_UiPanelTasks[3].panel      = 1;
    g_UiPanelTasks[3].mode       = 3;
    g_UiPanelTasks[3].state      = 2;
    g_UiPanelTasks[3].pos.vx     = -0x78;
    g_UiPanelTasks[3].pos.vy     = 0x3F;
    g_UiPanelTasks[3].unk_0A     = 0xFF;
    g_UiPanelTasks[3].item_table = (s32)&g_ShisuIngredients;
}

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

/* Scores the mix: four ratios clamped at 0, then their weighted total in D_801DA044. */
MATCH u8 func_801D1EE8(void) {
    s32  denominator;
    s32  numerator;
    s32* score;

    denominator = g_ShisuIngredients.topping_size * 4;
    numerator   = (g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds) * 5;
    if (denominator == 0) {
        D_801DA034 = 0;
    } else if (denominator - numerator > 0) {
        D_801DA034 = numerator * 100 / denominator;
    } else {
        D_801DA034 = 200 - numerator * 100 / denominator;
    }
    {
        s32* score = &D_801DA034;
        if (*score < 0) {
            *score = 0;
        }
    }

    denominator = g_ShisuIngredients.used[1];
    numerator   = g_ShisuIngredients.used[2] * 4;
    if (denominator == 0) {
        D_801DA038 = 0;
    } else if (denominator - numerator > 0) {
        D_801DA038 = numerator * 100 / denominator;
    } else {
        D_801DA038 = 200 - numerator * 100 / denominator;
    }
    {
        s32* score = &D_801DA038;
        if (*score < 0) {
            *score = 0;
        }
    }

    denominator = 2;
    numerator   = g_ShisuIngredients.rounds;
    if (denominator - numerator > 0) {
        D_801DA03C = numerator * 25 + 50;
    } else {
        D_801DA03C = 150 - numerator * 25;
    }
    {
        s32* score = &D_801DA03C;
        if (*score < 0) {
            *score = 0;
        }
    }

    denominator = g_ShisuIngredients.topping_size + g_ShisuIngredients.used[2];
    numerator   = g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds + g_ShisuIngredients.used[3];
    if (denominator == 0) {
        D_801DA040 = 0;
    } else if (denominator - numerator > 0) {
        D_801DA040 = numerator * 100 / denominator;
    } else {
        D_801DA040 = 200 - numerator * 100 / denominator;
    }
    score = &D_801DA040;
    if (*score < 0) {
        *score = 0;
    }

    D_801DA044 = 0;
    D_801DA044 = g_ShisuIngredients.topping_size * 10 * D_801DA034;
    D_801DA044 += g_ShisuIngredients.used[1] * (D_801DA038 * D_801DA03C / 100);
    D_801DA044 = (D_801DA044 + *score * 16) / 100;
    return D_801DA044;
}

/* One 0x28-byte textured-quad record of the table at SELF(Actor)->script: the clut
 * index, four vertices, the face normal and four packed uv pairs. */
typedef struct PanelPiece {
    s16 clut;           /* 0x00 */
    u16 vertices[4][3]; /* 0x02 */
    s16 normal[3];      /* 0x1A */
    u16 uv[4];          /* 0x20 */
} PanelPiece;

/* One 0x28-byte textured quad, with a halves view over the uv pairs. */
typedef union PanelQuadPrim {
    POLY_FT4 ft4;

    struct {
        u8  pad_00[0x0C];
        u16 uv0; /* 0x0C */
        u8  pad_0E[0x06];
        u16 uv1; /* 0x14 */
        u8  pad_16[0x06];
        u16 uv2; /* 0x1C */
        u8  pad_1E[0x06];
        u16 uv3; /* 0x24 */
        u8  pad_26[0x02];
    } halves;
} PanelQuadPrim;

#ifdef NON_MATCHING
NON_MATCHING void func_801D2308(void* record) {
    CVECTOR        color;
    VECTOR         unused;
    VECTOR         normal;
    MATRIX         light;
    MATRIX         m;
    MATRIX         light_mtx;
    long           depth;
    long           flag;
    u8             abr;
    u16            count;
    u16            tpage;
    PanelPiece*    piece;
    PanelQuadPrim* quad;
    u16            i;

    /* Swaps the record into the task cell; record keeps the caller's task. */
    record = (void*)((s32)record ^ (s32)g_Self);
    g_Self = (void*)((s32)g_Self ^ (s32)record);
    record = (void*)((s32)record ^ (s32)g_Self);
    PushMatrix();
    count = SELF(Actor)->range_54.table[0];
    Actor_BuildTransformMatrix(&m);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    if (SELF(Actor)->unk_48 == 0) {
        normal.vx = normal.vy = normal.vz = SELF(Actor)->scale.x;
        ScaleMatrix(&m, &normal);
    }
    light = m;
    func_8015B2AC(light_mtx.m[0], &SELF(Actor)->angle_x);
    Camera_ApplyMatrix(&light);
    SetLightMatrix(&light_mtx);

    abr = SELF(Actor)->range_54.table[3];
    if ((abr & 0x40) == 0) {
        abr = 2;
    }
    piece = (PanelPiece*)SELF(Actor)->script;
    tpage = GetTPage(TPAGE_DEPTH_4BIT, abr & 0x3, 704, 256);
    i     = 0;
    if (count != 0) {
        do {
            quad = (PanelQuadPrim*)g_GfxPrimCursor;
            SetPolyFT4(&quad->ft4);

            setVector(&g_ScratchPadVectors[0], piece->vertices[0][0], piece->vertices[0][1], piece->vertices[0][2]);
            setVector(&g_ScratchPadVectors[1], piece->vertices[1][0], piece->vertices[1][1], piece->vertices[1][2]);
            setVector(&g_ScratchPadVectors[2], piece->vertices[2][0], piece->vertices[2][1], piece->vertices[2][2]);
            setVector(&g_ScratchPadVectors[3], piece->vertices[3][0], piece->vertices[3][1], piece->vertices[3][2]);
            setVector(&normal, piece->normal[0], piece->normal[1], piece->normal[2]);
            quad->halves.uv0 = piece->uv[0];
            quad->halves.uv1 = piece->uv[1];
            quad->halves.uv2 = piece->uv[2];
            quad->halves.uv3 = piece->uv[3];

            RotTransPers(&g_ScratchPadVectors[0], (long*)&quad->ft4.x0, &depth, &flag);
            RotTransPers(&g_ScratchPadVectors[1], (long*)&quad->ft4.x1, &depth, &flag);
            RotTransPers(&g_ScratchPadVectors[2], (long*)&quad->ft4.x2, &depth, &flag);
            RotTransPers(&g_ScratchPadVectors[3], (long*)&quad->ft4.x3, &depth, &flag);

            quad->ft4.x0 += 88;
            quad->ft4.x1 += 88;
            quad->ft4.y0 += 40;
            quad->ft4.x2 += 88;
            quad->ft4.y1 += 40;
            quad->ft4.x3 += 88;
            quad->ft4.y2 += 40;
            quad->ft4.y3 += 40;

            setRGB0(&quad->ft4, SELF(Actor)->tint.bytes.rgb.r, SELF(Actor)->tint.bytes.rgb.g, SELF(Actor)->tint.bytes.rgb.b);
            if ((SELF(Actor)->range_54.table[3] & 0x80) != 0) {
                VectorNormalS(&normal, g_ScratchPadVectors);
                color.r  = SELF(Actor)->tint.bytes.rgb.r;
                color.g  = SELF(Actor)->tint.bytes.rgb.g;
                color.b  = SELF(Actor)->tint.bytes.rgb.b;
                color.cd = quad->ft4.code;
                NormalColorCol(g_ScratchPadVectors, &color, (CVECTOR*)&quad->ft4.r0);
            }

            quad->ft4.tpage = tpage;
            quad->ft4.clut  = GetClut(piece->clut * 16, STAGE_PALETTE_Y + 3);
            SetSemiTrans(&quad->ft4, (abr >> 6) & 1);
            if (((s32 (*)(Pos2*, Pos2*, Pos2*))MATH_TriangleWinding)((Pos2*)&quad->ft4.x0, (Pos2*)&quad->ft4.x1, (Pos2*)&quad->ft4.x2) > 0) {
                GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
            }

            piece++;
            i++;
        } while ((u16)i < count);
    }
    PopMatrix();
    SELF_SET(record);
}
#else
INCLUDE_ASM(func_801D2308);
#endif

/* Sets the base and topping models at the scroll target, full size, unturned and neutral-tinted. */
MATCH void func_801D27BC(void) {
    s32*  scroll_x;
    s32*  scroll_y;
    s32** record_cell;

    record_cell            = &D_801F501C;
    scroll_x               = &g_AreaScrollTargetX;
    scroll_y               = &g_AreaScrollTargetY;
    D_801DA09C             = *record_cell;
    D_801DA098             = D_801DA09C[1];
    D_801DA048.header.mode = 0;
    D_801DA048.unk_48      = 0;
    D_801DA048.scale.x     = 0x1000;
    D_801DA048.angle_x     = 0;
    D_801DA048.angle_y     = 0;
    D_801DA048.angle_z     = 0;
    g_ShisuBase[0]         = -0x80;
    g_ShisuBase[1]         = -0x80;
    g_ShisuBase[2]         = -0x80;
    D_801DA048.pos.x.fixed = *scroll_x;
    D_801DA048.pos.y.fixed = *scroll_y;
    D_801DA048.pos.z.fixed = (Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) - SHISU_HEIGHT_BIAS;

    D_801DA114             = *record_cell + 2;
    D_801DA110             = D_801DA114[1];
    D_801DA0C0.header.mode = 0;
    D_801DA0C0.unk_48      = 0;
    D_801DA0C0.scale.x     = 0x1000;
    D_801DA0C0.angle_x     = 0;
    D_801DA0C0.angle_y     = 0;
    D_801DA0C0.angle_z     = 0;
    g_ShisuTopping[0]      = -0x80;
    g_ShisuTopping[1]      = -0x80;
    g_ShisuTopping[2]      = -0x80;
    D_801DA0C0.pos.x.fixed = *scroll_x;
    D_801DA0C0.pos.y.fixed = *scroll_y;
    D_801DA0C0.pos.z.fixed = (Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) + SHISU_HEIGHT_BIAS;
}

/* Draws the base model with its tint shifted by the vinegar used, then restores the tint. */
MATCH void func_801D2978(void) {
    s8 amount;
    u8 saved[3];
    s8 shade;

    amount = g_ShisuIngredients.used[1] - g_ShisuIngredients.rounds;
    if (amount <= 0) {
        amount = 1;
    }
    if (amount > 20) {
        amount = 20;
    }
    g_ShisuBaseScale = g_ShisuScales[amount];
    saved[0]         = g_ShisuBaseR;
    saved[1]         = g_ShisuBaseG;
    saved[2]         = g_ShisuBaseB;
    if (0xFF - saved[0] > g_ShisuIngredients.used[2] * 3) {
        shade = saved[0] + g_ShisuIngredients.used[2] * 3;
    } else {
        shade = -1;
    }
    g_ShisuBaseR = shade;
    FAKE_BARRIER(); /* FAKE: keeps the tint store ahead of the next color's address. */
    {
        u8* green = &g_ShisuBaseG;

        if (0xFF - *green > g_ShisuIngredients.used[2] * 3) {
            shade = *green + g_ShisuIngredients.used[2] * 3;
        } else {
            shade = -1;
        }
        *green = shade;
    }
    FAKE_BARRIER(); /* FAKE: keeps the tint store ahead of the next color's address. */
    {
        u8* blue = &g_ShisuBaseB;

        if (*blue > g_ShisuIngredients.used[2] * 3) {
            *blue -= g_ShisuIngredients.used[2] * 3;
        } else {
            *blue = 0;
        }
    }
    func_801D2308(&D_801DA048);
    g_ShisuBaseR = saved[0];
    g_ShisuBaseG = saved[1];
    g_ShisuBaseB = saved[2];
}
