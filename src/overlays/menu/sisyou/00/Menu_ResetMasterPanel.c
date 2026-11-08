#include "sisyou_00.h"

MATCH void Menu_ResetMasterPanel(void) {
    g_MenuMasterStep         = 0;
    g_MenuMasterSubStep      = 0;
    g_MenuMasterPanelLock    = 0;
    D_801D4288               = 0;
    g_MenuMasterScrollOffset = 0;
}
