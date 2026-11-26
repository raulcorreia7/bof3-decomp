#ifndef OVERLAY_STATE_SCENE_H
#define OVERLAY_STATE_SCENE_H

#include "types.h"

/* func_801A7704 */
void Scene_Start(u8 scenario_index);
/* func_801A7804 */
void Scene_LoadOverlay(void);
/* func_801A78F8 */
void Scene_RequestChapterAdvance(void);
/* func_801A7C2C */
void Scene_ResetEventState(void);
/* func_801A7CAC */
void Scene_UpdateEvent(void);
/* func_801A86D4 */
void Scene_DispatchObject(void* record);
/* Scene_SetupParty */
/* func_801BE1B0 */
s32  Scene_SetupParty(u32 scene);
/* Scene_RunScenario */
/* func_801C1DF0 */
void Scene_RunScenario(s32 step_index);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_STATE_SCENE_H_LOCAL)
#define OVERLAY_STATE_SCENE_H_LOCAL

/* func_801A7CE8 */
void Scene_StepIdle(void);
/* func_801A7E54 */
void Scene_RunMineEntry(void);
void Scene_RunInn(void);
/* func_801A83DC */
void Scene_RunGeneFound(void);

#endif
