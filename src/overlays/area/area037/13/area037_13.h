#ifndef OVERLAY_WORLD00_AREA037_13_H
#define OVERLAY_WORLD00_AREA037_13_H

/* The world00/area037/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world00.h"
#include "area/spad.h"

/* The owner is src/engine/game/00/game_00.h; that header is not visible to this
 * overlay, so keep the local declaration with the owner's volatile qualifier. */
extern volatile u8 g_GameRequestKind;

/* The cell tables the actor placement reads: the x and y byte cells and the z
 * value, indexed by the actor param byte. */
extern u8  D_801F3B34[];
extern u8  D_801F3B38[];
extern s16 D_801F3B3C[];

#endif
