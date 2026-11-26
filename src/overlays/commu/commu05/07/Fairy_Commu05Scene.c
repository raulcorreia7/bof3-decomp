#include "commu05_07.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay entry: the commu state byte selects the step handler. */
MATCH void func_801D0C10(void) {
    SYS_DISPATCH_BYTE(g_Commu05Steps, D_801F294C);
}

MATCH void func_801D0C4C(void) {
    if (D_80145E44 != 0) {
        D_801D19F0.pages[0] = ((D_80145E44 - 1) / 7) + 1;
    } else {
        D_801D19F0.pages[0] = 0;
    }
    if (g_FairyVillagePendingQueueCount != 0) {
        D_801D19F0.pages[1] = ((g_FairyVillagePendingQueueCount - 1) / 20) + 1;
    } else {
        D_801D19F0.pages[1] = 0;
    }
    if (g_FairyVillageUpdateCount != 0) {
        D_801D19F0.pages[2] = ((g_FairyVillageUpdateCount - 1) / 8) + 1;
    } else {
        D_801D19F0.pages[2] = 0;
    }
    D_801D19F4 = 0;
    D_801F294C += 1;
}

MATCH void func_801D0D4C(void) {
    u8 page;
    u8 remaining;
    u8 count;

    remaining = D_801D19F4;
    page      = 0;
    while (1) {
        count = D_801D19F0.pages[page];
        if (remaining < count) {
            break;
        }
        remaining -= count;
        page++;
    }
    func_801D1724(0x20, 0x18);
    switch (page) {
        case 0:
            func_801D1048(0x28, 0x28, remaining);
            break;
        case 1:
            func_801D129C(0x28, 0x28, remaining);
            break;
        case 2:
        default:
            func_801D14C8(0x28, 0x28, remaining);
            break;
    }
    remaining = D_801D19F0.pages[0] + D_801D19F0.pages[1] + D_801D19F0.pages[2];
    if (g_PadStates[0].pressed & PADLright) {
        D_801D19F4++;
        if (D_801D19F4 >= remaining) {
            D_801D19F4 = 0;
        }
    }
    if (g_PadStates[0].pressed & PADLleft) {
        D_801D19F4--;
        if (D_801D19F4 < 0) {
            D_801D19F4 = remaining - 1;
        }
    }
    TEXT_Format(g_UiTextFormatBuffer, D_801D0C04, D_801D19F4 + 1, remaining);
    UI_TextDrawGlyphString(0xEE, 0x2C, 0, g_UiTextFormatBuffer);
    if (g_PadStates[0].pressed & (g_InputMasks[INPUT_SLOT_CANCEL] | g_InputMasks[INPUT_SLOT_CONFIRM])) {
        D_801F294C += 1;
    }
}

MATCH void func_801D0F34(void) {
    /* FAKE: retail reads g_SceneEventState.step as u8[]. */
    ((u8*)&g_SceneEventState.step)[0] += 1;
}

MATCH void func_801D0F50(s16 x, s16 y, u8 row) {
    SPRT* sprite;
    s32   tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    GFX_ADD_DRAW_MODE(tpage);
    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, row * 12 - 0x38, 0xF0);
    setWH(sprite, 0xC, 0xC);
    sprite->clut = getClut(144, 481);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

MATCH void func_801D1048(s16 x, s16 y, u8 group) {
    s32 i;
    s16 row_y;
    u8* buffer;

    UI_TextDraw(x + 0x28, y, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, MSG_AREA175_POPULATION_CHANGE));
    row_y = y + 0x14;
    func_801D0F50(x + 8, row_y, 1);
    UI_TextDraw(x + 0x18, row_y, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, MSG_AREA175_DEATH));
    buffer = g_UiTextFormatBuffer;
    TEXT_Format(buffer, D_801D0C0C, D_80145E44);
    UI_TextDrawAscii(x + 0x6C, row_y, 0, buffer);
    if (D_80145E44 == 1) {
        UI_TextDraw(x + 0x84, row_y, 0, 7, D_801D1964);
    } else {
        UI_TextDraw(x + 0x84, row_y, 0, 7, D_801D195C);
    }
    for (i = 0; i < 7; i++) {
        if (i + group * 7 >= D_80145E44) {
            break;
        }
        row_y = y + 0x2C + (i * 0x10);
        UI_TextDraw(x + 0x14, row_y, 0, 5, D_801457E8[D_80145E30[i + group * 7] & 0x7F]);
        /* kept: the shared message macro hoists the table base out of the loop. */
        if (D_80145E30[i + group * 7] & 0x80) {
            UI_TextDraw(x + 0x48, row_y, 0, TEXT_LENGTH_MAX, (u8*)(MEM(u16, (u32)AREA_MESSAGE_TABLE + MSG_AREA175_CAUSE_EXPEDITION_FAIL * 2) + (u32)AREA_MESSAGE_TABLE));
        } else {
            UI_TextDraw(x + 0x48, row_y, 0, TEXT_LENGTH_MAX, (u8*)(MEM(u16, (u32)AREA_MESSAGE_TABLE + MSG_AREA175_CAUSE_FOOD_SHORTAGE * 2) + (u32)AREA_MESSAGE_TABLE));
        }
    }
}

MATCH void func_801D129C(s16 x, s16 y, u8 group) {
    s32 i;
    s16 row_y;
    u8* buffer;

    UI_TextDraw(x + 0x28, y, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, MSG_AREA175_POPULATION_CHANGE));
    row_y = y + 0x14;
    func_801D0F50(x + 8, row_y, 0);
    UI_TextDraw(x + 0x18, row_y, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, MSG_AREA175_BIRTH));
    buffer = g_UiTextFormatBuffer;
    /* The row-count format and its two captions sit in the unit's data. */
    TEXT_Format(buffer, D_801D0C0C, g_FairyVillagePendingQueueCount);
    UI_TextDrawAscii(x + 0x6C, row_y, 0, buffer);
    if (g_FairyVillagePendingQueueCount == 1) {
        UI_TextDraw(x + 0x84, row_y, 0, 7, D_801D1974);
    } else {
        UI_TextDraw(x + 0x84, row_y, 0, 7, D_801D196C);
    }
    for (i = 0; i < 20; i++) {
        if (i + group * 20 >= g_FairyVillagePendingQueueCount) {
            break;
        }
        UI_TextDraw(x + 0x12 + (i % 3) * 0x48, y + 0x2C + (i / 3) * 0x10, 0, 5, D_801457E8[D_80145E48[group * 15 + i]]);
    }
}

#ifdef NON_MATCHING
// clang-format off
NON_MATCHING void func_801D14C8(x, y, group)
s16 x;
s16 y;
u8 group;
// clang-format on
{
    s32 i;
    s32 j;
    s32 k;
    u8(*names)[5];

    UI_TextDraw((s16)(x + 0x52), (s16)y, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 0xEC));
    i     = (group & 0xFF) * 8;
    j     = 0;
    names = D_801457E8;
next:
    if (i < g_FairyVillageUpdateCount) {
        if (D_801D197C[D_80145E60[i].type][1] != 0) {
            for (k = 0; k < 8; k++) {
                g_TextVariables[0][k] = names[D_80145E60[i].fairy][k];
            }
            g_TextVariables[0][5] = 0;
        }
        UI_TextDraw((s16)(x + 0x14), (s16)(j * 16 + 0x1C + y), 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801D197C[D_80145E60[i].type][0]));
        i++;
        j++;
        if (j < 8) {
            goto next;
        }
    }
}
#else
INCLUDE_ASM(func_801D14C8);
#endif

MATCH void func_801D1670(s16 x, s16 y, u16 u, u16 v, u8 width) {
    SPRT* sprite;

    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, u, v);
    setWH(sprite, (width << 4) + 0x10, 0x10);
    sprite->clut = getClut(48, 482);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

MATCH void func_801D1724(u16 x, u16 y) {
    s32 dy;
    s32 i;
    s32 j;
    s32 tpage;
    s16 row_y;

    tpage = getTPage(0, 0, 832, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    for (i = 0; i < 16; i++) {
        func_801D1670(x + i * 0x10, y, D_801D199C[i][0], D_801D199C[i][1], 0);
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            dy    = j * 0x10 + 0x10;
            row_y = y + dy;
            func_801D1670(x + i * 0x40, row_y, (D_801D19DC[j][0] & 1) << 5, (D_801D19DC[j][0] << 3) & 0xF0, 1);
            func_801D1670(x + i * 0x40 + 0x20, row_y, (D_801D19DC[j][1] & 1) << 5, (D_801D19DC[j][1] << 3) & 0xF0, 1);
        }
    }
    for (i = 0; i < 16; i++) {
        func_801D1670(x + i * 0x10, y + 0xB0, D_801D19BC[i][0], D_801D19BC[i][1], 0);
    }
}
