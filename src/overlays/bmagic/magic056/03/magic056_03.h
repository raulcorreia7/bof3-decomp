#ifndef OVERLAY_BMAGIC_MAGIC056_03_H
#define OVERLAY_BMAGIC_MAGIC056_03_H

/* The bmagic/magic056/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

#define MAGIC056_STEP_COUNT 9

typedef struct Magic056Steps {
    Callback handlers[MAGIC056_STEP_COUNT];
} Magic056Steps;

extern Magic056Steps D_801EEC10;
extern Callback      D_801F0754[];
void                 func_801EF4C0(void);
u8                   func_800AFB48(PartyMember* battler);
void                 func_800AF8F0(PartyMember* work);

extern Callback D_801F0760[];
void            func_801EFC74(void);

#endif
