#ifndef OVERLAY_BMAGIC_MAGIC083_03_H
#define OVERLAY_BMAGIC_MAGIC083_03_H

/* The bmagic/magic083/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 g_ScratchPadHalves;
extern s16 D_1F800004;

/* D_801F0EF0 */
extern Callback     g_BMagicShieldBattlerSteps[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
/* D_801F0F1C */
extern BattleEffect g_BMagicShieldGems[];
#define BMAGIC_EFFECT_SLOTS         g_BMagicShieldGems
#define BMAGIC_EFFECT_COUNT         24
#define BMAGIC_EFFECT_START_HANDLER Effect_StartOnZeroTick
/* func_801EF0CC */
s32 BMagic_ShieldVariant(void);
#define BMAGIC_EFFECT_SLOT_STEP BMagic_ShieldGemDispatch
/* func_801EF844 */
void BMagic_ShieldDrawDisc(void);
/* func_801EFB24 */
void BMagic_ShieldDrawRing(void);

/* func_801F0BA8 */
void BMagic_SetXFixed(s32 radius);

/* func_801F050C */
void BMagic_ShieldDrawGem(void);
void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);

/* The BMagic_ShieldDrawGem fan shades: per effect variant (byte 0x04), four RGB rows for the upper fan and four for the lower. */
/* D_801F0E74 */
extern u8 g_BMagicShieldGemUpperShades[][4][3];
/* D_801F0EA4 */
extern u8 g_BMagicShieldGemLowerShades[][4][3];

/* One RGB row per effect type, scaled by the effect timer. */
/* D_801F0ED4 */
extern u8 g_BMagicShieldDiscTints[][3];
/* D_801F0EE0 */
extern u8 g_BMagicShieldRingTints[][3];

#endif
