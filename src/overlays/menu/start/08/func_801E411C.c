#include "start_08.h"

extern void func_801E7608(void);

MATCH void func_801E411C(void) {
    u16* flag_word;
    s32  packed;
    u8   next_state;

    func_801E7608();
    UI_DrawText(70, 190, 0, 255U, Message_GetText(0xA8));
    flag_word = (u16*)&g_UiWindowChannel;
    *flag_word |= 2;
    packed = func_801E7348();

    if ((((u16)packed >> 8) == 0) || ((packed & 0xF) == 0)) {
        D_801ED86C = 1;
    } else if ((((u16)packed >> 8) == 2) && ((packed & 0xF) == ((u16)packed >> 8))) {
        D_801ED86C = 0;
        Message_Request(0xD8);
    } else if ((((((u16)packed >> 8) - 2) < 2U) && ((packed & 0xF) == 3)) || ((((u16)packed >> 8) == 3) && ((packed & 0xF) == 2))) {
        D_801ED86C = 0;
        Message_Request(0xD7);
    } else if (((((u16)packed >> 8) == 1) && (((packed & 0xF) == 1) || ((packed & 0xF) != 0))) || ((((u16)packed >> 8) != 0) && ((packed & 0xF) == 1))) {
        D_801ED86C = 0;
    }
    next_state      = g_MenuStartStep + 1;
    D_801ED7EC      = D_801ED86C - 1;
    g_MenuStartStep = next_state;
}
