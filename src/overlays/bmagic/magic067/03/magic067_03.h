#ifndef OVERLAY_BMAGIC_MAGIC067_03_H
#define OVERLAY_BMAGIC_MAGIC067_03_H

/* The bmagic/magic067/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic067Steps801EEC04 {
    Callback steps[5];
} Magic067Steps801EEC04;

typedef struct Magic067Steps801EEC18 {
    Callback steps[3];
} Magic067Steps801EEC18;

extern Magic067Steps801EEC04 D_801EEC04;
extern Magic067Steps801EEC18 D_801EEC18;
extern Callback              D_801F04C8[];
extern Callback              D_801F04D8[];

void func_801EF688(void);
void func_801EF79C(void);
void func_801F00C4(void);

#endif
