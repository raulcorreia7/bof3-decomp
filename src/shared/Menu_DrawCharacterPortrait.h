/* Draws the portrait of a character id with Menu_DrawPortrait; Rei (id 4)
 * shows portrait 0xB once the scenario id reaches 8. One definition shared by
 * the shop, start, Bate and Shisu overlays; every change here must verify
 * every member. */
/* func_801D910C (shop/00), func_801DC604 (start/08), func_801D3664 (bate/00), func_801D460C (shisu/00) */
MATCH void Menu_DrawCharacterPortrait(u16 sprite_x, u16 sprite_y, u8 atlas_index, u8 shade_mode) {
    if (((atlas_index & BYTE_MASK) == CHAR_ID_REI) && (g_SceneState.scenario_id >= 8)) {
        atlas_index = 0xB;
    }
    Menu_DrawPortrait(sprite_x & HALF_MASK, sprite_y & HALF_MASK, atlas_index & BYTE_MASK, shade_mode & BYTE_MASK);
}
