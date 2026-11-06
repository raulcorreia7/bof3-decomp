#include "start_08.h"

MATCH void func_801E17D0(void) {
    u8 next;

    D_80148655 = 0;
    if (D_80148654 == 5) {
        SND_PlayCue(EMI_CUE_ID(1, 2));
    }
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - D_80148654 * 0x10) & 0xFFF0, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT,
                       g_SaveData.window_style);
    func_801E26A8((D_80148654 << 6) | 0x1C, 0x40);
    func_801E2668(0xFF, 0x70, 0x26 - D_80148654 * 0x10);
    next       = D_80148654 - 1;
    D_80148654 = next;
    if (next == 0) {
        D_80148654 = 0;
        D_80148653 = 0;
        D_80148652 += 1;
    }
}
