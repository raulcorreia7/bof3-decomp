#ifndef OVERLAY_BMAGIC_MAGIC226_03_H
#define OVERLAY_BMAGIC_MAGIC226_03_H

/* The bmagic/magic226/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The scratch angle cell the meteor arc sets and reads. */
extern s16 D_1F800004;

/* D_801F0C44 */
extern Callback g_BMagicMeteorStrikeSteps[];

/* The per-row bytes the meteor copies into each effect slot it spawns. */
/* D_801F0C58 */
extern u8       g_BMagicMeteorStrikeFragmentTints[];
extern u8       D_801F0C5C[];
/* D_801F0C60 */
extern Callback g_BMagicMeteorStrikeSlotModes[];

/* The four rise speeds (z velocity) the meteor's arc picks by param.unk_0B & 3. */
/* D_801F0C68 */
extern s32 g_BMagicMeteorStrikeFragmentRiseSpeeds[];

/* D_801F0C78 */
extern Callback g_BMagicMeteorStrikeFragmentSteps[];
/* func_801F01B8 */
void            BMagic_MeteorStrikeDrawFragment(void);

/* D_801F0C84 */
extern Callback g_BMagicMeteorStrikeRingSteps[];

/* The effects the slot table holds: header.mode picks the handler of g_BMagicMeteorStrikeSlotModes. */
typedef enum BMagicMeteorStrikeSlotMode {
    BMAGIC_METEOR_STRIKE_SLOT_FRAGMENT = 0,
    BMAGIC_METEOR_STRIKE_SLOT_RING     = 1
} BMagicMeteorStrikeSlotMode;

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0C90[];
#define BMAGIC_EFFECT_SLOTS     D_801F0C90
#define BMAGIC_EFFECT_COUNT     BATTLE_EFFECT_COUNT
#define BMAGIC_EFFECT_SLOT_STEP BMagic_MeteorStrikeSlotUpdate
extern Magic220Steps D_801EEC04;
/* func_801EFD84 */
void                 BMagic_MeteorStrikeSlotUpdate(void);
/* func_801F07D4 */
void                 BMagic_MeteorStrikeDrawRing(void);

#endif
