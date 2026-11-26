#include "boss025_13.h"

MATCH void func_800C3038(void) {
    if (g_UiPanelTasks[20].state == 0 && (g_Battle.outcome.event_flags & 0x2) == 0) {
        SELF(PartyMember)->header.mode++;
    }
}
