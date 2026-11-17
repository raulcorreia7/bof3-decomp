#include "start_08.h"

/* func_801DA320 */
MATCH void Menu_RunPartyChange(void) {
    SYS_DISPATCH_BYTE(D_801EC53C, g_MenuStep.state);
}
