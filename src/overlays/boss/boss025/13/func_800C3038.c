#include "boss025_13.h"

MATCH void func_800C3038(void) {
    if (D_80148603 == 0 && (g_Battle.outcome.event_flags & 0x2) == 0) {
        g_Task->header.mode++;
    }
}
