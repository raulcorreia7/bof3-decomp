#ifndef OVERLAY_BMAGIC_MAGIC069_03_H
#define OVERLAY_BMAGIC_MAGIC069_03_H

/* The bmagic/magic069/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Scratchpad cells the line drawer stages: the two screen coordinates it offsets. The shade
 * halfword it stamps into the line colours is D_1F800006 of sys/scratchpad.h. */
extern volatile u16 D_1F80000C;
extern volatile u16 D_1F80000E;

/* The battle panel row offsets of battle/battle/03, two bytes per character, picked by the battler facing. */
extern u8 s_BattlePanelYOffsets[];
extern u8 D_801EB109[];

void func_801EEE30(void);

void            func_801EFA84(void);
void            func_801F0274(void);
extern Callback D_801F0518[];
extern Callback D_801F0504[];
void            func_801EFC00(void);
void            func_801EFF14(void);

/* The edge phases of the three triangles of each fan, in 64ths of a turn. */
extern u8 D_801F0534[];

#endif
