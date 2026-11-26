#ifndef OVERLAY_WORLDMAP_H
#define OVERLAY_WORLDMAP_H

#include "types.h"
#include "area/map.h"

/* func_8019A194 */
u8 WorldMap_FindRegion(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_WORLDMAP_H_LOCAL)
#define OVERLAY_WORLDMAP_H_LOCAL

/* func_8019A1D4 */
WorldMapPoint* WorldMap_GetPoints(void);
/* func_801A839C */
void           WorldMap_RunLocationGuide(void);
/* func_801A852C */
void           WorldMap_RunFairyEntry(void);

#endif
