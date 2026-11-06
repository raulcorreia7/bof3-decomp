#ifndef OVERLAY_WORLD04_AREA185_13_H
#define OVERLAY_WORLD04_AREA185_13_H

/* The world04/area185/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"
#include "work/save.h"

/* Game-overlay state bytes the area request handlers reset. */
/* The scenario state byte the request writes. */
/* The scenario progress byte. */

/* The work pointer the drawing pass reads its position from. */

/* The scratchpad vectors the rotating-tile pass builds. */
extern SVECTOR D_1F800014[];
/* The actor-record byte the request handler tests. */
/* The game-overlay mode byte the handlers set. */
/* The frame counter and the game-overlay record pointer. */
/* The play clock the projection reads. */
/* The menu audio call and the shared request helper. */
/* The four hand-off bytes the request table selects. */

#endif
