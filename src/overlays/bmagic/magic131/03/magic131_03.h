#ifndef OVERLAY_BMAGIC_MAGIC131_03_H
#define OVERLAY_BMAGIC_MAGIC131_03_H

/* The bmagic/magic131/03 overlay (KaiserBreath, ability 0x83). Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effects the task spawns: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum KaiserBreathEffectMode {
    KAISER_BREATH_EFFECT_DRAGON,
    KAISER_BREATH_EFFECT_FLASH,
    KAISER_BREATH_EFFECT_RINGS,
    KAISER_BREATH_EFFECT_BEAM
} KaiserBreathEffectMode;

/* The particles of the breath: header.mode picks the routine g_BMagicKaiserBreathParticleModes runs. */
typedef enum KaiserBreathParticleMode {
    KAISER_BREATH_PARTICLE_ORB,
    KAISER_BREATH_PARTICLE_SPARK
} KaiserBreathParticleMode;

/* The orbs and the sparks the breath spawns. */
#define KAISER_BREATH_ORB_COUNT      8
#define KAISER_BREATH_SPARK_COUNT    28

#define KAISER_BREATH_PARTICLE_COUNT 48

/* D_801EEC04 */
extern Callback g_BMagicKaiserBreathModes[];

/* func_801F030C */
void BMagic_KaiserBreathDrawFlash(void);
/* func_801F06B4 */
void BMagic_KaiserBreathDrawRings(void);
/* func_801F0D44 */
void BMagic_KaiserBreathBeamSetMatrix(void);
/* func_801F0DF4 */
void BMagic_KaiserBreathDrawBeam(void);
/* func_801F10F4 */
void BMagic_KaiserBreathRunParticle(void);
/* func_801F1844 */
void BMagic_KaiserBreathDrawGlow(void);
/* func_801F1A58 */
u8   BMagic_KaiserBreathAllocParticle(void);
/* func_801F1AC4 */
void BMagic_KaiserBreathFreeParticle(void);
/* func_801F1B14 */
void BMagic_KaiserBreathProjectParticle(void);

/* D_801F1BD4 */
extern Callback      g_BMagicKaiserBreathDragonSteps[];
/* D_801F1BF4 */
extern Callback      g_BMagicKaiserBreathFlashSteps[];
/* The ring UV rows held in the table's first words, read by BMagic_KaiserBreathDrawRings. */
extern u8            g_BMagicRingUvRows[];
/* D_801F1C08 */
extern Callback      g_BMagicKaiserBreathRingsSteps[];
/* D_801F1C24 */
extern Callback      g_BMagicKaiserBreathBeamSteps[];
/* D_801F1C30 */
extern Callback      g_BMagicKaiserBreathParticleModes[];
/* The orbit phase of each orb, by its index; the angle is the phase shifted left by 7. */
/* D_801F1C38 */
extern u8            g_BMagicKaiserBreathOrbPhases[];
/* D_801F1C48 */
extern Callback      g_BMagicKaiserBreathOrbSteps[];
/* The orbit phase of each spark, by its index; the angle is the phase shifted left by 6. */
/* D_801F1C54 */
extern u8            g_BMagicKaiserBreathSparkPhases[];
/* The depth of each spark in the 0x40 units its position adds. */
/* D_801F1C74 */
extern u8            g_BMagicKaiserBreathSparkDepths[];
/* D_801F1C94 */
extern Callback      g_BMagicKaiserBreathSparkSteps[];
/* D_801F1CA0 */
extern BMagicEffect  g_BMagicKaiserBreathParticles[KAISER_BREATH_PARTICLE_COUNT];
/* D_801F24E0 */
extern BMagicEffect* g_BMagicKaiserBreathParticle;

/* Pointers to character-indexed archive ids, one row of two per g_Battle.dragon_form; the battle's
 * scroll direction picks the row's first or second pointer and g_EmiLoadedCharacterIndex picks the id. */
extern u16* D_800B499C[][2];

/* Places the orbit point of a KaiserBreath orb or spark: the angle TABLE[unk_07]
 * shifted SHIFT goes to the scratchpad cell, and the point follows the area
 * scroll target at the radius phase_0C. A statement macro: the member declares
 * s16* angle_cell and u8 phase. */
#define MAGIC131_ORBIT_PLACE(TABLE, SHIFT)                                                                                                           \
    phase                                     = TABLE[g_BMagicKaiserBreathParticle->unk_07];                                                         \
    angle_cell                                = &D_1F800006;                                                                                         \
    *angle_cell                               = phase << (SHIFT);                                                                                    \
    g_BMagicKaiserBreathParticle->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << (SHIFT)) * (s16)g_BMagicKaiserBreathParticle->phase_0C) >> 3); \
    g_BMagicKaiserBreathParticle->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) * (s16)g_BMagicKaiserBreathParticle->phase_0C) >> 3)

/* The grow step of a KaiserBreath orbit: unk_06 advances by two, phase_0C by
 * 0x20, the point follows at the placed angle, and the step advances at phase
 * 0x200. A statement macro: the member declares s16* angle_cell and u8 phase. */
#define MAGIC131_ORBIT_GROW(TABLE, SHIFT)                       \
    g_BMagicKaiserBreathParticle->unk_06 += 2;                  \
    g_BMagicKaiserBreathParticle->phase_0C += 0x20;             \
    MAGIC131_ORBIT_PLACE(TABLE, SHIFT);                         \
    if ((s16)g_BMagicKaiserBreathParticle->phase_0C == 0x200) { \
        g_BMagicKaiserBreathParticle->header.step++;            \
    }

/* The closing step of a KaiserBreath orbit: phase_0C advances by 0x10, the
 * point follows at the placed angle, and timer_05 counts down by two; at zero
 * the effect clears. A statement macro: the member declares s16* angle_cell,
 * u8 phase and u8 timer. */
#define MAGIC131_ORBIT_CLOSE(TABLE, SHIFT)                                               \
    g_BMagicKaiserBreathParticle->phase_0C += 0x10;                                      \
    MAGIC131_ORBIT_PLACE(TABLE, SHIFT);                                                  \
    timer                                  = g_BMagicKaiserBreathParticle->timer_05 - 2; \
    g_BMagicKaiserBreathParticle->timer_05 = timer;                                      \
    if (timer == 0) {                                                                    \
        g_BattleEffectBattler->param.unk_0B -= 1;                                        \
        BMagic_KaiserBreathFreeParticle();                                               \
    }

#endif
