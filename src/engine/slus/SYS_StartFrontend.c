#include "engine/slus/slus.h"

/* prepares the frontend: clears the game state, reloads the palette stage,
 * publishes the area bank pointers, streams FIRST.EMI and registers the
 * GAME.EMI starter. It resets the graphics and sound pipeline for the overlay
 * start, clearing the work buffer.
 */
MATCH void SYS_StartFrontend(void) {
    u16*       dst;
    const u16* src;
    u16        word;
    u32        i;
    /* FAKE: retail keeps the copy count in a0. */
    FAKE_REG(u32, j, "a0");
    /* FAKE: retail keeps the clear pointer in v1. */
    FAKE_REG(u8*, clear, "v1");

    GFX_ClearRect(0, 0, 1024, 512);
    SYS_ThreadWait(1U);
    SND_Init();
    SND_SetBankLayout(0U);
    EMI_LoadArchive(EMI_SLOT_FIRST);
    while (EMI_IsReady() == 0)
        SYS_ThreadWait(1U);
    SsUtSetReverbDepth(0x28, 0x28);
    SsSetRVol(0x28, 0x28);
    SND_Start();
    clear = (u8*)&g_SaveData;
    for (i = 0; i < SAVE_BLOCK_SIZE; i++)
        *clear++ = 0;
    j                         = 0;
    dst                       = g_InputMasks;
    src                       = D_8017F56C;
    g_EmiLoadedCharacterIndex = 0xFF;
    g_Game.flags              = 0;
    g_Game.walk_flags         = 0;
    D_80144950                = 1;
    g_SndMono                 = 0;
    g_WindowStyle             = 0;
    D_80144953                = 0;
    D_80144954                = 0;
    D_80144955                = 0;
    g_AutoRun                 = 0;
    for (; j < 9U; j++) {
        word = *src;
        src += 1;
        *dst = word;
        dst += 1;
    }
    Menu_ResetPanelTasks();
    GFX_ResetPaletteFades();
    GFX_FreeAllPaletteSlots();
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    g_AreaDrawMode  = 6;
    g_Scripts   = AREA_SCRIPT_TABLE;
    D_801459F4      = MEM_PTR(u8, (SCENE_TABLE_BASE + 4));
    D_80143E07      = 0;
    D_80143E06      = 0;
    D_80143E05      = 0;
    D_80143D77      = 0;
    D_80143D76      = 0;
    D_80143D75      = 0;
    GFX_ResetPalette();
    g_GfxPalettePending += 1;
    SYS_ThreadRegister(1, SYS_EnterFrontend);
    SYS_ThreadExit();
}
