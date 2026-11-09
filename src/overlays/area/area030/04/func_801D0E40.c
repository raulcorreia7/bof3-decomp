#include "area030_04.h"

/* Dispatches the per-slot handler selected by scratchpad work byte 0x02. */
MATCH void func_801D0E40(void) {
    D_801E1CE8[FISHING_STATE->mode_index_02]();
    Fishing_DrawHud(12, FISHING_STATE->cursor_10);
}
