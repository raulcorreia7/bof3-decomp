#ifndef OVERLAY_BMAGIC_MAGIC003_03_H
#define OVERLAY_BMAGIC_MAGIC003_03_H

/* The bmagic/magic003/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The modes of the combo task: the READY and GO labels, the button prompts, the hit count, then the attack. */
typedef enum SuperComboMode {
    SUPER_COMBO_MODE_INIT,
    SUPER_COMBO_MODE_SHOW_READY,
    SUPER_COMBO_MODE_SHOW_GO,
    SUPER_COMBO_MODE_PICK_BUTTON,
    SUPER_COMBO_MODE_READ_BUTTON,
    SUPER_COMBO_MODE_WAIT_RESULT,
    SUPER_COMBO_MODE_SHOW_HIT_COUNT,
    SUPER_COMBO_MODE_START_ATTACK,
    SUPER_COMBO_MODE_END_ATTACK,
    SUPER_COMBO_MODE_END
} SuperComboMode;

/* The most prompts the combo gives. */
#define SUPER_COMBO_HIT_MAX 32

#define MAGIC003_STEP_COUNT 5

typedef struct Magic003Steps {
    Callback steps[MAGIC003_STEP_COUNT];
} Magic003Steps;

#define MAGIC003_SECOND_STEP_COUNT 4

typedef struct Magic003SecondSteps {
    Callback steps[MAGIC003_SECOND_STEP_COUNT];
} Magic003SecondSteps;

extern Magic003Steps D_801EEC04;

/* func_801EF324 */
void BMagic_SuperComboRunStrike(void);

/* func_801EF708 */
void BMagic_SuperComboRunImage(void);

/* func_801EFB8C */
void BMagic_SuperComboHitImageStart(void);

/* func_801EFCF8 */
void BMagic_SuperComboHitImagePlay(void);

/* func_801EFD4C */
void BMagic_SuperComboSpawnStrike(void);

/* func_801EFEC8 */
void BMagic_SuperComboSpawnImages(void);

/* The target column of g_BattleEffects: each store forms its own slot base. */
extern BattleEffectTargetColumn D_801EC3A4[];
extern Magic003SecondSteps      D_801EEC18;
/* D_801F0A84 */
extern u8                       g_BMagicSuperComboPromptDelays[];
/* D_801F0A98 */
extern u8                       g_BMagicSuperComboButtonMasks[];
/* D_801F0AD8 */
extern Callback                 g_BMagicSuperComboModes[];
extern u8                       D_801F0B04[];
/* func_801F03F0 */
void                            BMagic_SuperComboDrawButton(s32 button);

/* A palette fade colour per row: the signed red, green and blue steps. */
/* D_801F0A78 */
extern ColorDelta8 g_BMagicSuperComboImageTints[];

/* The length of each label and its glyph codes, 0 at the end and 0xFF for a space. */
/* D_801F0A9C */
extern u8 g_BMagicSuperComboLabelLengths[];
/* D_801F0AA0 */
extern u8 g_BMagicSuperComboLabels[][13];
/* D_801F0AD4 */
extern u8 g_BMagicSuperComboButtonCluts[];

/* A screen rectangle: the corner and the size. */
/* D_801F0B10 */
extern RectU16 g_BMagicSuperComboLabelBoxes[];

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0B38[];
#define BMAGIC_EFFECT_SLOTS D_801F0B38
#define BMAGIC_EFFECT_COUNT 32

/* func_801F0078 */
void BMagic_SuperComboSpawnHitImages(void);

/* func_801F0164 */
void BMagic_SuperComboDrawLabel(s32 label_index);
/* func_801F0550 */
void BMagic_SuperComboDrawHitCount(s32 hits);
/* func_801F07B0 */
void BMagic_SuperComboDrawLabelBox(s32 label_index);

#endif
