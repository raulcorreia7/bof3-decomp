#include "battle_03.h"

/* func_801EAAB8 */
MATCH void Battle_DrawMessagePanel(void) {
    func_801D7EB0((s16)g_MenuCurrentPanel->pos.x, (s16)g_MenuCurrentPanel->pos.y);
    UI_DrawText((g_MenuCurrentPanel->pos.x + 4u), (g_MenuCurrentPanel->pos.y + 3u), 0, TEXT_LENGTH_MAX, g_BattleMessages[D_801EBF04].text);
}
