#ifndef OVERLAY_BMAGIC_MAGIC020_03_H
#define OVERLAY_BMAGIC_MAGIC020_03_H

/* The bmagic/magic020/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

#define MAGIC020_SECOND_STEP_COUNT 3

typedef struct Magic020SecondSteps {
    Callback steps[MAGIC020_SECOND_STEP_COUNT];
} Magic020SecondSteps;

#define MAGIC020_STEP_COUNT 8

typedef struct Magic020Steps {
    Callback steps[MAGIC020_STEP_COUNT];
} Magic020Steps;

extern Magic020SecondSteps D_801EEC3C;
extern Magic020Steps       D_801EEC1C;
extern u8                  D_801EFEC4[];

u32  func_800AFB48(PartyMember* battler);
void func_800AF8F0(PartyMember* battler);
void func_801EFBA0(void);

void func_801EFD10(void);

void func_801EFD88(void);

#endif
