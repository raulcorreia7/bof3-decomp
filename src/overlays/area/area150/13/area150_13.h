#ifndef OVERLAY_WORLD03_AREA150_13_H
#define OVERLAY_WORLD03_AREA150_13_H

/* The world03/area150/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"

/* The scenario state byte the hit path sets. */

/* The game-overlay state byte the request writes. */

/* The request value table indexed by the selection byte. */
extern u16 D_801F3808[];

/* The scenario flag bytes the step tests, sets and clears. */
extern u8  D_80144EF8[];
extern u16 D_80144F54;
extern u8  D_80144F56;
extern u8  D_80144F57;
extern u8  D_8014504B;
/* The shop and save start the field scene. */
void       func_801C16B8(void);

#endif
