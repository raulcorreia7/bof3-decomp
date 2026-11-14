#ifndef OVERLAY_BMAGIC_MAGIC104_03_H
#define OVERLAY_BMAGIC_MAGIC104_03_H

/* The bmagic/magic104/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

extern Magic010SharedSteps D_801EEC04;
extern Callback            D_801F08F0[];
/* The step handlers the draw step dispatches. */
extern Callback            D_801F0900[];

/* The x and y offset of each of the eight spawned effects. */
extern Point2DL D_801F08A8[];

void func_801EF370(void);
void func_801EFA54(void);
void func_801EFB2C(void);
void func_801EFE34(void);
void func_801F03C4(void);

#endif
