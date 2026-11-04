#ifndef OVERLAY_BMAGIC_MAGIC151_03_H
#define OVERLAY_BMAGIC_MAGIC151_03_H

/* The bmagic/magic151/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable5 D_801EEC10;
extern BattleHandlerTable5 D_801EEC24;
extern BmagicEffectFuncs   D_801EEC38;

extern Callback D_801F24B8[];
void            func_801F026C(void);
void            func_801F0648(void);

extern Callback D_801F250C[];
extern u8       g_BattleActingBattler;
void            func_801F1DC0(void);
void            func_801F1E70(void);
void            func_801F2188(void);

#endif
