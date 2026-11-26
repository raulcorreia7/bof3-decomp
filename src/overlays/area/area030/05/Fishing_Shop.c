#include "area030_05.h"

/* D_800F71F0 */
static Callback s_ShopSteps[11] = {
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
    s_ShopSteps[s_ShopMode]();
}

/* func_800F5048 */
MATCH void Fishing_ShopOpen(void) {
    s_ShopSteps[3 + s_Step]();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    Fishing_ShopDrawTradeList(0);
    Fishing_ShopDrawNeeded();
    Fishing_ShopDrawBackdrop();
}

/* func_800F50B4 */
MATCH void Fishing_ShopInit(void) {
    UI_ModeSet(1);
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
    s_ShopSteps[5 + s_Step]();
    Fishing_ShopDrawBackdrop();
    Fishing_ShopDrawNeeded();
    if (((s8)s_ListCursor & (FISHING_SHOP_CURSOR_CHOSEN | FISHING_SHOP_CURSOR_LOCKED)) == 0) {
        UI_CursorDraw(26, (s8)s_ListCursor * 13 + 0x51, 0);
    }
}

/* func_800F51BC */
MATCH void Fishing_ShopChooseItem(void) {
    s32 repeated;
    u8  total;

    repeated = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown));
    if ((repeated & PADLup) != 0) {
        s_ListCursor -= 1;
        if ((s8)s_ListCursor < 0) {
            s_ListCursor = s_ShopItemCount - 1;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    } else if ((repeated & PADLdown) != 0) {
        s_ListCursor += 1;
        if ((s8)s_ListCursor >= s_ShopItemCount) {
            s_ListCursor = 0;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if ((g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
        if (Fishing_ShopTradeBlocked(s_ListCursor, 1) == 0) {
            total =
                Item_Count(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_id,
                           0) +
                Item_Count(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_id, 1);
            if (total >= FISHING_SHOP_STACK_MAX) {
                s_ListCursor |= FISHING_SHOP_CURSOR_LOCKED;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                s_ListItemId = 0;
                s_Step       = 3;
            } else {
                s_ListCursor |= FISHING_SHOP_CURSOR_CHOSEN;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                s_Step += 1;
            }
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
        goto tail; /* skips the cancel branch: the confirm path shares the tail */
    }
    if ((g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
        s_ShopDeclined = 1;
        s_ListCursor |= FISHING_SHOP_CURSOR_LOCKED;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        s_ShopMode += 1;
    }
tail:
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    if (((s8)s_ListCursor & (FISHING_SHOP_CURSOR_CHOSEN | FISHING_SHOP_CURSOR_LOCKED)) == 0) {
        WinDrawCueText(0x18, 0x14,
                       Item_GetDescription(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_category,
                                           g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_id) &
                           HALF_MASK);
    }
    Fishing_ShopDrawTradeList(0);
}

/* func_800F550C */
MATCH void Fishing_ShopChooseQuantity(void) {
    s32 delta;
    s32 slot;
    u8  previous;
    u8  quantity;
    s32 held;

    delta = 0;
    switch (INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL) & HALF_MASK) {
        case PADLright:
            delta = 1;
            break;
        case PADLup:
            delta = 10;
            break;
        case PADLleft:
            delta = -1;
            break;
        case PADLdown:
            delta = -10;
            break;
    }
    previous     = s_ListItemId;
    s_ListItemId = previous + delta;
    quantity     = s_ListItemId;
    if ((s8)quantity > 0) {
        if ((s8)quantity > FISHING_SHOP_STACK_MAX) {
            quantity = FISHING_SHOP_STACK_MAX;
        }
    } else {
        quantity = 1;
    }
    s_ListItemId = quantity;
    slot         = s_ListCursor & FISHING_SHOP_CURSOR_ROW;
    while (Fishing_ShopTradeBlocked(slot, s_ListItemId) != 0) {
        s_ListItemId = s_ListItemId - 1;
    }
    held = Item_Count(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].give_id, 0) +
           Item_Count(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].give_id, 1);
    held &= BYTE_MASK;
    while (1) {
        if (held + (s8)s_ListItemId <= FISHING_SHOP_STACK_MAX) {
            break;
        }
        s_ListItemId = s_ListItemId - 1;
    }
    if ((s8)s_ListItemId != (s8)previous) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CAST]) {
        s_ShopDeclined = 0;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        s_Step = s_Step + 1;
    } else if (g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) {
        s_ListItemId = 1;
        s_ListCursor &= ~FISHING_SHOP_CURSOR_CHOSEN;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        s_Step = s_Step - 1;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_TextDraw(24, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_COUNT_PROMPT));
    Fishing_ShopDrawTradeList(1);
    Fishing_ShopDrawQuantity();
    UI_CursorDraw(26, 107, 0);
}

/* func_800F5828 */
MATCH void Fishing_ShopConfirm(void) {
    s32  i;
    u8*  src;
    u16* pad;

    pad = &g_PadStates[0].pressed;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        s_ShopDeclined ^= 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    } else if (*pad & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        s_Step -= 1;
    } else if (*pad & g_InputMasks[FISHING_INPUT_CAST]) {
        if (s_ShopDeclined != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            s_Step -= 1;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
            s_ListCursor &= ~FISHING_SHOP_CURSOR_CHOSEN;
            Item_Add(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor]].give_id,
                     s_ListItemId, 0);
            Fishing_ShopTakeTradeItems();
            s_ListItemId = 1;
            s_Step       = 0;
        }
    }

    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);

    if (s_Step == 2) {
        src = Item_GetRecord(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][s_ListCursor & FISHING_SHOP_CURSOR_ROW]].give_category,
                             g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][s_ListCursor & FISHING_SHOP_CURSOR_ROW]].give_id);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = src[i];
        }
        D_801490E4[0] = 0;
        UI_TextDraw(40, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_CONFIRM_ITEM));
        UI_TextDraw(238, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_YES_NO));
        UI_CursorDraw((s_ShopDeclined << 5) + 0xED, 22, 0);
    }

    Fishing_ShopDrawTradeList(1);
    if (s_Step != 0) {
        Fishing_ShopDrawQuantity();
    }
}

/* func_800F5AD8 */
MATCH void Fishing_ShopTooGreedy(void) {
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    if ((g_PadStates[0].pressed & (g_InputMasks[FISHING_INPUT_CAST] | g_InputMasks[FISHING_INPUT_CANCEL])) != 0) {
        s_ListItemId = 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        s_Step = 0;
        s_ListCursor &= ~FISHING_SHOP_CURSOR_LOCKED;
        Fishing_ShopDrawTradeList(0);
    } else {
        UI_TextDraw(24, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_TOO_GREEDY));
        Fishing_ShopDrawTradeList(1);
        Fishing_ShopDrawQuantity();
    }
}

/* func_800F5BA4 */
MATCH void Fishing_ShopConfirmAll(void) {
    s_ShopSteps[9 + s_Step]();
}

/* func_800F5BE0 */
MATCH void Fishing_ShopConfirmAllInput(void) {
    u16* keys;

    keys = &g_PadStates[0].pressed;
    if ((INPUT_REPEATED(*keys, (PADLright | PADLleft)) & (PADLright | PADLleft)) != 0) {
        s_ShopDeclined ^= 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    } else {
        if ((*keys & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
            s_ShopDeclined = 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            {
                u8 prev_mode = s_ShopMode - 1;
                u8 unlocked  = s_ListCursor & ~FISHING_SHOP_CURSOR_LOCKED;

                s_ListCursor = unlocked;
                s_ShopMode   = prev_mode;
            }
        }
        if ((*keys & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
            if (s_ShopDeclined == 0) {
                UI_ModeSet(0);
                s_Step += 1;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                {
                    u8 prev_mode = s_ShopMode - 1;
                    u8 unlocked  = s_ListCursor & ~FISHING_SHOP_CURSOR_LOCKED;

                    s_ListCursor = unlocked;
                    s_ShopMode   = prev_mode;
                }
            }
        }
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    UI_TextDraw(24, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_CONFIRM_ALL));
    UI_CursorDraw(s_ShopDeclined * 32 + 0xEE, 22, 0);
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
    UI_TextDraw(24, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_CONFIRM_ALL));
    UI_CursorDraw(s_ShopDeclined * 32 + 0xEE, 22, 0);
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
    tpage              = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)cursor);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));
    for (i = 0; i < 2; i++) {
        s32 quad_tpage;

        cursor = g_GfxPrimCursor;
        SetPolyFT4((POLY_FT4*)cursor);
        quad_tpage                 = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
        ((POLY_FT4*)cursor)->x1    = i * 160 + 160;
        ((POLY_FT4*)cursor)->x0    = i * 160;
        ((POLY_FT4*)cursor)->tpage = quad_tpage;
        ((POLY_FT4*)cursor)->clut  = getClut(0, 490);
        ((POLY_FT4*)cursor)->y0    = 0;
        ((POLY_FT4*)cursor)->y1    = 0;
        ((POLY_FT4*)cursor)->y2    = 240;
        ((POLY_FT4*)cursor)->y3    = 240;
        setUV4(((POLY_FT4*)cursor), 0, 0, 160, 0, 0, 240, 160, 240);
        setRGB0(((POLY_FT4*)cursor), 64, 64, 64);
        ((POLY_FT4*)cursor)->x2 = ((POLY_FT4*)cursor)->x0;
        ((POLY_FT4*)cursor)->x3 = ((POLY_FT4*)cursor)->x1;
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));
    }
    cursor             = g_GfxPrimCursor;
    g_GfxPrimCursor    = cursor + 8;
    ((RECT*)cursor)->x = 0;
    ((RECT*)cursor)->y = 0;
    ((RECT*)cursor)->h = 256;
    ((RECT*)cursor)->w = 256;
    tpage              = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)cursor);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));
}

/* func_800F606C */
MATCH void Fishing_ShopDrawTradeList(s32 draw_all) {
    u8* name;
    u8  blocked;
    s32 i;
    u8  n;
    n = draw_all & BYTE_MASK;
    Fishing_ShopDrawListWindow(20, 56, n);
    UI_TextDraw(54, 62, (u8)(n * 7), TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_TRADE_ITEM_LABEL));
    for (i = 0; i < s_ShopItemCount; i++) {
        name    = Item_GetRecord(g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_category, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_id);
        blocked = Fishing_ShopTradeBlocked(i & BYTE_MASK, 1);
        if ((draw_all & BYTE_MASK) != 0) {
            UI_TextDraw(37, (0x51 + (i * 13)), UI_TEXT_DIM, Game_ReadCommand(name) & BYTE_MASK, name);
            Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_id,
                                     g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_category, 1);
        } else if (i == ((s8)s_ListCursor)) {
            if ((blocked & BYTE_MASK) == 0) {
                UI_TextDraw(37, (0x51 + (i * 13)), UI_TEXT_DIM, Game_ReadCommand(name) & BYTE_MASK, name);
                Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_id,
                                         g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_category, 1);
            }
            UI_TextDraw(37, (0x4F + (i * 13)), (u8)(blocked * 7), Game_ReadCommand(name) & BYTE_MASK, name);
            Fishing_ShopDrawItemIcon(28, (s16)(0x52 + (i * 13)), g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_id,
                                     g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_category, blocked & BYTE_MASK);
        } else {
            UI_TextDraw(37, (0x51 + (i * 13)), (u8)(blocked * 7), Game_ReadCommand(name) & BYTE_MASK, name);
            Fishing_ShopDrawItemIcon(28, (s16)(0x54 + (i * 13)), g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_id,
                                     g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][i]].give_category, blocked & BYTE_MASK);
        }
    }
}

/* func_800F63CC */
MATCH void Fishing_ShopDrawListWindow(u16 x, u16 y, u8 color) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_WindowDraw(x, (y + 1), 140, 160, (color | 0x80), g_WindowStyle);
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
    u8  need_item;

    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        need_item = g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot & BYTE_MASK]].need_item[i];
        if (need_item == GAME_NONE) {
            return false;
        }
        if ((Item_Count(ITEM_CATEGORY_ITEM, (need_item + ITEM_JELLYFISH), 0) & HALF_MASK) <
            g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot & BYTE_MASK]].need_count[i] * (amount & BYTE_MASK)) {
            return true;
        }
    }
    return false;
}

/* func_800F66D4 */
MATCH u8 Fishing_ShopItemCount(void) {
    u8 index;

    for (index = 0; index < 10; index++) {
        if (g_FishingShopStock[g_GameEntryFacing][index] == GAME_NONE) {
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

    slot = s_ListCursor & FISHING_SHOP_CURSOR_ROW;
    Fishing_ShopDrawNeededWindow(168, 64);
    UI_TextDraw(210, 71, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_NEEDED_LABEL));
    Fishing_ShopDrawNeededWindow(168, 140);
    UI_TextDraw(215, 147, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_OWNED_LABEL));
    if ((s8)s_ListCursor & FISHING_SHOP_CURSOR_LOCKED) {
        return;
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].need_item[i] == GAME_NONE) {
            break;
        }
        value = Item_GetRecord(ITEM_CATEGORY_ITEM, (u8)((g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].need_item[i] + ITEM_JELLYFISH) & BYTE_MASK));
        UI_TextDraw(173, (0x58 + i * 13), 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
        TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].need_count[i] * (s8)s_ListItemId);
        UI_TextDrawGlyphString(272, (0x5C + i * 13), 0, g_UiTextFormatBuffer);
        cost = Item_Count(ITEM_CATEGORY_ITEM, (g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].need_item[i] + ITEM_JELLYFISH) & BYTE_MASK, 0);
        if (cost < g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][slot]].need_count[i]) {
            UI_TextDraw(173, (0xA4 + i * 13), UI_TEXT_DIM, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
            TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, cost);
            UI_TextDrawGlyphString(272, (0xA8 + i * 13), UI_TEXT_DIM, g_UiTextFormatBuffer);
        } else {
            UI_TextDraw(173, (0xA4 + i * 13), 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);
            TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, cost);
            UI_TextDrawGlyphString(272, (0xA8 + i * 13), 0, g_UiTextFormatBuffer);
        }
    }
}

/* func_800F6A84 */
MATCH void Fishing_ShopDrawNeededWindow(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 x2;
    s16 y2;

    UI_WindowDraw(x, (y + 1), 132, 66, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);

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

    slot = s_ListCursor & FISHING_SHOP_CURSOR_ROW;
    Fishing_ShopDrawQuantityWindow(20, 100);

    entry = g_FishingShopStock[g_GameEntryFacing][slot];
    value = Item_GetRecord(g_FishingTrades[entry].give_category, g_FishingTrades[entry].give_id);
    UI_TextDraw(33, 104, 0, Game_ReadCommand((u8*)value) & BYTE_MASK, (u8*)value);

    TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, (s8)s_ListItemId);
    UI_TextDrawGlyphString(132, 108, 0, g_UiTextFormatBuffer);

    entry = g_FishingShopStock[g_GameEntryFacing][slot];
    Fishing_ShopDrawItemIcon(24, 108, g_FishingTrades[entry].give_id, g_FishingTrades[entry].give_category, 0);

    UI_TextDraw(33, 124, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_NONE_OWNED));

    entry = g_FishingShopStock[g_GameEntryFacing][slot];
    TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, Item_Count(g_FishingTrades[entry].give_category, g_FishingTrades[entry].give_id, 0) & HALF_MASK);
    UI_TextDrawGlyphString(132, 128, 0, g_UiTextFormatBuffer);

    UI_TextDraw(33, 136, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_SHOP_MESSAGE_NONE_EQUIPPED));

    entry = g_FishingShopStock[g_GameEntryFacing][slot];
    TEXT_Format(g_UiTextFormatBuffer, D_800F5000.format, Item_Count(g_FishingTrades[entry].give_category, g_FishingTrades[entry].give_id, 1) & HALF_MASK);
    UI_TextDrawGlyphString(132, 140, 0, g_UiTextFormatBuffer);
}

/* func_800F6EE0 */
MATCH void Fishing_ShopDrawQuantityWindow(u16 x, u16 y) {
    s32 i;
    s32 offset;
    s16 y2;

    UI_WindowDraw(x, y, 136, 54, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);
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
        UI_IconDraw((u16)x, (u16)y, s_ShopItemIcons[Item_GetIcon(category & BYTE_MASK, item_id) & BYTE_MASK], selected);
    }
}

/* func_800F7100 */
MATCH void Fishing_ShopTakeTradeItems(void) {
    s32 i;
    s32 trade_id;
    u8  count;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        trade_id = g_FishingShopStock[g_GameEntryFacing][(s8)s_ListCursor];
        if (g_FishingTrades[trade_id].need_item[i] == GAME_NONE) {
            break;
        }
        count = g_FishingTrades[trade_id].need_count[i] * ((s8)s_ListItemId);
        Item_Remove(ITEM_CATEGORY_ITEM, (g_FishingTrades[g_FishingShopStock[g_GameEntryFacing][s_ListCursor & FISHING_SHOP_CURSOR_ROW]].need_item[i] + ITEM_JELLYFISH) & BYTE_MASK, count & BYTE_MASK,
                    0);
    }
}
