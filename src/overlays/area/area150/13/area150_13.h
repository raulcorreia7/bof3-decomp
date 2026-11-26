#ifndef OVERLAY_WORLD03_AREA150_13_H
#define OVERLAY_WORLD03_AREA150_13_H

/* The world03/area150/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* FAKE: the call passes the count as s32, the width the real prototype (u8) lacks. */
#define Item_Add ((bool (*)(s32, s32, s32, s32))Item_Add)

/* The request value tables indexed by the selection byte. */
extern u16 D_801F3804[];
extern u16 D_801F3808[];

#endif
