/* Draws a party member's weapon, shield, helmet, armor and two accessories in
 * the equipment slots. One definition shared by the equipment panel copies in
 * emi/etc/shop/00, emi/etc/start/08, emi/etc/bate/00 and emi/etc/shisu/00; each
 * member includes it where the function sits. Every change here must verify
 * every member.
 */
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
    palette      = selected ? 7 : 0;
    record_index = index;
    UI_DrawWindowOutline((s16)(x + 2), (s16)(y + 0x44), 0x87, 0x58, 0xF1);
    icon_x = (s16)(x + 0xF);
    record = &g_Characters[record_index];
    UI_DrawText(icon_x, (s16)(y + 70), palette, 8, (u8*)(&g_Weapons[record->equipment.weapon]));
    UI_DrawText(icon_x, (s16)(y + 83), palette, 8, (u8*)(&g_Armors[record->equipment.shield]));
    UI_DrawText(icon_x, (s16)(y + 96), palette, 8, (u8*)(&g_Armors[record->equipment.helmet]));
    UI_DrawText(icon_x, (s16)(y + 109), palette, 8, (u8*)(&g_Armors[record->equipment.armor]));
    UI_DrawText(icon_x, (s16)(y + 129), palette, 8, (u8*)(&g_Accessories[record->equipment.accessories[0]]));
    UI_DrawText(icon_x, (s16)(y + 142), palette, 8, (u8*)(&g_Accessories[record->equipment.accessories[1]]));
    x = (x + 5) & HALF_MASK;
    func_801AEA80(x, (y + 0x49) & HALF_MASK, 8, selected);
    func_801AEA80(x, (y + 0x56) & HALF_MASK, 0xA, selected);
    func_801AEA80(x, (y + 0x63) & HALF_MASK, 9, selected);
    func_801AEA80(x, (y + 0x70) & HALF_MASK, 0xB, selected);
    func_801AEA80(x, (y + 0x84) & HALF_MASK, 0xC, selected);
    y += 0x91;
    func_801AEA80(x, y & HALF_MASK, 0xC, selected);
}
