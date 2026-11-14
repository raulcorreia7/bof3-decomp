#ifndef OVERLAY_BMAGIC_MAGIC083_03_H
#define OVERLAY_BMAGIC_MAGIC083_03_H

/* The bmagic/magic083/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F0EF0[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0F1C[];
#define BMAGIC_EFFECT_SLOTS         D_801F0F1C
#define BMAGIC_EFFECT_COUNT         24
#define BMAGIC_EFFECT_START_HANDLER Effect_StartOnZeroTick
void func_801EED04(void);
s32  func_801EF0CC(void);
#define BMAGIC_EFFECT_SLOT_STEP func_801EFE54
void func_801EF844(void);
void func_801EFB24(void);

void func_801F0BA8(s32 arg0);

void func_801F050C(void);
void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);

/* The func_801F050C fan shades: per effect variant (byte 0x04), four RGB rows for the upper fan and four for the lower. */
extern u8 D_801F0E74[][4][3];
extern u8 D_801F0EA4[][4][3];

/* One RGB row per effect kind, scaled by the effect timer. */
extern u8 D_801F0ED4[][3];
extern u8 D_801F0EE0[][3];

#endif
