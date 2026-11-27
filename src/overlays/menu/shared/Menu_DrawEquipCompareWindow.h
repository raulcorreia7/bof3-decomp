/* The equipment compare window: a party member's name, power, defense, intelligence and agility, the value each stat would reach with the equipment in patch (func_80164EF8) beside an icon chosen by its compare flag, and the six equipment slots, with the task's two selected slots raised. */
#define MENU_EQUIP_COMPARE_WINDOW_WIDTH  120
#define MENU_EQUIP_COMPARE_WINDOW_HEIGHT 163
#define MENU_EQUIP_COMPARE_STATS         4 /* power, defense, intelligence and agility */

/* func_801DE5D4 (start), func_801DB0DC (shop), func_801D5634 (bate), func_801D65DC (shisu) */
MATCH void Menu_DrawEquipCompareWindow(u8 index, s32 x, s32 y, u8* patch, u8 hide_changes, MenuPanelTask* task) {
    struct {
        u8  flags[8];
        u16 values[4];
        u8* names[EQUIP_SLOT_COUNT];
    } compare;

    Character* chr;
    Stats*     stats;
    u8         i;
    s32        icon;
    s32        label_y;
    u16        left;
    u16        top;

    left = x;
    top  = y;
    UI_WindowDraw(x + 4, y + 4, MENU_EQUIP_COMPARE_WINDOW_WIDTH, MENU_EQUIP_COMPARE_WINDOW_HEIGHT, 0, CHARACTER_BLOCK->window_style);
    chr   = (Character*)CHARACTER_BLOCK->records[index];
    stats = &chr->stats;
    UI_TextDraw(x + 32, y + 7, 0, CHARACTER_NAME_LENGTH, chr->name);
    for (i = 0, label_y = y + 26; i < MENU_EQUIP_COMPARE_STATS; i++) {
        UI_TextDraw(x + 5, label_y + i * 13, 0, 4, &g_MenuEquipCompareLabels[i * MENU_EQUIP_STAT_LABEL_SIZE]);
    }
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->power);
    UI_TextDrawGlyphString(left + 49, top + 28, 0, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->defense);
    UI_TextDrawGlyphString(left + 49, top + 41, 0, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->intelligence);
    UI_TextDrawGlyphString(left + 49, top + 54, 0, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->agility);
    UI_TextDrawGlyphString(left + 49, top + 67, 0, g_UITextFormatBuffer);

    if (hide_changes == 0) {
        func_80164EF8(index, patch, compare.flags, compare.values);
        for (i = 0; i < MENU_EQUIP_COMPARE_STATS; i++) {
            if (compare.flags[i] == 4) {
                icon = 0x11;
            } else if (compare.flags[i] == 1) {
                icon = 0x12;
            } else {
                icon = 0x13;
            }
            GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
            Menu_DrawPanelIcon(left + 81, top + 26 + i * 13 + 2, icon, 0x1C, GetClut(0, STAGE_PALETTE_Y), GFX_COLOR_NEUTRAL);
            TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, compare.values[i]);
            UI_TextDrawGlyphString(left + 89, top + 26 + i * 13 + 2, compare.flags[i], g_UITextFormatBuffer);
        }
    }

    compare.names[EQUIP_SLOT_WEAPON]      = g_Weapons[chr->equip.weapon].header.name;
    compare.names[EQUIP_SLOT_SHIELD]      = g_Armors[chr->equip.shield].header.name;
    compare.names[EQUIP_SLOT_HELMET]      = g_Armors[chr->equip.helmet].header.name;
    compare.names[EQUIP_SLOT_ARMOR]       = g_Armors[chr->equip.armor].header.name;
    compare.names[EQUIP_SLOT_ACCESSORY_1] = (u8*)g_Accessories[chr->equip.accessories[0]].header.name;
    compare.names[EQUIP_SLOT_ACCESSORY_2] = (u8*)g_Accessories[chr->equip.accessories[1]].header.name;
    for (i = 0; i < EQUIP_SLOT_COUNT; i++) {
        if (i == task->unk_0B) {
            UI_IconDraw((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 1);
            UI_TextDraw(left + 17, top + 85 + i * 13, UI_TEXT_DIM, Game_ReadCommand(compare.names[i]) & BYTE_MASK, compare.names[i]);
            UI_IconDraw((u16)(left + 6), (u16)(top + i * 13 + 85), g_MenuEquipSlotIcons[i], 0);
            UI_TextDraw(left + 17, top + 85 + i * 13 - 2, UI_TEXT_HIGHLIGHT, Game_ReadCommand(compare.names[i]) & BYTE_MASK, compare.names[i]);
        } else if (i == task->unk_0A) {
            UI_IconDraw((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 1);
            UI_TextDraw(left + 17, top + 85 + i * 13, UI_TEXT_DIM, Game_ReadCommand(compare.names[i]) & BYTE_MASK, compare.names[i]);
            UI_IconDraw((u16)(left + 6), (u16)(top + i * 13 + 85), g_MenuEquipSlotIcons[i], 0);
            UI_TextDraw(left + 17, top + 85 + i * 13 - 2, UI_TEXT_NORMAL, Game_ReadCommand(compare.names[i]) & BYTE_MASK, compare.names[i]);
        } else {
            UI_IconDraw((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 0);
            UI_TextDraw(left + 17, top + 85 + i * 13, UI_TEXT_NORMAL, Game_ReadCommand(compare.names[i]) & BYTE_MASK, compare.names[i]);
        }
    }

    UI_SpriteDrawRun(left, top, g_MenuEquipCompareSprites, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 7; i++) {
        UI_SpriteDraw(left, top + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(left + 120, top + (i + 3) * 8, 8, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(left, top + (i + 11) * 8, 4, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(left + 120, top + (i + 11) * 8, 8, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 14; i++) {
        UI_SpriteDraw(left + (i + 1) * 8, top + 80, 0xE, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(left + (i + 1) * 8, top + 160, 0x11, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(left, top + 80, 0xD, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(left + 120, top + 80, 0xF, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(left, top + 160, 0x10, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(left + 120, top + 160, 0x12, UI_SPRITE_ALT_PAGE);
}
