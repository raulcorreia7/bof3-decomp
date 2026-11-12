#ifndef OVERLAY_BMAGIC_MAGIC015_00_H
#define OVERLAY_BMAGIC_MAGIC015_00_H

/* The bmagic/magic015/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

#define MAGIC015_STEP_COUNT 4

typedef struct Magic015Steps {
    Callback steps[MAGIC015_STEP_COUNT];
} Magic015Steps;

#define MAGIC015_THIRD_STEP_COUNT 5

typedef struct Magic015ThirdSteps {
    Callback steps[MAGIC015_THIRD_STEP_COUNT];
} Magic015ThirdSteps;

#define MAGIC015_SECOND_STEP_COUNT 8

typedef struct Magic015SecondSteps {
    Callback steps[MAGIC015_SECOND_STEP_COUNT];
} Magic015SecondSteps;

extern Magic015Steps D_801EEC04;

extern Magic015Steps       D_801EEC14;
extern Magic015Steps       D_801EEC24;
extern Magic015ThirdSteps  D_801EEC54;
extern Magic015SecondSteps D_801EEC34;
extern Callback            D_801EEC68[];

void func_801F1250(void);
void func_801F131C(void);
void func_801F13D4(void);

/* Fades the tint down to -0x80, then once the effect battler's param is 1 and the fade is done, moves the effect onto that battler and advances. Needs a local `s8 tint`. */
#define EFFECT_APPEAR_AT_BATTLER()                                                                                           \
    tint = (s8)g_Task->unk_5D;                                                                                               \
    if (tint != -0x80) {                                                                                                     \
        g_Task->unk_5D = tint - 0x10;                                                                                        \
        g_Task->unk_5E -= 0x10;                                                                                              \
        g_Task->unk_5F -= 0x10;                                                                                              \
    }                                                                                                                        \
    if ((g_BattleEffectBattler->param.unk_0B == 1) && ((s8)g_Task->unk_5D == -0x80) && (Actor_StepAnimOnce() & BYTE_MASK)) { \
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;                                                            \
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;                                                            \
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;                                                            \
        g_Task->header.step++;                                                                                               \
    }

#endif
