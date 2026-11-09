#ifndef AREA_SPAD_H
#define AREA_SPAD_H

/* The field, plchar, world and scenario overlays read the entity row that the scratchpad cell at 0x1F800044 points to through this view. */

#include "psx/mem.h"
#include "sys/actor.h"

#define g_Task ((Actor*)g_Task)

#endif
