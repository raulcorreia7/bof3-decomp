#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC008_EARLY_STEP_COUNT 7
#define MAGIC008_STEP_COUNT       10

typedef struct Magic008EarlySteps {
    Callback handlers[MAGIC008_EARLY_STEP_COUNT];
} Magic008EarlySteps;

typedef struct Magic008Steps {
    Callback handlers[MAGIC008_STEP_COUNT];
} Magic008Steps;

#define MAGIC008_FIRST_STEP_COUNT 4

typedef struct Magic008FirstSteps {
    Callback steps[MAGIC008_FIRST_STEP_COUNT];
} Magic008FirstSteps;

#define MAGIC008_SECOND_STEP_COUNT 3

typedef struct Magic008SecondSteps {
    Callback steps[MAGIC008_SECOND_STEP_COUNT];
} Magic008SecondSteps;

#define MAGIC008_THIRD_STEP_COUNT 5

typedef struct Magic008ThirdSteps {
    Callback steps[MAGIC008_THIRD_STEP_COUNT];
} Magic008ThirdSteps;

extern Magic008FirstSteps D_801EEC04;
extern BMagicEffectFuncs  D_801EEC58;

extern Magic008SecondSteps D_801EEC14;
extern Magic008ThirdSteps  D_801EEC70;
extern Magic008FirstSteps  D_801EEC20;
extern Magic008FirstSteps  D_801EEC30;
extern Magic008SecondSteps D_801EEC40;
extern Magic008SecondSteps D_801EEC4C;
extern Magic008FirstSteps  D_801EEC84;
extern BMagicEffectFuncs   D_801EEC94;

extern Magic008EarlySteps D_801EECAC;
extern Magic008Steps      D_801EECC8;
extern Point2DL           D_801F1C04[];

/* The columns of g_BattleEffects: the retail code forms one slot base per store. */
extern BattleEffectByteColumn   D_801EC331[];
extern BattleEffectByteColumn   D_801EC332[];
extern BattleEffectByteColumn   D_801EC335[];
extern BattleEffectByteColumn   D_801EC336[];
extern BattleEffectTargetColumn D_801EC3A4[];

#endif
