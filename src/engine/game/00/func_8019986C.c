#include "game_00.h"

MATCH void func_8019986C(void) {
    s16 value;
    u8* color;

    g_MenuTaskStates[g_MenuCurrentPanel->state]();
    func_801D50E8(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, (s16)g_MenuCurrentPanel->u.message.width, 0x13, (s32)GAME_WINDOW_STYLE);
    value = (s16)g_MenuCurrentPanel->u.message.id;
    if (value != 0) {
        color = Message_GetText((u32)(u16)value);
        UI_DrawText((s16)(g_MenuCurrentPanel->pos.x + 7), (s16)(g_MenuCurrentPanel->pos.y + 3), 0, 255, color);
    }
}
