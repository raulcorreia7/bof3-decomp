#ifndef OVERLAY_BMAGIC_MAGIC074_03_H
#define OVERLAY_BMAGIC_MAGIC074_03_H

/* The bmagic/magic074/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F20DC;

void func_801EED18(void);
void func_801EF710(void);
void func_801F0440(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F055C[];
#define BMAGIC_EFFECT_SLOTS D_801F055C
#define BMAGIC_EFFECT_COUNT 160
extern BattleHandlerTable3 D_801EEC1C;
void                       func_801F00B0(void);
void                       func_801EFBE4(u16 angle, u16 radius);
void                       func_801EFE18(u16 angle, u16 radius);

#endif
