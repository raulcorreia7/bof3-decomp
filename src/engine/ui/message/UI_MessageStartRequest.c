#include "engine/slus/slus.h"

/* initializes the record header bytes and resolves the halfword at
 * SLUS_LOAD_ADDRESS indexed by g_UiMessageRequest into the two record pointers.
 */
MATCH void UI_MessageStartRequest(void) {
    s32 entry;

    entry                    = *(u16*)(SLUS_LOAD_ADDRESS + g_UiMessageRequest * 2);
    g_UiMessageStateTimer[0] = 8;
    g_UiMessageState.state   = 1;
    D_801490B9               = 0;
    g_UiWindowStep           = 0;
    entry += SLUS_LOAD_ADDRESS;
    g_UiMessageScript = entry;
    D_801490B0        = (u8*)entry;
}
