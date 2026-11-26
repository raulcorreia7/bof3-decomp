#ifndef OVERLAY_SCENARIO_SCENA14_00_H
#define OVERLAY_SCENARIO_SCENA14_00_H

/* The scenario/scena14/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern u8 D_80144908[];

extern u8 D_80144F5F;

extern u8 D_80146134;

/* kept: written as g_ScenarioState.flags_01, func_801F8850 changes size and the image symbols move. */
extern u8 D_80146871;
extern u8 D_80148660;

extern u32      D_801F6C00;
extern Callback D_801FC418[];
extern Callback D_801FC424[];

extern s8  D_801FC44C[];
extern u8  D_801FC450[];
extern u8  D_801FC454[];
extern u16 D_801FC458[];
extern u16 D_801FC460[];
extern u8  D_801FC4C0;

void func_801C7A54(s32 arg);
void func_801F4400(void);
void func_801F4508(void);
void func_801F4674(void);
void func_801F4764(void);
void func_801F7960(void);
u16  func_801FA904(u8* tags, u16* messages);
/* D_801FC468 */

#endif
