#ifndef OVERLAY_STATE_MODE_H
#define OVERLAY_STATE_MODE_H

#include "types.h"
/* func_8015C058 */
void Game_ClearScriptActive(void);

/* func_80196F78 */
void       Game_RunCampMenu(void);
/* func_80196FFC */
void       Game_LoadCampMenu(void);
/* func_80197068 */
void       Game_RunMain(void);
/* func_801970EC */
void       Game_NewGame(void);
/* func_8019FA28 */
void       Game_RequestAreaChange(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing);
/* func_801A782C */
void       Game_ScenarioUpdate(void);
/* func_801A7878 */
void       Game_ScenarioDispatchRecord(void* record);
/* func_801A7A34 */
s8         Game_ScenarioCall(u16 handler_arg0, u16 handler_arg1);
/* func_801A7BF0 */
void       Game_UpdateScene(void);
/* Game_ReadCommand */
/* func_801AF20C */
s32        Game_ReadCommand(u8* command_stream);
/* Game_ProjectWorldPoint */
/* func_801AFFD8 */
void       Game_ProjectWorldPoint(const void* world_position, void* screen_xy, void* projection);
/* Game_GetInput */
/* func_801B59B4 */
bool       Game_GetInput(void);
/* func_801B5E58 */
void       Game_RewardZenny(s32 zenny);
/* Game_GetPartySize */
/* func_801BE0C0 */
s8         Game_GetPartySize(s32 pos_x, s32 pos_y, s32 range_mode);
/* func_8015C088; int with no value returned (see its definition) */
extern s32 Game_SetScriptActive(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_STATE_MODE_H_LOCAL)
#define OVERLAY_STATE_MODE_H_LOCAL

void Game_UpdateAreaLoad(void);
void Game_UpdateField(void);
void Game_MenuUpdate(void);
void Game_MenuLoad(void);
void Game_MenuReturn(void);
void Game_UpdateBattle(void);
/* func_80197EFC */
void Game_ScrollToParty(void);
/* func_80197F48 */
void Game_ReturnFromBattle(void);
void Game_CameraLookUpdate(void);
/* func_801981D4 */
void Game_CameraLookEnd(void);
void Game_ShopUpdate(void);
void Game_ShopLoadOverlay(void);
void Game_ShopReturn(void);
void Game_FishingUpdate(void);
/* func_801984E8 */
void Game_FishingEnd(void);
/* func_801985C8 */
void Game_FishingReturn(void);
void Game_AbilityMenuUpdate(void);
void Game_AbilityMenuLoad(void);
void Game_AbilityMenuReturn(void);
void Game_ShisuUpdate(void);
void Game_ShisuLoad(void);
void Game_ShisuReturn(void);
void Game_SceneCameraUpdate(void);
/* func_80198B00 */
void Game_RunScene(void);
/* func_80198B44 */
void Game_SceneCameraOrbit(void);
/* func_80198B6C */
void Game_SceneCameraEnd(void);
/* func_80198CAC */
void Game_UpdateClock(void);
/* func_801990D0 */
void Game_EaseCameraToRest(void);
/* func_80199308 */
void Game_RunSceneFrame(void);
/* func_80199368 */
void Game_MenuUpdateFrame(void);
/* func_801993F0 */
void Game_AbilityMenuUpdateFrame(void);
/* func_80199418 */
void Game_ShisuUpdateFrame(void);
/* func_801A3594 */
void Game_FadeDispatchWhite(void);
/* func_801A35D8 */
void Game_FadeStartWhite(void);
/* func_801A37D4 */
void Game_FadeDispatchBlack(void);
/* func_801A3818 */
void Game_FadeStartBlack(void);
/* func_801A8CB4 */
s8   Game_CallArea(s32 handler_x, s32 handler_y);
/* func_801B1AE8 */
void Game_LeaderSwitchRun(void);
/* func_801B2950 */
void Game_LeaderSwitchEnd(void);
/* func_801B2A00 */
void Game_MenuRequest(void);
/* func_801B2A20 */
void Game_MenuWaitClose(void);
/* func_801B5684 */
bool Game_LeaderSwitchRequest(void);
/* func_801B5758 */
bool Game_MenuRequestField(void);
/* func_801B5884 */
bool Game_CameraLookRequest(void);
/* func_801B5910 */
bool Game_SceneCameraRequest(void);
/* func_801B5AE4 */
s8   Game_FindRockAhead(s32 route_index, s32 route_flags);
/* func_801B5EBC */
bool Game_RequestPersonalAction(void);
/* func_801B5F68 */
bool Game_RequestRockKick(s32 walk_speed);
/* func_801B6044 */
bool Game_RequestGarrPush(void);
s32  Game_HasVitalItem(u8** cursor);
/* func_8015B7F0 */
s32  Game_HasPartyFlag(u8** cursor);
/* func_8019FAA0 */
void Game_EnterArea(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing);
/* func_801B1E24 */
void Game_LeaderSwitchGather(void);
/* func_801B207C */
void Game_LeaderSwitchSpinDarken(void);
/* func_801B26E0 */
void Game_LeaderSwitchSpinRestore(void);

#endif
