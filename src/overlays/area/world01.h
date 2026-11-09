#ifndef WORLD01_FAMILY_H
#define WORLD01_FAMILY_H

#include "sys/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT       0xFF

/* The shop panel step the request sets. */
#define g_MenuMasterSubStep      (*(s8*)&g_MenuMasterSubStep)

#endif
