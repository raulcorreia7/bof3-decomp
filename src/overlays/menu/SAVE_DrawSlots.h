/* Draw the visible stock rows and the panel header. One definition shared by
 * the shop and start overlays; each image header declares the stock count,
 * rows, first row and the two draw helpers.
 */
/* func_801D67B0 (shop), func_801E6C68 (start) */
#define SAVE_SLOT_INSET_X      16
#define SAVE_SLOT_INSET_Y      6
#define SAVE_SLOT_PITCH        56
#define SAVE_SLOT_FRAME_WIDTH  209
#define SAVE_SLOT_FRAME_HEIGHT 52

MATCH void SAVE_DrawSlots(s16 panel_x, s16 panel_y, u8 row_cursor) {
    MenuListRow* row;
    s32          index;
    s32          x;
    s32          y;
    u8           i;

    i = 0;
    if (g_SaveSlotCount != 0) {
        x = (s16)(panel_x + SAVE_SLOT_INSET_X);
        do {
            index = i;
            y     = (s16)(panel_y + SAVE_SLOT_INSET_Y + index * SAVE_SLOT_PITCH);
            if (g_SaveSlots[index].source_index != GAME_NONE) {
                row = &g_SaveSlots[index];
            } else {
                row = NULL;
            }
            SAVE_DrawSlot(index, x, y, (void*)row);
            i++;
        } while (i < g_SaveSlotCount);
    }
    Menu_DrawCursorFrame((u16)(panel_x + SAVE_SLOT_INSET_X),
                         (u16)(panel_y + SAVE_SLOT_INSET_Y + g_SaveSlotFirst * SAVE_SLOT_PITCH), SAVE_SLOT_FRAME_WIDTH,
                         SAVE_SLOT_FRAME_HEIGHT, row_cursor, 6);
}
