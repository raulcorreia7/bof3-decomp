#ifndef OVERLAY_BMAGIC_MAGIC150_03_H
#define OVERLAY_BMAGIC_MAGIC150_03_H

/* The bmagic/magic150/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 D_801EFAAC;
extern u16 D_801EFAB0;
/* The eight-entry table the cursor walks and the cursor itself. */
extern u8  D_801EFAB4[];
extern u8* D_801EFAF4;

/* A world point and the screen cells its left, centre and right projections land in. */
typedef struct ProjectedSpan {
    s32     pos[3];
    u8      pad_0C[4];
    DVECTOR screen[3]; /* 0x10 left, 0x14 centre, 0x18 right */
} ProjectedSpan;

void func_801EF254(void);
u8   func_801EF8EC(void);
/* func_801EF2C0 */
void BMagic_ProjectSpan(ProjectedSpan* span);

void func_801AFE18(void);
void func_801EF040(void);
void func_801EF6F8(void);

#endif
