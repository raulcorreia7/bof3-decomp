#include "battle_03.h"

MATCH void func_801EA9FC(void) {
    s16 y;

    y = (s16)g_MenuCurrentPanel->y;
    if (y == -22) {
        D_801EC2E4                = 0;
        g_MenuCurrentPanel->state = 0;
    } else {
        g_MenuCurrentPanel->y = y - 8;
    }
    func_801D7EB0((s32)(s16)g_MenuCurrentPanel->x, (s32)(s16)g_MenuCurrentPanel->y);
    UI_DrawText((s16)(g_MenuCurrentPanel->x + 4), (s16)(g_MenuCurrentPanel->y + 3), 0, 0xFF,
                D_801EB5B4[((D_801EBF04 - 1) & 0xF) * 2]);
}
