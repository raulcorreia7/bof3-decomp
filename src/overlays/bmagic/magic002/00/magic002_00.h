#ifndef OVERLAY_BMAGIC_MAGIC002_00_H
#define OVERLAY_BMAGIC_MAGIC002_00_H

/* The bmagic/magic002/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The 32-bit cells at +0x14 and +0x20 of each effect slot, read as columns. */
typedef struct BattleEffectWordColumn {
    s32 value;
    u8  pad[BATTLE_EFFECT_STRIDE - sizeof(s32)];
} BattleEffectWordColumn;

extern BattleEffectWordColumn D_801EC344[];
extern BattleEffectWordColumn D_801EC350[];

/* The 16-bit cell at +0x58 of each effect slot, read as a column. */
typedef struct BattleEffectHalfColumn {
    u16 value;
    u8  pad[BATTLE_EFFECT_STRIDE - sizeof(u16)];
} BattleEffectHalfColumn;

extern BattleEffect* D_801EC2E0;

extern BattleEffectHalfColumn D_801EC388[];

/* The direction the magic002 sphere's two shades are measured against. */
extern SVECTOR D_801EEC10;

void func_801EF030(s32 x, s32 y, u16 radius, s32 phase);
void func_801EF1FC(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2);

#endif
