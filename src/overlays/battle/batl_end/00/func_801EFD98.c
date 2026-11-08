#include "batl_end_00.h"

#define BATL_END_PANEL_MODE_COUNT 6

typedef struct BatlEndPanelModes {
    Callback modes[BATL_END_PANEL_MODE_COUNT];
} BatlEndPanelModes;

extern BatlEndPanelModes D_801EEC28;

MATCH void func_801EFD98(void) {
    BatlEndPanelModes handlers = D_801EEC28;

    handlers.modes[g_MenuCurrentPanel->mode]();
}
