#ifndef OVERLAY_SCENARIO_SCENA15_00_H
#define OVERLAY_SCENARIO_SCENA15_00_H

/* The scenario/scena15/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "battle/records.h"
#include "area/effects.h"

/* The sprite quad func_801F7FFC and func_801F81D8 draw: a 24 by 48 quad at (x, y) whose texture window is centred
 * on the work record's screen position. They differ only in the vertex colours. */
#define SCENA15_SPRITE_GEOMETRY(prim, x, y)                                                                                                                                      \
    setXY4(prim, x, y, (x) + 24, y, x, (y) + 48, (x) + 24, (y) + 48);                                                                                                            \
    setUV4(prim, (u8)TASK(Actor)->screen_x - 12, (u8)TASK(Actor)->screen_y - 37, (u8)TASK(Actor)->screen_x + 12, (u8)TASK(Actor)->screen_y - 37, (u8)TASK(Actor)->screen_x - 12, \
           (u8)TASK(Actor)->screen_y + 11, (u8)TASK(Actor)->screen_x + 12, (u8)TASK(Actor)->screen_y + 11)

#define SCENA15_SPRITE_END(prim)                                                              \
    (prim)->tpage = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_ADD, 0x340, 0x100);                 \
    SetSemiTrans(prim, 1);                                                                    \
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(POLY_GT4))

extern u32      D_801F6C00;
/* D_801FE57C */
extern Callback D_801FE590[];
extern Callback D_801FE5A0[];
extern Callback D_801FE5B0[];
extern Callback D_801FE5C0[];
extern s32      D_801FE740;

/* One textured cell of the scene's sprite sheet: the texture page origin and the cell's corner in
 * it. func_801F9500 takes the second cell when bit 0x4 of the task's unk_06 is set. */
typedef struct Scena15SpriteCell {
    s16 page_x; /* 0x0 */
    s16 page_y; /* 0x2 */
    u8  u;      /* 0x4 */
    u8  v;      /* 0x5 */
} Scena15SpriteCell;

ASSERT_OFFSET(Scena15SpriteCell, u, 0x4);
ASSERT_OFFSET(Scena15SpriteCell, v, 0x5);
ASSERT_SIZE(Scena15SpriteCell, 6);

extern Scena15SpriteCell D_801FE5E8[];

/* func_801F71B0 */
void            Scene_DrawLightPillar(u8 fade);
void            func_801F752C(AreaSpark* spark);
/* func_801F75D8 */
void            Area_AddSpark(void);
/* func_801F7748 */
bool            Scene_DrawSparks(void);
void            func_801F79C4(void);
void            func_801F7FFC(s16 x, s16 y);
void            func_801F81D8(s16 x, s16 y);
void            func_801F9500(WorldPos* pos, s32* vx);
void            func_801F97CC(WorldPos* pos, s32* arg);
void            func_801F9A20(WorldPos* pos, s32* vx);
extern Callback D_801FE5CC[];
extern Callback D_801FE66C[];
extern Callback D_801FE678[];
extern s8       D_801FE6E8[];
/* D_801FE6EC */
void            func_801F83AC(Pos2u* out);
void            func_801F8704(void);
extern u8       D_80143F1D;
extern s8       D_8014504A;
extern s8       D_8014504B;
extern u8       D_80148660;
extern u8       D_801FE608[];
extern u8       D_801FE71C[];
/* The scene band's velocity. */
extern Pos3     D_801FE738;
extern u8       D_801FE748;
extern u8       D_801FE74C;
void            func_801F8958(void);
void            func_801F9020(Coord* position, s32* step);
void            func_801F92F0(Coord* position, s32* step);

extern u8       D_80143F49;
extern u16      D_80146258;
extern s16      D_801492DA;
extern s16      D_801492DC;
extern Callback jtbl_801F6C6C[6];
extern u8       D_801FE694[];
extern u8       D_801FE6C8[];
extern u8       D_801FE750;
extern u8       D_801FE754;

#endif
