#ifndef OVERLAY_FIELD_WORLD_H
#define OVERLAY_FIELD_WORLD_H

#include "types.h"

/* func_8019A194 */
u8 WorldMap_FindRegion(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_FIELD_WORLD_H_LOCAL)
#define OVERLAY_FIELD_WORLD_H_LOCAL

/* func_8019A1D4 */
u8* WorldMap_GetPoints(void);

#endif
