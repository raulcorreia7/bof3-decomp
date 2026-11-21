#include "shop_00.h"

/* func_801D7344 */
MATCH void Menu_RunInoculation(void) {
    SYS_DISPATCH_BYTE(g_InoculationSteps, g_MenuStep.sub_step);
}
