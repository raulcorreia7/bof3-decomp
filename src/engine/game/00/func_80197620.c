#include "game_00.h"

MATCH void func_80197620(void) {
    u8 sep_index;
    u8 seq_index;

    EMI_LoaderStreamInitSlot(EMI_SLOT_STATUS);
    while (EMI_LoaderIsReady() == 0) {
        CallbackWait(1u);
    }
    GFX_CopyPalette(1u);
    GFX_CopyPalette(2u);
    g_GfxPalettePending = 1u;
    D_80148650          = 0u;
    D_80148654          = 3;
    /* FAKE: keep the mode argument in the call delay slot. */
    ORDER_LOCK(UI_SetMode(3));
    func_80198C38(1u);
    if ((D_80143F20 == 0x6Eu) && !(SND_FindFreeFxVoice(&sep_index, &seq_index) & 0xFF)) {
        SND_StartDecrescendo(sep_index, seq_index, 0x14, 0x10);
    }
    {
        u16* counter;

        counter = &g_GameEntrySubstate;
        *counter += 1u;
    }
}
