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
    u8*        clear;

    GFX_ClearRect(0, 0, GFX_VRAM_WIDTH, GFX_VRAM_HEIGHT);
    SYS_ThreadWait(1U);
    SND_Init();
    SND_SetBankLayout(0U);
    EMI_ArchiveLoad(EMI_SLOT_FIRST);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1U);
    }
    SsUtSetReverbDepth(0x28, 0x28);
    SsSetRVol(0x28, 0x28);
    SND_Start();
    clear = (u8*)&g_SaveData;
    for (i = 0; i < SAVE_BLOCK_SIZE; i++) {
        *clear++ = 0;
    }
    i                         = 0;
    dst                       = g_InputMasks;
    src                       = s_DefaultInputMasks;
    g_EmiLoadedCharacterIndex = 0xFF;
    g_Game.flags              = 0;
    g_Game.walk_flags         = 0;
    g_MessageSpeed            = 1;
    g_SndMono                 = 0;
    g_WindowStyle             = 0;
    g_WindowClut              = 0;
    D_80144954                = 0;
    D_80144955                = 0;
    g_AutoRun                 = 0;
    for (; i < 9U; i++) {
        word = *src;
        src += 1;
        *dst = word;
        dst += 1;
    }
    UI_PanelResetTasks();
    GFX_PaletteResetFades();
    GFX_PaletteFreeAllSlots();
    g_AreaDrawFlags         = AREA_DRAW_ALL_FLAGS;
    g_AreaDrawMode          = GFX_LAYER_FIELD_SCENE;
    g_Scripts               = AREA_SCRIPT_TABLE;
    g_SceneActorDefs        = MEM_PTR(u8, (SCENE_TABLE_BASE + 4));
    /* The frame that shows first is cleared first, then the other; each
     * triple keeps the retail field order. */
    g_GfxBuffers[1].draw.b0 = 0;
    g_GfxBuffers[1].draw.g0 = 0;
    g_GfxBuffers[1].draw.r0 = 0;
    g_GfxBuffers[0].draw.b0 = 0;
    g_GfxBuffers[0].draw.g0 = 0;
    g_GfxBuffers[0].draw.r0 = 0;
    GFX_PaletteReset();
    g_GfxPalettePending += 1;
    SYS_ThreadRegister(1, SYS_EnterFrontend);
    SYS_ThreadExit();
}
