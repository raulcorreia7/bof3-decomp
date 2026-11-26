#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D2ADC(void) {
    u8  saved[3];
    s8  shade;
    u8* green;
    u8* blue;

    g_ShisuToppingScale = g_ShisuScales[g_ShisuIngredients.topping_size];
    saved[0]            = g_ShisuToppingR;
    saved[1]            = g_ShisuToppingG;
    saved[2]            = g_ShisuToppingB;
    if (g_ShisuToppingR > g_ShisuIngredients.used[3] * 3) {
        g_ShisuToppingR -= g_ShisuIngredients.used[3] * 3;
    } else {
        g_ShisuToppingR = 0;
    }
    green = &g_ShisuToppingG;
    if (0xFF - *green > g_ShisuIngredients.used[3] * 3) {
        shade = *green + g_ShisuIngredients.used[3] * 3;
    } else {
        shade = -1;
    }
    *green = shade;
    FAKE_BARRIER(); /* FAKE: keeps the tint store ahead of the next color's address. */
    blue = &g_ShisuToppingB;
    if (*blue > g_ShisuIngredients.used[3] * 3) {
        *blue -= g_ShisuIngredients.used[3] * 3;
    } else {
        *blue = 0;
    }
    func_801D2308(&D_801DA0C0);
    g_ShisuToppingR = saved[0];
    g_ShisuToppingG = saved[1];
    g_ShisuToppingB = saved[2];
}

MATCH void func_801D2C0C(void) {
    SYS_DISPATCH_BYTE(D_801D9720, D_801DA048.header.mode);
}

MATCH void func_801D2C48(void) {
}

MATCH void func_801D2C50(void) {
    s32* value;

    value = &g_ShisuBaseAngle;
    *value += 0x20;
    func_801D2978();
}

MATCH void func_801D2C84(void) {
    s32* value = &g_ShisuBaseAngle;

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
    h = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
    if ((h << 16) < *p) {
        *p         = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16;
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
    SYS_DISPATCH_BYTE(D_801D9734, D_801DA0C0.header.mode);
}

MATCH void func_801D2DE4(void) {
}

MATCH void func_801D2DEC(void) {
    s32* value;

    value = &g_ShisuToppingAngle;
    *value -= 0x20;
    func_801D2ADC();
}

MATCH void func_801D2E20(void) {
    s32* value = &g_ShisuToppingAngle;

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

    target = (Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) + g_ShisuBaseScale * 0xA00;
    delta  = (Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16) + SHISU_HEIGHT_BIAS - target;
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

    value = &g_ShisuToppingAngle;
    *value += 0x20;
    func_801D2ADC();
}

MATCH void func_801D2F9C(void) {
    SYS_DISPATCH_TASK(g_ShisuTaskSteps, 2, g_UiPanelCurrent);
}

MATCH void func_801D2FE0(void) {
}

MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, 0);
}

MATCH void func_801D3018(void) {
    s16 id;

    g_ShisuTask1Steps[g_UiPanelCurrent->state]();
    Menu_DrawHeaderBar((u16)g_UiPanelCurrent->pos.vx, (u16)g_UiPanelCurrent->pos.vy, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    id = (s16)g_UiPanelCurrent->u.message.id;
    if (id != 0) {
        UI_TextDraw((s16)(g_UiPanelCurrent->pos.vx + 7), (s16)(g_UiPanelCurrent->pos.vy + 3), 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, id));
    }
}

/* func_801D30E4 */
MATCH void UI_PanelSlideOutTask_801D30E4(void) {
    Menu_SlidePanelUp();
}

/* func_801D3124 */
MATCH void UI_PanelSlideInTaskTop_801D3124(void) {
    u16 next_pos;

    next_pos                 = g_UiPanelCurrent->pos.vy + 0x10;
    g_UiPanelCurrent->pos.vy = next_pos;
    if ((s16)next_pos >= 0x11) {
        g_UiPanelCurrent->pos.vy = 16U;
        g_UiPanelCurrent->state  = 0;
    }
}

/* func_801D3164 */
MATCH void Shisu_UpdateCommandPanel(void) {
    g_ShisuTask2Steps[g_UiPanelCurrent->state]();
    Menu_DrawCommandRow(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, g_UiPanelCurrent->unk_0A, g_UiPanelCurrent->unk_0B, 0);
}

/* func_801D31CC */
MATCH void UI_PanelSlideOutTask_801D31CC(void) {
    Menu_SlidePanelUp();
}

/* func_801D320C */
MATCH void Menu_AdvancePanelY(void) {
    u16 next_pos;

    next_pos                 = g_UiPanelCurrent->pos.vy + 0x10;
    g_UiPanelCurrent->pos.vy = next_pos;
    if ((s16)next_pos >= 0x27) {
        g_UiPanelCurrent->pos.vy = 38U;
        g_UiPanelCurrent->state  = 0;
    }
}

MATCH void func_801D324C(void) {
    g_ShisuTask3Steps[g_UiPanelCurrent->state]();
    func_801D3320(g_UiPanelCurrent);
}

MATCH void func_801D32A0(void) {
    u16 x;

    x                        = g_UiPanelCurrent->pos.vx - 0x20;
    g_UiPanelCurrent->pos.vx = x;
    if ((s16)x < -200) {
        g_UiPanelCurrent->pos.vx = -0xC8;
        g_UiPanelCurrent->state  = 0;
    }
}

/* func_801D32E0 */
MATCH void UI_PanelSetPosX_801D32E0(void) {
    u16 next_pos;

    next_pos                 = g_UiPanelCurrent->pos.vx + 0x20;
    g_UiPanelCurrent->pos.vx = next_pos;
    if ((s16)next_pos >= 0x12) {
        g_UiPanelCurrent->pos.vx = 17U;
        g_UiPanelCurrent->state  = 0;
    }
}

MATCH void func_801D3320(MenuPanelTask* task) {
    u8 i;

    UI_WindowDraw((u16)(task->pos.vx + 3), (u16)(task->pos.vy + 3), 0x95, 0xA0, 0, g_WindowStyle);
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
            UI_ListDrawItemRow((s16)(task->pos.vx + 7), (s16)((u32)task->pos.vy + (i * 13 + 0x1A)), shade, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], flag);
        } else {
            if (MEM_PTR(u8, task->item_table)[i] != 0) {
                UI_ListDrawItemRow((s16)(task->pos.vx + 7), (s16)((u32)task->pos.vy + (i * 13 + 0x1A)), 7, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], 1);
            }
            UI_ListDrawItemRow((s16)(task->pos.vx + 7), (s16)(task->pos.vy + i * 13 + 0x18), shade, 0, D_801D9798[i], MEM_PTR(u8, task->item_table)[i], flag);
        }
        i++;
    } while (i < 4);
    UI_TextDraw((s16)((u16)task->pos.vx + 0x4E - strlen((char*)D_801D979C) * 4), (s16)(task->pos.vy + 7), 0, MENU_LABEL_LENGTH, D_801D979C);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, D_801D9780, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, D_801D978C, UI_SPRITE_ALT_PAGE);
    i = 0;
    do {
        UI_SpriteDraw((s16)(task->pos.vx + (i + 5) * 8), task->pos.vy, 1, UI_SPRITE_ALT_PAGE);
        i++;
    } while (i < 0xA);
    i = 0;
    do {
        UI_SpriteDraw(task->pos.vx, (s16)(task->pos.vy + (i + 3) * 8), 4, UI_SPRITE_ALT_PAGE);
        i++;
    } while (i < 0x11);
    UI_SpriteDraw((s16)(task->pos.vx + 0x90), (s16)(task->pos.vy + 0x18), 0x20, UI_SPRITE_ALT_PAGE);
    i = 0;
    do {
        UI_SpriteDraw((s16)(task->pos.vx + 0x90), (s16)(task->pos.vy + (i + 4) * 8), 0x21, UI_SPRITE_ALT_PAGE);
        i++;
    } while (i < 0xF);
    UI_SpriteDraw(task->pos.vx, (s16)(task->pos.vy + 0xA0), 5, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(task->pos.vx + 0x90), (s16)(task->pos.vy + 0x98), 0x22, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(task->pos.vx + 8), task->pos.vy, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(task->pos.vx + 0x90), task->pos.vy, 0x34, UI_SPRITE_ALT_PAGE);
    i = 0;
    do {
        UI_SpriteDraw((s16)(task->pos.vx + (i + 1) * 8), (s16)(task->pos.vy + 0xA0), 6, UI_SPRITE_ALT_PAGE);
        i++;
    } while (i < 0x11);
}

/* Draws one party member's status window from g_Characters: portrait, name, level, the poison
 * and confusion labels, HP, AP and the experience bar. */
MATCH void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_index, s32 shaded, s32 unused) {
    Character* records;
    Character* stats;
    u32        clut;
    u32        text_clut;
    s32        text_y;
    s32        x;
    s32        y;

    clut = (u8)shaded ? 7 : 0;
    UI_WindowDraw(px + 3, py + 3, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (u8)shaded, CHARACTER_BLOCK->window_style);
    x = px;
    y = py;
    /* FAKE: the order lock keeps the x and y copies below the window call. */
    FAKE_ORDER_LOCK_BEGIN
        records = (Character*)CHARACTER_BLOCK->records;
        stats   = &records[character_index];
        Menu_DrawCharacterPortrait((px + 0x56) & HALF_MASK, (py + 2) & HALF_MASK, stats->character_id, (u8)shaded == 0 ? (stats->status >> 6) & 2 : 1);
        text_clut = clut & BYTE_MASK;
        UI_TextDraw(x + 20, y + 3, text_clut, CHARACTER_NAME_LENGTH, stats);
    FAKE_ORDER_LOCK_END;
    TEXT_Format(g_UiTextFormatBuffer, g_MenuStatFormat, stats->level);
    text_y = (s16)(y + 0x17);
    UI_TextDrawGlyphString(x + 22, text_y, text_clut, g_UiTextFormatBuffer);
    if ((LOWU(stats->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_TextDrawString(x + 46, text_y, text_clut != 0 ? text_clut : 1, MENU_LABEL_LENGTH, D_801D9B3C);
        } else {
            UI_TextDrawString(x + 46, text_y, text_clut != 0 ? text_clut : 1, MENU_LABEL_LENGTH, D_801D9B44);
        }
    } else if (stats->status & STATUS_POISONED) {
        UI_TextDrawString(x + 46, text_y, text_clut != 0 ? text_clut : 1, MENU_LABEL_LENGTH, D_801D9B3C);
    } else if (stats->status & STATUS_CONFUSED) {
        UI_TextDrawString(x + 46, text_y, text_clut != 0 ? text_clut : 1, MENU_LABEL_LENGTH, D_801D9B44);
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
    TEXT_Format(g_UiTextFormatBuffer, g_MenuCurrentValueFormat, stats->hp);
    UI_TextDrawGlyphString(x + 22, y + 31, clut, g_UiTextFormatBuffer);
    if ((u8)shaded == 0) {
        clut = (stats->fatigue != 0) * 4;
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiTextFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_hp);
    UI_TextDrawGlyphString(x + 22, y + 31, clut, g_UiTextFormatBuffer);
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
    TEXT_Format(g_UiTextFormatBuffer, g_MenuCurrentValueFormat, stats->ap);
    UI_TextDrawGlyphString(x + 22, y + 39, clut, g_UiTextFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    TEXT_Format(g_UiTextFormatBuffer, g_MenuMaxValueFormat, stats->stats.max_ap);
    UI_TextDrawGlyphString(x + 22, y + 39, clut, g_UiTextFormatBuffer);
    UI_SpriteDrawRun(x, y, D_801D97A4, 0);
    Menu_DrawExperienceLine(x + 0x14, y + 0x12, character_index, stats->level, stats->exp);
    /* FAKE: dead stores keep px and py the CSE heads of their x and y copies. */
    px = 0;
    py = 0;
}

#include "overlays/menu/shared/Menu_DrawStatPanel.h"

#include "overlays/menu/shared/Menu_DrawEquipmentPanel.h"

MATCH void func_801D4158(s16 x, s16 y, u8 index, u8 flag) {
    Character* character;
    s16        label_x;
    s32        text_x;
    s32        exp_value;
    /* FAKE: retail reserves 24 frame bytes between the outgoing arguments and
     * the saved registers that no statement in the body uses. */
    FAKE_STACK_PADS(u8, 24);

    UI_WindowDraw((u16)(x + 3), (u16)(y + 3), 0x65, 0x25, 0, CHARACTER_BLOCK->window_style);
    character = (Character*)CHARACTER_BLOCK->records[index];
    text_x    = x;
    label_x   = text_x + 0x26;
    UI_TextDraw((flag == 0) ? text_x + 0x2C : label_x, (s16)(y + 7), 0, TEXT_LENGTH_MAX, (flag == 0) ? (u8*)&g_MenuLabelEquip[8] : (u8*)&g_MenuLabelEquip[0xC]);
    if (flag == 0) {
        exp_value = character->exp;
    } else {
        exp_value = Char_GetExpForLevel(index, (character->level + 1) & 0xFF);
    }
    if (exp_value != -1) {
        sprintf(g_UiTextFormatBuffer, &g_MenuStatFormat[0x14], exp_value);
    } else {
        sprintf(g_UiTextFormatBuffer, &g_MenuStatFormat[0x18]);
    }
    UI_TextDrawAscii((s16)(x + 0x15), (s16)(y + 0x1A), 0, g_UiTextFormatBuffer);
    UI_SpriteDrawRun(x, y, &g_MenuInventoryTab1OnSprites[0x24], UI_SPRITE_ALT_PAGE);
}

#include "overlays/menu/shared/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/shared/Menu_DrawTintedLine.h"

#include "overlays/menu/shared/Menu_DrawItemRow.h"

#include "overlays/menu/shared/Menu_DrawEquipment.h"

#include "overlays/menu/shared/Menu_DrawFormationPreview.h"

#include "overlays/menu/shared/Menu_DrawIcon.h"

/* func_801D5620 */
MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#include "overlays/menu/shared/Menu_DrawExperienceLine.h"

#include "overlays/menu/shared/Menu_DrawZennyWindow.h"

#include "overlays/menu/shared/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/shared/Menu_ChooseYesNo.h"

#include "overlays/menu/shared/Menu_DrawCommandRow.h"

#include "overlays/menu/shared/Item_GetPrice.h"

#include "overlays/menu/shared/Char_GetExpForLevel.h"

#include "overlays/menu/shared/Char_GetExpProgress.h"

#include "shared/Menu_DrawHeaderBar.h"

#include "overlays/menu/shared/Menu_DrawEquipCompareWindow.h"

#include "overlays/menu/shared/Menu_DrawRowIcons.h"

#include "overlays/menu/shared/Menu_DrawEquipStatWindow.h"

const char g_MenuInventoryCountFormat[8] = "%3d/%3d";
const u8   D_801D0D48[4]                 = {0, 0, 0, 0};

#include "overlays/menu/shared/Menu_DrawClutStrip.h"

#include "overlays/menu/shared/Menu_DrawFilledPanel.h"

#include "overlays/menu/shared/Menu_DrawWindowFrame.h"

#include "overlays/menu/shared/Menu_DrawInventoryWindow.h"

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

    UI_WindowDraw((panel->pos.x + 3) & HALF_MASK, (panel->pos.y + 3) & HALF_MASK, 154, 160, 0, g_WindowStyle);
    n    = 0;
    list = Party_GetAbilities(panel->group, panel->group_first, 0);
    y    = panel->pos.y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->type, D_80148656, *list) == 0;
            shade  = locked ? UI_TEXT_DIM : UI_TEXT_NORMAL;
            if (n == panel->drawn_cursor) {
                shade = UI_TEXT_HIGHLIGHT;
            }
            level   = Char_AbilityGetElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_AbilityGetCost(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *list, 0);
            if (n == panel->drawn_cursor || n == panel->group_cursor) {
                if (shade != UI_TEXT_DIM) {
                    UI_ListDrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x1A), UI_TEXT_DIM, level, (u8*)ability, count, 1);
                }
                UI_ListDrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x18), shade, level, (u8*)ability, count, locked);
            } else {
                UI_ListDrawAbilityRow((s16)(panel->pos.x + 7), (s16)(y + 0x1A), shade, level, (u8*)ability, count, locked);
            }
        }
        n++;
        y += 13;
        list++;
    } while (n < 10);
    x = panel->pos.x + 0x4E;
    UI_TextDraw((x - strlen(D_801D9EA4[panel->group_first]) * 4), (panel->pos.y + 7), 0, MENU_LABEL_LENGTH, D_801D9EA4[panel->group_first]);
    UI_SpriteDrawRun(panel->pos.x, panel->pos.y, (FIELD(u8, panel, 0x9u) & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(panel->pos.x, panel->pos.y, (FIELD(u8, panel, 0x9u) & MENU_LIST_FLAG_TAB_1) ? D_801D999C : D_801D9990, UI_SPRITE_ALT_PAGE);
    flags = FIELD(u8, panel, 0x9u);
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        FIELD(u8, panel, 0x9u) = 0;
    } else {
        FIELD(u8, panel, 0x9u) = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < 10; n++) {
        UI_SpriteDraw(panel->pos.x + (n + 5) * 8, panel->pos.y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (n = 0; n < 17; n++) {
        UI_SpriteDraw(panel->pos.x, panel->pos.y + (n + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(panel->pos.x + 144, panel->pos.y + 24, 0x20, UI_SPRITE_ALT_PAGE);
    for (n = 0; n < 15; n++) {
        UI_SpriteDraw(panel->pos.x + 144, panel->pos.y + (n + 4) * 8, 0x21, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(panel->pos.x, panel->pos.y + 160, 5, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(panel->pos.x + 144, panel->pos.y + 152, 0x22, UI_SPRITE_ALT_PAGE);
    if ((s16)panel->unk_10 != 0) {
        UI_SpriteDraw(panel->pos.x + 8, panel->pos.y, 0x32, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(panel->pos.x + 144, panel->pos.y, 0x34, UI_SPRITE_ALT_PAGE);
    }
    for (n = 0; n < 17; n++) {
        UI_SpriteDraw(panel->pos.x + (n + 1) * 8, panel->pos.y + 160, 6, UI_SPRITE_ALT_PAGE);
    }
}

#include "overlays/menu/shared/Menu_DrawPanelFrame.h"

/* func_801D8A78 */
#include "overlays/menu/shared/Menu_DrawEquipChoiceWindow.h"

#include "overlays/menu/shared/SAVE_DrawSlotRow.h"

#include "overlays/menu/shared/SAVE_DrawPortTabs.h"
