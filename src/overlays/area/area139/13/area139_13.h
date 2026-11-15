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
/* The game mode the trigger records of this payload match. */
extern u8       D_80145E98;
/* Trigger records: two match bytes, a mode nibble and a flag bit. */
extern u8       D_801F45E4[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F4430[];
extern Callback D_801F4448[];

#endif
