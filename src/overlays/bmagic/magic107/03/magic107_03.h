#ifndef OVERLAY_BMAGIC_MAGIC107_03_H
#define OVERLAY_BMAGIC_MAGIC107_03_H

/* The bmagic/magic107/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define EFFECT_TICK_INCREMENT 1
#define EFFECT_TICK_LIMIT     0xC0

/* Column views of g_BattleEffects: func_801EEC5C stores through them because
 * member stores let the D_8014637C load move above the target store. */
extern u8       D_801EC338[];
extern u8       D_801EC364[];
extern u8       D_801EC368[];
extern u8       D_801EC36C[];
extern u8       D_801EC3A4[];
extern Callback D_801F048C[];
extern s32      D_1F80000C;

void func_801EED40(void);
void func_801EF0E4(void);
void func_801EF290(void);
void func_801EF544(void);
void func_801EFAE0(void);
void func_801EFEA8(void);
void func_801F01AC(void);

#endif
