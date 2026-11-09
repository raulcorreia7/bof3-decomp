#include "sisyou_00.h"

/* Sisyou step table: the seven step handlers func_801D2614, func_801D2688, func_801D278C, func_801D2BE8, func_801D32D4, func_801D3924 and Menu_ApplyMasterMode, indexed by the step byte g_MenuMasterStep. */

MATCH void Menu_UpdateMaster(void) {
    SYS_DISPATCH_BYTE(g_MasterMenuStates, g_MenuMasterStep);
}
