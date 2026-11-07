/* The stat window of the equip screen: the power, defense and agility a party member would have with item_id in
 * equip_slot, coloured by Char_PreviewEquip as higher or lower, beside the portrait. When the member cannot equip the
 * item the window is shaded and shows the current stats. start/08, shop/00, bate/00 and shisu/00 include it where the
 * function sits, and each image header declares g_MenuEquipStatLabels and g_MenuEquipStatSprites. */
/* func_801DEEE8 (start), func_801DB9F0 (shop), func_801D5F48 (bate), func_801D6EF0 (shisu) */
MATCH void Menu_DrawEquipStatWindow(u16 x, u16 y, u8 character_index, u8 equip_slot, u8 item_id) {
    Character* character;
    u8         flags[4];
    u16        values[4];
    u8         shaded;
    u8         clut;
    u8         category;
    u8         i;

    character = &g_Characters[character_index];
    clut      = 0;
    switch (equip_slot) {
        case 0:
        case 12:
        default:
            category = ITEM_CAT_ITEM;
            break;
        case 1:
            category = ITEM_CAT_WEAPON;
            break;
        case 2:
        case 3:
        case 4:
            category = ITEM_CAT_ARMOR;
            break;
        case 5:
        case 10:
        case 11:
            category = ITEM_CAT_ACCESSORY;
            break;
    }
    shaded = ((Item_GetEquipability(category, item_id) >> character_index) ^ 1) & 1;
    UI_DrawWindow((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, MENU_EQUIP_STAT_WINDOW_WIDTH, MENU_EQUIP_STAT_WINDOW_HEIGHT,
                  shaded, g_WindowStyle);
    if (shaded == 0) {
        Char_PreviewEquip(character_index, equip_slot - 1, item_id, flags, values);
        /* The third row shows agility in place of intellect. */
        values[2] = values[3];
        flags[2]  = flags[3];
        for (i = 0; i < MENU_EQUIP_STAT_ROWS; i++) {
            TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, values[i]);
            UI_DrawGlyphString(x + 44, y + i * 15 + 8, flags[i], g_UiFormatBuffer);
        }
    } else {
        clut = 7;
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.power);
        UI_DrawGlyphString(x + 44, y + 8, 7, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.defense);
        UI_DrawGlyphString(x + 44, y + 23, 7, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.agility);
        UI_DrawGlyphString(x + 44, y + 38, 7, g_UiFormatBuffer);
    }
    Menu_DrawCharacterPortrait((x + 0x46) & HALF_MASK, (y + 2) & HALF_MASK, character->character_id, shaded);
    for (i = 0; i < MENU_EQUIP_STAT_ROWS; i++) {
        UI_DrawText(x + 5, y + i * 15 + 6, clut, 0xFF, &g_MenuEquipStatLabels[i * MENU_EQUIP_STAT_LABEL_SIZE]);
    }
    UI_DrawSpriteRun(x, y, g_MenuEquipStatSprites, 0);
}
