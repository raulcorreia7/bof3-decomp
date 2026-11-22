#ifndef OVERLAY_BMAGIC_MAGIC079_03_H
#define OVERLAY_BMAGIC_MAGIC079_03_H

/* The bmagic/magic079/03 overlay. Only this image includes the file. */

#define FAKE_DECL_BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F02B4[];

/* The ring radius of each timer cell, read by the effect's step branches. */
extern s32 D_801F02DC[];
extern s32 D_801F031C[];
extern s32 D_801F037C[];

void func_801EF458(void);

extern Callback D_801F02C8[];
void            func_801F002C(void);

extern Callback D_801F035C[];

extern Callback D_801F036C[];

#endif
