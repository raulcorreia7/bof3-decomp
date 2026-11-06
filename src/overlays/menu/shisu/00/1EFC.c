#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* blocker: entry reads v0 and v1 before setting them. */
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

/* blocker: intermediate subtraction; first diff: +0x54 loads 0x02000000, not 0xFE000000. */
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
    SYS_DISPATCH_TASK(g_MenuStatusTaskFuncs, 2, g_MenuCurrentPanel);
}

MATCH void func_801D2FE0(void) {
}

MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, 0);
}

INCLUDE_ASM(func_801D3018);

MATCH void func_801D30E4(void) {
    Menu_SlidePanelUp();
}

MATCH void func_801D3124(void) {
    u16 next_pos;

    next_pos              = g_MenuCurrentPanel->y + 0x10;
    g_MenuCurrentPanel->y = next_pos;
    if ((s16)next_pos >= 0x11) {
        g_MenuCurrentPanel->y     = 16U;
        g_MenuCurrentPanel->state = 0;
    }
}

MATCH void func_801D3164(void) {
    D_801D9768[g_MenuCurrentPanel->state]();
    Menu_DrawCommandRow(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, g_MenuCurrentPanel->unk_0A,
                        g_MenuCurrentPanel->unk_0B, 0);
}

MATCH void func_801D31CC(void) {
    Menu_SlidePanelUp();
}

MATCH void func_801D320C(void) {
    u16 next_pos;

    next_pos              = g_MenuCurrentPanel->y + 0x10;
    g_MenuCurrentPanel->y = next_pos;
    if ((s16)next_pos >= 0x27) {
        g_MenuCurrentPanel->y     = 38U;
        g_MenuCurrentPanel->state = 0;
    }
}

MATCH void func_801D324C(void) {
    D_801D9774[g_MenuCurrentPanel->state]();
    func_801D3320(g_MenuCurrentPanel);
}

MATCH void func_801D32A0(void) {
    u16 x;

    x                     = g_MenuCurrentPanel->x - 0x20;
    g_MenuCurrentPanel->x = x;
    if ((s16)x < -200) {
        LOH(g_MenuCurrentPanel->x) = -0xC8;
        g_MenuCurrentPanel->state  = 0;
    }
}

MATCH void func_801D32E0(void) {
    u16 next_pos;

    next_pos              = g_MenuCurrentPanel->x + 0x20;
    g_MenuCurrentPanel->x = next_pos;
    if ((s16)next_pos >= 0x12) {
        g_MenuCurrentPanel->x     = 17U;
        g_MenuCurrentPanel->state = 0;
    }
}

INCLUDE_ASM(func_801D3320);

/* blocker: register homes (py in s2, shaded byte in s3). */
INCLUDE_ASM(Menu_DrawCharacterWindow);

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

INCLUDE_ASM(func_801D4158);

#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

#include "overlays/menu/Menu_DrawItemRow.h"

#include "overlays/menu/Menu_DrawEquipment.h"

INCLUDE_ASM(func_801D4DC0);

#include "overlays/menu/Menu_DrawIcon.h"

/* func_801D5620 */
MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

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

/* blocker: frame 0x58 against 0x50 and save order. */
INCLUDE_ASM(Menu_DrawEquipStatWindow);

INCLUDE_ASM(func_801D7224);

#include "overlays/menu/Menu_DrawFilledPanel.h"

/* blocker: per-band draw-mode setup. */
INCLUDE_ASM(Menu_DrawWindowFrame);

/* blocker: first diff: +0x138 lhu v1,18(s1) (template andi v1,s0,0xff). */
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

    UI_DrawWindow((panel->x + 3) & HALF_MASK, (panel->y + 3) & HALF_MASK, 154, 160, 0, g_SaveData.window_style);
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
            count   = Char_GetAbilityCost(g_CharSlot[g_SaveData.walk_order[(s8)D_80148656]], *list, 0);
            if (n == panel->drawn_cursor || n == panel->group_cursor) {
                if (shade != 7) {
                    func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), 7, level, (u8*)ability, count, 1);
                }
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x18), shade, level, (u8*)ability, count, locked);
            } else {
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), shade, level, (u8*)ability, count, locked);
            }
        }
        n++;
        y += 0xD;
        list++;
    } while (n < 10);
    x = panel->x + 0x4E;
    UI_DrawText((x - strlen(D_801D9EA4[panel->group_first]) * 4), (panel->y + 7), 0, 0x10,
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
    UI_DrawWindow(left + 8, y, 200, 48, 0, g_SaveData.window_style);
    if (row != NULL) {
        if (GetGraphType() != 1) {
            GetGraphType();
        }
        GFX_AddDrawMode(0xF);
        Menu_DrawPanelIcon((left + 9), (top + 5), (u8)(index + 3), 0x1E, GetClut(16, 480), 128);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            icon = *(row->unk_00 + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_DrawText((x + 21), (y + 3), 0, 5, (u8*)row);
        sprintf((char*)g_UiFormatBuffer, D_801D0D64, row->unk_00[8]);
        UI_DrawGlyphString((x + 31), (y + 24), 0, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801D0D68, row->unk_00[0xC], row->unk_00[0xD]);
        label_x = x + 0x27;
        UI_DrawGlyphString(label_x, (y + 37), 0, g_UiFormatBuffer);
        UI_DrawGlyphString(label_x, (y + 36), 0, (u8*)&D_801D0D74);
        UI_DrawGlyphString(label_x, (y + 39), 0, (u8*)&D_801D0D74);
        Menu_DrawExperienceLine((x + 0x14), (y + 0x12), 0, row->unk_00[8], ((MenuListRowWords*)row)->unk_10);
    }
    UI_DrawSpriteRun(x, y, D_801D9A60, row->unk_00[0x14] && row ? 2 : 0);
    if (row != NULL && row->unk_00[0x14] != 0) {
        UI_DrawSprite((x + 50), (y + 22), 0x3D, 0);
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
    left    = (x + 6);
    UI_DrawText((x + 42), (y + 7), 0, 0xFF, texture);

    color = (flags & 1) ? 0 : 7;
    UI_DrawText(left, (y + 25), color, 0xFF, Resource_GetText(0x85));
    right  = (x + 94);
    text_y = (y + 25);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D78);

    color = (flags & 2) ? 0 : 7;
    UI_DrawText(left, (y + 41), color, 0xFF, Resource_GetText(0x85));
    text_y = (y + 41);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D7C);

    row_offset = (row << 4);
    Menu_DrawCursorSprite((x + 8), (row_offset + y + 28), 0);
}
