#ifndef OVERLAY_BMAGIC_MAGIC073_03_H
#define OVERLAY_BMAGIC_MAGIC073_03_H

/* The bmagic/magic073/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F21F0;

void func_801EED18(void);
void func_801EEF50(void);
void func_801EF724(void);
void func_801F0454(void);

u8 func_801F04A4(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F0670[];
#define BMAGIC_EFFECT_SLOTS D_801F0670
#define BMAGIC_EFFECT_COUNT 160
extern BattleHandlerTable3 D_801EEC1C;
void                       func_801F00C4(void);
void                       func_801EFBF8(u16 angle, u16 radius);
void                       func_801EFE2C(u16 angle, u16 radius);

#endif
