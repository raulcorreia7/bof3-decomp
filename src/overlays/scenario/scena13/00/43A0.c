#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Draws the area message and fades the palette in over its first 0x20 frames and out over its last 0x20. */
MATCH void func_801FAFA0(s32 message, u8 frames) {
    u16  elapsed;
    u16  limit;
    s32  total;
    u16* cell;

    cell                         = (u16*)g_ScratchPad.cells.bytes + 1;
    total                        = frames * 0x1E - 1;
    *cell                        = total;
    g_UiMessageRequest           = message;
    g_ScratchPad.cells.halves[0] = total - g_ScenarioState.timer_06;
    elapsed                      = total - g_ScenarioState.timer_06;
    limit                        = total;
    if (elapsed < limit) {
        UI_TextDraw(0x50, 0x3C, 0, TEXT_LENGTH_MAX, (MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, (u16)message) + 2));
        limit   = g_ScratchPad.cells.halves[0];
        elapsed = limit;
        if (elapsed < 0x20) {
            GFX_PaletteCopyCapped(limit & 0xFF);
        } else if (elapsed == 0x20) {
            Scene_RestorePalette();
        } else if (*cell - 0x20 < elapsed) {
            GFX_PaletteCopyCapped((u8)(0x20 - (limit - (*cell - 0x20))));
        }
    } else if (elapsed == limit) {
        Scene_RestorePalette();
    }
}

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
