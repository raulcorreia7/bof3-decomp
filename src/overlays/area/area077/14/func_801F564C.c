#include "area077_14.h"

MATCH void func_801F564C(void) {
    ((Actor*)g_Task)->unk_09 = 0;
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 7)) {
        ((Actor*)g_Task)->header.step = 3;
    } else {
        func_801F529C(3, 0, 3, 3);
        ((Actor*)g_Task)->header.step++;
    }
}
