#ifndef OVERLAY_BMAGIC_MAGIC226_03_H
#define OVERLAY_BMAGIC_MAGIC226_03_H

/* The bmagic/magic226/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The scratch angle cell the meteor arc sets and reads. */
extern s16 D_1F800004;

extern Callback D_801F0C44[];
extern Callback D_801F0C60[];

/* The four rise speeds (z velocity) the meteor's arc picks by param.unk_0B & 3. */
extern s32 D_801F0C68[];

extern Callback D_801F0C78[];
void            func_801F01B8(void);

extern Callback     D_801F0C84[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0C90[];
#define BMAGIC_EFFECT_SLOTS     D_801F0C90
#define BMAGIC_EFFECT_COUNT     BATTLE_EFFECT_COUNT
#define BMAGIC_EFFECT_SLOT_STEP func_801EFD84
extern Magic220SharedSteps D_801EEC04;
void                       func_801EFD84(void);
void                       func_801F07D4(void);

#endif
