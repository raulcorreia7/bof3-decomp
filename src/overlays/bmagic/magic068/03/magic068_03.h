#ifndef OVERLAY_BMAGIC_MAGIC068_03_H
#define OVERLAY_BMAGIC_MAGIC068_03_H

/* The bmagic/magic068/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Magic068SharedSteps D_801EEC04;
extern u8                  D_801EC2E4;
extern u16                 D_801EFCA4[][3];
/* The Foretell score bonus, indexed by the standing party count less the standing enemy count. */
extern s8                  D_801EFC9F[];

void func_801DE8C0(s8 index, s8 record_kind, u8* text);

void func_801EF55C(void);

#endif
