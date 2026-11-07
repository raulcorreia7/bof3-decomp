#include "start_08.h"

MATCH void func_801E8D60(void) {
    g_MenuStartPanel0StateFuncs[g_MenuCurrentPanel->state]();
    func_801E8DB4(g_MenuCurrentPanel);
}
