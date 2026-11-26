#ifndef OVERLAY_BMAGIC_MAGIC151_03_H
#define OVERLAY_BMAGIC_MAGIC151_03_H

/* The bmagic/magic151/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8          D_800B4C90[];
extern u8          D_80149298[];
extern PartyMember s_BattleBattlerTemplates[BATTLE_PARTY_CHARACTERS_COUNT];

/* The effects the sequence spawns: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicAccessionEffectMode {
    BMAGIC_ACCESSION_EFFECT_DOME,
    BMAGIC_ACCESSION_EFFECT_RAY,
    BMAGIC_ACCESSION_EFFECT_BAND,
    BMAGIC_ACCESSION_EFFECT_GLOW,
    BMAGIC_ACCESSION_EFFECT_SEQUENCE
} BMagicAccessionEffectMode;

#define MAGIC151_STEP_COUNT 5

typedef struct Magic151Steps {
    Callback steps[MAGIC151_STEP_COUNT];
} Magic151Steps;

/* The palette row the battle load copies. */
extern BattlePanel   D_80148332[];
/* The panel x offsets by scroll direction. */
extern s8            D_801EAEA4[];
/* The panel x and y offsets of each battler facing, two bytes a facing. */
extern s8            D_801EB0B0[];
extern s8            D_801EB0B1[];
/* The staged encounter origin and ground height. */
extern s32           D_801EC364;
extern s32           D_801EC368;
extern s32           D_801EC36C;
/* D_801EEC10 */
extern Magic151Steps g_BMagicAccessionSoloSteps;
/* D_801EEC24 */
extern Magic151Steps g_BMagicAccessionMergeSteps;

/* D_801EEC38 */
extern BMagicEffectSteps g_BMagicAccessionSequenceSteps;
void                     func_800A68A4(void);
void                     func_801DE190(u8 slot);
void                     func_801DE1B0(u8 slot);
/* func_801F026C */
void                     BMagic_AccessionDrawDome(void);
/* func_801F0648 */
void                     BMagic_AccessionDrawFlare(void);
/* func_801F0D0C */
void                     BMagic_AccessionDrawRay(u8 azimuth, u8 polar);
/* func_801F14D0 */
void                     BMagic_AccessionDrawBand(s16 band_height, s16 radius, u16 jitter_mask);

/* D_801F24B8 */
extern Callback g_BMagicAccessionDomeSteps[];
/* The azimuth and polar angle of each ray by ray index. */
/* D_801F24D0 */
extern u8       g_BMagicAccessionRayAngles[][2];
/* D_801F24F0 */
extern Callback g_BMagicAccessionRaySteps[];
/* D_801F24FC */
extern Callback g_BMagicAccessionBandSteps[];
/* D_801F250C */
extern Callback g_BMagicAccessionGlowSteps[];
void            Effect_SetActorMatrix5(void);
void            BMagic_DrawGlowRingInner(void);
void            BMagic_DrawGlowRingOuter(void);

#endif
