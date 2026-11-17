#include "start_08.h"

/* func_801D9AF0 */
MATCH void Menu_RunFormation(void) {
    SYS_DISPATCH_BYTE(g_MenuFormationSteps, g_MenuStep.state);
}
