#include "start_08.h"

MATCH void Menu_DispatchStep(void) {
    SYS_DISPATCH_BYTE(g_MenuStartStates, g_MenuStep.step);
}
