#include "batl_end_00.h"

extern BattlePanelModeFuncs6 D_801EEC28;

MATCH void func_801EFD98(void) {
    BattlePanelModeFuncs6 handlers = D_801EEC28;

    handlers.handlers[g_MenuCurrentPanel->mode]();
}
