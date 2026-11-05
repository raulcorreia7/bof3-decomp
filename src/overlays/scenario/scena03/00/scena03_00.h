#ifndef OVERLAY_SCENARIO_SCENA03_00_H
#define OVERLAY_SCENARIO_SCENA03_00_H

/* The scenario/scena03/00 overlay's local declarations. Only this image
 * includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern s8        D_80144EA0;
extern u32       D_801F6C00;
extern Callback  D_801FCF50[];
extern Callback  D_801FCF70[];
extern Callback  D_801FCF88[];
extern Callback  D_801FCF94[];
extern Callback  D_801FCFA0[];
extern Callback  D_801FCFAC[];
extern Callback  D_801FCFD4[];
extern Callback  D_801FCFE0[];
extern SceneFunc D_801FD00C[];
extern SVECTOR   D_1F800014[];
extern s32       D_80145EC4;
extern u8        D_801468E4[];
extern u8        D_801FCF30[];
extern u8        D_801FCF5C[];

extern Callback D_801FCF24[];

void func_801FC5A4(void);

/* Sets one scene flag bit, then runs func_801FC5A4. */
static inline void Scene_SetFlagThenContinue(void* flags, u8 bit) {
    SYS_SetFlag(flags, bit);
    func_801FC5A4();
}

extern u16 D_80146876;
extern u8  D_80146874;
extern u8  D_80146875;

extern u8 D_80144F5B;
extern u8 D_80144F5C;
extern u8 D_80144F5F;

s32 func_8019601C();

#endif
