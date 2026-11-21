#include "battle_03.h"

/* func_801EA9FC */
MATCH void Battle_SlideOutMessagePanel(void) {
    s16 y;

    y = g_UiPanelCurrent->pos.y;
    if (y == -22) {
        D_801EC2E4              = 0;
        g_UiPanelCurrent->state = 0;
    } else {
        g_UiPanelCurrent->pos.y = y - 8;
    }
    func_801D7EB0((s16)g_UiPanelCurrent->pos.x, (s16)g_UiPanelCurrent->pos.y);
    UI_TextDraw((g_UiPanelCurrent->pos.x + 4), (g_UiPanelCurrent->pos.y + 3), 0, TEXT_LENGTH_MAX, g_BattleMessages[((D_801EBF04 - 1) & 0xF)].text);
}
