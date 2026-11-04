#include "sisyou_00.h"

/* Sisyou step table: the seven step handlers func_801D2614, func_801D2688,
 * func_801D278C, func_801D2BE8, func_801D32D4, func_801D3924 and
 * Master_ApplyMaster, indexed by the step byte g_MasterStep. */

MATCH void Master_DispatchMenu(void) {
    SYS_DISPATCH_BYTE(g_MasterMenuFuncs, g_MasterStep);
}
