#ifndef OVERLAY_BMAGIC_MAGIC091_03_H
#define OVERLAY_BMAGIC_MAGIC091_03_H

/* The bmagic/magic091/03 overlay. Only this image includes the file. */

#include "area/area.h"
#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
extern u16     g_BattleEffectPalette[];
/* Palette row 26 (BATL_OVR) in the arena, and its row in the working copy, from entry 1. */
#define BATTLE_PALETTE_SOURCE_ENTRY_1 MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW + 2)
#define BATTLE_EFFECT_PALETTE_ENTRY_1 MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + 2)

extern ActorEffectSteps D_801EEC04;
extern Callback         D_801EFC64[];

#endif
