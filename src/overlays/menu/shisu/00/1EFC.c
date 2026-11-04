#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D2AFC);

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

INCLUDE_ASM(func_801D2C84);

INCLUDE_ASM(func_801D2CE4);

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

INCLUDE_ASM(func_801D2E20);

INCLUDE_ASM(func_801D2E80);

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
    SYS_DISPATCH_TASK(g_MenuStatusTaskFuncs, 2, g_MenuPanelTaskCurrent);
}

MATCH void func_801D2FE0(void) {
}

/* func_801D2FE8 */
MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y, 0);
}

INCLUDE_ASM(func_801D3018);

MATCH void func_801D30E4(void) {
    Menu_SlidePanelUp();
}

MATCH void func_801D3124(void) {
    u16 next_pos;

    next_pos                  = g_MenuPanelTaskCurrent->y + 0x10;
    g_MenuPanelTaskCurrent->y = next_pos;
    if ((s16)next_pos >= 0x11) {
        g_MenuPanelTaskCurrent->y     = 16U;
        g_MenuPanelTaskCurrent->state = 0;
    }
}

MATCH void func_801D3164(void) {
    D_801D9768[g_MenuPanelTaskCurrent->state]();
    Menu_DrawCommandRow(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y, g_MenuPanelTaskCurrent->unk_0A,
                        g_MenuPanelTaskCurrent->unk_0B, 0);
}

MATCH void func_801D31CC(void) {
    Menu_SlidePanelUp();
}

MATCH void func_801D320C(void) {
    u16 next_pos;

    next_pos                  = g_MenuPanelTaskCurrent->y + 0x10;
    g_MenuPanelTaskCurrent->y = next_pos;
    if ((s16)next_pos >= 0x27) {
        g_MenuPanelTaskCurrent->y     = 38U;
        g_MenuPanelTaskCurrent->state = 0;
    }
}

MATCH void func_801D324C(void) {
    D_801D9774[g_MenuPanelTaskCurrent->state]();
    func_801D3320(g_MenuPanelTaskCurrent);
}

MATCH void func_801D32A0(void) {
    u16 x;

    x                         = g_MenuPanelTaskCurrent->x - 0x20;
    g_MenuPanelTaskCurrent->x = x;
    if ((s16)x < -200) {
        LOH(g_MenuPanelTaskCurrent->x) = -0xC8;
        g_MenuPanelTaskCurrent->state  = 0;
    }
}

MATCH void func_801D32E0(void) {
    u16 next_pos;

    next_pos                  = g_MenuPanelTaskCurrent->x + 0x20;
    g_MenuPanelTaskCurrent->x = next_pos;
    if ((s16)next_pos >= 0x12) {
        g_MenuPanelTaskCurrent->x     = 17U;
        g_MenuPanelTaskCurrent->state = 0;
    }
}

INCLUDE_ASM(func_801D3320);

/* Same body in the shop, start, Bate and Shisu overlays; the shop draft is the closest start, and the retail register homes keep py in s2 and the shaded byte in s3. */
INCLUDE_ASM(Menu_DrawCharacterWindow);

#include "overlays/menu/Menu_DrawStatPanel.h"

MATCH void func_801D3F0C(s16 x, s16 y, u8 record_index) {
    const volatile void* objects[6];
    Character*           record;
    u16                  row_y;
    u8                   row;

    Menu_DrawFilledPanel(x, y, 9, 0xA);
    record = &g_Characters[record_index];
    UI_DrawText((s16)(x + 46), (s16)(y + 7), 0, 0xFF, (u8*)&D_801D9B64);
    func_801644D8(0, (s32)(u16)(x + 7), (s32)(u16)(y + 5), 0x10, 0x10, 0x80);

    objects[0] = &g_Weapons[record->weapon];
    objects[1] = &g_Armors[record->shield];
    objects[2] = &g_Armors[record->helmet];
    objects[3] = &g_Armors[record->armor];
    objects[4] = &g_Accessories[record->accessories[0]];
    objects[5] = &g_Accessories[record->accessories[1]];

    for (row = 0; row < 6; row++) {
        row_y = (u16)(y + (row * 0xD + 0x1A));
        func_801AEA80((s32)(u16)(x + 5), (s32)(u16)(row_y + 2), D_801D9B5C[row], 0);
        UI_DrawText((s16)(x + 17), (s16)row_y, 0, func_801AF20C((u8*)objects[row]) & BYTE_MASK, (u8*)objects[row]);
    }
}

INCLUDE_ASM(func_801D4158);

#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

/* func_801D4754 */
MATCH void Menu_DrawItemRow(s32 x0, s32 y0, s32 item, s32 selection) {
    u8* cell;
    s32 row_off;
    u8  count;
    u8  mode;
    u8  palette;
    u8  item_index;
    s16 tx;
    s16 stat_x;
    s16 stat_y;
    s32 count_y;

    mode       = selection & BYTE_MASK;
    palette    = (u8)((0u - (u32)(mode != 0)) & 7);
    item_index = item & BYTE_MASK;
    UI_DrawWindowOutline((s16)(x0 + 2), (s16)(y0 + 2), 0x86, 0x2A, 0xF1);
    row_off = item_index * 0xA4;
    cell    = (u8*)&g_Characters[0].max_hp + row_off;
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x4u));
    stat_x = (s16)(x0 + 0x29);
    stat_y = (s16)(y0 + 5);
    UI_DrawGlyphString(stat_x, stat_y, (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x6u));
    UI_DrawGlyphString(stat_x, (s16)(y0 + 18), (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0xAu));
    UI_DrawGlyphString((s16)(x0 + 111), stat_y, (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x8u));
    UI_DrawGlyphString((s16)(x0 + 111), (s16)(y0 + 18), (u32)palette, g_UiFormatBuffer);
    UI_DrawText((s16)(x0 + 5), (s16)(y0 + 3), (s32)palette, 4U, (u8*)&D_801D9BA8);
    UI_DrawText((s16)(x0 + 5), (s16)(y0 + 16), (s32)palette, 4U, &D_801D9BA8[6]);
    UI_DrawText((s16)(x0 + 75), (s16)(y0 + 3), (s32)palette, 4U, &D_801D9BA8[0xC]);
    UI_DrawText((s16)(x0 + 75), (s16)(y0 + 16), (s32)palette, 4U, &D_801D9BA8[0x12]);
    UI_DrawWindowOutline((s16)(x0 + 0x33), (s16)(y0 + 0x2E), 0x56, 0x14, 0xF1);
    Menu_DrawIcon((u16)(x0 + 0x36), (u16)(y0 + 0x30), 4U, mode);
    sprintf((s8*)g_UiFormatBuffer, g_MenuZennyFormat, *(s32*)((u8*)&g_Characters[0].exp + row_off));
    UI_DrawGlyphString((s16)(x0 + 78), (s16)(y0 + 48), (u32)palette, g_UiFormatBuffer);
    Menu_DrawIcon((u16)(x0 + 0x36), (u16)(y0 + 0x39), 5U, mode);
    count = ((u8*)&g_Characters[0].level)[row_off];
    if (count < 0x63U) {
        count_y = y0;
        sprintf((s8*)g_UiFormatBuffer, g_MenuZennyFormat, Char_GetExpForLevel(item_index, (count + 1) & BYTE_MASK));
    } else {
        count_y = y0;
        sprintf((s8*)g_UiFormatBuffer, (s8*)D_801D0C2C);
    }
    UI_DrawGlyphString((s16)(x0 + 78), (s16)(count_y + 57), (u32)palette, g_UiFormatBuffer);
}

#include "overlays/menu/Menu_DrawEquipment.h"

INCLUDE_ASM(func_801D4DC0);

#include "overlays/menu/Menu_DrawIcon.h"

MATCH void func_801D5620(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

/* func_801D56D8 */
#include "overlays/menu/Menu_DrawExperienceLine.h"

#include "overlays/menu/Menu_DrawZennyWindow.h"

#include "overlays/menu/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/Menu_ToggleOption.h"

#include "overlays/menu/Menu_DrawCommandRow.h"

#include "overlays/menu/Item_GetPrice.h"

#include "overlays/menu/Char_GetExpForLevel.h"

#include "overlays/menu/Char_GetExpProgress.h"

INCLUDE_ASM(Menu_DrawHeaderBar);

INCLUDE_ASM(func_801D65DC);

#include "overlays/menu/Menu_DrawRowIcons.h"

/* Same body in the shop, start, Bate and Shisu overlays; the shop draft differs from retail in frame size (0x58 against 0x50) and save order, and the retail parameter locals sit in s6, s3, s0 and s4. */
INCLUDE_ASM(Menu_DrawEquipStatWindow);

INCLUDE_ASM(func_801D7224);

#include "overlays/menu/Menu_DrawFilledPanel.h"

/* Same body in the shop, start, Bate and Shisu overlays; the start draft covers the five SPRT bands and four corner sprites, and the missing piece is a source shape for the retail per-band draw-mode setup. */
INCLUDE_ASM(Menu_DrawWindowFrame);

/* Same shape as bate/00 func_801D6C54: follows etc/game/00 func_801999F8.
 * First differing instruction: +0x138 `lhu v1,18(s1)` (template `andi v1,s0,0xff`). */
INCLUDE_ASM(func_801D7BFC);

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

    UI_DrawWindow((panel->x + 3) & HALF_MASK, (panel->y + 3) & HALF_MASK, 154, 160, 0, D_80144952);
    n    = 0;
    list = Party_GetAbilities(panel->group, panel->group_first, 0);
    y    = panel->y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->kind, D_80148656, *list) == 0;
            shade  = locked ? 7 : 0;
            if (n == panel->drawn_cursor) {
                shade = 2;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[D_80144F5A[(s8)D_80148656]], *list, 0);
            if (n == panel->drawn_cursor || n == panel->group_cursor) {
                if (shade != 7) {
                    func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), 7, (u8)level, (u8*)ability, (u8)count, 1);
                }
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x18), shade, (u8)level, (u8*)ability, (u8)count, locked);
            } else {
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), shade, (u8)level, (u8*)ability, (u8)count, locked);
            }
        }
        n++;
        y += 0xD;
        list++;
    } while (n < 10);
    x = panel->x + 0x4E;
    UI_DrawText((s16)(x - strlen(D_801D9EA4[panel->group_first]) * 4), (s16)(panel->y + 7), 0, 0x10,
                D_801D9EA4[panel->group_first]);
    UI_DrawSpriteRun(panel->x, panel->y, (FIELD(u8, panel, 0x9u) & 2) ? D_801D9978 : D_801D9960, 1);
    UI_DrawSpriteRun(panel->x, panel->y, (FIELD(u8, panel, 0x9u) & 1) ? D_801D999C : D_801D9990, 1);
    flags = FIELD(u8, panel, 0x9u);
    if (!(flags & 0xF0)) {
        FIELD(u8, panel, 0x9u) = 0;
    } else {
        FIELD(u8, panel, 0x9u) = flags - 0x10;
    }
    for (n = 0; n < 10; n++) {
        UI_DrawSprite(panel->x + (n + 5) * 8, panel->y, 1, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x, panel->y + (n + 3) * 8, 4, 1);
    }
    UI_DrawSprite(panel->x + 144, panel->y + 24, 0x20, 1);
    for (n = 0; n < 15; n++) {
        UI_DrawSprite(panel->x + 144, panel->y + (n + 4) * 8, 0x21, 1);
    }
    UI_DrawSprite(panel->x, panel->y + 160, 5, 1);
    UI_DrawSprite(panel->x + 144, panel->y + 152, 0x22, 1);
    if ((s16)panel->unk_10 != 0) {
        UI_DrawSprite(panel->x + 8, panel->y, 0x32, 1);
        UI_DrawSprite(panel->x + 144, panel->y, 0x34, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x + (n + 1) * 8, panel->y + 160, 6, 1);
    }
}

#include "overlays/menu/Menu_DrawPanelFrame.h"

INCLUDE_ASM(func_801D8A78);

MATCH void func_801D91B0(u8 index, s32 left, s32 top, MenuListRow* row) {
    s16 x;
    s16 y;
    s16 label_x;
    u8  i;
    u8  icon;

    x = left;
    y = top;
    UI_DrawWindow(left + 8, y, 200, 48, 0, D_80144952);
    if (row != NULL) {
        if (GetGraphType() != 1) {
            GetGraphType();
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, 0xF, NULL);
        GFX_AddPrim(1, 0xC);
        func_801D5620((u16)(left + 9), (u16)(top + 5), (u8)(index + 3), 0x1E, (u16)GetClut(16, 480), 128);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            icon = *(row->unk_00 + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_DrawText((s16)(x + 21), (s16)(y + 3), 0, 5, (u8*)row);
        sprintf((char*)g_UiFormatBuffer, D_801D0D64, row->unk_00[8]);
        UI_DrawGlyphString((s16)(x + 31), (s16)(y + 24), 0, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801D0D68, row->unk_00[0xC], row->unk_00[0xD]);
        label_x = x + 0x27;
        UI_DrawGlyphString(label_x, (s16)(y + 37), 0, g_UiFormatBuffer);
        UI_DrawGlyphString(label_x, (s16)(y + 36), 0, (u8*)&D_801D0D74);
        UI_DrawGlyphString(label_x, (s16)(y + 39), 0, (u8*)&D_801D0D74);
        Menu_DrawExperienceLine((u16)(x + 0x14), (u16)(y + 0x12), 0, row->unk_00[8], *(u32*)(row->unk_00 + 0x10));
    }
    UI_DrawSpriteRun((s16)x, (s16)y, D_801D9A60, row->unk_00[0x14] && row ? 2 : 0);
    if (row != NULL && row->unk_00[0x14] != 0) {
        UI_DrawSprite((s16)(x + 50), (s16)(y + 22), 0x3D, 0);
    }
}

MATCH void func_801D94B0(s16 x, s16 y, u32 flags, u8 row, u8 variant) {
    s16 left;
    s16 right;
    s16 text_y;
    u16 row_offset;
    u8  color;
    u32 shade;
    u8* texture;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(20, (u16)(x + 7), (u16)(y + 5), 16, 16, 128);
    shade = 0x1C;
    if (variant == 0) {
        shade = 0x1B;
    }
    texture = Resource_GetText(shade);
    left    = (s16)(x + 6);
    UI_DrawText((s16)(x + 42), (s16)(y + 7), 0, 0xFF, texture);

    color = (flags & 1) ? 0 : 7;
    UI_DrawText(left, (s16)(y + 25), color, 0xFF, Resource_GetText(0x85));
    right  = (s16)(x + 94);
    text_y = (s16)(y + 25);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D78);

    color = (flags & 2) ? 0 : 7;
    UI_DrawText(left, (s16)(y + 41), color, 0xFF, Resource_GetText(0x85));
    text_y = (s16)(y + 41);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D7C);

    row_offset = (u16)((u32)row << 4);
    Menu_DrawCursorSprite((u16)(x + 8), (u16)(row_offset + y + 28), 0);
}
