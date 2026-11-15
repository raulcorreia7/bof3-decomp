#ifndef OVERLAY_WORLD03_AREA139_13_H
#define OVERLAY_WORLD03_AREA139_13_H

/* The world03/area139/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
#define g_CurrentActor ((u8*)g_CurrentActor)

/* One three-byte colour row per actor row: D_801F442C holds the red byte of
 * each row, D_801F442D the green and D_801F442E the blue. */
extern u8       D_801F442C[];
extern u8       D_801F442D[];
extern u8       D_801F442E[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F4430[];
extern Callback D_801F4448[];

/* The payload func_801F3AD0 steps by: cell offsets at 0x38 and 0x39, the z
 * and screen-x words at 0x30 and 0x34, indexed by twice the row's x cell. */
extern u8 D_801F442C[];

/* The sprite-word fields above the floor quad's cell coordinate. */
#define AREA_FLOOR_QUAD_PART ((0x150) << 16)

#endif
