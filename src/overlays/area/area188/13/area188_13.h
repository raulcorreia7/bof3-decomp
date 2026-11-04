#ifndef OVERLAY_WORLD04_AREA188_13_H
#define OVERLAY_WORLD04_AREA188_13_H

/* The world04/area188/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

#include "shared/WorldSpin.h"

extern u8 D_801F6898[];

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

/* The shared record table as its byte view. */

/* The scrolling halfword and the selection byte the store paths write. */

/* The scratchpad work row the state dispatchers read. */
/* The per-state handler tables the dispatchers index. */
extern Callback D_801F4DF4[];
extern Callback D_801F4DFC[];
extern Callback D_801F4E04[];
extern u8       D_801F689C;
/* The image's two sticky state bytes. */
extern u8       D_801F68A0;

/* The game-overlay state bytes the cancel path resets. */

void Area_SetCellCode(s16 column, s16 row, u8 code);
void Area_ProjectPoint(s32* pos, long* screen_xy);

void func_801F3E7C(void);
void func_801F3DE0(void);
void func_801F44B4(void);

#endif
