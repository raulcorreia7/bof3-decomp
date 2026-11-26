#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "types.h"
#include "area/map.h"
#include "sys/actor.h"
#include "psx/psyq.h"
#include "gfx/palette.h"
#include "gfx/prim.h"
#include "engine/state/battle/battle.h"
#include "engine/state/mode/mode.h"
#include "engine/state/scene/scene.h"
#include "engine/worldmap/worldmap.h"
#include "engine/sys/math/math.h"
#include "engine/actor/motion/motion.h"
#include "engine/actor/task/task.h"
#include "engine/party/party/party.h"
#include "engine/party/character/character.h"
#include "engine/party/item/item.h"
#include "engine/ui/text/text.h"
#include "engine/ui/menu/menu.h"
#include "engine/area/map/map.h"
#include "engine/camera/camera.h"

/* The resident game overlay's functions the other images call, in address order. */

/* UI_WindowDraw frame_flags: the low nibble is the frame style, bits 4-7 cut one corner each.
 * UI_WindowDrawOutline uses its own corner order (see UI_WINDOW_OUTLINE_* below). */
#define UI_WINDOW_OPEN_TOP_LEFT             0x80
#define UI_WINDOW_OPEN_BOTTOM_LEFT          0x20
#define UI_WINDOW_OPEN_TOP_RIGHT            0x40
#define UI_WINDOW_OPEN_BOTTOM_RIGHT         0x10
#define UI_WINDOW_OPEN_ALL                  0xF0
#define UI_WINDOW_STYLE_MASK                0x0F
#define UI_WINDOW_STYLE_PLAIN               0
#define UI_WINDOW_STYLE_DARK                1
#define UI_WINDOW_STYLE_TRANSLUCENT         2

/* UI_WindowDrawOutline flags: bit 0 blends the edge pieces, bits 4-7 cut the corners in this order. */
#define UI_WINDOW_OUTLINE_OPEN_TOP_LEFT     0x10
#define UI_WINDOW_OUTLINE_OPEN_TOP_RIGHT    0x20
#define UI_WINDOW_OUTLINE_OPEN_BOTTOM_LEFT  0x40
#define UI_WINDOW_OUTLINE_OPEN_BOTTOM_RIGHT 0x80
#define UI_WINDOW_OUTLINE_OPEN_ALL          0xF0
#define UI_WINDOW_OUTLINE_BLEND             0x01

/* UI_SpriteDraw and UI_SpriteDrawRun flags: bit 0 picks the second sprite page, bit 1 the second CLUT row. */
#define UI_SPRITE_ALT_PAGE                  0x01
#define UI_SPRITE_ALT_CLUT                  0x02

/* func_8019625C */
void func_8019625C(void);
/* func_80199440 */
void func_80199440(void);
/* Scene_StartToggleLock */
/* func_8019ABB0 */
void Scene_StartToggleLock(s32 frames);
/* func_8019F75C */
void Actor_ShatterStart(void);
/* func_8019F818 */
void Actor_ShatterRun(Actor* actor);
/* Area_RequestLinkAtCell */
/* func_801A0048 */
bool Area_RequestLinkAtCell(s32 cell_x, s32 cell_y);
/* func_801A0514 */
void func_801A0514(void);
/* func_801A061C */
void func_801A061C(void);
/* func_801A18C8 */
void func_801A18C8(Actor* record);
/* Actor_IsAheadBlocked */
/* func_801A1AE4 */
bool Actor_IsAheadBlocked(Actor* arg);
/* func_801A3A08 */
void func_801A3A08(void);
/* Actor_TurnRampStep */
/* func_801A3D1C */
void Actor_TurnRampStep(void* unused);
/* func_801A6C98 */
void Actor_SpawnPartyFromDefRow(u8* record);
/* Actor_SpawnSearchSpot */
/* func_801A7330 */
void Actor_SpawnSearchSpot(const volatile u8* data);
u8   func_801ABD68(s32 pos_x, s32 pos_y, s32 step_count, void* deltas);
/* func_801AC1DC */
void func_801AC1DC(s32* out, u8 selector);
/* func_801AE214 */
void UI_CursorDrawName(s32 line_x, s32 line_y, s32 line_length, s32 line_mode);
/* func_801AF390 */
s32  func_801AF390(s16 x, s16 y, u8* table, s32 flags);
/* func_801AF5B0 */
u8   func_801AF5B0(s32 item_category, s32 character_index, s32 ability_type);
/* UI_ScrollList */
/* func_801AFD10 */
s32  UI_ScrollList(u8* first_row, u8* scroll_y, u8* extra_rows, u8* scroll);
/* MATH_TriangleWinding */
/* func_801AFF90 */
s16  MATH_TriangleWinding(Pos2* origin, Pos2* first_point, Pos2* second_point);
/* func_801B0E44 */
u8   func_801B0E44(void);
/* func_801B6610 */
bool func_801B6610(s16 map_x, s16 map_y);
/* func_801BDAB8 */
void func_801BDAB8(void);
/* func_801BFE34 */
void func_801BFE34(s32 work_type, s32 work_index, s32 work_mode);
/* func_801C1E3C */
void func_801C1E3C(s32 step_index);
void func_801C2538(void);
void func_801C2710(void);
/* func_801C29A0 */
bool func_801C29A0(s8 tuning_delta);
/* func_801C2BEC */
void Party_FloorDamageUpdate(void);
/* func_801C329C */
void func_801C329C(void);
/* func_801C4C48 */
void func_801C4C48(void);

#endif
