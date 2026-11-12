#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "types.h"
#include "area/map.h"
#include "sys/actor.h"
#include "psx/psyq.h"

/* The resident game overlay's functions the other images call, in address order. */

/* func_8019601C */
u8    Actor_FindFreeSlot(void);
/* func_80196070 */
void  Actor_Clear(void);
/* func_801960C0 */
void  Actor_Free(u8 record_index);
/* func_8019611C */
void  Actor_ClearAll(void);
/* func_8019615C */
void  Actor_Create(u8* request);
/* func_8019625C */
void  func_8019625C(void);
/* func_8019651C */
s32   GFX_AllocPaletteFade(void* target, s32 red, s32 green, s32 blue, s32 flag_value);
/* func_80196670 */
void  GFX_FreePaletteFade(u8 index);
/* func_80196718 */
void  GFX_FreePaletteFadeTarget(void* target);
/* func_80196784 */
u8    GFX_MarkPaletteCells(u8 mode, u8 value, u8 search);
/* func_801968BC */
u8    GFX_AllocPaletteCell(u8 mode);
/* func_80196B20 */
u8    GFX_FindPaletteCell(u8 value);
/* func_80196B9C */
void  GFX_UploadPaletteRows(void);
/* func_80196C8C */
void  GFX_UpdatePaletteAnimations(void);
/* func_80196CF0 */
u8    GFX_StartPaletteAnimation(u8* owner, u8* source_table);
/* func_80196D84 */
void  GFX_StepPaletteAnimation(u8 palette_slot);
/* func_80196F78 */
void  Game_UpdateCampMenu(void);
/* func_80196FFC */
void  Game_LoadCampMenu(void);
/* func_80197068 */
void  Game_UpdateMain(void);
/* func_801970EC */
void  Game_NewGame(void);
/* func_80199440 */
void  func_80199440(void);
/* func_80199678 */
void  Menu_DrawPanelCursor(void);
/* func_8019973C */
void  Menu_SlidePanelLeft(void);
/* func_8019A0E4 */
void  Actor_DispatchAll(void);
/* func_8019A194 */
u8    Game_FindAreaHandler(void);
/* func_8019ABB0 */
void  func_8019ABB0(s32 mode);
/* func_8019F75C */
void  func_8019F75C(void);
/* func_8019F818 */
void  func_8019F818(Actor* actor);
/* func_8019FA28 */
void  Game_RequestAreaChange(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing);
/* func_801A0048 */
bool  func_801A0048(s32 cell_x, s32 cell_y);
/* func_801A0514 */
void  func_801A0514(void);
/* func_801A061C */
void  func_801A061C(void);
/* func_801A18C8 */
void  func_801A18C8(Actor* record);
/* func_801A1AE4 */
bool  func_801A1AE4(Actor* arg);
/* func_801A3A08 */
void  func_801A3A08(void);
/* func_801A3D1C */
void  func_801A3D1C(void* unused);
/* func_801A3E50 */
void  Area_RunSetupStream(u8* cursor);
/* func_801A4BC0 */
void  Area_SetCellCode(s16 column, s16 row, u8 code);
/* func_801A4D54 */
void  func_801A4D54(u8* script);
/* func_801A7330 */
void  func_801A7330(const volatile u8* data);
/* func_801A7704 */
void  Scene_Start(u8 scenario_index);
/* func_801A7804 */
void  Scene_LoadOverlay(void);
/* func_801A782C */
void  Game_UpdateScenario(void);
/* func_801A7878 */
void  Game_DispatchScenarioRecord(void* object);
/* func_801A78F8 */
void  Scene_RequestChapterAdvance(void);
/* func_801A7A34 */
s8    Game_CallScenarioHandler(u16 handler_arg0, u16 handler_arg1);
/* func_801A7BF0 */
void  Game_UpdateScene(void);
/* func_801A7C2C */
void  Scene_ResetEventState(void);
/* func_801A7CAC */
void  Scene_UpdateEvent(void);
/* func_801A86D4 */
void  Scene_DispatchObject(void* record);
/* func_801ABBA8 */
void  func_801ABBA8(void* sub, s32 route);
/* func_801AC1DC */
void  func_801AC1DC(s32* out, u8 selector);
/* func_801AE214 */
void  func_801AE214(s32 line_x, s32 line_y, s32 line_length, s32 line_mode);
/* func_801AE3F0 */
void  UI_DrawWindow(u16 x, u16 y, u16 width, u16 height, s32 style_flags, u8 window_style);
/* func_801AEA80 */
void  func_801AEA80(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 shade_mode);
/* func_801AEBA0 */
void  func_801AEBA0(s16 frame_x, s16 frame_y, s16 frame_width, s16 frame_height, s32 mode_pair_flag);
/* func_801AED54 */
void  UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags);
/* func_801AF20C */
s32   func_801AF20C(u8* command_stream);
/* UI_GetSpriteRect */
/* func_801AF270 */
u8*   UI_GetSpriteRect(u8 sprite_id, u8 flags);
/* func_801AF2A0 */
void  UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags);
/* func_801AF390 */
s32   func_801AF390(s16 x, s16 y, u8* table, s32 flags);
/* func_801AF5B0 */
u8    func_801AF5B0(s32 item_category, s32 character_index, s32 ability_kind);
/* func_801AFD10 */
s32   func_801AFD10(u8* column_counter, u8* row_offset, u8* row_flag, u8* position);
/* func_801AFE18 */
void* Area_SetCameraMatrix(void* out_matrix);
/* func_801AFF04 */
void  Area_ProjectPoint(s32* pos, DVECTOR* screen_xy);
/* func_801AFF64 */
void  Matrix_SetIdentity(MATRIX* matrix);
/* func_801AFFD8 */
void  func_801AFFD8(const void* world_position, void* screen_xy, void* projection);
/* func_801B0DFC */
void  func_801B0DFC(void);
/* func_801B0E44 */
u8    func_801B0E44(void);
/* func_801B2D00 */
s32   Actor_GetTurnStep(s32 selector);
/* func_801B59B4 */
bool  func_801B59B4(void);
/* func_801B5E58 */
void  Game_RewardZenny(s32 zenny);
/* func_801B6610 */
bool  func_801B6610(s16 map_x, s16 map_y);
/* func_801BC400 */
void  Area_ResetScene(void);
/* func_801BDAB8 */
void  func_801BDAB8(void);
/* func_801BDB7C */
u8    Party_CountOrder(u8 mode);
/* func_801BDD58 */
u8    func_801BDD58(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record);
/* func_801BDE14 */
s8    func_801BDE14(s32 pos_x, s32 pos_y, s32 range_mode);
/* func_801BE0C0 */
s8    func_801BE0C0(s32 pos_x, s32 pos_y, s32 range_mode);
/* func_801BE1B0 */
s32   func_801BE1B0(u32 index);
/* func_801BFE34 */
void  func_801BFE34(s32 work_kind, s32 work_index, s32 work_mode);
/* func_801C1400 */
void  Party_BuildBattlers(u32 mode);
/* Party_LoadPalettes */
/* func_801C1630 */
void  Party_LoadPalettes(void);
/* func_801C187C */
s32   Party_JoinMember(s32 char_id);
/* Party_RemoveMember */
/* func_801C1ABC */
void  Party_RemoveMember(s32 character_id);
/* func_801C1DF0 */
void  func_801C1DF0(s32 handler_index);
/* func_801C1E3C */
void  func_801C1E3C(s32 handler_index);
/* func_801C2438 */
void  func_801C2438(void);
/* func_801C24D0 */
void  func_801C24D0(void);
/* func_801C29A0 */
bool  func_801C29A0(s8 tuning_delta);
/* func_801C2BEC */
s32   func_801C2BEC(void);
/* func_801C329C */
void  func_801C329C(void);
/* func_801C3598 */
void  func_801C3598(void);
/* func_801C4C48 */
void  func_801C4C48(void);
/* func_801C5DFC */
void  func_801C5DFC(u8 route_index);
/* func_801C601C */
void  func_801C601C(s8 route_index);
/* func_801C7A54 */
void  Battle_StartScripted(u8 mode_byte);

#endif
