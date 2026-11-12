#include "area098_13.h"

MATCH void func_801F3EB0(void) {
    u8* row;
    s16 timer;

    g_Task->screen_y = g_Task->screen_y + 1;
    if ((g_Task->screen_x & 0x3) == 0) {
        row = Area_FindFreeWorkRow();
        if (row != NULL) {
            func_801F4DBC(row);
        }
    }
    func_801F4E7C();
    timer            = g_Task->screen_x - 1;
    g_Task->screen_x = timer;
    if (timer == 0) {
        g_Task->timer = 0;
        g_Task->header.mode++;
    }
}
