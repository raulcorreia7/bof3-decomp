#ifndef OVERLAY_BMAGIC_MAGIC126_03_H
#define OVERLAY_BMAGIC_MAGIC126_03_H

/* The bmagic/magic126/03 overlay (ShadowBreath, ability 0x7E). Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 D_1F800004;
extern s16 g_ScratchPadHalves;

/* The effects the task spawns: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicShadowBreathEffectMode {
    BMAGIC_SHADOW_BREATH_EFFECT_GLOW,
    BMAGIC_SHADOW_BREATH_EFFECT_PILLAR,
    BMAGIC_SHADOW_BREATH_EFFECT_ORB
} BMagicShadowBreathEffectMode;

/* The orbs the task starts, and the motes the burst starts. */
#define BMAGIC_SHADOW_BREATH_ORB_COUNT  8
#define BMAGIC_SHADOW_BREATH_BURST_MOTES 64

/* One of the 128 records BMagic_AllocEffect claims: a task header, the spawn index and the battler it acts on;
 * the update runs each claimed record through the mote dispatch as the current mote with that battler swapped in. */
typedef struct ShadowBreathMote {
    TaskHeader   header; /* 0x00 */
    u8           unk_03;
    u8           unk_04; /* +0x04 spawn index; the angle is its low four bits */
    u8           unk_05;
    u8           unk_06;
    u8           pad_07;
    s32          unk_08;
    u16          unk_0C;
    u16          unk_0E;
    s32          unk_10;
    s32          unk_14;
    u8           pad_18[4];
    PartyMember* battler; /* +0x1C */
} ShadowBreathMote;

ASSERT_OFFSET(ShadowBreathMote, unk_04, 0x04);
ASSERT_OFFSET(ShadowBreathMote, unk_08, 0x08);
ASSERT_OFFSET(ShadowBreathMote, unk_0C, 0x0C);
ASSERT_OFFSET(ShadowBreathMote, unk_0E, 0x0E);
ASSERT_OFFSET(ShadowBreathMote, unk_10, 0x10);
ASSERT_OFFSET(ShadowBreathMote, unk_14, 0x14);
ASSERT_OFFSET(ShadowBreathMote, battler, 0x1C);
ASSERT_SIZE(ShadowBreathMote, 0x20);

#define BMAGIC_EFFECT_SLOTS g_BMagicShadowBreathMotes
#define BMAGIC_EFFECT_COUNT 128

/* func_801EECE4 */
void BMagic_ShadowBreathInit(void);
/* func_801EF1C8 */
void BMagic_ShadowBreathDrawShadow(void);
void BMagic_DrawGlowRingOuter(void);
void BMagic_DrawGlowRingInner(void);
/* func_801EFD5C */
void BMagic_ShadowBreathDrawPillar(void);
/* func_801F06AC */
void BMagic_ShadowBreathDrawOrb(void);
/* func_801F091C */
void BMagic_ShadowBreathMoteDispatch(void);
void BMagic_DrawMote(void);
/* func_801F116C */
void BMagic_ShadowBreathMoteFree(void);
/* func_801F11AC */
void BMagic_ShadowBreathMoteProject(void);

/* D_801F1268 */
extern Callback g_BMagicShadowBreathGlowSteps[];
/* D_801F1278 */
extern Callback g_BMagicShadowBreathPillarSteps[];
/* D_801F1288 */
extern Callback g_BMagicShadowBreathOrbSteps[];
/* D_801F1298 */
extern BMagicTint g_BMagicShadowBreathOrbTints[];
/* D_801F12A8 */
extern Callback g_BMagicShadowBreathMoteModes[];
/* D_801F12AC */
extern Callback g_BMagicShadowBreathMoteSteps[];
/* D_801F12BC */
extern ShadowBreathMote g_BMagicShadowBreathMotes[];
/* D_801F22BC */
extern PartyMember* g_BMagicShadowBreathMote;
/* The current record as a mote: g_BMagicShadowBreathMote points into g_BMagicShadowBreathMotes. */
#define MAGIC126_MOTE ((ShadowBreathMote*)g_BMagicShadowBreathMote)

#endif
