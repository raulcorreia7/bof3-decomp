#ifndef OVERLAY_BMAGIC_MAGIC126_03_H
#define OVERLAY_BMAGIC_MAGIC126_03_H

/* The bmagic/magic126/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
extern s16     D_1F800004;

extern Callback D_801F1268[];

extern Callback D_801F1278[];

extern Callback D_801F1288[];

extern Callback D_801F12AC[];
extern u8       D_801F12BC[];
extern u8       D_801F12D8[];
void            func_801EFD5C(void);
void            func_801F06AC(void);
void            func_801F091C(void);

void                func_801F0ED0(void);
void                func_801F116C(void);
void                func_801F11AC(void);
extern PartyMember* D_801F22BC;

void BMagic_DrawGlowRingInner(void);

void func_801EF1C8(void);
void BMagic_DrawGlowRingOuter(void);

#endif
