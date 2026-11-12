#ifndef OVERLAY_BMAGIC_MAGIC003_03_H
#define OVERLAY_BMAGIC_MAGIC003_03_H

/* The bmagic/magic003/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8 D_801463D6;

#define MAGIC003_STEP_COUNT 5

typedef struct Magic003Steps {
    Callback steps[MAGIC003_STEP_COUNT];
} Magic003Steps;

#define MAGIC003_SECOND_STEP_COUNT 4

typedef struct Magic003SecondSteps {
    Callback steps[MAGIC003_SECOND_STEP_COUNT];
} Magic003SecondSteps;

extern Magic003Steps D_801EEC04;

void func_801EF324(void);

void func_801EF708(void);

void func_801EFB8C(void);

void func_801EFCF8(void);

void func_801EFD4C(void);

void func_801EFEC8(void);

extern Magic003SecondSteps D_801EEC18;
extern Callback            D_801F0AD8[];
u32                        BMagic_AllocEffect(void);
void                       BMagic_DispatchEffectMode(void);
extern u8                  D_801F0A84[];
extern u8                  D_801F0A98[];
extern u8                  D_801F0B04[];
void                       func_801F03F0(s32 dir);
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect        D_801F0B38[];
#define BMAGIC_EFFECT_SLOTS D_801F0B38
#define BMAGIC_EFFECT_COUNT 32

void func_801F0164(s32 arg0);

void func_801F0078(void);
void func_801F0550(s32 arg0);
void func_801F07B0(s32 arg0);

#endif
