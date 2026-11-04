#include "engine/slus/slus.h"

/* initializes the record header bytes and resolves the halfword at
 * SLUS_LOAD_ADDRESS indexed by g_MessageRequest into the two record pointers.
 */
MATCH void Message_StartRequest(void) {
    s32 entry;

    entry               = *(u16*)(SLUS_LOAD_ADDRESS + g_MessageRequest * 2);
    D_801490A6[0]       = 8;
    D_801490A0.state_00 = 1;
    D_801490B9          = 0;
    g_UiWindowStep      = 0;
    entry += SLUS_LOAD_ADDRESS;
    D_801490AC = entry;
    D_801490B0 = (u8*)entry;
}
