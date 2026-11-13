#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D2ADC(void) {
    u8  saved[3];
    s8  shade;
    u8* green;
    u8* blue;

    D_801DA100 = D_801D9688[g_MenuStatusItems.unk_0B];
    saved[0]   = D_801DA11D;
    saved[1]   = D_801DA11E;
    saved[2]   = D_801DA11F;
    if (D_801DA11D > g_MenuStatusItems.used[3] * 3) {
        D_801DA11D -= g_MenuStatusItems.used[3] * 3;
    } else {
        D_801DA11D = 0;
    }
    green = &D_801DA11E;
    if (0xFF - *green > g_MenuStatusItems.used[3] * 3) {
        shade = *green + g_MenuStatusItems.used[3] * 3;
    } else {
        shade = -1;
    }
    *green = shade;
    FAKE_BARRIER(); /* FAKE: keeps the tint store ahead of the next color's address. */
    blue = &D_801DA11F;
    if (*blue > g_MenuStatusItems.used[3] * 3) {
        *blue -= g_MenuStatusItems.used[3] * 3;
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
    Menu_DrawCursorSprite(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0);
}

MATCH void func_801D3018(void) {
    s16 id;

    g_MenuStatusTask1StateFuncs[g_MenuCurrentPanel->state]();
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
MATCH void Menu_StatusCommandsPanel(void) {
    g_MenuStatusTask2StateFuncs[g_MenuCurrentPanel->state]();
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
    g_MenuStatusTask3StateFuncs[g_MenuCurrentPanel->state]();
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

INCLUDE_ASM(func_801D3320);

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

#include "overlays/menu/Menu_DrawFormationPreview.h"

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
            shade  = locked ? 7 : 0;
            if (n == panel->drawn_cursor) {
                shade = 2;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *list, 0);
            if (n == panel->drawn_cursor || n == panel->group_cursor) {
                if (shade != 7) {
                    func_801AF930((s16)(panel->pos.x + 7), (s16)(y + 0x1A), 7, level, (u8*)ability, count, 1);
                }
                func_801AF930((s16)(panel->pos.x + 7), (s16)(y + 0x18), shade, level, (u8*)ability, count, locked);
            } else {
                func_801AF930((s16)(panel->pos.x + 7), (s16)(y + 0x1A), shade, level, (u8*)ability, count, locked);
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
