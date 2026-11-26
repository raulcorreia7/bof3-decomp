#ifndef OVERLAY_BMAGIC_MAGIC015_00_H
#define OVERLAY_BMAGIC_MAGIC015_00_H

/* The bmagic/magic015/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effects Charge starts: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicChargeEffectMode {
    BMAGIC_CHARGE_EFFECT_LEAD,
    BMAGIC_CHARGE_EFFECT_TRAIL
} BMagicChargeEffectMode;

/* The effect Flying Kick starts; modes 1 and 2 belong to the other entries. */
#define BMAGIC_FLYING_KICK_EFFECT_IMAGE 3

#define MAGIC015_STEP_COUNT             4

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

/* D_801EEC04 */
extern Magic015Steps       g_BMagicChargeTaskModes;
extern Magic015Steps       D_801EEC14;
/* D_801EEC24 */
extern Magic015Steps       g_BMagicFlyingKickTaskModes;
/* D_801EEC34 */
extern Magic015SecondSteps g_BMagicChargeLeadSteps;
/* D_801EEC54 */
extern Magic015ThirdSteps  g_BMagicChargeTrailSteps;
extern Callback            D_801EEC68[];
/* Per-strength tint steps of the magic015 landing effect: the red step, then the green and blue step. */
extern u8                  D_801F1640[][2];
/* The battle/battle/15 sprite-cell routines, called with a battler or the effect work record. */
/* func_800AFB48 */
u32                        Battle_CopyCellPalette(PartyMember* record);
/* func_800AFAB8 */
void                       Battle_ClearCellPaletteEntry(PartyMember* record);
/* D_801EEC84 */
extern Callback            g_BMagicFlyingKickImageSteps[];

/* func_801F1250 */
void BMagic_PushGroundMatrix(void);
/* func_801F131C */
void BMagic_PushTargetMatrix(void);
/* func_801F13D4 */
void BMagic_DrawShadow(void);

/* Fades the tint down to -0x80, then once the effect battler's param is 1 and the fade is done, moves the effect onto that battler and advances. Needs a local `s8 tint`. */
#define EFFECT_APPEAR_AT_BATTLER()                                                                                                       \
    tint = (s8)TASK(PartyMember)->unk_5D;                                                                                                \
    if (tint != -0x80) {                                                                                                                 \
        TASK(PartyMember)->unk_5D = tint - 0x10;                                                                                         \
        TASK(PartyMember)->unk_5E -= 0x10;                                                                                               \
        TASK(PartyMember)->unk_5F -= 0x10;                                                                                               \
    }                                                                                                                                    \
    if ((g_BattleEffectBattler->param.unk_0B == 1) && ((s8)TASK(PartyMember)->unk_5D == -0x80) && (Script_AnimStepOnce() & BYTE_MASK)) { \
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;                                                             \
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;                                                             \
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;                                                             \
        TASK(PartyMember)->header.step++;                                                                                                \
    }

#endif
