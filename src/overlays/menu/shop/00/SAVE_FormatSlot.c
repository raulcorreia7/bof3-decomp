#include "shop_00.h"

/* func_801D7080 */
MATCH void SAVE_FormatSlot(void) {
    u8 i;

    for (i = 0; i < 64; i++) {
        g_UiFormatBuffer[i] = 0;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C98, D_801E5434[D_801E6108], D_801E5434[g_PlayClock.hours / 10], D_801E5434[g_PlayClock.hours % 10], D_801E5434[g_PlayClock.minutes / 10],
                D_801E5434[g_PlayClock.minutes % 10], D_801E5434[g_Characters[CHAR_INDEX_RYU].level / 10], D_801E5434[*MEM_PTR(u8, SHOP_CLOCK_SECONDS_ADDR) % 10]);
}
