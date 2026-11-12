#ifndef OVERLAY_BMAGIC_MAGIC069_03_H
#define OVERLAY_BMAGIC_MAGIC069_03_H

/* The bmagic/magic069/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Scratchpad cells the line drawer stages: the shade byte it stamps into the line colours and the
 * two screen coordinates it offsets. */
extern volatile u16 D_1F800006;
extern volatile u16 D_1F80000C;
extern volatile u16 D_1F80000E;

void func_801EEE30(void);

void            func_801EFA84(void);
void            func_801F0274(void);
extern Callback D_801F0518[];
extern Callback D_801F0504[];
void            func_801EFC00(void);
void            func_801EFF14(void);

#endif
