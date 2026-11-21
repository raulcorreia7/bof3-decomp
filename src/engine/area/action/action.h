#ifndef OVERLAY_AREA_ACTION_H
#define OVERLAY_AREA_ACTION_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_AREA_ACTION_H_LOCAL)
#define OVERLAY_AREA_ACTION_H_LOCAL

/* func_801ACE10 */
void FieldAction_Run(s32 step_index);
/* func_801ACEBC */
void FieldAction_RunSteps(void);
/* func_801ACF2C */
void FieldAction_RollStep(void);
/* func_801AD0EC */
void FieldAction_FindSmall(void);
/* func_801AD184 */
void FieldAction_FindLarge(void);
/* func_801AD218 */
void FieldAction_End(void);
/* func_801AD2CC */
void FieldAction_WaitMessage(void);
/* func_801AD35C */
void FieldAction_RunReact(void);
/* func_801AD3B4 */
void FieldAction_React(void);
/* func_801AD44C */
void FieldAction_None(void);
/* func_801AD46C */
void FieldAction_RunAltSteps(void);
/* func_801AD4DC */
void FieldAction_RollAltStep(void);
/* func_801AD69C */
void FieldAction_NoneAlt(void);
/* func_801AD6BC */
void FieldAction_RunFadeSteps(void);
/* func_801AD734 */
void FieldAction_RollFade(void);
/* func_801AD90C */
void FieldAction_ShowFind(void);
/* func_801AD9C4 */
void FieldAction_WaitMessageFade(void);
/* func_801AD9F0 */
void FieldAction_Fade(void);

#endif
