#include "shop_00.h"

MATCH void func_801D7080(void) {
    u8 i;

    for (i = 0; i < 64; i++) {
        g_UiFormatBuffer[i] = 0;
    }
    sprintf((char*)g_UiFormatBuffer, (const char*)D_801D0C98, D_801E5434[D_801E6108],
            D_801E5434[g_SaveData.play_clock.hours_00 / 10], D_801E5434[g_SaveData.play_clock.hours_00 % 10],
            D_801E5434[g_SaveData.play_clock.minutes_01 / 10], D_801E5434[g_SaveData.play_clock.minutes_01 % 10],
            D_801E5434[g_SaveData.characters[CHAR_INDEX_RYU].level / 10],
            D_801E5434[*MEM_PTR(u8, SHOP_CLOCK_SECONDS_ADDR) % 10]);
}
