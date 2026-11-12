#ifndef OVERLAY_SCENARIO_SCENA17_00_H
#define OVERLAY_SCENARIO_SCENA17_00_H

/* The scenario/scena17/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

extern u8       D_80146865;
extern u8       D_80146866;
void            Shop_DispatchStep(void);
extern u8       D_80146867;
extern s8       D_80146873;
extern u8       D_80146874;
extern u8       D_80146875;
extern u32      D_801F6C00;
extern Callback D_801F973C[];
extern Callback D_801F9748[];

void            func_801F88CC(s32 arg0, s32 arg1);
void            func_801F8B10(s32 arg0, s32 arg1);
void            func_801F8EF0(void);
void            func_801F8FAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void            func_801F91F0(s16 x, s16 y, u8* text);
u8              func_801F938C(void);
/* func_801F9490 */
void            Scene_RunSaveMenu(void);
extern Callback D_801F9758[];

extern Callback D_801F9798[];

extern Callback  D_801F97A4[];
/* D_801F97D8 */
extern SceneFunc g_SceneActorDispatch[];
extern u8*       D_801F981C[];
extern Callback  D_801F9DBC[];
extern u16       D_801F9DD0;
extern u8        D_801F9DD4;
extern u8        D_801F9DD8;

#endif
