#ifndef OVERLAY_BMAGIC_MAGIC106_03_H
#define OVERLAY_BMAGIC_MAGIC106_03_H

/* The bmagic/magic106/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern void (*D_801EF9C0[])(void);
extern void (*D_801EF9C4[])(void);
extern u8* D_801F05F8;

void func_801EF52C(void);
void func_801EF5F4(void);
void func_801EEEE0(void);
void func_801EECE4(void);
void Effect_PlayOnZeroTick(void);

/* The effect work rows the module runner walks (stride 0x20). */
extern u8 D_801EF9F8[];
extern u8 D_801EFA14[];

#endif
