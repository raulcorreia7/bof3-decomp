#ifndef OVERLAY_BMAGIC_MAGIC060_00_H
#define OVERLAY_BMAGIC_MAGIC060_00_H

/* The bmagic/magic060/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic060Steps {
    Callback steps[5];
} Magic060Steps;

extern Magic060Steps D_801EEC04;

extern Callback D_801F0BBC[];
void            func_801F012C(void);

extern Callback D_801F0BCC[];
void            func_801F0428(void);

void func_801EF174(void);
void func_801EF2DC(void);

#endif
