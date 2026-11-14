#ifndef OVERLAY_BMAGIC_MAGIC216_00_H
#define OVERLAY_BMAGIC_MAGIC216_00_H

/* The bmagic/magic216/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8 D_801EC2E4;

/* The acting battler slot; the active_battler member of g_Battle under its own symbol. */
extern volatile u8 g_BattleActiveBattler;

/* The steal chance of each drop rate index. */
extern s8 D_801EF078[];

bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
/* Battle_AddMessage */
void func_801DE8C0(s32 index, s32 record_kind, u8* text);
void func_801EEF98(s32 index, s32 category);

#endif
