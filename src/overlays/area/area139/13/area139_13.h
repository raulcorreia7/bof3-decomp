#ifndef OVERLAY_WORLD03_AREA139_13_H
#define OVERLAY_WORLD03_AREA139_13_H

/* The world03/area139/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
#define g_CurrentActor ((u8*)g_CurrentActor)

/* The overlay payload: one three-byte colour row per actor row (red at
 * D_801F442C, green at D_801F442D, blue at D_801F442E), and behind it the
 * entry-cell payload func_801F3AD0 steps by, with the cell bytes at 0x38 and
 * 0x39 and the z and screen-x words at 0x30 and 0x34. */
extern u8       D_801F442C[];
extern u8       D_801F442D[];
extern u8       D_801F442E[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F4430[];
extern Callback D_801F4448[];
/* The game mode the trigger records of this payload match. */
/* Trigger records: two match bytes, a mode nibble and a flag bit. */
extern u8       D_801F45E4[];

/* The sprite-word fields above the floor quad's cell coordinate. */
#define AREA_FLOOR_QUAD_PART ((0x150) << 16)

/* The pair of rings the cell line joins. */
void func_801F36DC(s16 x0, s16 y0, s16 radius0, u16 angle0, s16 x1, s16 y1, s16 radius1, u16 angle1);

#endif
