#include "engine/slus/slus.h"

MATCH void UI_SetModeWait(u16 local_mode) {
    u16* busy;

    busy = &g_UiWindowEffectBusy;
    if (*busy != 0) {
        return;
    }
    g_UiLocalMode = local_mode & BYTE_MASK;
    CallbackRegister(2, UI_DispatchLocalMode);
    if (*busy != 0) {
        do {
            CallbackWait(1);
        } while (WINDOW_EFFECT_BUSY());
    }
}
