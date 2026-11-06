#ifndef OVERLAY_WORLD00_AREA028_13_H
#define OVERLAY_WORLD00_AREA028_13_H

/* The area028 world overlay's local declarations: the 32-entry position ring,
 * the scratch position view and the work state handler table. Only this image
 * includes the file. */

#include "overlays/area/world00.h"
#include "work/area_spad.h"

#define WORLD_POSITION_RING_ENTRY_COUNT 32u

extern UPoint2D D_800E4A00;

void          func_801F2C80(void);
void          func_801F2F5C(void);
void          func_801F2FB0(void* slot);
AreaSlotWork* func_801F3004(void);
void          func_801F318C(s16 radius);
void          func_801F3414(void);
void          func_801F3424(void);

#endif
