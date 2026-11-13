#ifndef OVERLAY_WORLD04_AREA191_13_H
#define OVERLAY_WORLD04_AREA191_13_H

/* The world04/area191/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scenario state byte and its flag word. */

/* The game-overlay state bytes the request paths write. */
extern u8 D_80146874;
extern u8 D_80146875;
/* The scratchpad work row. */
/* The state dispatch table in the trailing payload. */
extern u8 D_801F3C54[];
/* The selection record and its two step tables. */
extern u8 D_801F41D0[];
extern u8 D_801F41D1[];

extern u8  D_801F4260[];
/* The neighbour tables the cell lookup reads. */
extern u8  D_801F4290[];
/* The spawn-row table the selection pass walks, one row set per mode. */
extern u8* D_801F43D8[];

/* The published field work row and the state byte the reset writes. */

/* The draw pass this image's entry runs. */
void Area_DrawScreenTint(void);

void func_801F39AC(void);
void func_801F3AB0(void);

#endif
