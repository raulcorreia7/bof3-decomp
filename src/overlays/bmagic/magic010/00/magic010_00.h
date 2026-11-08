#ifndef OVERLAY_BMAGIC_MAGIC010_00_H
#define OVERLAY_BMAGIC_MAGIC010_00_H

/* The bmagic/magic010/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The task record of this overlay: the fade row index is the byte at +0x0B, past unk_09. */
typedef struct Magic010Task {
    TaskHeader header;
    u8         pad_03[6];
    u8         unk_09;
    u8         unk_0A;
    u8         timer;
} Magic010Task;

#define MAGIC010_TASK ((Magic010Task*)g_Task)

/* Battle flag and the request hand-off these overlays toggle. */
extern Magic010SharedSteps D_801EEC04;
#endif
