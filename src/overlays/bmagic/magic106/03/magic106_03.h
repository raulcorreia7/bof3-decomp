#ifndef OVERLAY_BMAGIC_MAGIC106_03_H
#define OVERLAY_BMAGIC_MAGIC106_03_H

/* The bmagic/magic106/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern void (*D_801EF9C0[])(void);
extern void (*D_801EF9C4[])(void);
/* Per blade of the four-blade fan: the two corner radii, the two corner angles and the phase of the height wave. */
extern s16 D_801EF9D4[];
extern s16 D_801EF9DC[];
extern s16 D_801EF9E4[];
extern s16 D_801EF9EC[];
extern u8  D_801EF9F4[];
/* The effect work rows the module runner walks (stride 0x20). */
extern u8  D_801EF9F8[];

void func_801EF52C(void);
void func_801EF5F4(void);

/* The battler column of the D_801EF9F8 rows, eight words to a row. */
extern PartyMember* D_801EFA14[];

#endif
