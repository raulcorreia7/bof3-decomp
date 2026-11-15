#ifndef OVERLAY_WORLD03_AREA139_13_H
#define OVERLAY_WORLD03_AREA139_13_H

/* The world03/area139/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
#define g_CurrentActor ((u8*)g_CurrentActor)

/* The overlay payload: one three-byte colour row per actor row (red at
 * D_801F442C, green at D_801F442D, blue at D_801F442E), and behind it the
 * entry-cell payload func_801F3AD0 steps by, with the cell bytes at 0x38 and
 * 0x39 and the z and screen-x words at 0x30 and 0x34. */
extern u8       D_801F442C[];
extern u8       D_801F442D[];
extern u8       D_801F442E[];
/* The game mode the trigger records of this payload match. */
extern u8       D_80145E98;
/* Trigger records: two match bytes, a mode nibble and a flag bit. */
extern u8       D_801F45E4[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F4430[];
extern Callback D_801F4448[];

/* The sprite-word fields above the floor quad's cell coordinate. */
#define AREA_FLOOR_QUAD_PART ((0x150) << 16)

#endif
