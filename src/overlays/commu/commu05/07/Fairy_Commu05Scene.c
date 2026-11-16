#include "commu05_07.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay entry: the commu state byte selects the step handler. */
MATCH void func_801D0C10(void) {
    SYS_DISPATCH_BYTE(g_Commu05States, D_801F294C);
}

MATCH void func_801D0C4C(void) {
    if (D_80145E44 != 0) {
        D_801D19F0.unk_00 = ((D_80145E44 - 1) / 7) + 1;
    } else {
        D_801D19F0.unk_00 = 0;
    }
    if (g_FairyVillagePendingQueueCount != 0) {
        D_801D19F0.unk_01 = ((g_FairyVillagePendingQueueCount - 1) / 20) + 1;
    } else {
        D_801D19F0.unk_01 = 0;
    }
    if (g_FairyVillageUpdateCount != 0) {
        D_801D19F0.unk_02 = ((g_FairyVillageUpdateCount - 1) / 8) + 1;
    } else {
        D_801D19F0.unk_02 = 0;
    }
    D_801D19F0.unk_04 = 0;
    D_801F294C += 1;
}

INCLUDE_ASM(func_801D0D4C);

MATCH void func_801D0F34(void) {
    /* FAKE: retail reads g_SceneEventState.step as u8[]. */
    ((u8*)&g_SceneEventState.step)[0] += 1;
}

MATCH void func_801D0F50(s16 x, s16 y, u8 row) {
    SPRT* sprite;
    s32   tpage;

    tpage = getTPage(0, 0, 896, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, row * 12 - 0x38, 0xF0);
    setWH(sprite, 0xC, 0xC);
    sprite->clut = 0x7849;
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(1, sizeof(SPRT));
}

INCLUDE_ASM(func_801D1048);

MATCH void func_801D129C(s16 x, s16 y, u8 group) {
    s32 i;
    s16 row_y;
    u8* buffer;

    UI_DrawText(x + 0x28, y, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 55));
    row_y = y + 0x14;
    func_801D0F50(x + 8, row_y, 0);
    UI_DrawText(x + 0x18, row_y, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 59));
    buffer = g_UiFormatBuffer;
    /* The row-count format and its two captions sit in the unit's data. */
    TEXT_Format(buffer, D_801D0C0C, g_FairyVillagePendingQueueCount);
    UI_DrawAsciiString(x + 0x6C, row_y, 0, buffer);
    if (g_FairyVillagePendingQueueCount == 1) {
        UI_DrawText(x + 0x84, row_y, 0, 7, D_801D1974);
    } else {
        UI_DrawText(x + 0x84, row_y, 0, 7, D_801D196C);
    }
    for (i = 0; i < 20; i++) {
        if (i + group * 20 >= g_FairyVillagePendingQueueCount) {
            break;
        }
        UI_DrawText(x + 0x12 + (i % 3) * 0x48, y + 0x2C + (i / 3) * 0x10, 0, 5, D_801457E8[D_80145E48[group * 15 + i]]);
    }
}

INCLUDE_ASM(func_801D14C8);

MATCH void func_801D1670(s16 x, s16 y, u16 u, u16 v, u8 width) {
    SPRT* sprite;

    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, u, v);
    setWH(sprite, (width << 4) + 0x10, 0x10);
    sprite->clut = 0x7883;
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(1, sizeof(SPRT));
}

MATCH void func_801D1724(u16 x, u16 y) {
    s32 dy;
    s32 i;
    s32 j;
    s32 tpage;
    s16 row_y;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2D;
    } else {
        tpage = 0x1D;
    }
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, sizeof(DR_MODE));
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
