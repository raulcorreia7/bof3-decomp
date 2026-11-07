/* Draw the row's equipment and item icons. One definition shared by the shop,
 * start, Bate and Shisu overlays; each overlay includes this file where the
 * function sits.
 */
/* func_801D5E90 (bate), func_801D6E38 (shisu), func_801DB938 (shop), func_801DEE30 (start) */
MATCH void Menu_DrawRowIcons(u8* row_record, s32 palette_index) {
    u8 palette;

    palette = palette_index & BYTE_MASK;
    UI_DrawWindow(*(u16*)(row_record + 4), *(u16*)(row_record + 6), 139, 159, (palette_index + 0xF0) & BYTE_MASK,
                  g_WindowStyle);
    Menu_DrawEquipment(*(u16*)(row_record + 4), *(u16*)(row_record + 6),
                       g_BattlePartyBattlers[row_record[0xC]].character_index, palette);
    Menu_DrawItemRow(*(u16*)(row_record + 4), *(u16*)(row_record + 6),
                     g_BattlePartyBattlers[row_record[0xC]].character_index, palette);
}
