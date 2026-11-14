/* Draw the equipment panel: the six equipped objects, each with its sprite, and the EQUIP caption.toml. */

/* Layout in pixels: the panel in frame cells, the caption and its icon, and the equipment rows. */
#define MENU_EQUIPMENT_PANEL_WIDTH  9
#define MENU_EQUIPMENT_PANEL_HEIGHT 10
#define MENU_EQUIPMENT_CAPTION_X    46
#define MENU_EQUIPMENT_CAPTION_Y    7
#define MENU_EQUIPMENT_EMBLEM_X     7
#define MENU_EQUIPMENT_EMBLEM_Y     5
#define MENU_EQUIPMENT_EMBLEM_SIZE  16
#define MENU_EQUIPMENT_FIRST_ROW_Y  26
#define MENU_EQUIPMENT_ROW_HEIGHT   13
#define MENU_EQUIPMENT_ROW_ICON_X   5
#define MENU_EQUIPMENT_ROW_ICON_DY  2
#define MENU_EQUIPMENT_ROW_NAME_X   17
#define MENU_EQUIPMENT_ROW_COUNT    6

/* 0x801D2F64 (bate), 0x801D3F0C (shisu), 0x801D8A0C (shop), 0x801DBF04 (start) */
MATCH void Shop_DrawEquipment(s16 x, s16 y, u8 record_index) {
    const volatile void* objects[MENU_EQUIPMENT_ROW_COUNT];
    Character*           record;
    u16                  row_y;
    u8                   row;

    Menu_DrawFilledPanel(x, y, MENU_EQUIPMENT_PANEL_WIDTH, MENU_EQUIPMENT_PANEL_HEIGHT);
    record = &g_Characters[record_index];
    UI_DrawText((s16)(x + MENU_EQUIPMENT_CAPTION_X), (s16)(y + MENU_EQUIPMENT_CAPTION_Y), 0, TEXT_LENGTH_MAX, g_MenuLabelEquip);
    func_801644D8(0, (s32)(u16)(x + MENU_EQUIPMENT_EMBLEM_X), (s32)(u16)(y + MENU_EQUIPMENT_EMBLEM_Y), MENU_EQUIPMENT_EMBLEM_SIZE, MENU_EQUIPMENT_EMBLEM_SIZE, 0x80);

    objects[0] = &g_Weapons[record->equip.weapon];
    objects[1] = &g_Armors[record->equip.shield];
    objects[2] = &g_Armors[record->equip.helmet];
    objects[3] = &g_Armors[record->equip.armor];
    objects[4] = &g_Accessories[record->equip.accessories[0]];
    objects[5] = &g_Accessories[record->equip.accessories[1]];

    for (row = 0; row < MENU_EQUIPMENT_ROW_COUNT; row++) {
        row_y = (u16)(y + (row * MENU_EQUIPMENT_ROW_HEIGHT + MENU_EQUIPMENT_FIRST_ROW_Y));
        func_801AEA80((s32)(u16)(x + MENU_EQUIPMENT_ROW_ICON_X), (s32)(u16)(row_y + MENU_EQUIPMENT_ROW_ICON_DY), g_MenuEquipRowIcons[row], 0);
        UI_DrawText((s16)(x + MENU_EQUIPMENT_ROW_NAME_X), (s16)row_y, 0, Game_ReadCommand((u8*)objects[row]) & BYTE_MASK, (u8*)objects[row]);
    }
}
