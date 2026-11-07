#include "area148_13.h"

MATCH void func_801F44B8(void) {
    func_801F4798(&((Actor*)g_Task)->pos.x, &((Actor*)g_Task)->unk_18);
    func_801F4614();
    ((Actor*)g_Task)->unk_0A -= 1;
    if (((Actor*)g_Task)->unk_0A == 0) {
        ((Actor*)g_Task)->timer += 1;
        ((Actor*)g_Task)->header.mode = 1;
    }
}
