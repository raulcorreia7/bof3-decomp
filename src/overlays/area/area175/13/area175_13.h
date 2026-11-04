#ifndef OVERLAY_WORLD04_AREA175_13_H
#define OVERLAY_WORLD04_AREA175_13_H

/* The world04/area175/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"
#include "shared/WorldSpin.h"

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0x7
#define AREA_SPIN_SCALE_BASE 8
#define AREA_SPIN_FADE       0

/* The frame counter and game-overlay record pointer. */

/* The scenario progress byte. */

/* The work-record pointer stored in the scratchpad. */

/* The game-overlay state bytes the request writes. */
/* The selection bytes the request saves. */
/* The payload includes the overlay's per-state handler tables. */
extern u8 D_801F45EC[];

/* Fairy_VillageInit in the commu overlay at the same address. */
void func_801EECA4(void);
void Area_ProjectPoint(s32* pos, long* screen_xy);

#endif
