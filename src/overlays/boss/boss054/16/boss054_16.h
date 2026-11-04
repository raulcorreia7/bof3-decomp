#ifndef OVERLAY_BOSS_BOSS054_16_H
#define OVERLAY_BOSS_BOSS054_16_H

/* The boss/boss054/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"
#include "overlays/battle/battle.h"
#include "battle/ram.h"

typedef struct Boss054Funcs {
    Callback handlers[10];
} Boss054Funcs;

ASSERT_SIZE(Boss054Funcs, 0x28);
ASSERT_OFFSET(Boss054Funcs, handlers, 0x00);

extern BattleHandlerTable3 D_800C182C;

extern Boss054Funcs D_800C1804;
extern u8           D_800C2078[];
extern u16          D_800C2084[];
extern Callback     D_800C2090[];
extern Callback     D_800C20C0[];

void func_800C18E0(s32 mode);
void func_800C1D7C(void);

extern BattleEffect* D_801EC2E0;

#endif
