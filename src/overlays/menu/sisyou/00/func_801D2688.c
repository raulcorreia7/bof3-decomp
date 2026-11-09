#include "sisyou_00.h"

/* Sub-handler table of sisyou step 1 (g_MasterMenuStates[1] is func_801D2688). */

MATCH void func_801D2688(void) {
    SYS_DISPATCH_BYTE(g_MasterMenuSubFuncs, g_MenuMasterSubStep);
}
