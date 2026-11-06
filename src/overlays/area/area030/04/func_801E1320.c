#include "area030_04.h"

/* Draws the roster panel and count caption. */
MATCH void func_801E1320(s16 x, s16 y) {
    FishingIconData      icons;
    FishingThresholdData thresholds;
    u32                  value;
    u32                  index;
    FishingIcon*         record;
    s32                  i;

    icons      = D_801D0C3C;
    thresholds = D_801D0C70;

    func_801E0C80(3, 1);
    func_801E0DCC(6, 1, x, y);
    func_801E0DCC(7, 1, (x + 0x58), y);

    value = func_801E0B6C();
    index = 0;
    while (1) {
        if ((value & HALF_MASK) < thresholds.thresholds[index]) {
            break;
        }
        index++;
    }

    record        = &icons.records[index];
    D_801454EC[0] = index;
    func_801E0DCC(record->icon, 1, (x + 0x1D), (y + 0x1D));
    if (record->first != 0) {
        func_801E0DCC(0x48, 1, (record->offset + 0x1D + x), (y + 0x21));
        if (record->second != 0) {
            func_801E0DCC(0x48, 1, (record->offset + x + 0x24), (y + 0x21));
        }
    }

    sprintf((char*)g_UiFormatBuffer, D_801D0C8C, value & HALF_MASK);
    for (i = 0; i < 5; i++) {
        if (g_UiFormatBuffer[i] == ' ') {
            g_UiFormatBuffer[i] = STRING_SPACE;
        }
    }
    UI_DrawText((x + 0x45), (y + 9), 0, 5, g_UiFormatBuffer);
}
