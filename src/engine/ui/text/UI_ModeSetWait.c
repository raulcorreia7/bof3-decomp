#include "engine/slus/slus.h"

MATCH void UI_ModeSetWait(u16 local_mode) {
    u16* busy;

    busy = &g_UiWindowEffectBusy;
    if (*busy != 0) {
        return;
    }
    g_UiModeLocal = local_mode & BYTE_MASK;
    SYS_ThreadRegister(2, UI_ModeDispatchLocal);
    if (*busy != 0) {
        do {
            SYS_ThreadWait(1);
        } while (WINDOW_EFFECT_BUSY());
    }
}
