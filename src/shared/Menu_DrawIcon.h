/* Draw one panel icon from its atlas cell and palette. One definition shared by
 * the battle, commu02, shisu, shop, sisyou, start and Bate overlays; each
 * includes this file where the function sits; every change here must verify
 * every member. */
/* Menu_DrawIcon (battle/15, commu02/08, sisyou), func_801D4678 (bate), func_801D5620 (shisu), func_801DA120 (shop), func_801DD618 (start) */
MATCH void Menu_DrawIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}
