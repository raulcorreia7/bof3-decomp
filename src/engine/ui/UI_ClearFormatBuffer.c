#include "engine/slus/slus.h"

/* clears the first eight words of the g_UiFormatBuffer table.
 */
MATCH void UI_ClearFormatBuffer(void) {
    u32* p;
    u8   index;

    p     = (u32*)g_UiFormatBuffer;
    index = 0;
    do {
        *p = 0;
        index++;
        p++;
    } while (index < 8);
}
