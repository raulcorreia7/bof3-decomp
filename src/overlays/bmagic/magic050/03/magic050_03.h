#ifndef OVERLAY_BMAGIC_MAGIC050_03_H
#define OVERLAY_BMAGIC_MAGIC050_03_H

/* The bmagic/magic050/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EFAF0[];
extern u8       D_801EFA90[];
/* The 16.16 offsets added to the area scroll target, one row per effect level. */
extern Offset2  D_801EFAA0[];
void            func_801EF898(void);

#endif
