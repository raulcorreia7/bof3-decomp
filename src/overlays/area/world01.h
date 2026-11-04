#ifndef WORLD01_FAMILY_H
#define WORLD01_FAMILY_H

/* Declarations shared by two or more world01 images; an image header that
 * reads one includes this file. */

#include "sys/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT       0xFF

#define AREA_WORK_WINDOW         0x800E4800u /* the per-area work window (AreaHandlerRecord.work_08) */
/* The shop panel step the request sets. */
#define g_MasterSubStep          (*(s8*)&g_MasterSubStep)

/* The selection byte that arms the area request. */
extern s8 D_801490C7;

u8 Game_FindAreaHandler(void);

#endif
