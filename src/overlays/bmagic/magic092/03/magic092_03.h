#ifndef OVERLAY_BMAGIC_MAGIC092_03_H
#define OVERLAY_BMAGIC_MAGIC092_03_H

/* The bmagic/magic092/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* func_801EED04 */
void BMagic_FireblastInit(void);
/* func_801EF7FC */
void BMagic_FireblastSlotUpdate(void);

/* D_801F07C0 */
extern Callback g_BMagicFireblastTargetSteps[];
/* func_801EFB04 */
void            Effect_DrawFlameColumn(void);

/* D_801F07D0 */
extern Callback g_BMagicFireblastSlotModes[];

/* The effects of the record table: header.mode picks the handler of g_BMagicFireblastSlotModes. */
typedef enum BMagicFireblastSlotMode {
    BMAGIC_FIREBLAST_SLOT_FLAME = 0,
    BMAGIC_FIREBLAST_SLOT_GLOW  = 1
} BMagicFireblastSlotMode;

/* D_801F07D8 */
extern Callback     g_BMagicFireblastFlameSteps[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
/* D_801F07F8 */
extern BattleEffect g_BMagicFireblastEffects[];
#define BMAGIC_EFFECT_SLOTS g_BMagicFireblastEffects
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT
/* func_801EF580 */
void            BMagic_FireblastDrawShadow(void);
/* func_801F04BC */
void            BMagic_FireblastDrawGlow(void);
/* D_801F07E8 */
extern Callback g_BMagicFireblastGlowSteps[];

/* The pixels BMagic_FireblastGlowUpdate moves a glow each frame: toward the side param.unk_0B picks, and up. */
#define BMAGIC_FIREBLAST_GLOW_DRIFT_X 16
#define BMAGIC_FIREBLAST_GLOW_RISE_Y  12

/* The frames between the starts of the target effects of two battlers. */
#define BMAGIC_FIREBLAST_TARGET_DELAY 16

#endif
