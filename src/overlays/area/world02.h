#ifndef WORLD02_FAMILY_H
#define WORLD02_FAMILY_H

#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The per-actor 16-byte turn records. */
extern s8  D_80147CB9[];
extern s32 D_80147CBC[];

extern Callback D_801F5750[];

#endif
