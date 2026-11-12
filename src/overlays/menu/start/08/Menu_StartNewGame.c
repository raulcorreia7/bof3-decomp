#include "start_08.h"

extern void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style); /* local: void read; a sibling copy is s32 */

MATCH void Menu_StartNewGame(void) {
    u32* p;
    u8*  counter;
    u8   count;
    s32  i;

    counter  = &D_8014865F;
    count    = *counter;
    *counter = count - 1;
    if (count == 0) {
        D_801448EA[0] = 0;
        g_GameAreaId  = 0xFFFF;
        Scene_Start(0);
        i = 0x13;
        p = (u32*)(D_801448EA + 0x636);
        for (; i >= 0; i--) {
            *p = 0;
            p -= 2;
        }
        CallbackReplace(Game_UpdateMain);
    }
    if (WINDOW_EFFECT_BUSY()) {
        Menu_DrawClutStrip(D_80144953);
        Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
        func_801E26A8(0x1C, 0x40);
        func_801E2668(0, 0x70, 0x26);
    }
}
