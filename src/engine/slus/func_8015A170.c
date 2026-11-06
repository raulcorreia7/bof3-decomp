#include "engine/slus/slus.h"

/* walks the D_801490CF table's D_801490C6+1 entries through
 * UI_DrawTextAt, passing 0x3A as the first argument and threading each returned
 * cursor into the next call.
 */
MATCH void func_8015A170(void) {
    u8* cursor;
    s32 i;

    cursor = D_801490B0;
    for (i = 0; i <= g_MessageWindow.last_row; i++) {
        cursor = UI_DrawTextAt(0x3A, D_801490CF[i], cursor);
    }
}
