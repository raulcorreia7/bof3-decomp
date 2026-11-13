#ifndef OVERLAY_WORLD04_AREA192_13_H
#define OVERLAY_WORLD04_AREA192_13_H

/* The world04/area192/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"

/* The selection record and its two step tables. */
extern u8  D_801F380C[];
extern u8  D_801F380D[];
extern u8  D_801F3890[];
/* The neighbour tables the cell lookup reads. */
extern u8  D_801F38C0[];
/* The area counter the selection pass reads. */
extern u8  D_80144F56;
/* The spawn-row table the selection pass walks, one row set per mode. */
extern u8* D_801F3A08[];

/* The area flag word, the cue timer and the three scene bytes. */

/* The game-overlay state bytes the request paths write. */

/* The published field work row and the state byte the reset writes. */

/* The cell lookup the selection pass runs. */
u16  func_801F33E4(s32 base, s32 arg1, s32 row, s32 mode);
/* The selection pass this image's update entry runs. */
void func_801F3444(void);

void func_801F3548(void);

#endif
