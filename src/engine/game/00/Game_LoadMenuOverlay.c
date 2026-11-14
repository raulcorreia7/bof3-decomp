#include "game_00.h"

MATCH void Game_LoadMenuOverlay(void) {
    u8 sep_index;
    u8 seq_index;

    EMI_LoadArchive(EMI_SLOT_STATUS);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1u);
    }
    GFX_CopyPalette(1u);
    GFX_CopyPalette(2u);
    g_GfxPalettePending = 1u;
    g_MenuStep.step     = 0u;
    D_80148654          = 3;
    /* FAKE: keep the mode argument in the call delay slot. */
    FAKE_ORDER_LOCK(UI_SetMode(3));
    func_80198C38(1u);
    if ((D_80143F20 == 0x6Eu) && !(SND_FindFreeEffectVoice(&sep_index, &seq_index) & BYTE_MASK)) {
        SND_StartDecrescendo(sep_index, seq_index, 0x14, 0x10);
    }
    {
        u16* counter;

        counter = &g_GameEntrySubstate;
        *counter += 1u;
    }
}
