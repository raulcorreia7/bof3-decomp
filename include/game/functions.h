#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "types.h"
#include "area/map.h"
#include "sys/actor.h"
#include "psx/psyq.h"
#include "gfx/palette.h"
#include "gfx/prim.h"

/* The resident game overlay's functions the other images call, in address order. */

/* UI_DrawWindow frame_flags: the low nibble is the frame style, bits 4-7 cut one corner each.
 * UI_DrawWindowOutline uses its own corner order (see UI_WINDOW_OUTLINE_* below). */
#define UI_WINDOW_OPEN_TOP_LEFT             0x80
#define UI_WINDOW_OPEN_BOTTOM_LEFT          0x20
#define UI_WINDOW_OPEN_TOP_RIGHT            0x40
#define UI_WINDOW_OPEN_BOTTOM_RIGHT         0x10
#define UI_WINDOW_OPEN_ALL                  0xF0
#define UI_WINDOW_STYLE_MASK                0x0F
#define UI_WINDOW_STYLE_PLAIN               0
#define UI_WINDOW_STYLE_DARK                1
#define UI_WINDOW_STYLE_TRANSLUCENT         2

/* UI_DrawWindowOutline flags: bit 0 blends the edge pieces, bits 4-7 cut the corners in this order. */
#define UI_WINDOW_OUTLINE_OPEN_TOP_LEFT     0x10
#define UI_WINDOW_OUTLINE_OPEN_TOP_RIGHT    0x20
#define UI_WINDOW_OUTLINE_OPEN_BOTTOM_LEFT  0x40
#define UI_WINDOW_OUTLINE_OPEN_BOTTOM_RIGHT 0x80
#define UI_WINDOW_OUTLINE_OPEN_ALL          0xF0
#define UI_WINDOW_OUTLINE_BLEND             0x01

/* UI_DrawSprite and UI_DrawSpriteRun flags: bit 0 picks the second sprite page, bit 1 the second CLUT row. */
#define UI_SPRITE_ALT_PAGE                  0x01
#define UI_SPRITE_ALT_CLUT                  0x02

/* func_8019601C */
u8    Actor_FindFreeSpawned(void);
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
/* func_80196F78 */
void  Game_RunCampMenu(void);
/* func_80196FFC */
void  Game_LoadCampMenu(void);
/* func_80197068 */
void  Game_RunMain(void);
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
u8    WorldMap_FindRegion(void);
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
void  Area_SetCellCode(s32 column, s32 row, u8 code);
/* Actor_SpawnFromRecord */
/* func_801A4D54 */
void  Actor_SpawnFromRecord(u8* script);
/* func_801A65A0 */
void  Actor_SpawnPartyFromRecord(u8* script);
void  func_801A6C98(u8* record);
/* func_801A7330 */
void  func_801A7330(const volatile u8* data);
/* func_801A7704 */
void  Scene_Start(u8 scenario_index);
/* func_801A7804 */
void  Scene_LoadOverlay(void);
/* func_801A782C */
void  Game_UpdateScenario(void);
/* func_801A7878 */
void  Game_DispatchScenarioRecord(void* record);
/* func_801A78F8 */
void  Scene_RequestChapterAdvance(void);
/* func_801A7A34 */
s8    Game_CallScenario(u16 handler_arg0, u16 handler_arg1);
/* func_801A7BF0 */
void  Game_UpdateScene(void);
/* func_801A7C2C */
void  Scene_ResetEventState(void);
/* func_801A7CAC */
void  Scene_UpdateEvent(void);
/* func_801A86D4 */
void  Scene_DispatchObject(void* record);
/* Area_MoveActorRoute */
/* func_801ABBA8 */
void  Area_MoveActorRoute(void* sub, s32 route);
u8    func_801ABD68(s32 pos_x, s32 pos_y, s32 step_count, void* deltas);
/* func_801AC1DC */
void  func_801AC1DC(s32* out, u8 selector);
void  Char_ApplyLevelUps(s32 char_id);
/* func_801AE214 */
void  func_801AE214(s32 line_x, s32 line_y, s32 line_length, s32 line_mode);
/* func_801AE3F0 */
void  UI_DrawWindow(u16 x, u16 y, u16 width, u16 height, s32 frame_flags, u8 palette);
/* UI_DrawIcon */
/* func_801AEA80 */
void  UI_DrawIcon(s32 sprite_x, s32 sprite_y, s32 icon_id, s32 dimmed);
/* UI_DrawWindowFrame */
/* func_801AEBA0 */
void  UI_DrawWindowFrame(s16 frame_x, s16 frame_y, s16 frame_width, s16 frame_height, s32 mode_pair_flag);
/* func_801AED54 */
void  UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags);
/* Game_ReadCommand */
/* func_801AF20C */
s32   Game_ReadCommand(u8* command_stream);
/* UI_GetSpriteRect */
/* func_801AF270 */
u8*   UI_GetSpriteRect(u8 sprite_id, u8 flags);
/* func_801AF2A0 */
void  UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags);
/* func_801AF390 */
s32   func_801AF390(s16 x, s16 y, u8* table, s32 flags);
/* func_801AF390 */
void  UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
bool  Item_PassesTest(u8 test, u8 character_id, u8 category, u8 item_id);
/* func_801AF5B0 */
u8    func_801AF5B0(s32 item_category, s32 character_index, s32 ability_kind);
/* func_801AF800 */
void  UI_DrawItemRow(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);
/* func_801AFA1C */
void  UI_DrawScrollbar(u8* marks, u8 thumb_top, s16 x, s16 y, u8 thumb_size, u8 total, u8 track_size);
/* func_801AFD10 */
s32   func_801AFD10(u8* column_counter, u8* row_offset, u8* row_flag, u8* position);
/* func_801AFE18 */
void* Area_SetCameraMatrix(void* out_matrix);
/* func_801AFF04 */
void  Area_ProjectPoint(s32* pos, DVECTOR* screen_xy);
/* func_801AFF64 */
void  MATH_SetIdentity(MATRIX* matrix);
/* func_801AFF90 */
s16   func_801AFF90(Pos2* origin, Pos2* first_point, Pos2* second_point);
/* Game_ProjectWorldPoint */
/* func_801AFFD8 */
void  Game_ProjectWorldPoint(const void* world_position, void* screen_xy, void* projection);
/* Actor_UpdateMovement */
/* func_801B0DFC */
void  Actor_UpdateMovement(void);
/* func_801B0E44 */
u8    func_801B0E44(void);
/* func_801B2D00 */
s32   Actor_GetTurnStep(s32 target_facing);
/* Game_GetInput */
/* func_801B59B4 */
bool  Game_GetInput(void);
/* func_801B5E58 */
void  Game_RewardZenny(s32 zenny);
/* func_801B6610 */
bool  func_801B6610(s16 map_x, s16 map_y);
/* func_801BC400 */
void  Area_UpdateIdleActor(void);
/* func_801BDAB8 */
void  func_801BDAB8(void);
/* func_801BDB7C */
u8    Party_CountOrder(u8 order);
u8    Party_CountOrder(u8 mode);
/* Actor_IsInRange */
/* func_801BDD58 */
u8    Actor_IsInRange(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record);
/* Actor_FindInRange */
/* func_801BDE14 */
s8    Actor_FindInRange(s32 pos_x, s32 pos_y, s32 range_mode);
/* Game_GetPartySize */
/* func_801BE0C0 */
s8    Game_GetPartySize(s32 pos_x, s32 pos_y, s32 range_mode);
/* Scene_SetupParty */
/* func_801BE1B0 */
s32   Scene_SetupParty(u32 scene);
/* func_801BFE34 */
void  func_801BFE34(s32 work_kind, s32 work_index, s32 work_mode);
/* func_801C1254 */
void  Party_LoadMemberSprite(s32 character_id, s32 party_slot);
/* func_801C1400 */
void  Party_BuildBattlers(u32 order);
/* Party_LoadPalettes */
/* func_801C1630 */
void  Party_LoadPalettes(void);
void  Char_RebuildPartyStats(void);
/* func_801C187C */
s32   Party_JoinMember(s32 char_id);
/* Party_RemoveMember */
/* func_801C1ABC */
void  Party_RemoveMember(s32 character_id);
/* Scene_RunScenario */
/* func_801C1DF0 */
void  Scene_RunScenario(s32 step_index);
/* func_801C1E3C */
void  func_801C1E3C(s32 step_index);
/* Actor_SetSemiTransparent */
/* func_801C2438 */
void  Actor_SetSemiTransparent(void);
/* func_801C24D0 */
void  Area_RunWalk(void);
void  func_801C2538(void);
void  func_801C2710(void);
/* func_801C29A0 */
bool  func_801C29A0(s8 tuning_delta);
/* func_801C2BEC */
void  func_801C2BEC(void);
/* func_801C329C */
void  func_801C329C(void);
/* func_801C3598 */
void  func_801C3598(void);
/* func_801C4C48 */
void  func_801C4C48(void);
/* Area_SetFacingOffsetX */
/* func_801C5DFC */
void  Area_SetFacingOffsetX(u8 route_index);
/* Area_StartScrollRoute */
/* func_801C601C */
void  Area_StartScrollRoute(s8 route_index);
/* func_801C7A54 */
void  Battle_StartScripted(u8 mode_byte);

#endif
