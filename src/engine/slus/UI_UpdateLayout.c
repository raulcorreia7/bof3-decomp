#include "engine/slus/slus.h"

/* rebuilds the two window cells from the packed halfwords
 * D_80148334/D_80148336, runs the layout and selection passes, and reports
 * whether the shared word's confirm bit is clear.
 */
MATCH s32 UI_UpdateLayout(void) {
    u16 confirm;

    D_801490BC.origin_x = ((s16)D_80148334 >> 4) + 10;
    D_801490BC.origin_y = ((s16)D_80148336 >> 4) + 6;
    func_801507BC();
    func_801518F4();
    if ((g_UiWindowChannel & FRONTEND_FLAG_SELECTION) == 0) {
        UI_DrawMessageScript();
    }
    confirm = g_UiWindowChannel & FRONTEND_FLAG_CONFIRM;
    return confirm == 0;
}
