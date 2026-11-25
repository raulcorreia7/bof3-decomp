#ifndef OVERLAY_BMAGIC_MAGIC003_03_H
#define OVERLAY_BMAGIC_MAGIC003_03_H

/* The bmagic/magic003/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The modes of the combo task: the READY and GO labels, the button prompts, the hit count, then the attack. */
typedef enum BMagicSuperComboMode {
    BMAGIC_SUPER_COMBO_MODE_INIT,
    BMAGIC_SUPER_COMBO_MODE_SHOW_READY,
    BMAGIC_SUPER_COMBO_MODE_SHOW_GO,
    BMAGIC_SUPER_COMBO_MODE_PICK_BUTTON,
    BMAGIC_SUPER_COMBO_MODE_READ_BUTTON,
    BMAGIC_SUPER_COMBO_MODE_WAIT_RESULT,
    BMAGIC_SUPER_COMBO_MODE_SHOW_HIT_COUNT,
    BMAGIC_SUPER_COMBO_MODE_START_ATTACK,
    BMAGIC_SUPER_COMBO_MODE_END_ATTACK,
    BMAGIC_SUPER_COMBO_MODE_END
} BMagicSuperComboMode;

/* The most prompts the combo gives. */
#define BMAGIC_SUPER_COMBO_HIT_MAX 32

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
void BMagic_SuperComboStrikeUpdate(void);

/* func_801EF708 */
void BMagic_SuperComboAfterimageUpdate(void);

/* func_801EFB8C */
void BMagic_SuperComboHitImageStart(void);

/* func_801EFCF8 */
void BMagic_SuperComboHitImagePlay(void);

/* func_801EFD4C */
void BMagic_SuperComboStrikeSpawn(void);

/* func_801EFEC8 */
void BMagic_SuperComboAfterimageSpawn(void);

/* The target column of g_BattleEffects: each store forms its own slot base. */
extern BattleEffectTargetColumn D_801EC3A4[];
extern Magic003SecondSteps      D_801EEC18;
/* D_801F0A84 */
extern u8                       g_BMagicSuperComboPressTimes[];
/* D_801F0A98 */
extern u8                       g_BMagicSuperComboButtonMasks[];
/* D_801F0AD8 */
extern Callback                 g_BMagicSuperComboModes[];
extern u8                       D_801F0B04[];
/* func_801F03F0 */
void                            BMagic_SuperComboDrawButton(s32 button);

/* A palette fade colour per row: the signed red, green and blue steps. */
/* D_801F0A78 */
extern ColorDelta8 g_BMagicSuperComboAfterimageTints[];

/* The letter count of each label, which centres it, and its glyph codes, 0 at the end and 0xFF for a space. */
/* D_801F0A9C */
extern u8 g_BMagicSuperComboLabelLengths[];
/* D_801F0AA0 */
extern u8 g_BMagicSuperComboLabels[][13];
/* D_801F0AD4 */
extern u8 g_BMagicSuperComboButtonCluts[];

/* The boxes by index: the four label backdrops, then the button glyph's; each the corner and the size. */
/* D_801F0B10 */
extern RectU16 g_BMagicSuperComboBoxes[];

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0B38[];
#define BMAGIC_EFFECT_SLOTS D_801F0B38
#define BMAGIC_EFFECT_COUNT 32

/* func_801F0078 */
void BMagic_SuperComboHitImageSpawn(void);

/* func_801F0164 */
void BMagic_SuperComboDrawLabel(s32 label_index);
/* func_801F0550 */
void BMagic_SuperComboDrawHitCount(s32 hits);
/* func_801F07B0 */
void BMagic_SuperComboDrawBox(s32 box_index);

#endif
