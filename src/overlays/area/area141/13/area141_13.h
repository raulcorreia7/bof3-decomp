#ifndef OVERLAY_WORLD03_AREA141_13_H
#define OVERLAY_WORLD03_AREA141_13_H

/* The world03/area141/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"
#include "work/save.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The fixed work record the dispatch compares the work pointer against. */
extern Actor D_80143F48;

/* The state handler tables the dispatchers index. */
extern Callback D_801F47E8[];
extern u8       D_801F4DBC[];
extern Callback D_801F4DC4[];

void func_801F390C(void);

extern Callback D_801F4DCC[];
void            func_801F4300(u8* table, s32 arg);

/* The game-overlay state bytes the cancel path resets. */
extern u8 D_801F4E50[];

#endif
