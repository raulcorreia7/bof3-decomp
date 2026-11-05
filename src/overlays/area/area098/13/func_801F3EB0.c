#include "area098_13.h"

MATCH void func_801F3EB0(void) {
    u8* row;
    s16 timer;

    g_SpadWork->unk_30 = g_SpadWork->unk_30 + 1;
    if ((g_SpadWork->unk_2E & 3) == 0) {
        row = Area_FindFreeWorkRow();
        if (row != NULL) {
            func_801F4DBC(row);
        }
    }
    func_801F4E7C();
    timer              = g_SpadWork->unk_2E - 1;
    g_SpadWork->unk_2E = timer;
    if (timer == 0) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->unk_01++;
    }
}
