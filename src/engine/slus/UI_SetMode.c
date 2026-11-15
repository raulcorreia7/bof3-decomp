#include "engine/slus/slus.h"

/* stores one frontend-local mode and installs the matching callback.
 */
MATCH void UI_SetMode(u16 local_mode) {
    if (WINDOW_EFFECT_BUSY()) {
        return;
    }
    g_UiLocalMode = local_mode & BYTE_MASK;
    SYS_ThreadRegister(2, UI_DispatchLocalMode);
}
