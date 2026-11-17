#ifndef OVERLAY_WORLD03_AREA119_13_H
#define OVERLAY_WORLD03_AREA119_13_H

/* The world03/area119/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "area/area.h"
#include "overlays/area/world03.h"
#include "area/spad.h"
#include <rand.h>

#define g_SceneFlags ((void*)g_SceneFlags)

extern u8  D_80144ED0[];
/* The per-cell byte-code table the map bundle publishes. */
extern u8* g_AreaCellCodes;
/* The area camera position words the route tests. */
extern s32 D_80145EC4;
extern s32 D_80145EC8;
extern u8  D_80146920[];
extern u8  D_801F45C4[];

/* The eight spawn positions the overlay cycles through, in sixteenths of a cell. */
extern Pos2u D_801F4614[8];

/* The distance from a camera word to the point the overlay watches, given as the
 * point's offset from zero. */
static inline s32 Area119_Distance(s32 value, s32 point) {
    s32 delta;

    delta = value + point;
    return ABS(delta);
}

void func_801F3324(void);
void func_801F369C(s32 level);
void func_801F3F04(s32 depth);

void func_801F301C(void);

#endif
