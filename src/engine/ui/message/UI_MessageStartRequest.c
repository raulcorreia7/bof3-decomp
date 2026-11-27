#include "engine/slus/slus.h"

/* initializes the record header bytes and resolves the halfword at
 * SLUS_LOAD_ADDRESS indexed by g_UIMessageRequest into the two record pointers.
 */
MATCH void UI_MessageStartRequest(void) {
    s32 entry;

    entry                    = *(u16*)(SLUS_LOAD_ADDRESS + g_UIMessageRequest * 2);
    g_UIMessageStateTimer[0] = 8;
    g_UIMessageState.state   = 1;
    g_UIMessageState.index   = 0;
    g_UIMessageStep          = 0;
    entry += SLUS_LOAD_ADDRESS;
    g_UIMessageScript = entry;
    D_801490B0        = (u8*)entry;
}
