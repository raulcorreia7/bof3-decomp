#include "area030_04.h"

/* Dispatches local-mode 1 update, writes 31 to the AREA030
 * flag at `0x8014832E`, then increments byte `3` of the buffer referenced by
 * the scratch-pad pointer cell at `0x1F800044`. */
MATCH void func_801DDCB8(void) {
    UI_SetMode(1);
    g_AreaDrawFlags = AREA_DRAW_SORTED_RECORDS | 0x2 | AREA_DRAW_CELL_LAYERS | AREA_DRAW_APPEND_ACTOR_PRIMITIVES | AREA_DRAW_APPEND_AREA_PRIMITIVES;
    g_Task->unk_03  = (g_Task->unk_03 + 1u);
}
