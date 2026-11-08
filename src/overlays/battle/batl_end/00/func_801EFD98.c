#include "batl_end_00.h"

typedef struct Panel801EEC28Modes {
    Callback modes[6];
} Panel801EEC28Modes;

extern Panel801EEC28Modes D_801EEC28;

MATCH void func_801EFD98(void) {
    Panel801EEC28Modes handlers = D_801EEC28;

    handlers.modes[g_MenuCurrentPanel->mode]();
}
