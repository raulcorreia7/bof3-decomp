/* The stat window of the equip screen: the power, defense and agility a party member would have with item_id, an item of item_kind (the shop and equip lists pass Item_GetKind), coloured by Char_PreviewEquip as higher or lower, beside the portrait. When the member cannot equip the item the window is shaded and shows the current stats. */
/* func_801DEEE8 (start), func_801DB9F0 (shop), func_801D5F48 (bate), func_801D6EF0 (shisu) */
MATCH void Menu_DrawEquipStatWindow(u16 x, u16 y, u8 character_index, u8 item_kind, u8 item_id) {
    Character* character;
    u8         flags[EQUIP_PREVIEW_STAT_COUNT];
    u16        values[EQUIP_PREVIEW_STAT_COUNT];
    u8         shaded;
    u8         clut;
    u8         category;
    u8         i;

    character = &g_Characters[character_index];
    clut      = 0;
    switch (item_kind) {
        case ITEM_TYPE_ITEM:
        case ITEM_TYPE_UNUSED:
        default:
            category = ITEM_CAT_ITEM;
            break;
        case ITEM_TYPE_WEAPON:
            category = ITEM_CAT_WEAPON;
            break;
        case ITEM_TYPE_SHIELD:
        case ITEM_TYPE_HELMET:
        case ITEM_TYPE_ARMOR:
            category = ITEM_CAT_ARMOR;
            break;
        case ITEM_TYPE_ACCESSORY:
        case ITEM_TYPE_FISHING_LURE:
        case ITEM_TYPE_FISHING_ROD:
            category = ITEM_CAT_ACCESSORY;
            break;
    }
    shaded = ((Item_GetEquipability(category, item_id) >> character_index) ^ 1) & 1;
    UI_DrawWindow((x + MENU_EQUIP_STAT_INSET) & HALF_MASK, (y + MENU_EQUIP_STAT_INSET) & HALF_MASK, MENU_EQUIP_STAT_WINDOW_WIDTH, MENU_EQUIP_STAT_WINDOW_HEIGHT, shaded, g_WindowStyle);
    if (shaded == 0) {
        Char_PreviewEquip(character_index, EQUIP_SLOT_OF_TYPE(item_kind), item_id, flags, values);
        /* The agility row takes the place of the intellect entry. */
        values[EQUIP_STAT_ROW_AGILITY] = values[EQUIP_PREVIEW_AGILITY];
        flags[EQUIP_STAT_ROW_AGILITY]  = flags[EQUIP_PREVIEW_AGILITY];
        for (i = 0; i < MENU_EQUIP_STAT_ROWS; i++) {
            TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, values[i]);
            UI_DrawGlyphString(x + MENU_EQUIP_STAT_VALUE_X, y + i * MENU_EQUIP_STAT_ROW_HEIGHT + MENU_EQUIP_STAT_VALUE_Y, flags[i], g_UiFormatBuffer);
        }
    } else {
        clut = MENU_SHADE_DIM;
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.power);
        UI_DrawGlyphString(x + MENU_EQUIP_STAT_VALUE_X, y + EQUIP_STAT_ROW_POWER * MENU_EQUIP_STAT_ROW_HEIGHT + MENU_EQUIP_STAT_VALUE_Y, MENU_SHADE_DIM, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.defense);
        UI_DrawGlyphString(x + MENU_EQUIP_STAT_VALUE_X, y + EQUIP_STAT_ROW_DEFENSE * MENU_EQUIP_STAT_ROW_HEIGHT + MENU_EQUIP_STAT_VALUE_Y, MENU_SHADE_DIM, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->stats.agility);
        UI_DrawGlyphString(x + MENU_EQUIP_STAT_VALUE_X, y + EQUIP_STAT_ROW_AGILITY * MENU_EQUIP_STAT_ROW_HEIGHT + MENU_EQUIP_STAT_VALUE_Y, MENU_SHADE_DIM, g_UiFormatBuffer);
    }
    Menu_DrawCharacterPortrait((x + MENU_EQUIP_STAT_PORTRAIT_X) & HALF_MASK, (y + MENU_EQUIP_STAT_PORTRAIT_Y) & HALF_MASK, character->character_id, shaded);
    for (i = 0; i < MENU_EQUIP_STAT_ROWS; i++) {
        UI_DrawText(x + MENU_EQUIP_STAT_LABEL_X, y + i * MENU_EQUIP_STAT_ROW_HEIGHT + MENU_EQUIP_STAT_LABEL_Y, clut, TEXT_LENGTH_MAX, &g_MenuEquipStatLabels[i * MENU_EQUIP_STAT_LABEL_SIZE]);
    }
    UI_DrawSpriteRun(x, y, g_MenuEquipStatSprites, 0);
}
