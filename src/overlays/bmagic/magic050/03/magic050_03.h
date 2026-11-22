#ifndef OVERLAY_BMAGIC_MAGIC050_03_H
#define OVERLAY_BMAGIC_MAGIC050_03_H

/* The bmagic/magic050/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* FAKE: g_ScratchPad.cells.words[3] under its own symbol; the store before the fan loop matches only apart from the record. */
extern s32      D_1F80000C;
extern u8       D_801EFA90[];
/* The 16.16 offsets added to the area scroll target, one row per effect level. */
extern Offset2  D_801EFAA0[];
extern Callback D_801EFAF0[];
void            func_801EF898(void);

#endif
