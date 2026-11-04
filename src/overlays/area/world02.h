#ifndef WORLD02_FAMILY_H
#define WORLD02_FAMILY_H

/* Declarations shared by two or more world02 images; an image header that
 * reads one includes this file. */

#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The selection byte that arms the area request. */
extern s8       D_801490C7;
extern Callback D_801F5750[];

/* func_8015B5F4 */
void SYS_ToggleFlag(void* bits, u8 bit_index);
#endif
