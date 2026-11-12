#ifndef OVERLAY_BMAGIC_MAGIC158_03_H
#define OVERLAY_BMAGIC_MAGIC158_03_H

/* The bmagic/magic158/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801EF788[];
/* The angle cell the effect's sine and cosine pair share. */
extern s16          D_1F800004;
/* The tint rows the effect picks from: red, green and blue of each row. */
extern u8           D_801EF76C[];
extern u8           D_801EF76D[];
extern u8           D_801EF76E[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EF794[];
#define BMAGIC_EFFECT_SLOTS         D_801EF794
#define BMAGIC_EFFECT_COUNT         64
#define BMAGIC_EFFECT_START_HANDLER Effect_PlayOnZeroTick
void func_801EED04(void);
#define BMAGIC_EFFECT_SLOT_STEP BMagic_DispatchEffectMode
void func_801EF2F0(void);
void func_801EF3EC(void);

#endif
