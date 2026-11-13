#include "engine/slus/slus.h"

/* seeds the text cursor (current x at D_80145ACA, current y at
 * D_80145ACC = y + 1, line-start x at D_80145ACE = x, state byte D_80145AD0 =
 * 0) and prints the record with UI_DrawTextGlyphs(palette, byte_count, text).
 */
MATCH void UI_DrawText(s16 x, s16 y, s32 palette, u32 byte_count, u8* text) {
    D_80145ACA = x;
    D_80145ACE = x;
    D_80145ACC = y + 1;
    D_80145AD0 = 0;
    UI_DrawTextGlyphs(palette, byte_count, text);
}
