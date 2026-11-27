#ifndef OVERLAY_BMAGIC_MAGIC069_03_H
#define OVERLAY_BMAGIC_MAGIC069_03_H

/* The bmagic/magic069/03 overlay (Influence, ability 0x45). Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The battle panel row offsets of battle/battle/03, two bytes per character, picked by the battler facing. */
extern u8 s_BattlePanelYOffsets[];
extern u8 D_801EB109[];

/* The effects the task spawns: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicInfluenceEffectMode {
    BMAGIC_INFLUENCE_EFFECT_RIGHT_RING,
    BMAGIC_INFLUENCE_EFFECT_LEFT_RING,
    BMAGIC_INFLUENCE_EFFECT_MARK
} BMagicInfluenceEffectMode;

/* The rings the task spawns on each side. */
#define BMAGIC_INFLUENCE_RING_COUNT 3

/* func_801EEC5C */
void            BMagic_InfluenceInit(void);
/* func_801EFA84 */
void            BMagic_InfluenceDrawMark(void);
/* func_801F0274 */
void            BMagic_InfluenceSpawnMarks(void);
/* D_801F0504 */
extern Callback g_BMagicInfluenceRightRingSteps[];
/* D_801F0518 */
extern Callback g_BMagicInfluenceLeftRingSteps[];
/* The mark steps follow the left ring's two steps. */
extern Callback g_BMagicInfluenceMarkSteps[];
/* func_801EFC00 */
void            BMagic_InfluenceDrawFans(void);
/* func_801EFF14 */
void            BMagic_InfluenceDrawRing(void);

/* The edge phases of the three triangles of each fan, in 64ths of a turn. */
/* D_801F0534 */
extern u8 g_BMagicInfluenceFanPhases[];

#endif
