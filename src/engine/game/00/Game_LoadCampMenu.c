#include "game_00.h"

MATCH void Game_LoadCampMenu(void) {
    u16* ent;
    u16  ev;
    u8   pv;

    EMI_LoadArchive(EMI_SLOT_START);

    while (!EMI_IsReady()) {
        SYS_ThreadWait(1u);
    }

    GFX_ResetPalette();

    ent = (u16*)&g_GameEntryState;
    ev  = g_GfxPalettePending;
    pv  = ev;
    ev  = *ent;
    pv++;
    ev++;
    g_GfxPalettePending = pv;
    *ent                = ev;
}
