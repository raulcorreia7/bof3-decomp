#ifndef OVERLAY_BMAGIC_MAGIC064_03_H
#define OVERLAY_BMAGIC_MAGIC064_03_H

/* The bmagic/magic064/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The twelve step callbacks at D_801EEC10, copied to the stack and indexed by the work state byte. */
typedef struct BMagic064Steps {
    Callback handlers[12];
} BMagic064Steps;

extern u8                  g_BattleActiveBattler;
extern BMagic064Steps      D_801EEC10;
extern BattleHandlerTable4 D_801EEC40;
extern BattleHandlerTable3 D_801EEC50;
extern BattleHandlerTable3 D_801EEC70;
extern void*               D_801F28B4;

void func_801EF8F4(void);
void func_801F001C(void);
void func_801F04A0(void);
void func_801F05A4(void);

void func_801F03D8(void);
void func_801F0EEC(s32 arg0, s32 arg1, s32 arg2);
void func_801F103C(void);

#endif
