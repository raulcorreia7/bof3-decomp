#include "start_08.h"

void      Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style); /* extern */
extern u8 D_801ED7FC;            /* local: u8 read; a sibling copy is s8 */
extern u8 g_MenuStartReturnStep; /* local: u8 read; a sibling copy is s8 */

MATCH void func_801E5E30(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    switch (D_801ED7FC) {
        case 0:
            break;
        case 5:
            func_801E14A8(0x62, 0x4C, D_801ED870, LOBU(g_SaveCardPort), 0);
            break;
        case 10:
            SAVE_DrawSlots(0x20, 0x30, 0U);
            break;
    }
    UI_DrawText(28, 21, 0, 0xFFU, Resource_GetText(D_801ED7FC + 0xA6));
    g_MenuStartTimer -= 1;
    if (g_MenuStartTimer == 0) {
        g_MenuStartStep = g_MenuStartReturnStep;
    }
}
