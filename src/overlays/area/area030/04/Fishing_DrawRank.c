#include "area030_04.h"

/* Draws the roster panel and count caption. */
/* func_801E1320 */
MATCH void Fishing_DrawRank(s16 x, s16 y) {
    FishingIconData  icons;
    FishingThreshold thresholds;
    u32              value;
    u32              index;
    FishingIcon*     record;
    s32              i;

    icons      = g_FishingRankIcons;
    thresholds = D_801D0C70;

    Fishing_SetDrawMode(3, 1);
    Fishing_DrawSprite(6, 1, x, y);
    Fishing_DrawSprite(7, 1, (x + 88), y);

    value = Fishing_TotalScore();
    index = 0;
    while (1) {
        if ((value & HALF_MASK) < thresholds.thresholds[index]) {
            break;
        }
        index++;
    }

    record        = &icons.records[index];
    D_801454EC[0] = index;
    Fishing_DrawSprite(record->icon, 1, (x + 29), (y + 29));
    if (record->first != 0) {
        Fishing_DrawSprite(72, 1, (record->offset + 29 + x), (y + 33));
        if (record->second != 0) {
            Fishing_DrawSprite(72, 1, (record->offset + x + 36), (y + 33));
        }
    }

    TEXT_Format(g_UiFormatBuffer, D_801D0C8C, value & HALF_MASK);
    for (i = 0; i < 5; i++) {
        if (g_UiFormatBuffer[i] == ' ') {
            g_UiFormatBuffer[i] = STRING_SPACE;
        }
    }
    UI_DrawText((x + 69), (y + 9), 0, 5, g_UiFormatBuffer);
}
