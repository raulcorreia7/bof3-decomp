#include "area030_05.h"

/* D_800F71F0 */
static Callback s_ShopStates[11] = {
    Fishing_ShopOpen,    Fishing_ShopChooseTrade, Fishing_ShopConfirmAll,      Fishing_ShopInit, Fishing_ShopWaitOpen, Fishing_ShopChooseItem, Fishing_ShopChooseQuantity,
    Fishing_ShopConfirm, Fishing_ShopTooGreedy,   Fishing_ShopConfirmAllInput, Fishing_ShopExit,
};

/* The 16-byte table after the dispatch pointers; no reader in this image. */
static u8 D_800F721C[16] = {
    0x13, 0x13, 0x80, 0x5D, 0x6F, 0x65, 0x60, 0x6F, 0x12, 0x05, 0x8E, 0x6D, 0x5C, 0x83, 0x13, 0xA1,
};

/* Sprite id by item icon, read through Item_GetIcon in Fishing_ShopDrawItemIcon. */
/* D_800F722C */
static u8 s_ShopItemIcons[16] = {
    0x06, 0x08, 0x0A, 0x09, 0x0B, 0x0C, 0x06, 0x06, 0x06, 0x06, 0x14, 0x15, 0x16, 0x00, 0x00, 0x00,
};

/* The work block: the four cells the handlers write and the two dispatch
 * indexes. Each cell is its own symbol at a 4-byte stride; every other byte is
 * unread padding. */
static u8 s_ListCursor = 0;
static u8 pad_800F723D = 0, pad_800F723E = 0, pad_800F723F = 0;
/* D_800F7240 */
static u8 s_ShopItemCount = 0;
static u8 pad_800F7241 = 0, pad_800F7242 = 0, pad_800F7243 = 0;
static u8 s_ListItemId = 0;
static u8 pad_800F7245 = 0, pad_800F7246 = 0, pad_800F7247 = 0;
/* D_800F7248 */
static u8 s_ShopDeclined = 0;
static u8 pad_800F7249 = 0, pad_800F724A = 0, pad_800F724B = 0;
/* D_800F724C */
static u8 s_ShopMode   = 0;
static u8 s_Step       = 0;
static u8 pad_800F724E = 0, pad_800F724F = 0;

/* func_800F500C */
MATCH void Fishing_ShopRun(void) {
    s_ShopStates[s_ShopMode]();
}

/* func_800F5048 */
MATCH void Fishing_ShopOpen(void) {
    s_ShopStates[3 + s_Step]();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    Fishing_ShopDrawTradeList(0);
    Fishing_ShopDrawNeeded();
    Fishing_ShopDrawBackdrop();
}

/* func_800F50B4 */
MATCH void Fishing_ShopInit(void) {
    UI_SetMode(1);
    s_ListCursor    = 0;
    s_ListItemId    = 1;
    s_ShopItemCount = Fishing_ShopItemCount();
    s_Step += 1;
}

/* func_800F510C */
MATCH void Fishing_ShopWaitOpen(void) {
    if (WINDOW_EFFECT_IDLE()) {
        s_ShopMode = 1;
        s_Step     = 0;
    }
}

/* func_800F5138 */
MATCH void Fishing_ShopChooseTrade(void) {
    s_ShopStates[5 + s_Step]();
    Fishing_ShopDrawBackdrop();
    Fishing_ShopDrawNeeded();
    if (((s8)s_ListCursor & 0xC0) == 0) {
        Menu_DrawCursorSprite(26, (s8)s_ListCursor * 13 + 0x51, 0);
    }
}

/* func_800F51BC */
MATCH void Fishing_ShopChooseItem(void) {
    s32 r;
    u8  total;

    r = PAD_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    if ((r & PADLup) != 0) {
        s_ListCursor -= 1;
        if ((s8)s_ListCursor < 0) {
            s_ListCursor = s_ShopItemCount - 1;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    } else if ((r & PADLdown) != 0) {
        s_ListCursor += 1;
        if ((s8)s_ListCursor >= s_ShopItemCount) {
            s_ListCursor = 0;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if ((g_InputPressed & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
        if (Fishing_ShopTradeBlocked(s_ListCursor, 1) == 0) {
            total = Item_Count(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3], D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, 0) +
                    Item_Count(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3], D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, 1);
            if (total >= 99) {
                s_ListCursor |= 0x80;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                s_ListItemId = 0;
                s_Step       = 3;
            } else {
                s_ListCursor |= 0x40;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                s_Step += 1;
            }
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
        goto tail; /* skips the cancel branch: the confirm path shares the tail */
    }
    if ((g_InputPressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
        s_ShopDeclined = 1;
        s_ListCursor |= 0x80;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        s_ShopMode += 1;
    }
tail:
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    if (((s8)s_ListCursor & 0xC0) == 0) {
        WinDrawCueText(0x18, 0x14,
                       Item_GetDescription(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] << 3], D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00) & HALF_MASK);
    }
    Fishing_ShopDrawTradeList(0);
}

/* func_800F550C */
MATCH void Fishing_ShopChooseQuantity(void) {
    s32 s0;
    s32 s1;
    u8  s2;
    u8  s3;

    s0 = 0;
    switch (PAD_GetRepeatedButtons(g_InputPressed & INPUT_DIRECTIONAL) & HALF_MASK) {
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
    while (Fishing_ShopTradeBlocked(s1, s_ListItemId) != 0) {
        s_ListItemId = s_ListItemId - 1;
    }
    s0 = Item_Count(D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_01, D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_00, 0) +
         Item_Count(D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_01, D_801E2F7C[D_801E3134[g_GameContextKind][s1]].cost_00, 1);
    s0 &= BYTE_MASK;
    while (1) {
        if (s0 + (s8)s_ListItemId < 100) {
            break;
        }
        s_ListItemId = s_ListItemId - 1;
    }
    if ((s8)s_ListItemId != (s8)s2) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputPressed & g_InputMasks[FISHING_INPUT_CAST]) {
        s_ShopDeclined = 0;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        s_Step = s_Step + 1;
    } else if (g_InputPressed & g_InputMasks[FISHING_INPUT_CANCEL]) {
        s_ListItemId = 1;
        s_ListCursor &= 0xBF;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        s_Step = s_Step - 1;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_DrawText(24, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_QUANTITY_PROMPT));
    Fishing_ShopDrawTradeList(1);
    Fishing_ShopDrawQuantity();
    Menu_DrawCursorSprite(26, 107, 0);
}

/* func_800F5828 */
MATCH void Fishing_ShopConfirm(void) {
    s32  i;
    u8*  src;
    u16* pad;

    pad = &g_InputPressed;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        s_ShopDeclined ^= 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    } else if (*pad & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        s_Step -= 1;
    } else if (*pad & g_InputMasks[FISHING_INPUT_CAST]) {
        if (s_ShopDeclined != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            s_Step -= 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 5));
            s_ListCursor &= 0xBF;
            Item_Add(D_801E2F7D[D_801E3134[g_GameContextKind][(s8)s_ListCursor] * 8], D_801E2F7C[D_801E3134[g_GameContextKind][(s8)s_ListCursor]].cost_00, s_ListItemId, 0);
            Fishing_ShopTakeTradeItems();
            s_ListItemId = 1;
            s_Step       = 0;
        }
    }

    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);

    if (s_Step == 2) {
        src = Item_GetRecord(D_801E2F7D[D_801E3134[g_GameContextKind][s_ListCursor & 0xF] * 8], D_801E2F7C[D_801E3134[g_GameContextKind][s_ListCursor & 0xF]].cost_00);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = src[i];
        }
        D_801490E4[0] = 0;
        UI_DrawText(40, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_CONFIRM_ITEM));
        UI_DrawText(238, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_YES_NO));
        Menu_DrawCursorSprite((s_ShopDeclined << 5) + 0xED, 22, 0);
    }

    Fishing_ShopDrawTradeList(1);
    if (s_Step != 0) {
        Fishing_ShopDrawQuantity();
    }
}

/* func_800F5AD8 */
MATCH void Fishing_ShopTooGreedy(void) {
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    if ((g_InputPressed & (g_InputMasks[FISHING_INPUT_CAST] | g_InputMasks[FISHING_INPUT_CANCEL])) != 0) {
        s_ListItemId = 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        s_Step = 0;
        s_ListCursor &= 0x7F;
        Fishing_ShopDrawTradeList(0);
    } else {
        UI_DrawText(24, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_TOO_GREEDY));
        Fishing_ShopDrawTradeList(1);
        Fishing_ShopDrawQuantity();
    }
}

/* func_800F5BA4 */
MATCH void Fishing_ShopConfirmAll(void) {
    s_ShopStates[9 + s_Step]();
}

/* func_800F5BE0 */
MATCH void Fishing_ShopConfirmAllInput(void) {
    u16* keys;

    keys = &g_InputPressed;
    if ((INPUT_REPEATED(*keys, (PADLright | PADLleft)) & (PADLright | PADLleft)) != 0) {
        s_ShopDeclined ^= 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    } else {
        if ((*keys & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
            s_ShopDeclined = 1;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            {
                u8 work = s_ShopMode - 1;
                u8 sel  = s_ListCursor & 0x7F;

                s_ListCursor = sel;
                s_ShopMode   = work;
            }
        }
        if ((*keys & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
            if (s_ShopDeclined == 0) {
                UI_SetMode(0);
                s_Step += 1;
            } else {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                {
                    u8 work = s_ShopMode - 1;
                    u8 sel  = s_ListCursor & 0x7F;

                    s_ListCursor = sel;
                    s_ShopMode   = work;
                }
            }
        }
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_DrawText(24, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_CONFIRM_ALL));
    Menu_DrawCursorSprite(s_ShopDeclined * 32 + 0xEE, 22, 0);
    Fishing_ShopDrawTradeList(0);
    Fishing_ShopDrawNeeded();
    Fishing_ShopDrawBackdrop();
}

/* func_800F5D98 */
MATCH void Fishing_ShopExit(void) {
    if (WINDOW_EFFECT_IDLE()) {
        g_GameEntrySubstate = 1;
        return;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_DrawText(24, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_CONFIRM_ALL));
    Menu_DrawCursorSprite(s_ShopDeclined * 32 + 0xEE, 22, 0);
    Fishing_ShopDrawTradeList(0);
    Fishing_ShopDrawNeeded();
    Fishing_ShopDrawBackdrop();
}

/* Queues a draw-mode packet, two 160x240 textured quads side by side, then a
 * second draw-mode packet. */
/* func_800F5E44 */
MATCH void Fishing_ShopDrawBackdrop(void) {
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
    GFX_AddPrim(7, sizeof(DR_MODE));
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
        setUV4(((POLY_FT4*)cursor), 0, 0, 160, 0, 0, 240, 160, 240);
        setRGB0(((POLY_FT4*)cursor), 64, 64, 64);
        ((POLY_FT4*)cursor)->x2 = ((POLY_FT4*)cursor)->x0;
        ((POLY_FT4*)cursor)->x3 = ((POLY_FT4*)cursor)->x1;
        GFX_AddPrim(7, sizeof(POLY_FT4));
    }
    cursor             = g_GfxPrimCursor;
    g_GfxPrimCursor    = cursor + 8;
    ((RECT*)cursor)->x = 0;
    ((RECT*)cursor)->y = 0;
    ((RECT*)cursor)->h = 256;
    ((RECT*)cursor)->w = 256;
    tpage              = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)cursor);
    GFX_AddPrim(7, sizeof(DR_MODE));
}

/* func_800F606C */
MATCH void Fishing_ShopDrawTradeList(s32 draw_all) {
    s32 h;
    u8  w;
    s32 i;
    int new_var;
    u8  n;
    n = draw_all & BYTE_MASK;
    Fishing_ShopDrawListWindow(20, 56, n);
    UI_DrawText(54, 62, (u8)(n * 7), 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_TRADE_ITEM_LABEL));
    for (i = 0; i < s_ShopItemCount; i++) {
        h = Item_GetRecord(D_801E2F7D[D_801E3134[g_GameContextKind][i] * (new_var = 8)], ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var]);
        w = Fishing_ShopTradeBlocked(i & BYTE_MASK, 1);
        if ((draw_all & BYTE_MASK) != 0) {
            UI_DrawText(37, (0x51 + (i * 13)), 7, Game_ReadCommand((u8*)h) & BYTE_MASK, (u8*)h);
            Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var], D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], 1);
        } else if (i == ((s8)s_ListCursor)) {
            if ((w & BYTE_MASK) == 0) {
                UI_DrawText(37, (0x51 + (i * 13)), 7, Game_ReadCommand((u8*)h) & BYTE_MASK, (u8*)h);
                Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var], D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], 1);
            }
            UI_DrawText(37, (0x4F + (i * 13)), (u8)(w * 7), Game_ReadCommand((u8*)h) & BYTE_MASK, (u8*)h);
            Fishing_ShopDrawItemIcon(28, (s16)(0x52 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var], D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], w & BYTE_MASK);
        } else {
            UI_DrawText(37, (0x51 + (i * 13)), (u8)(w * 7), Game_ReadCommand((u8*)h) & BYTE_MASK, (u8*)h);
            Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), ((u8*)D_801E2F7C)[D_801E3134[g_GameContextKind][i] * new_var], D_801E2F7D[D_801E3134[g_GameContextKind][i] * new_var], w & BYTE_MASK);
        }
    }
}

/* func_800F63CC */
MATCH void Fishing_ShopDrawListWindow(u16 x, u16 y, u8 color) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_DrawWindow(x, (y + 1), 140, 160, (color | 0x80), g_WindowStyle);
    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(37, 1, x, y);

    for (i = 0; i < 10; i++) {
        offset = i * 8 + 0x20;
        Fishing_DrawSprite(38, 1, (x + offset), y);
    }

    Fishing_DrawSprite(39, 1, (x + 0x70), y);

    x2 = x + 0x88;
    Fishing_DrawSprite(40, 1, x2, y);

    y2 = y + 0x18;
    Fishing_DrawWindowFill(x, y2, 132, 0);
    Fishing_DrawWindowFill(x2, y2, 132, 1);

    y2 = y + 0x9C;
    Fishing_DrawSprite(48, 1, x, y2);

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        Fishing_DrawSprite(49, 1, (x + offset), y2);
    }

    Fishing_DrawSprite(50, 1, (x + 0x88), (y + 0x9C));
}

/* func_800F65A8 */
MATCH u8 Fishing_ShopTradeBlocked(s32 slot, s32 amount) {
    s32 i;
    u8  value;
    u8(*limit)[8];

    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        value = D_801E2F7E[D_801E3134[g_GameContextKind][slot & BYTE_MASK]][i];
        if (value == GAME_NONE) {
            return false;
        }
        limit = (u8(*)[8]) & D_801E2F7E[0][3];
        if ((Item_Count(ITEM_CAT_ITEM, (value + 0x38), 0) & HALF_MASK) < limit[D_801E3134[g_GameContextKind][slot & BYTE_MASK]][i] * (amount & BYTE_MASK)) {
            return true;
        }
    }
    return false;
}

/* func_800F66D4 */
MATCH u8 Fishing_ShopItemCount(void) {
    u8 index;

    for (index = 0; index < 10; index++) {
        if (D_801E3134[g_GameContextKind][index] == GAME_NONE) {
            break;
        }
    }
    return index;
}

/* func_800F6730 */
MATCH void Fishing_ShopDrawNeeded(void) {
    s32 i;
    s32 value;
    u8  slot;
    u8  cost;

    slot = s_ListCursor & 0xF;
    Fishing_ShopDrawNeededWindow(168, 64);
    UI_DrawText(210, 71, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_NEEDED_LABEL));
    Fishing_ShopDrawNeededWindow(168, 140);
    UI_DrawText(215, 147, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_OWNED_LABEL));
    if ((s8)s_ListCursor & 0x80) {
        return;
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] == GAME_NONE) {
            break;
        }
        value = Item_GetRecord(ITEM_CAT_ITEM, (u8)((D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] + 0x38) & BYTE_MASK));
        UI_DrawText(173, (0x58 + i * 13), 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
        TEXT_Format(g_UiFormatBuffer, D_800F5000.format, D_801E2F81[D_801E3134[g_GameContextKind][slot]][i] * (s8)s_ListItemId);
        UI_DrawGlyphString(272, (0x5C + i * 13), 0, g_UiFormatBuffer);
        cost = Item_Count(ITEM_CAT_ITEM, (D_801E2F7E[D_801E3134[g_GameContextKind][slot]][i] + 0x38) & BYTE_MASK, 0);
        if (cost < D_801E2F81[D_801E3134[g_GameContextKind][slot]][i]) {
            UI_DrawText(173, (0xA4 + i * 13), 7, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
            TEXT_Format(g_UiFormatBuffer, D_800F5000.format, cost);
            UI_DrawGlyphString(272, (0xA8 + i * 13), 7, g_UiFormatBuffer);
        } else {
            UI_DrawText(173, (0xA4 + i * 13), 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
            TEXT_Format(g_UiFormatBuffer, D_800F5000.format, cost);
            UI_DrawGlyphString(272, (0xA8 + i * 13), 0, g_UiFormatBuffer);
        }
    }
}

/* func_800F6A84 */
MATCH void Fishing_ShopDrawNeededWindow(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_DrawWindow(x, (y + 1), 132, 66, 0x80, g_WindowStyle);

    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(37, 1, x, y);

    for (i = 0; i < 9; i++) {
        offset = i * 8 + 0x20;
        Fishing_DrawSprite(38, 1, (x + offset), y);
    }

    Fishing_DrawSprite(39, 1, (x + 0x68), y);

    x2 = x + 0x80;
    Fishing_DrawSprite(40, 1, x2, y);

    y2 = y + 0x18;
    Fishing_DrawWindowFill(x, y2, 40, 0);
    Fishing_DrawWindowFill(x2, y2, 40, 1);

    y2 = y + 0x40;
    Fishing_DrawSprite(48, 1, x, y2);

    i      = 0;
    offset = 8;
    do {
        Fishing_DrawSprite(49, 1, (x + offset), y2);
        i += 1;
        offset += 8;
    } while (i < 15);

    Fishing_DrawSprite(50, 1, (x + 0x80), (y + 0x40));
}

/* func_800F6C5C */
MATCH void Fishing_ShopDrawQuantity(void) {
    u8  slot;
    s32 entry;
    s32 value;

    slot = s_ListCursor & 0xF;
    Fishing_ShopDrawQuantityWindow(20, 100);

    entry = D_801E3134[g_GameContextKind][slot];
    value = Item_GetRecord(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00);
    UI_DrawText(33, 104, 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);

    TEXT_Format(g_UiFormatBuffer, D_800F5000.format, (s8)s_ListItemId);
    UI_DrawGlyphString(132, 108, 0, g_UiFormatBuffer);

    entry = D_801E3134[g_GameContextKind][slot];
    Fishing_ShopDrawItemIcon(24, 108, D_801E2F7C[entry].cost_00, D_801E2F7C[entry].cost_01, 0);

    UI_DrawText(33, 124, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_NONE_OWNED));

    entry = D_801E3134[g_GameContextKind][slot];
    TEXT_Format(g_UiFormatBuffer, D_800F5000.format, Item_Count(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00, 0) & HALF_MASK);
    UI_DrawGlyphString(132, 128, 0, g_UiFormatBuffer);

    UI_DrawText(33, 136, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MSG_NONE_EQUIPPED));

    entry = D_801E3134[g_GameContextKind][slot];
    TEXT_Format(g_UiFormatBuffer, D_800F5000.format, Item_Count(D_801E2F7C[entry].cost_01, D_801E2F7C[entry].cost_00, 1) & HALF_MASK);
    UI_DrawGlyphString(132, 140, 0, g_UiFormatBuffer);
}

/* func_800F6EE0 */
MATCH void Fishing_ShopDrawQuantityWindow(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 y2;

    UI_DrawWindow(x, y, 136, 54, 0x80, g_WindowStyle);
    Fishing_SetDrawMode(8, 1);
    Fishing_DrawSprite(51, 1, x, y);

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        Fishing_DrawSprite(52, 1, (x + offset), y);
    }

    Fishing_DrawSprite(53, 1, (x + 0x84), y);

    y2 = y + 0x8;
    Fishing_DrawWindowFill(x, y2, 44, 2);
    Fishing_DrawWindowFill((x + 0x84), y2, 44, 3);

    Fishing_DrawSprite(54, 1, x, (y + 0x34));

    for (i = 0; i < 16; i++) {
        offset = i * 8 + 0x8;
        Fishing_DrawSprite(55, 1, (x + offset), (y + 0x34));
    }

    Fishing_DrawSprite(56, 1, (x + 0x84), (y + 0x34));
}

/* func_800F7094 */
MATCH void Fishing_ShopDrawItemIcon(s32 x, s32 y, s32 item_id, s32 category, u8 selected) {
    item_id &= BYTE_MASK;
    if (item_id != ITEM_NOTHING) {
        func_801AEA80((u16)x, (u16)y, s_ShopItemIcons[Item_GetIcon(category & BYTE_MASK, item_id) & BYTE_MASK], selected);
    }
}

/* func_800F7100 */
MATCH void Fishing_ShopTakeTradeItems(void) {
    s32           i;
    s32           list_index;
    unsigned char new_var;
    u8*           p;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        list_index = D_801E3134[g_GameContextKind][(s8)s_ListCursor];
        if (D_801E2F7E[list_index][i] == GAME_NONE) {
            break;
        }
        p       = D_801E2F7E[list_index] + 3;
        new_var = p[i] * ((s8)s_ListItemId);
        Item_Remove(ITEM_CAT_ITEM, (D_801E2F7E[D_801E3134[g_GameContextKind][s_ListCursor & 0xF]][i] + 0x38) & BYTE_MASK, new_var & BYTE_MASK, 0);
    }
}
