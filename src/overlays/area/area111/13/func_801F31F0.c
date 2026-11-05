#include "area111_13.h"

MATCH void func_801F31F0(void) {
    FIELD(s16, g_Task, 0x30u) += 4;
    if (FIELD(s16, g_Task, 0x30u) >= 0x100) {
        Actor_Clear();
    }
    func_801F3244();
}
