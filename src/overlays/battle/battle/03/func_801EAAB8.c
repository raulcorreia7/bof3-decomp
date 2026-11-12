#include "battle_03.h"

MATCH void func_801EAAB8(void) {
    func_801D7EB0((s16)g_MenuCurrentPanel->pos.x, (s16)g_MenuCurrentPanel->pos.y);
    UI_DrawText((g_MenuCurrentPanel->pos.x + 4u), (g_MenuCurrentPanel->pos.y + 3u), 0, 255u, D_801EB5B4[D_801EBF04 * 2]);
}
