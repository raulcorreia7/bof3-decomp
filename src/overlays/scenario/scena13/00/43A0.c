#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FAFA0(s32 message, u8 frames) {
    u16  elapsed;
    u16  limit;
    s32  total;
    s32  t;
    u16* cell;

    cell                                     = (u16*)g_ScratchPad.cells.bytes + 1;
    total                                    = frames * 0x1E - 1;
    *cell                                    = total;
    g_UiMessageRequest                       = message;
    *(volatile u16*)g_ScratchPad.cells.bytes = total - g_ScenarioState.timer_06;
    elapsed                                  = total - g_ScenarioState.timer_06;
    limit                                    = total;
    if (elapsed < limit) {
        UI_TextDraw(0x50, 0x3C, 0, TEXT_LENGTH_MAX, (MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, (u16)message) + 2));
        limit   = *(volatile u16*)g_ScratchPad.cells.bytes;
        elapsed = limit;
        if (elapsed < 0x20) {
            GFX_PaletteCopyCapped(limit & 0xFF);
        } else if (elapsed == 0x20) {
            Scene_RestorePalette();
        } else if (*cell - 0x20 < elapsed) {
            t = limit - (*cell - 0x20);
            GFX_PaletteCopyCapped((0x20 - t) & 0xFF);
        }
    } else if (elapsed == limit) {
        Scene_RestorePalette();
    }
}
#else
INCLUDE_ASM(func_801FAFA0);
#endif

#include "overlays/scenario/shared/GFX_PaletteCopyCapped.h"

/* func_801FB164 */
MATCH void Scene_RestorePalette(void) {
    s32 i;

    i = 0;
    do {
        g_GraphicsPaletteDst[i] = MEM_PTR(const volatile u16, AREA_PALETTE_ARENA)[i];
        i++;
    } while (i < 16);
    g_GfxPalettePending = (g_GfxPalettePending + 1u);
}
