#ifndef OVERLAY_WORLD03_AREA144_13_H
#define OVERLAY_WORLD03_AREA144_13_H

/* The world03/area144/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The field status byte the timer bumps are gated on. */
/* The state handler tables the dispatchers index. */
extern Callback D_801F3E68[];
/* The palette-dirty byte the setup step clears. */
extern u8       D_801F4960;

void func_801F2E18(void);
/* The palette row clear the setup step enters. */
void func_801F30CC(void);

/* The mode gate the step tests. */
u8 func_801F34FC(void);

#endif
