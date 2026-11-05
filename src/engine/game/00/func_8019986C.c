#include "game_00.h"

MATCH void func_8019986C(void) {
    s16 value;
    u8* color;

    g_MenuTaskHandlers[g_MenuCurrentPanel->state]();
    func_801D50E8(FIELD(s16, g_MenuCurrentPanel, 4u), FIELD(s16, g_MenuCurrentPanel, 6u),
                  g_MenuCurrentPanel->unk_12, 0x13, GAME_WINDOW_STYLE);
    value = g_MenuCurrentPanel->unk_10;
    if (value != 0) {
        color = Resource_GetText((u16)value);
        UI_DrawText((g_MenuCurrentPanel->x + 7), (g_MenuCurrentPanel->y + 3), 0, 0xFF, color);
    }
}
