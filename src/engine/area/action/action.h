#ifndef OVERLAY_AREA_ACTION_H
#define OVERLAY_AREA_ACTION_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_AREA_ACTION_H_LOCAL)
#define OVERLAY_AREA_ACTION_H_LOCAL

/* func_801ACE10 */
void AreaAction_Run(s32 step_index);
/* func_801ACEBC */
void AreaAction_RunSteps(void);
/* func_801ACF2C */
void AreaAction_RollStep(void);
/* func_801AD0EC */
void AreaAction_FindSmall(void);
/* func_801AD184 */
void AreaAction_FindLarge(void);
/* func_801AD218 */
void AreaAction_End(void);
/* func_801AD2CC */
void AreaAction_WaitMessage(void);
/* func_801AD35C */
void AreaAction_RunReact(void);
/* func_801AD3B4 */
void AreaAction_React(void);
/* func_801AD44C */
void AreaAction_None(void);
/* func_801AD46C */
void AreaAction_RunAltSteps(void);
/* func_801AD4DC */
void AreaAction_RollAltStep(void);
/* func_801AD69C */
void AreaAction_NoneAlt(void);
/* func_801AD6BC */
void AreaAction_RunFadeSteps(void);
/* func_801AD734 */
void AreaAction_RollFade(void);
/* func_801AD90C */
void AreaAction_ShowFind(void);
/* func_801AD9C4 */
void AreaAction_WaitMessageFade(void);
/* func_801AD9F0 */
void AreaAction_Fade(void);

#endif
