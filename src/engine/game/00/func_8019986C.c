#include "game_00.h"

MATCH void func_8019986C(void) {
    s16 value;
    u8* color;

    g_UiPanelTaskSteps[g_UiPanelCurrent->state]();
    func_801D50E8(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, (s16)g_UiPanelCurrent->u.message.w, 0x13, (s32)GAME_WINDOW_STYLE);
    value = (s16)g_UiPanelCurrent->u.message.id;
    if (value != 0) {
        color = UI_MessageGetText((u32)(u16)value);
        UI_TextDraw((s16)(g_UiPanelCurrent->pos.x + 7), (s16)(g_UiPanelCurrent->pos.y + 3), 0, TEXT_LENGTH_MAX, color);
    }
}
