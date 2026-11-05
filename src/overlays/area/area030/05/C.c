#include "area030_05.h"

static Callback D_800F71F0[11] = {
    func_800F5048, func_800F5138, func_800F5BA4, func_800F50B4, func_800F510C, func_800F51BC,
    func_800F550C, func_800F5828, func_800F5AD8, func_800F5BE0, func_800F5D98,
};

/* The 16-byte table after the dispatch pointers; no reader in this image. */
static u8 D_800F721C[16] = {
    0x13, 0x13, 0x80, 0x5D, 0x6F, 0x65, 0x60, 0x6F, 0x12, 0x05, 0x8E, 0x6D, 0x5C, 0x83, 0x13, 0xA1,
};

/* Kind table indexed by Item_GetKind in func_800F7094. */
static u8 D_800F722C[16] = {
    0x06, 0x08, 0x0A, 0x09, 0x0B, 0x0C, 0x06, 0x06, 0x06, 0x06, 0x14, 0x15, 0x16, 0x00, 0x00, 0x00,
};

/* The work block: the four cells the handlers write and the two dispatch
 * indexes. Each cell is its own symbol at a 4-byte stride; every other byte is
 * unread padding. */
static u8 s_ListCursor = 0;
static u8 pad_800F723D = 0, pad_800F723E = 0, pad_800F723F = 0;
static u8 D_800F7240   = 0;
static u8 pad_800F7241 = 0, pad_800F7242 = 0, pad_800F7243 = 0;
static u8 s_ListItemId = 0;
static u8 pad_800F7245 = 0, pad_800F7246 = 0, pad_800F7247 = 0;
static u8 D_800F7248   = 0;
static u8 pad_800F7249 = 0, pad_800F724A = 0, pad_800F724B = 0;
static u8 D_800F724C   = 0;
static u8 s_Step       = 0;
static u8 pad_800F724E = 0, pad_800F724F = 0;

MATCH void func_800F500C(void) {
    D_800F71F0[D_800F724C]();
}

MATCH void func_800F5048(void) {
    D_800F71F0[3 + s_Step]();
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    func_800F606C(0);
    func_800F6730();
    func_800F5E44();
}

MATCH void func_800F50B4(void) {
    UI_SetMode(1);
    s_ListCursor = 0;
    s_ListItemId = 1;
    D_800F7240   = func_800F66D4();
    s_Step += 1;
}

MATCH void func_800F510C(void) {
    if (WINDOW_EFFECT_IDLE()) {
        D_800F724C = 1;
        s_Step     = 0;
    }
}

MATCH void func_800F5138(void) {
    D_800F71F0[5 + s_Step]();
    func_800F5E44();
    func_800F6730();
    if (((s8)s_ListCursor & 0xC0) == 0) {
        Menu_DrawCursorSprite(0x1A, (s8)s_ListCursor * 13 + 0x51, 0);
    }
}

MATCH void func_800F51BC(void) {
    s32 r;
    u8  total;

    r = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    if ((r & PADLup) != 0) {
        s_ListCursor -= 1;
        if ((s8)s_ListCursor < 0) {
            s_ListCursor = D_800F7240 - 1;
        }
        SND_PlayCue(EMI_CUE_ID(1, 0));
    } else if ((r & PADLdown) != 0) {
        s_ListCursor += 1;
        if ((s8)s_ListCursor >= D_800F7240) {
            s_ListCursor = 0;
        }
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if ((g_InputPressed & D_80145AC2) != 0) {
        if (func_800F65A8(s_ListCursor, 1) == 0) {
            total = Party_CountItem(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3],
                                    D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, 0) +
                    Party_CountItem(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3],
                                    D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, 1);
            if (total >= 99) {
                s_ListCursor |= 0x80;
                SND_PlayCue(EMI_CUE_ID(1, 4));
                s_ListItemId = 0;
                s_Step       = 3;
            } else {
                s_ListCursor |= 0x40;
                SND_PlayCue(EMI_CUE_ID(1, 4));
                s_Step += 1;
            }
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
        goto tail; /* skips the cancel branch: the confirm path shares the tail */
    }
    if ((g_InputPressed & D_80145AC4) != 0) {
        D_800F7248 = 1;
        s_ListCursor |= 0x80;
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_800F724C += 1;
    }
tail:
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    if (((s8)s_ListCursor & 0xC0) == 0) {
        WinDrawCueText(0x18, 0x14,
                       Item_GetDescription(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3],
                                           D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00) &
                           0xFFFF);
    }
    func_800F606C(0);
}

MATCH void func_800F550C(void) {
    s32 s0;
    s32 s1;
    u8  s2;
    u8  s3;

    s0 = 0;
    switch (INPUT_GetRepeatedButtons(g_InputPressed & INPUT_DIRECTIONAL) & HALF_MASK) {
        case 0x2000:
            s0 = 1;
            break;
        case 0x1000:
            s0 = 10;
            break;
        case 0x8000:
            s0 = -1;
            break;
        case 0x4000:
            s0 = -10;
            break;
    }
    s2           = s_ListItemId;
    s_ListItemId = s2 + s0;
    s3           = s_ListItemId;
    if ((s8)s3 > 0) {
        if ((s8)s3 >= 100) {
            s3 = 99;
        }
    } else {
        s3 = 1;
    }
    s_ListItemId = s3;
    s1           = s_ListCursor & 0xF;
    while (func_800F65A8(s1, s_ListItemId) != 0) {
        s_ListItemId = s_ListItemId - 1;
    }
    s0 = Party_CountItem(D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_01,
                         D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_00, 0) +
         Party_CountItem(D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_01,
                         D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_00, 1);
    s0 &= BYTE_MASK;
    while (1) {
        if (s0 + (s8)s_ListItemId < 100) {
            break;
        }
        s_ListItemId = (s8)s_ListItemId - 1;
    }
    if ((s8)s_ListItemId != (s8)s2) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (g_InputPressed & D_80145AC2) {
        D_800F7248 = 0;
        SND_PlayCue(EMI_CUE_ID(1, 4));
        s_Step = s_Step + 1;
    } else if (g_InputPressed & D_80145AC4) {
        s_ListItemId = 1;
        s_ListCursor &= 0xBF;
        SND_PlayCue(EMI_CUE_ID(1, 6));
        s_Step = s_Step - 1;
    }
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    UI_DrawText(0x18, 0x14, 0, 0xFF, (u8*)(D_8001009C + 0x80010000u));
    func_800F606C(1);
    func_800F6C5C();
    Menu_DrawCursorSprite(0x1A, 0x6B, 0);
}

MATCH void func_800F5828(void) {
    s32  i;
    u8*  src;
    u16* pad;

    pad = &g_InputPressed;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        D_800F7248 ^= 1;
        SND_PlayCue(EMI_CUE_ID(1, 0));
    } else if (*pad & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        s_Step -= 1;
    } else if (*pad & D_80145AC2) {
        if (D_800F7248 != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            s_Step -= 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 5));
            s_ListCursor &= 0xBF;
            Party_AddItem(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] * 8],
                          D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, s_ListItemId, 0);
            func_800F7100();
            s_ListItemId = 1;
            s_Step       = 0;
        }
    }

    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);

    if (s_Step == 2) {
        src = Item_GetRecord(D_801E2F7D[D_801E3134[g_GameContextKind][s_ListCursor & 0xF] * 8],
                             D_801E2F7C[D_801E3134[g_GameContextKind][s_ListCursor & 0xF]].cost_00);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = src[i];
        }
        D_801490E4 = 0;
        UI_DrawText(0x28, 0x14, 0, 0xFF, (u8*)(D_8001008C + 0x80010000u));
        UI_DrawText(0xEE, 0x14, 0, 0xFF, (u8*)(D_80010094 + 0x80010000u));
        Menu_DrawCursorSprite((D_800F7248 << 5) + 0xED, 0x16, 0);
    }

    func_800F606C(1);
    if (s_Step != 0) {
        func_800F6C5C();
    }
}

MATCH void func_800F5AD8(void) {
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    if ((g_InputPressed & (D_80145AC2 | D_80145AC4)) != 0) {
        s_ListItemId = 1;
        SND_PlayCue(EMI_CUE_ID(1, 6));
        s_Step = 0;
        s_ListCursor &= 0x7F;
        func_800F606C(0);
    } else {
        UI_DrawText(0x18, 0x14, 0, 0xFF, (u8*)((u16)D_8001009A + 0x80010000u));
        func_800F606C(1);
        func_800F6C5C();
    }
}

MATCH void func_800F5BA4(void) {
    D_800F71F0[9 + s_Step]();
}

MATCH void func_800F5BE0(void) {
    u16* keys;

    keys = &g_InputPressed;
    if ((INPUT_REPEATED(*keys, (PADLright | PADLleft)) & (PADLright | PADLleft)) != 0) {
        D_800F7248 ^= 1;
        SND_PlayCue(EMI_CUE_ID(1, 0));
    } else {
        if ((*keys & D_80145AC4) != 0) {
            D_800F7248 = 1;
            SND_PlayCue(EMI_CUE_ID(1, 6));
            {
                u8 work = D_800F724C - 1;
                u8 sel  = s_ListCursor & 0x7F;

                s_ListCursor = sel;
                D_800F724C   = work;
            }
        }
        if ((*keys & D_80145AC2) != 0) {
            if (D_800F7248 == 0) {
                UI_SetMode(0);
                s_Step += 1;
            } else {
                SND_PlayCue(EMI_CUE_ID(1, 4));
                {
                    u8 work = D_800F724C - 1;
                    u8 sel  = s_ListCursor & 0x7F;

                    s_ListCursor = sel;
                    D_800F724C   = work;
                }
            }
        }
    }
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    UI_DrawText(0x18, 0x14, 0, 0xFF, (u8*)((u16)D_8001008A + 0x80010000u));
    Menu_DrawCursorSprite(D_800F7248 * 32 + 0xEE, 0x16, 0);
    func_800F606C(0);
    func_800F6730();
    func_800F5E44();
}

MATCH void func_800F5D98(void) {
    if (WINDOW_EFFECT_IDLE()) {
        g_GameEntrySubstate = 1;
        return;
    }
    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    UI_DrawText(0x18, 0x14, 0, 0xFF, (u8*)((u16)D_8001008A + 0x80010000u));
    Menu_DrawCursorSprite(D_800F7248 * 32 + 0xEE, 0x16, 0);
    func_800F606C(0);
    func_800F6730();
    func_800F5E44();
}

/* Queues a draw-mode packet, two 160x240 textured quads side by side, then a
 * second draw-mode packet. */
MATCH void func_800F5E44(void) {
    u8* cursor;
    s32 i;
    s32 tpage;

    cursor             = g_GfxPrimCursor;
    g_GfxPrimCursor    = cursor + 8;
    ((RECT*)cursor)->x = (g_FrameCount * 2) & 0x60;
    ((RECT*)cursor)->y = 128;
    ((RECT*)cursor)->h = 32;
    ((RECT*)cursor)->w = 32;
    tpage              = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)cursor);
    GFX_AddPrim(7, 0xC);
    for (i = 0; i < 2; i++) {
        s32 quad_tpage;

        cursor = g_GfxPrimCursor;
        SetPolyFT4((POLY_FT4*)cursor);
        quad_tpage                 = getTPage(1, 0, 320, 256);
        ((POLY_FT4*)cursor)->x1    = i * 160 + 160;
        ((POLY_FT4*)cursor)->x0    = i * 160;
        ((POLY_FT4*)cursor)->tpage = quad_tpage;
        ((POLY_FT4*)cursor)->clut  = 0x7A80;
        ((POLY_FT4*)cursor)->y0    = 0;
        ((POLY_FT4*)cursor)->y1    = 0;
        ((POLY_FT4*)cursor)->y2    = 240;
        ((POLY_FT4*)cursor)->y3    = 240;
        ((POLY_FT4*)cursor)->u0    = 0;
        ((POLY_FT4*)cursor)->v0    = 0;
        ((POLY_FT4*)cursor)->u1    = 160;
        ((POLY_FT4*)cursor)->v1    = 0;
        ((POLY_FT4*)cursor)->u2    = 0;
        ((POLY_FT4*)cursor)->v2    = 240;
        ((POLY_FT4*)cursor)->u3    = 160;
        ((POLY_FT4*)cursor)->v3    = 240;
        ((POLY_FT4*)cursor)->r0    = 0x40;
        ((POLY_FT4*)cursor)->g0    = 0x40;
        ((POLY_FT4*)cursor)->b0    = 0x40;
        ((POLY_FT4*)cursor)->x2    = ((POLY_FT4*)cursor)->x0;
        ((POLY_FT4*)cursor)->x3    = ((POLY_FT4*)cursor)->x1;
        GFX_AddPrim(7, 0x28);
    }
    cursor             = g_GfxPrimCursor;
    g_GfxPrimCursor    = cursor + 8;
    ((RECT*)cursor)->x = 0;
    ((RECT*)cursor)->y = 0;
    ((RECT*)cursor)->h = 256;
    ((RECT*)cursor)->w = 256;
    tpage              = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)cursor);
    GFX_AddPrim(7, 0xC);
}

MATCH void func_800F606C(s32 arg0) {
    s32 h;
    u8  w;
    s32 i;
    int new_var;
    u8  n;
    n = arg0 & BYTE_MASK;
    func_800F63CC(0x14, 0x38, n);
    UI_DrawText(0x36, 0x3E, (u8)(n * 7), 0xFF, (u8*)(((u16)D_8001008E) + 0x80010000u));
    for (i = 0; i < D_800F7240; i++) {
        h = (u32)Item_GetRecord(D_801E2F7D[D_801E3134[g_GameContextKind][i] * (new_var = 8)],
                                ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var]);
        w = func_800F65A8(i & BYTE_MASK, 1);
        if ((arg0 & BYTE_MASK) != 0) {
            UI_DrawText(0x25, (s16)(0x51 + (i * 13)), 7, func_801AF20C((u8*)h) & BYTE_MASK, (u8*)h);
            func_800F7094(0x1C, (s16)(0x54 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var],
                          D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], 1);
        } else if (i == ((s8)s_ListCursor)) {
            if ((w & BYTE_MASK) == 0) {
                UI_DrawText(0x25, (s16)(0x51 + (i * 13)), 7, func_801AF20C((u8*)h) & BYTE_MASK, (u8*)h);
                func_800F7094(0x1C, (s16)(0x54 + (i * 13)),
                              ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var],
                              D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], 1);
            }
            UI_DrawText(0x25, (s16)(0x4F + (i * 13)), (u8)(w * 7), func_801AF20C((u8*)h) & BYTE_MASK, (u8*)h);
            func_800F7094(0x1C, (s16)(0x52 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var],
                          D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], w & BYTE_MASK);
        } else {
            UI_DrawText(0x25, (s16)(0x51 + (i * 13)), (u8)(w * 7), func_801AF20C((u8*)h) & BYTE_MASK, (u8*)h);
            func_800F7094(0x1C, (s16)(0x54 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var],
                          D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], w & BYTE_MASK);
        }
    }
}

MATCH void func_800F63CC(u16 x, u16 y, u8 color) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_DrawWindow((u16)x, (u16)(y + 1), 0x8C, 0xA0, (u8)(color | 0x80), D_80144952);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, (s16)x, (s16)y);

    for (i = 0; i < 10; i++) {
        offset = i * 8 + 0x20;
        func_801E0DCC(0x26, 1, (s16)(x + offset), (s16)y);
    }

    func_801E0DCC(0x27, 1, (s16)(x + 0x70), (s16)y);

    x2 = x + 0x88;
    func_801E0DCC(0x28, 1, x2, (s16)y);

    y2 = y + 0x18;
    func_801D799C(x, y2, 0x84, 0);
    func_801D799C(x2, y2, 0x84, 1);

    y2 = y + 0x9C;
    func_801E0DCC(0x30, 1, (s16)x, y2);

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        func_801E0DCC(0x31, 1, (s16)(x + offset), y2);
    }

    func_801E0DCC(0x32, 1, (s16)(x + 0x88), (s16)(y + 0x9C));
}

MATCH u8 func_800F65A8(s32 slot, s32 amount) {
    s32 i;
    u8  value;
    u8(*limit)[8];

    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        value = D_801E2F7E[D_801E3134[g_GameContextKind][slot & BYTE_MASK]][i];
        if (value == GAME_NONE) {
            return false;
        }
        limit = (u8(*)[8]) & D_801E2F7E[0][3];
        if ((Party_CountItem(0, (u8)(value + 0x38), 0) & HALF_MASK) <
            limit[D_801E3134[g_GameContextKind][slot & BYTE_MASK]][i] * (amount & BYTE_MASK)) {
            return true;
        }
    }
    return false;
}

MATCH u8 func_800F66D4(void) {
    u8 index;

    for (index = 0; index < 10; index++) {
        if (D_801E3134[g_GameContextKind][index] == GAME_NONE) {
            break;
        }
    }
    return index;
}

MATCH void func_800F6730(void) {
    s32 i;
    s32 value;
    u8  slot;
    u8  cost;

    slot = s_ListCursor & 0xF;
    func_800F6A84(0xA8, 0x40);
    UI_DrawText(0xD2, 0x47, 0, 0xFF, (u8*)(D_80010090 + 0x80010000u));
    func_800F6A84(0xA8, 0x8C);
    UI_DrawText(0xD7, 0x93, 0, 0xFF, (u8*)(D_80010092 + 0x80010000u));
    if ((s8)s_ListCursor & 0x80) {
        return;
    }
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        if (D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] == GAME_NONE) {
            break;
        }
        value = (s32)Item_GetRecord(0, (u8)((D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] + 0x38) & BYTE_MASK));
        UI_DrawText(0xAD, (s16)(0x58 + i * 13), 0, func_801AF20C((u8*)value) & BYTE_MASK, (u8*)value);
        sprintf(g_UiFormatBuffer, D_800F5000.format,
                D_801E2F81[D_801E3134[g_GameContextKind][slot]][i] * (s8)s_ListItemId);
        UI_DrawGlyphString(0x110, (s16)(0x5C + i * 13), 0, g_UiFormatBuffer);
        cost = Party_CountItem(0, (D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] + 0x38) & BYTE_MASK, 0);
        if (cost < D_801E2F81[D_801E3134[g_GameContextKind][slot]][i]) {
            UI_DrawText(0xAD, (s16)(0xA4 + i * 13), 7, func_801AF20C((u8*)value) & BYTE_MASK, (u8*)value);
            sprintf(g_UiFormatBuffer, D_800F5000.format, cost);
            UI_DrawGlyphString(0x110, (s16)(0xA8 + i * 13), 7, g_UiFormatBuffer);
        } else {
            UI_DrawText(0xAD, (s16)(0xA4 + i * 13), 0, func_801AF20C((u8*)value) & BYTE_MASK, (u8*)value);
            sprintf(g_UiFormatBuffer, D_800F5000.format, cost);
            UI_DrawGlyphString(0x110, (s16)(0xA8 + i * 13), 0, g_UiFormatBuffer);
        }
    }
}

MATCH void func_800F6A84(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_DrawWindow((u16)x, (u16)(y + 1), 0x84, 0x42, 0x80, D_80144952);

    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, (s16)x, (s16)y);

    for (i = 0; i < 9; i++) {
        offset = i * 8 + 0x20;
        func_801E0DCC(0x26, 1, (s16)(x + offset), (s16)y);
    }

    func_801E0DCC(0x27, 1, (s16)(x + 0x68), (s16)y);

    x2 = x + 0x80;
    func_801E0DCC(0x28, 1, x2, (s16)y);

    y2 = y + 0x18;
    func_801D799C(x, y2, 0x28, 0);
    func_801D799C(x2, y2, 0x28, 1);

    y2 = y + 0x40;
    func_801E0DCC(0x30, 1, (s16)x, y2);

    i      = 0;
    offset = 8;
    do {
        func_801E0DCC(0x31, 1, (s16)(x + offset), y2);
        i += 1;
        offset += 8;
    } while (i < 15);

    func_801E0DCC(0x32, 1, (s16)(x + 0x80), (s16)(y + 0x40));
}

MATCH void func_800F6C5C(void) {
    u8  slot;
    s32 entry;
    s32 value;

    slot = s_ListCursor & 0xF;
    func_800F6EE0(0x14, 0x64);

    entry = D_801E3134[g_GameContextKind][slot];
    value = (s32)Item_GetRecord(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00);
    UI_DrawText(0x21, 0x68, 0, func_801AF20C((u8*)value) & BYTE_MASK, (u8*)value);

    sprintf(g_UiFormatBuffer, D_800F5000.format, (s8)s_ListItemId);
    UI_DrawGlyphString(0x84, 0x6C, 0, g_UiFormatBuffer);

    entry = D_801E3134[g_GameContextKind][slot];
    func_800F7094(0x18, 0x6C, D_801E2F7C[entry].cost_00, D_801E2F7C[entry].cost_01, 0);

    UI_DrawText(0x21, 0x7C, 0, 0xFF, (u8*)(D_80010096 + 0x80010000u));

    entry = D_801E3134[g_GameContextKind][slot];
    sprintf(g_UiFormatBuffer, D_800F5000.format,
            Party_CountItem(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00, 0) & HALF_MASK);
    UI_DrawGlyphString(0x84, 0x80, 0, g_UiFormatBuffer);

    UI_DrawText(0x21, 0x88, 0, 0xFF, (u8*)(D_80010098 + 0x80010000u));

    entry = D_801E3134[g_GameContextKind][slot];
    sprintf(g_UiFormatBuffer, D_800F5000.format,
            Party_CountItem(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00, 1) & HALF_MASK);
    UI_DrawGlyphString(0x84, 0x8C, 0, g_UiFormatBuffer);
}

MATCH void func_800F6EE0(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 y2;

    UI_DrawWindow(x, y, 0x88, 0x36, 0x80, D_80144952);
    func_801E0C80(8, 1);
    func_801E0DCC(0x33, 1, (s16)x, (s16)y);

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        func_801E0DCC(0x34, 1, (s16)(x + offset), (s16)y);
    }

    func_801E0DCC(0x35, 1, (s16)(x + 0x84), (s16)y);

    y2 = y + 0x8;
    func_801D799C((s16)x, y2, 0x2C, 2);
    func_801D799C((s16)(x + 0x84), y2, 0x2C, 3);

    func_801E0DCC(0x36, 1, (s16)x, (s16)(y + 0x34));

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        func_801E0DCC(0x37, 1, (s16)(x + offset), (s16)(y + 0x34));
    }

    func_801E0DCC(0x38, 1, (s16)(x + 0x84), (s16)(y + 0x34));
}

MATCH void func_800F7094(s32 x, s32 y, s32 kind, s32 value, u8 selected) {
    kind &= BYTE_MASK;
    if (kind != 0) {
        func_801AEA80((u16)x, (u16)y, D_800F722C[Item_GetKind(value & BYTE_MASK, kind) & BYTE_MASK], selected);
    }
}

MATCH void func_800F7100(void) {
    s32           i;
    s32           idx;
    unsigned char new_var;
    u8*           p;
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        idx = D_801E3134[g_GameContextKind][(s8)s_ListCursor];
        if (D_801E2F7E[idx][i] == GAME_NONE) {
            break;
        }
        p       = D_801E2F7E[idx] + 3;
        new_var = p[i] * ((s8)s_ListItemId);
        Party_RemoveItem(0, (D_801E2F7E[D_801E3134[g_GameContextKind][s_ListCursor & 0xF]][i] + 0x38) & BYTE_MASK,
                         new_var & BYTE_MASK, 0);
    }
}
