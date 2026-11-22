#include "engine/slus/slus.h"

/* stores one frontend-local mode and installs the matching callback.
 */
MATCH void UI_ModeSet(u16 local_mode) {
    if (WINDOW_EFFECT_BUSY()) {
        return;
    }
    g_SysThreads[2].tail.screen_effect.mode = local_mode & BYTE_MASK;
    SYS_ThreadRegister(2, UI_ModeDispatchLocal);
}
