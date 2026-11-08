#include "area148_13.h"

MATCH void func_801F44B8(void) {
    func_801F4798(&(g_Task)->pos.x, &(g_Task)->unk_18);
    func_801F4614();
    (g_Task)->unk_0A -= 1;
    if ((g_Task)->unk_0A == 0) {
        (g_Task)->timer += 1;
        (g_Task)->header.mode = 1;
    }
}
