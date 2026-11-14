#ifndef OVERLAY_BMAGIC_MAGIC091_03_H
#define OVERLAY_BMAGIC_MAGIC091_03_H

/* The bmagic/magic091/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
extern u16     g_BattleEffectPalette[];
/* The palette copy runs on constant pointers into row 0 of the source and target palettes, skipping entry 0. */
#define BATTLE_PALETTE_SOURCE_ENTRY_1 MEM_PTR(u16, (0x8003 << 16) | 0x6C02)
#define BATTLE_EFFECT_PALETTE_ENTRY_1 MEM_PTR(u16, (0x8003 << 16) | 0xAC02)

extern ActorEffectSteps D_801EEC04;
extern Callback         D_801EFC64[];

#endif
