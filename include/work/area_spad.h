#ifndef WORK_AREA_SPAD_H
#define WORK_AREA_SPAD_H

/* The field, plchar, world and scenario overlays read the entity row that the
 * scratchpad cell at 0x1F800044 points to through this view. A unit that must
 * reload the cell on every access keeps its own volatile spelling; spelling the
 * global by name at each use is what re-materializes lui+lw per read. */

#include "psx/mem.h"
#include "work/actor.h"

#define g_Task ((Actor*)g_Task)

#endif
