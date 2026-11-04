#ifndef OVERLAY_SCENARIO_SCENA02_00_H
#define OVERLAY_SCENARIO_SCENA02_00_H

/* The scenario/scena02/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

/* The four script variable bytes read as one word. */
#define g_ScriptVarsWord (*(s32*)&g_ScriptVars)

extern u8 D_80146874;

extern u8 D_80146875;

extern u32      D_801F6C00;
extern Callback D_801FE294[];

extern Callback  D_801FE288[];
extern SceneFunc D_801FE304[66];

extern s32 D_80145EC4;

extern u8 D_80146865;
extern u8 D_80146866;
extern u8 D_80146867;

#endif
