#include "start_08.h"

/* func_801D970C */
MATCH void Menu_RunPartyScreen(void) {
    SYS_DISPATCH_BYTE(g_MenuPartySteps, g_MenuStep.sub_step);
}
