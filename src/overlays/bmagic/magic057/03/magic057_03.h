#ifndef OVERLAY_BMAGIC_MAGIC057_03_H
#define OVERLAY_BMAGIC_MAGIC057_03_H

/* The bmagic/magic057/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect* volatile D_801EC2E0;

/* The effects the task spawns: header.mode picks the routine g_BMagicBoneDanceEffectModes runs. */
typedef enum BMagicBoneDanceEffectMode {
    BMAGIC_BONE_DANCE_EFFECT_BONE,
    BMAGIC_BONE_DANCE_EFFECT_SHAKE,
    BMAGIC_BONE_DANCE_EFFECT_GROUND
} BMagicBoneDanceEffectMode;

/* The bones the task spawns, the bounces of each and the shakes of the camera. */
#define BMAGIC_BONE_DANCE_BONE_COUNT   32
#define BMAGIC_BONE_DANCE_BONE_BOUNCES 3
#define BMAGIC_BONE_DANCE_SHAKE_COUNT  3

#define MAGIC057_STEP_COUNT            4

typedef struct Magic057Steps {
    Callback steps[MAGIC057_STEP_COUNT];
} Magic057Steps;

#define MAGIC057_SECOND_STEP_COUNT 3

typedef struct Magic057SecondSteps {
    Callback steps[MAGIC057_SECOND_STEP_COUNT];
} Magic057SecondSteps;

/* D_801EEC10 */
extern Magic057Steps       g_BMagicBoneDanceTaskSteps;
/* D_801EEC20 */
extern Magic057SecondSteps g_BMagicBoneDanceEffectModes;
/* D_801EEC2C */
extern Magic057SecondSteps g_BMagicBoneDanceBoneSteps;
/* D_801EEC38 */
extern Magic057SecondSteps g_BMagicBoneDanceShakeSteps;
/* D_801EEC44 */
extern Magic057SecondSteps g_BMagicBoneDanceGroundSteps;

/* D_801EFADC */
extern u8 g_BMagicBoneDanceShakeFrames[];

/* The shake phase routines BMagic_BoneDanceShakeRun runs on byte 0x03. */
/* func_801EF7A0 */
void BMagic_BoneDanceShakeDown(void);
/* func_801EF7E0 */
void BMagic_BoneDanceShakeUp(void);

#endif
