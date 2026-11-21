/* The most glyphs one equipment row draws; the record's name field is ITEM_NAME_LENGTH. */
#define MENU_EQUIPMENT_NAME_LENGTH 8

/* Draws a party member's weapon, shield, helmet, armor and two accessories in the equipment slots. */
/* func_801D3B4C (bate), func_801D4AF4 (shisu), func_801D95F4 (shop), func_801DCAEC (start) */
MATCH void Menu_DrawEquipment(s32 origin_x, s32 origin_y, s32 index, s32 selection) {
    Character* record;
    s32        x;
    s32        y;
    s16        icon_x;
    u8         record_index;
    u8         selected;
    u8         palette;

    x            = origin_x;
    y            = origin_y;
    selected     = selection & BYTE_MASK;
    palette      = selected ? UI_TEXT_DIM : UI_TEXT_NORMAL;
    record_index = index;
    UI_WindowDrawOutline((s16)(x + 2), (s16)(y + 0x44), 0x87, 0x58, UI_WINDOW_OUTLINE_OPEN_ALL | UI_WINDOW_OUTLINE_BLEND);
    icon_x = (s16)(x + 0xF);
    record = &g_Characters[record_index];
    UI_TextDraw(icon_x, (s16)(y + 70), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Weapons[record->equip.weapon]));
    UI_TextDraw(icon_x, (s16)(y + 83), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Armors[record->equip.shield]));
    UI_TextDraw(icon_x, (s16)(y + 96), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Armors[record->equip.helmet]));
    UI_TextDraw(icon_x, (s16)(y + 109), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Armors[record->equip.armor]));
    UI_TextDraw(icon_x, (s16)(y + 129), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Accessories[record->equip.accessories[0]]));
    UI_TextDraw(icon_x, (s16)(y + 142), palette, MENU_EQUIPMENT_NAME_LENGTH, (u8*)(&g_Accessories[record->equip.accessories[1]]));
    x = (x + 5) & HALF_MASK;
    UI_IconDraw(x, (y + 0x49) & HALF_MASK, 8, selected);
    UI_IconDraw(x, (y + 0x56) & HALF_MASK, 0xA, selected);
    UI_IconDraw(x, (y + 0x63) & HALF_MASK, 9, selected);
    UI_IconDraw(x, (y + 0x70) & HALF_MASK, 0xB, selected);
    UI_IconDraw(x, (y + 0x84) & HALF_MASK, 0xC, selected);
    y += 0x91;
    UI_IconDraw(x, y & HALF_MASK, 0xC, selected);
}
