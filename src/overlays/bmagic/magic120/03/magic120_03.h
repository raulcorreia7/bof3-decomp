#ifndef OVERLAY_BMAGIC_MAGIC120_03_H
#define OVERLAY_BMAGIC_MAGIC120_03_H

/* The bmagic/magic120/03 overlay (Whelp Breath, ability 0x78). Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effects the task spawns: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicWhelpBreathEffectMode {
    BMAGIC_WHELP_BREATH_EFFECT_STREAM,
    BMAGIC_WHELP_BREATH_EFFECT_ACTOR
} BMagicWhelpBreathEffectMode;

/* The roles of the actors: byte 0x0B of an actor effect picks its script and its steps. */
typedef enum BMagicWhelpBreathActor {
    BMAGIC_WHELP_BREATH_ACTOR_PLAY,
    BMAGIC_WHELP_BREATH_ACTOR_LOOP,
    BMAGIC_WHELP_BREATH_ACTOR_PUFFS,
    BMAGIC_WHELP_BREATH_ACTOR_SHADE
} BMagicWhelpBreathActor;

/* The frames the stream waits before it aims. */
#define BMAGIC_WHELP_BREATH_AIM_DELAY 4
/* Task byte 0x0B once the stream has grown. */
#define BMAGIC_WHELP_BREATH_GROWN     1

/* D_801F0CB0 */
extern Callback g_BMagicWhelpBreathStreamSteps[];

/* D_801F0CE4: the offset of each of the three rows of puffs from an enemy, in 16.16. */
extern Pos3 g_BMagicWhelpBreathPuffOffsets[];

/* D_801F0D08: the phase of the shade wedge for each facing, in 1/64 turn. */
extern u8 g_BMagicWhelpBreathShadePhases[];
/* D_801F0D0C: the age of each of the six puffs. */
extern u8 g_BMagicWhelpBreathPuffAges[];

/* func_801F078C */
void BMagic_WhelpBreathSetEnemyMatrix(void);

void func_800B0118(void);

/* The z half of an enemy battler row: BMagic_WhelpBreathDrawShade loads it unsigned (lhu),
 * where a part.integer load sign-extends. */
extern u8 D_801EB66E[];

/* func_801EF44C */
void BMagic_WhelpBreathDrawStream(void);
/* func_801F0274 */
void BMagic_WhelpBreathDrawPuffRows(void);
/* func_801F08AC */
void BMagic_WhelpBreathDrawShade(void);
/* func_801F0974 */
void BMagic_WhelpBreathDrawShadeWedge(void);

/* D_801F0CC4 */
extern Callback BMagic_Steps[];

#endif
