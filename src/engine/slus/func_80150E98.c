#include "engine/slus/slus.h"

/* when the pad word is nonzero or g_UiWindowChannel has 0xC0 set, increments the message panel state and the handler index g_UiWindowStep[0] and sets bit 2 of that counter. */
MATCH void func_80150E98(void) {
    u8  mode;
    u8  index;
    u16 flags;

    if ((g_InputPressed != 0) ||
        ((*(s32*)&g_UiWindowChannel & (FRONTEND_FLAG_ADVANCE_REQUEST | FRONTEND_FLAG_MODE_LATCH)) != 0)) {
        mode  = g_MenuPanelTasks[0].state;
        /* FAKE: g_UiWindowStep is a one-byte scalar elsewhere; this unit reads it as an array element. */
        index = MEM(u8, (u32)&g_UiWindowStep);
        flags = g_UiWindowChannel;
        mode += 1;
        index += 1;
        flags |= FRONTEND_FLAG_SELECTION;
        g_MenuPanelTasks[0].state     = mode;
        MEM(u8, (u32)&g_UiWindowStep) = index;
        g_UiWindowChannel             = flags;
    }
}
