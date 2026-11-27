#include "batl_end_00.h"

#define BATL_END_PANEL_MODE_COUNT 6

typedef struct BattleEndPanelModes {
    Callback modes[BATL_END_PANEL_MODE_COUNT];
} BattleEndPanelModes;

extern BattleEndPanelModes D_801EEC28;

MATCH void func_801EFD98(void) {
    BattleEndPanelModes handlers = D_801EEC28;

    handlers.modes[g_UIPanelCurrent->mode]();
}
