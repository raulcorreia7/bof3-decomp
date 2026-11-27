#include "engine/game/00/game_00.h"

/* func_8019986C */
/* Runs the task panel step of its state, then draws its window and message text. */
MATCH void UI_PanelRunTask(void) {
    s16 value;
    u8* color;

    g_UIPanelTaskSteps[g_UIPanelCurrent->state]();
    func_801D50E8(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, (s16)g_UIPanelCurrent->u.message.w, 0x13, (s32)GAME_WINDOW_STYLE);
    value = (s16)g_UIPanelCurrent->u.message.id;
    if (value != 0) {
        color = UI_MessageGetText((u32)(u16)value);
        UI_TextDraw((s16)(g_UIPanelCurrent->pos.vx + 7), (s16)(g_UIPanelCurrent->pos.vy + 3), 0, TEXT_LENGTH_MAX, color);
    }
}
