#include "battle_03.h"

/* func_801EAAB8 */
MATCH void Battle_DrawMessagePanel(void) {
    func_801D7EB0(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy);
    UI_TextDraw((g_UiPanelCurrent->pos.vx + 4u), (g_UiPanelCurrent->pos.vy + 3u), 0, TEXT_LENGTH_MAX, g_BattleMessages[D_801EBF04].text);
}
