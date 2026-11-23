#include "battle_15.h"

/* func_80164EF8 and Menu_DrawPanelIcon are not declared by the shared headers. */
void func_80164EF8(s32 index, u8* patch, u8* flags, u16* values);
void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);

/* func_800B3324 */
/* The equipped-item compare window: the member's name and four stats, the four stats the
 * equipped items would give (func_80164EF8), and the six equipment rows with their icons.
 * The labels, slot icons and slot categories come from the panel tables object. */
#ifdef NON_MATCHING
NON_MATCHING void func_800B3324(u8 index, s32 x, s32 y, s32 patch, u8 hide_changes, MenuPanelTask* task) {
    struct {
        u8  pad[32];
        u8  flags[8];
        u16 values[4];
    } compare;

    Character* chr;
    Stats*     stats;
    u8*        record;
    u8         items[EQUIP_SLOT_COUNT];
    u8         i;
    u8         shade;
    s32        icon;
    s32        draw_y;
    s32        label_y;
    s32        left;
    s32        top;

    UI_WindowDraw((u16)(x + 4), (u16)(y + 4), 0x78, 0xA3, 0, CHARACTER_BLOCK->window_style);
    chr = (Character*)CHARACTER_BLOCK->records[index];

    shade = (u8)Game_ReadCommand((u8*)chr);
    left  = x;
    top   = y;
    stats = &chr->stats;
    if (shade > CHARACTER_NAME_LENGTH) {
        shade = CHARACTER_NAME_LENGTH;
    }
    UI_TextDraw((s16)(x + (0x3E - shade * 6)), (s16)(y + 7), UI_TEXT_NORMAL, CHARACTER_NAME_LENGTH, (u8*)chr);
    for (i = 0, label_y = y + 0x1A; i < 4; i++) {
        UI_TextDraw((s16)(x + 5), (s16)(label_y + i * 13), UI_TEXT_NORMAL, 4, s_BattlePanelEquipTables.stat_labels[i]);
    }

    Char_RebuildStats(chr);
    sprintf(g_UiTextFormatBuffer, D_80096A54, stats->power);
    UI_TextDrawGlyphString((s16)(left + 0x31), (s16)(top + 0x1C), UI_TEXT_NORMAL, g_UiTextFormatBuffer);
    sprintf(g_UiTextFormatBuffer, D_80096A54, stats->defense);
    UI_TextDrawGlyphString((s16)(left + 0x31), (s16)(top + 0x29), UI_TEXT_NORMAL, g_UiTextFormatBuffer);
    sprintf(g_UiTextFormatBuffer, D_80096A54, stats->intelligence);
    UI_TextDrawGlyphString((s16)(left + 0x31), (s16)(top + 0x36), UI_TEXT_NORMAL, g_UiTextFormatBuffer);
    sprintf(g_UiTextFormatBuffer, D_80096A54, stats->agility);
    UI_TextDrawGlyphString((s16)(left + 0x31), (s16)(top + 0x43), UI_TEXT_NORMAL, g_UiTextFormatBuffer);

    if ((hide_changes & 1) == 0) {
        func_80164EF8(index, (u8*)patch, compare.flags, compare.values);
        for (i = 0; i < 4; i++) {
            if (compare.flags[i] == 4) {
                icon = 0x11;
            } else if (compare.flags[i] == 1) {
                icon = 0x12;
            } else {
                icon = 0x13;
            }
            GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
            Menu_DrawPanelIcon((u16)(left + 0x51), (u16)(top + (i * 13 + 0x1A) + 2), icon, 0x1C, GetClut(0, STAGE_PALETTE_Y), GFX_COLOR_NEUTRAL);
            sprintf(g_UiTextFormatBuffer, D_80096A54, compare.values[i]);
            UI_TextDrawGlyphString((s16)(left + 0x59), (s16)(top + (i * 13 + 0x1A) + 2), compare.flags[i], g_UiTextFormatBuffer);
        }
    }

    items[EQUIP_SLOT_WEAPON]      = chr->equip.weapon;
    items[EQUIP_SLOT_SHIELD]      = chr->equip.shield;
    items[EQUIP_SLOT_HELMET]      = chr->equip.helmet;
    items[EQUIP_SLOT_ARMOR]       = chr->equip.armor;
    items[EQUIP_SLOT_ACCESSORY_1] = chr->equip.accessories[0];
    items[EQUIP_SLOT_ACCESSORY_2] = chr->equip.accessories[1];
    draw_y                        = top + 0x55;
    task->u.addr.unk_10           = 0;
    for (i = 0; i < EQUIP_SLOT_COUNT; i++) {
        record = Item_GetRecord(s_BattlePanelEquipTables.slot_categories[i], items[i]);
        shade  = (i == task->unk_0B) ? UI_TEXT_HIGHLIGHT : UI_TEXT_NORMAL;
        if ((task->flags & 2) != 0) {
            if ((Item_PassesTest(ITEM_TEST_SELECTABLE, g_CharSlot[g_PartyBattleOrder[(s8)D_80148656]], s_BattlePanelEquipTables.slot_categories[i], items[i]) & BYTE_MASK) == 0) {
                shade = UI_TEXT_DIM;
            } else if (i == task->unk_0A) {
                task->u.addr.unk_10 = (s_BattlePanelEquipTables.slot_categories[i] << 8) + items[i];
            }
        }
        if (shade != UI_TEXT_DIM) {
            UI_IconDraw((u16)(left + 6), (u16)(draw_y + 2), s_BattlePanelEquipTables.slot_icons[i], 1);
            UI_TextDraw((s16)(left + 0x11), (s16)draw_y, UI_TEXT_DIM, Game_ReadCommand(record) & BYTE_MASK, record);
        }
        if (i == task->unk_0B || i == task->unk_0A) {
            draw_y -= 2;
        }
        UI_IconDraw((u16)(left + 6), (u16)(draw_y + 2), s_BattlePanelEquipTables.slot_icons[i], shade == UI_TEXT_DIM);
        UI_TextDraw((s16)(left + 0x11), (s16)draw_y, shade, Game_ReadCommand(record) & BYTE_MASK, record);
        if (i == task->unk_0B || i == task->unk_0A) {
            draw_y += 2;
        }
        draw_y += 13;
    }

    UI_SpriteDrawRun((s16)left, (s16)top, s_BattlePanelValueRun, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 7; i++) {
        UI_SpriteDraw((s16)left, (s16)(top + (i + 3) * 8), 4, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw((s16)(left + 0x78), (s16)(top + (i + 3) * 8), 8, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw((s16)left, (s16)(top + (i + 11) * 8), 4, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw((s16)(left + 0x78), (s16)(top + (i + 11) * 8), 8, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 14; i++) {
        UI_SpriteDraw((s16)(left + (i + 1) * 8), (s16)(top + 0x50), 0xE, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw((s16)(left + (i + 1) * 8), (s16)(top + 0xA0), 0x11, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)left, (s16)(top + 0x50), 0xD, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(left + 0x78), (s16)(top + 0x50), 0xF, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)left, (s16)(top + 0xA0), 0x10, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(left + 0x78), label_y = (s16)(top + 0xA0), 0x12, UI_SPRITE_ALT_PAGE);
}
#else
INCLUDE_ASM(func_800B3324);
#endif
