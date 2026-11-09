#ifndef WORLD02_FAMILY_H
#define WORLD02_FAMILY_H

/* an image header that reads one includes this file. */

#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

extern Callback D_801F5750[];

#endif
