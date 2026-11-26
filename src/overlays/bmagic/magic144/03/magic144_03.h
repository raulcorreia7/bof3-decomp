#ifndef OVERLAY_BMAGIC_MAGIC144_03_H
#define OVERLAY_BMAGIC_MAGIC144_03_H

/* The bmagic/magic144/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The pixels BMagic_WallOfFireGlowUpdate moves a glow each frame: toward the side param.unk_0B picks, and up. */
#define BMAGIC_WALL_OF_FIRE_GLOW_DRIFT_X 16
#define BMAGIC_WALL_OF_FIRE_GLOW_RISE_Y  12

/* The effect the task starts: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicWallOfFireEffectMode {
    BMAGIC_WALL_OF_FIRE_EFFECT_TARGET = 0
} BMagicWallOfFireEffectMode;

/* The effects of the record table: header.mode picks the handler of g_BMagicWallOfFireSlotModes. */
typedef enum BMagicWallOfFireSlotMode {
    BMAGIC_WALL_OF_FIRE_SLOT_FLAME = 0,
    BMAGIC_WALL_OF_FIRE_SLOT_GLOW  = 1
} BMagicWallOfFireSlotMode;

/* func_801EED04 */
void BMagic_WallOfFireInit(void);

/* D_801F04D4 */
extern Callback g_BMagicWallOfFireTargetSteps[];
/* D_801F04E4 */
extern Callback g_BMagicWallOfFireSlotModes[];

/* D_801F04FC */
extern Callback g_BMagicWallOfFireGlowSteps[];
/* func_801EF818 */
void            Effect_DrawFlameColumn(void);

/* D_801F04EC */
extern Callback     g_BMagicWallOfFireFlameSteps[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
/* D_801F050C */
extern BattleEffect g_BMagicWallOfFireEffects[];
#define BMAGIC_EFFECT_SLOTS g_BMagicWallOfFireEffects
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT
/* func_801EF294 */
void BMagic_WallOfFireDrawShadow(void);
/* func_801EF510 */
void BMagic_WallOfFireSlotUpdate(void);

/* func_801F01D0 */
void BMagic_WallOfFireDrawGlow(void);

#endif
