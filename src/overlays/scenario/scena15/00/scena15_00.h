#ifndef OVERLAY_SCENARIO_SCENA15_00_H
#define OVERLAY_SCENARIO_SCENA15_00_H

/* The scenario/scena15/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#include "battle/records.h"
#include "shared/AreaSpark.h"

extern u32      D_801F6C00;
/* D_801FE57C */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801FE590[];
extern Callback D_801FE5A0[];
extern Callback D_801FE5B0[];
extern Callback D_801FE5C0[];

void             func_801F71B0(u8 arg);
void             func_801F752C(AreaSpark* spark);
/* func_801F75D8 */
void             Area_AddSpark(void);
/* func_801F7748 */
bool             Scene_GetZFixed(void);
void             func_801F79C4(void);
void             func_801F7FFC(s16 x, s16 y);
void             func_801F81D8(s16 x, s16 y);
extern Callback  D_801FE5CC[];
extern Callback  D_801FE66C[];
extern Callback  D_801FE678[];
extern s8        D_801FE6E8[];
/* D_801FE6EC */
extern SceneFunc g_SceneActorDispatch[];
void             func_801F83AC(Point2u* out);
void             func_801F8704(void);
extern u8        D_801FE71C[];
/* The scene band's velocity. */
extern Point3l  D_801FE738;
extern u8        D_801FE748;
extern u8        D_801FE74C;
void             func_801F8958(void);
void             func_801F9020(Coord* position, s32* step);
void             func_801F92F0(Coord* position, s32* step);

extern u8 D_801FE750;

#endif
