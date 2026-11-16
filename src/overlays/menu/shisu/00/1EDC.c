#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D2ADC(void) {
    u8  saved[3];
    s8  shade;
    u8* green;
    u8* blue;

    D_801DA100 = D_801D9688[g_MenuShisuIngredients.unk_0B];
    saved[0]   = D_801DA11D;
    saved[1]   = D_801DA11E;
    saved[2]   = D_801DA11F;
    if (D_801DA11D > g_MenuShisuIngredients.used[3] * 3) {
        D_801DA11D -= g_MenuShisuIngredients.used[3] * 3;
    } else {
        D_801DA11D = 0;
    }
    green = &D_801DA11E;
    if (0xFF - *green > g_MenuShisuIngredients.used[3] * 3) {
        shade = *green + g_MenuShisuIngredients.used[3] * 3;
    } else {
        shade = -1;
    }
    *green = shade;
    FAKE_BARRIER(); /* FAKE: keeps the tint store ahead of the next color's address. */
    blue = &D_801DA11F;
    if (*blue > g_MenuShisuIngredients.used[3] * 3) {
        *blue -= g_MenuShisuIngredients.used[3] * 3;
    } else {
        *blue = 0;
    }
    func_801D2308(&D_801DA0C0);
    D_801DA11D = saved[0];
    D_801DA11E = saved[1];
    D_801DA11F = saved[2];
}

MATCH void func_801D2C0C(void) {
    SYS_DISPATCH_BYTE(D_801D9720, D_801DA049);
}

MATCH void func_801D2C48(void) {
}

MATCH void func_801D2C50(void) {
    s32* value;

    value = &D_801DA0B4;
    *value += 0x20;
    func_801D2978();
}

MATCH void func_801D2C84(void) {
    s32* value = &D_801DA0B4;

    if ((*value & 0xFFF) != 0) {
        *value     = (*value + 0x40) & 0xFC0;
        D_801DA04E = 0;
    } else {
        D_801DA04E = 1;
    }
    func_801D2978();
}

MATCH void func_801D2CE4(void) {
    s32* p;
    s32  h;

    p = &D_801DA084;
    *p += 0x200000;
    h = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
    if ((h << 16) < *p) {
        *p         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16;
        D_801DA04E = 1;
    } else {
        D_801DA04E = 0;
    }
    func_801D2978();
}

MATCH void func_801D2D88(void) {
    func_801D2978();
}

MATCH void func_801D2DA8(void) {
    SYS_DISPATCH_BYTE(D_801D9734, D_801DA0C1);
}

MATCH void func_801D2DE4(void) {
}

MATCH void func_801D2DEC(void) {
    s32* value;

    value = &D_801DA12C;
    *value -= 0x20;
    func_801D2ADC();
}

MATCH void func_801D2E20(void) {
    s32* value = &D_801DA12C;

    if ((*value & 0xFFF) != 0) {
        *value     = (*value - 0x40) & 0xFC0;
        D_801DA0C6 = 0;
    } else {
        D_801DA0C6 = 1;
    }
    func_801D2ADC();
}

MATCH void func_801D2E80(void) {
    s32* follow;
    s32  target;
    s32  delta;

    target = (Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) + D_801DA088 * 0xA00;
    delta  = (Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) + MENU_SHISU_HEIGHT_BIAS - target;
    follow = &D_801DA0FC;
    *follow -= delta / 16;
    if (*follow < target) {
        *follow    = target;
        D_801DA0C6 = 1;
    } else {
        D_801DA0C6 = 0;
    }
    func_801D2ADC();
}

MATCH void func_801D2F48(void) {
    func_801D2ADC();
}

MATCH void func_801D2F68(void) {
    s32* value;

    value = &D_801DA12C;
    *value += 0x20;
    func_801D2ADC();
}

MATCH void func_801D2F9C(void) {
    SYS_DISPATCH_TASK(g_MenuShisuTaskSteps, 2, g_MenuCurrentPanel);
}

MATCH void func_801D2FE0(void) {
}

MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0);
}

MATCH void func_801D3018(void) {
    s16 id;

    g_MenuShisuTask1Steps[g_MenuCurrentPanel->state]();
    Menu_DrawHeaderBar(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    id = (s16)g_MenuCurrentPanel->u.message.id;
    if (id != 0) {
        UI_DrawText((s16)(g_MenuCurrentPanel->pos.x + 7), (s16)(g_MenuCurrentPanel->pos.y + 3), 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, id));
    }
}

MATCH void func_801D30E4(void) {
    Menu_SlidePanelUp();
}

MATCH void func_801D3124(void) {
    u16 next_pos;

    next_pos                  = g_MenuCurrentPanel->pos.y + 0x10;
    g_MenuCurrentPanel->pos.y = next_pos;
    if ((s16)next_pos >= 0x11) {
        g_MenuCurrentPanel->pos.y = 16U;
        g_MenuCurrentPanel->state = 0;
    }
}

/* func_801D3164 */
MATCH void Menu_ShisuCommandsPanel(void) {
    g_MenuShisuTask2Steps[g_MenuCurrentPanel->state]();
    Menu_DrawCommandRow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_0A, g_MenuCurrentPanel->unk_0B, 0);
}

MATCH void func_801D31CC(void) {
    Menu_SlidePanelUp();
}

/* func_801D320C */
MATCH void Menu_SetPosY(void) {
    u16 next_pos;

    next_pos                  = g_MenuCurrentPanel->pos.y + 0x10;
    g_MenuCurrentPanel->pos.y = next_pos;
    if ((s16)next_pos >= 0x27) {
        g_MenuCurrentPanel->pos.y = 38U;
        g_MenuCurrentPanel->state = 0;
    }
}

MATCH void func_801D324C(void) {
    g_MenuShisuTask3Steps[g_MenuCurrentPanel->state]();
    func_801D3320(g_MenuCurrentPanel);
}

MATCH void func_801D32A0(void) {
    u16 x;

    x                         = g_MenuCurrentPanel->pos.x - 0x20;
    g_MenuCurrentPanel->pos.x = x;
    if ((s16)x < -200) {
        LOH(g_MenuCurrentPanel->pos.x) = -0xC8;
        g_MenuCurrentPanel->state      = 0;
    }
}

/* func_801D32E0 */
MATCH void Menu_SetPosX(void) {
    u16 next_pos;

    next_pos                  = g_MenuCurrentPanel->pos.x + 0x20;
    g_MenuCurrentPanel->pos.x = next_pos;
    if ((s16)next_pos >= 0x12) {
        g_MenuCurrentPanel->pos.x = 17U;
        g_MenuCurrentPanel->state = 0;
    }
}

MATCH void func_801D3320(MenuPanelTask* task) {
    u8 i;

    UI_DrawWindow((u16)(task->pos.x + 3), (u16)(task->pos.y + 3), 0x95, 0xA0, 0, g_WindowStyle);
    i = 0;
    do {
        u8 shade;
        u8 flag;

        if (MEM_PTR(u8, task->item_table)[i] != 0) {
            shade = 0;
            flag  = 0;
        } else {
            shade = 7;
            flag  = 1;
        }
        if (i != task->unk_0A) {
            func_801AF800((s16)(task->pos.x + 7), (s16)((u32)task->pos.y + (i * 13 + 0x1A)), shade, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], flag);
        } else {
            if (MEM_PTR(u8, task->item_table)[i] != 0) {
                func_801AF800((s16)(task->pos.x + 7), (s16)((u32)task->pos.y + (i * 13 + 0x1A)), 7, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], 1);
            }
            func_801AF800((s16)(task->pos.x + 7), (s16)(task->pos.y + i * 13 + 0x18), shade, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], flag);
        }
        i++;
    } while (i < 4);
    UI_DrawText((s16)(task->pos.x + 0x4E - strlen((char*)D_801D979C) * 4), (s16)(task->pos.y + 7), 0, 0x10, D_801D979C);
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, D_801D9780, 1);
    UI_DrawSpriteRun((s16)task->pos.x, (s16)task->pos.y, D_801D978C, 1);
    i = 0;
    do {
        UI_DrawSprite((s16)(task->pos.x + (i + 5) * 8), (s16)task->pos.y, 1, 1);
        i++;
    } while (i < 0xA);
    i = 0;
    do {
        UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + (i + 3) * 8), 4, 1);
        i++;
    } while (i < 0x11);
    UI_DrawSprite((s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x18), 0x20, 1);
    i = 0;
    do {
        UI_DrawSprite((s16)(task->pos.x + 0x90), (s16)(task->pos.y + (i + 4) * 8), 0x21, 1);
        i++;
    } while (i < 0xF);
    UI_DrawSprite((s16)task->pos.x, (s16)(task->pos.y + 0xA0), 5, 1);
    UI_DrawSprite((s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x98), 0x22, 1);
    UI_DrawSprite((s16)(task->pos.x + 8), (s16)task->pos.y, 0x32, 1);
    UI_DrawSprite((s16)(task->pos.x + 0x90), (s16)task->pos.y, 0x34, 1);
    i = 0;
    do {
        UI_DrawSprite((s16)(task->pos.x + (i + 1) * 8), (s16)(task->pos.y + 0xA0), 6, 1);
        i++;
    } while (i < 0x11);
}

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_index, s32 shaded, s32 unused) {
    Character* records;
    Character* stats;
    u32        clut;
    u32        text_clut;
    s32        text_y;
    s32        x;
    s32        y;

    clut = (u8)shaded ? 7 : 0;
    UI_DrawWindow(px + 3, py + 3, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (u8)shaded, CHARACTER_BLOCK->window_style);
    x = px;
    y = py;
    /* FAKE: the order lock keeps the x and y copies below the window call. */
    FAKE_ORDER_LOCK_BEGIN
        records = (Character*)CHARACTER_BLOCK->records;
        stats   = &records[character_index];
        Menu_DrawCharacterPortrait(px + 0x56, py + 2, stats->character_id, (u8)shaded == 0 ? (stats->status >> 6) & 2 : 1);
        text_clut = clut & BYTE_MASK;
        UI_DrawText(x + 20, y + 3, text_clut, 5, stats);
    FAKE_ORDER_LOCK_END;
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, stats->level);
    text_y = (s16)(y + 0x17);
    UI_DrawGlyphString(x + 22, text_y, text_clut, g_UiFormatBuffer);
    if ((LOWU(stats->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D9B3C);
        } else {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D9B44);
        }
    } else if (stats->status & STATUS_POISONED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D9B3C);
    } else if (stats->status & STATUS_CONFUSED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D9B44);
    }
    if (stats->hp < (u32)(stats->stats.max_hp >> 2)) {
        stats->status |= STATUS_LOW_HP;
    } else {
        stats->status &= ~STATUS_LOW_HP;
    }
    if ((u8)shaded == 0) {
        if (stats->status & STATUS_LOW_HP) {
            clut = 4;
        }
        if (stats->hp < 2) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuCurrentValueFormat, stats->hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    if ((u8)shaded == 0) {
        clut = (stats->fatigue != 0) * 4;
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    if ((u8)shaded == 0) {
        if (stats->ap < (u32)(stats->stats.max_ap >> 2)) {
            clut = 4;
        }
        if (stats->ap == 0) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, g_MenuCurrentValueFormat, stats->ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    TEXT_Format(g_UiFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801D97A4, 0);
    Menu_DrawExperienceLine(x + 0x14, y + 0x12, character_index, stats->level, stats->exp);
    /* FAKE: dead stores keep px and py the CSE heads of their x and y copies. */
    px = 0;
    py = 0;
}

#else
INCLUDE_ASM(Menu_DrawCharacterWindow);
#endif

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

MATCH void func_801D4158(s16 x, s16 y, u8 index, u8 flag) {
    Character* character;
    s16        label_x;
    s32        text_x;
    s32        exp_value;
    /* FAKE: retail reserves 24 frame bytes between the outgoing arguments and
     * the saved registers that no statement in the body uses. */
    FAKE_STACK_PADS(u8, 24);

    UI_DrawWindow((u16)(x + 3), (u16)(y + 3), 0x65, 0x25, 0, CHARACTER_BLOCK->window_style);
    character = (Character*)CHARACTER_BLOCK->records[index];
    text_x    = x;
    label_x   = text_x + 0x26;
    UI_DrawText((flag == 0) ? text_x + 0x2C : label_x, (s16)(y + 7), 0, 0xFF, (flag == 0) ? (u8*)&g_MenuLabelEquip[8] : (u8*)&g_MenuLabelEquip[0xC]);
    if (flag == 0) {
        exp_value = character->exp;
    } else {
        exp_value = Char_GetExpForLevel(index, (character->level + 1) & 0xFF);
    }
    if (exp_value != -1) {
        sprintf(g_UiFormatBuffer, &g_MenuStatFormat[0x14], exp_value);
    } else {
        sprintf(g_UiFormatBuffer, &g_MenuStatFormat[0x18]);
    }
    UI_DrawAsciiString((s16)(x + 0x15), (s16)(y + 0x1A), 0, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, &g_MenuInventoryTab1OnSprites[0x24], 1);
}

#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

#include "overlays/menu/Menu_DrawItemRow.h"

#include "overlays/menu/Menu_DrawEquipment.h"

#include "overlays/menu/Menu_DrawFormationPreview.h"

#include "overlays/menu/Menu_DrawIcon.h"

/* func_801D5620 */
MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#include "overlays/menu/Menu_DrawExperienceLine.h"

#include "overlays/menu/Menu_DrawZennyWindow.h"

#include "overlays/menu/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/Menu_ChooseYesNo.h"

#include "overlays/menu/Menu_DrawCommandRow.h"

#include "overlays/menu/Item_GetPrice.h"

#include "overlays/menu/Char_GetExpForLevel.h"

#include "overlays/menu/Char_GetExpProgress.h"

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s16       bottom_y;
    u8        bottom_v;
    s32       clut_x;
    s16       odd_h;
    s32       width_plus_1;
    s32       odd_width;

    u16 base_x;
    s32 r_s1;
    u16 r_s4;
    s32 r_s8;

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    setWH(texture_window, 16, 16);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    base_x = (u16)x;
    r_s8   = (s16)(x + 2);
    clut_x = ((s32)window_style << 5) + 0x10;
    setXY0(primitive, (s16)base_x, (s16)(u16)y);
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)base_x;
    primitive->x1 = (s16)r_s8;
    primitive->x3 = (s16)r_s8;
    setUV0(primitive, 0u, 0u);
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    setRGB0(primitive, 172, 172, 172);
    bottom_v      = (u8)(height + 1);
    bottom_y      = (s16)((s32)(u16)y + bottom_v);
    primitive->y2 = bottom_y;
    primitive->y3 = bottom_y;
    primitive->u1 = 2u;
    primitive->v2 = bottom_v;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    primitive->y0 += 2;
    primitive->y2 -= 3;
    primitive->v0 += 2;
    primitive->v2 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    width_plus_1    = (s32)(width + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    r_s1 = (s32)(u16)width_plus_1;
    r_s1 = ((s32)(u16)r_s1 - 4) >> 1;
    r_s4 = r_s1;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    odd_width = (width - 3) & 1;
    odd_h     = (s16)odd_width;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, (s16)r_s8, (s16)(u16)y, (s16)(r_s1 + r_s8), (s16)(u16)y, (s16)r_s8, bottom_y, (s16)(r_s1 + r_s8), bottom_y);
    setUV4(primitive, 0u, 0u, (u8)r_s4, 0u, 0u, bottom_v, (u8)r_s4, bottom_v);
    setRGB0(primitive, 172, 172, 172);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y0 = (s16)(u16)y;
    primitive->x0 = (s16)((s32)base_x + r_s1 + 2);
    primitive->x1 = (s16)(((s32)base_x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)((s32)base_x + r_s1 + 2);
    primitive->y2 = bottom_y;
    primitive->x3 = (s16)(((s32)base_x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y3 = bottom_y;
    setUV4(primitive, 0u, 0u, (u8)(r_s4 + odd_h), 0u, 0u, bottom_v, (u8)(r_s4 + odd_h), bottom_v);
    setRGB0(primitive, 172, 172, 172);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y2 = bottom_y;
    primitive->v2 = bottom_v;
    primitive->x1 = (s16)((s32)base_x + width_plus_1);
    primitive->y1 = (s16)(u16)y;
    primitive->x3 = (s16)((s32)base_x + width_plus_1);
    setXY0(primitive, (s16)((s32)base_x + width_plus_1 - 2), (s16)(u16)y);
    primitive->x2 = (s16)((s32)base_x + width_plus_1 - 2);
    primitive->y3 = bottom_y;
    setUV0(primitive, 0u, 0u);
    primitive->u1 = 2u;
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    setRGB0(primitive, 172, 172, 172);
    primitive->y1 += 2;
    primitive->y3 -= 3;
    primitive->y2 -= 1;
    primitive->v1 += 2;
    primitive->v2 -= 1;
    primitive->v3 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    setWH(texture_window, 256, 256);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    func_801AEBA0((s16)r_s8, (s16)((s32)(u16)y + 2), (s16)(width - 4), (s16)(height - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif

#include "overlays/menu/Menu_DrawEquipCompareWindow.h"

#include "overlays/menu/Menu_DrawRowIcons.h"

#include "overlays/menu/Menu_DrawEquipStatWindow.h"

const char g_MenuInventoryCountFormat[8] = "%3d/%3d";
const u8   D_801D0D48[4]                 = {0, 0, 0, 0};

#include "overlays/menu/Menu_DrawClutStrip.h"

#include "overlays/menu/Menu_DrawFilledPanel.h"

#include "overlays/menu/Menu_DrawWindowFrame.h"

#include "overlays/menu/Menu_DrawInventoryWindow.h"

MATCH void func_801D835C(MenuChoicePanel* panel) {
    Ability* ability;
    u8*      list;
    s32      level;
    s32      count;
    s32      locked;
    u8       shade;
    s32      x;
    u16      y;
    u8       flags;
    u8       n;

    UI_DrawWindow((panel->pos.x + 3) & HALF_MASK, (panel->pos.y + 3) & HALF_MASK, 154, 160, 0, g_WindowStyle);
    n    = 0;
    list = Party_GetAbilities(panel->group, panel->group_first, 0);
    y    = panel->pos.y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->kind, D_80148656, *list) == 0;
            shade  = locked ? MENU_SHADE_DIM : MENU_SHADE_NORMAL;
            if (n == panel->drawn_cursor) {
                shade = MENU_SHADE_SELECTED;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *list, 0);
            if (n == panel->drawn_cursor || n == panel->group_cursor) {
                if (shade != MENU_SHADE_DIM) {
                    UI_DrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x1A), MENU_SHADE_DIM, level, (u8*)ability, count, 1);
                }
                UI_DrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x18), shade, level, (u8*)ability, count, locked);
            } else {
                UI_DrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x1A), shade, level, (u8*)ability, count, locked);
            }
        }
        n++;
        y += 13;
        list++;
    } while (n < 10);
    x = panel->pos.x + 0x4E;
    UI_DrawText((x - strlen(D_801D9EA4[panel->group_first]) * 4), (panel->pos.y + 7), 0, 16, D_801D9EA4[panel->group_first]);
    UI_DrawSpriteRun(panel->pos.x, panel->pos.y, (FIELD(u8, panel, 0x9u) & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, 1);
    UI_DrawSpriteRun(panel->pos.x, panel->pos.y, (FIELD(u8, panel, 0x9u) & MENU_LIST_FLAG_TAB_1) ? D_801D999C : D_801D9990, 1);
    flags = FIELD(u8, panel, 0x9u);
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        FIELD(u8, panel, 0x9u) = 0;
    } else {
        FIELD(u8, panel, 0x9u) = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < 10; n++) {
        UI_DrawSprite(panel->pos.x + (n + 5) * 8, panel->pos.y, 1, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->pos.x, panel->pos.y + (n + 3) * 8, 4, 1);
    }
    UI_DrawSprite(panel->pos.x + 144, panel->pos.y + 24, 0x20, 1);
    for (n = 0; n < 15; n++) {
        UI_DrawSprite(panel->pos.x + 144, panel->pos.y + (n + 4) * 8, 0x21, 1);
    }
    UI_DrawSprite(panel->pos.x, panel->pos.y + 160, 5, 1);
    UI_DrawSprite(panel->pos.x + 144, panel->pos.y + 152, 0x22, 1);
    if ((s16)panel->unk_10 != 0) {
        UI_DrawSprite(panel->pos.x + 8, panel->pos.y, 0x32, 1);
        UI_DrawSprite(panel->pos.x + 144, panel->pos.y, 0x34, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->pos.x + (n + 1) * 8, panel->pos.y + 160, 6, 1);
    }
}

#include "overlays/menu/Menu_DrawPanelFrame.h"

/* func_801D8A78 */
#include "overlays/menu/Menu_DrawEquipChoiceWindow.h"

#include "overlays/menu/SAVE_DrawSlotRow.h"

#include "overlays/menu/SAVE_DrawPortTabs.h"
