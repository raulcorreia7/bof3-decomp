#ifndef OVERLAY_AREA_MAP_H
#define OVERLAY_AREA_MAP_H

#include "types.h"
#include "psx/psyq.h"
#include "slus/part.h"

/* One status sprite cell: the size index selects a width and height row from D_8017F53C. */
typedef struct SpriteCell {
    u8 size; /* 0x00 low nibble indexes D_8017F53C */
    u8 x;    /* 0x01 signed offset; retail reads it as (s8) */
    u8 y;    /* 0x02 signed offset; retail reads it as (s8) */
    u8 u;    /* 0x03 */
    u8 v;    /* 0x04 */
} SpriteCell;

/* The 0xC-byte panel sort rows at 0x80147CFC: func_8015AD00 fills one row per
 * quad, Area_DrawGridActors walks the list, and MATH_SwapVectors swaps two rows. The
 * list's second row starts at 0x80147D08 and the depth word at 0x80147D0C, so
 * those addresses are interior views of the same rows. */
typedef struct PanelSortItem {
    u8* primitive; /* 0x00 */
    u16 z;         /* 0x04 - largest projected z of the quad; `lh` reads */
    u16 tagged_z;  /* 0x06 - copy of z; bit 15 is the live-row tag */
    u8* work;      /* 0x08 */
} PanelSortItem;

ASSERT_SIZE(PanelSortItem, 0xC);
/* The executable's area map, camera, cell and scene functions, in address order. */
/* func_8014BA54 */
extern void Area_SceneDraw(void);
/* func_8014BAB8 */
void        Area_SwapGridActors(s32 first, s32 second);
/* func_8014BAEC */
extern void Area_SwapActors(s32 first, s32 second);
/* func_8014BB20 */
extern void Area_DrawActors(void);
/* func_8014C4D4 */
extern void Area_DrawObjectSprite(void);
/* func_8014CE78 */
extern void Area_BuildClut(u16* dst);
/* func_8014D260 */
void        Area_SetDrawMode(void);
/* func_8014D290 */
void        Area_AddGridActor(void);
/* func_8014D4E0 */
extern void Area_AddActor(void);
/* func_8014DD3C */
bool        Area_SceneSelectRecord(s32 wanted_id);

/* func_801A3E50 */
void        Area_RunSetupStream(u8* cursor);
/* func_801A4BC0 */
void        Area_SetCellCode(s32 column, s32 row, u8 code);
/* Area_MoveActorRoute */
/* func_801ABBA8 */
void        Area_MoveActorRoute(void* sub, s32 route);
/* func_801BC400 */
void        Area_UpdateIdleActor(void);
/* func_801C24D0 */
void        Area_RunWalk(void);
/* Area_SetFacingOffsetX */
/* func_801C5DFC */
void        Area_SetFacingOffsetX(u8 route_index);
/* Area_StartScrollRoute */
/* func_801C601C */
void        Area_StartScrollRoute(s8 route_index);
void        Area_LoadCellRowsPrev(void);
void        Area_LoadCellRowsNext(void);
/* func_80153DE8 */
void        Area_InitMapRenderer(void);
/* func_80154698 */
extern void Area_RefreshCellGrid(void);
/* func_80154FD8 */
void        Area_AdvanceScroll(s16 height);
/* func_8015507C */
s32         Area_SetCellPalette(s32 x, s32 y);
/* func_80155218 */
u8          Area_ClearCellPalette(s32 x, s32 y);
void        Area_ClearCell(s32 x, s32 y);
/* func_80155560 */
extern s32  Area_ApplyTileToQuad(u32 part_word, void* prim, s32 mode);
/* func_801558F0 */
s32         Area_GetCellId(s32 x, s32 y);
/* func_801559AC */
POLY_FT4*   Area_FindCellQuad(s32 column, s32 row);
/* func_80155A08 */
void        Area_AddCellPrim(s32 x, s32 y, s32 depth, s32 size);
/* func_80155AF8 */
void        Area_UpdatePaletteTint(s32 delta);
/* func_80155B40 */
void        Area_DrawCellLayer(s32 layer);
/* func_80155D88 */
void        Area_SceneAddPrim(s32 scene);
/* func_80155E7C */
s8          Area_TestCondition(s32 request);
/* func_80156ED4 */
void        Area_DrawCellQuad(s32 mask, s32 index);
/* func_80157358 */
void        Area_DrawParts(ScenePart* part_list, s32 x, s32 y);
/* func_801579A8 */
void        Area_SceneDrawSprite(u8* record, s32 origin_x, s32 origin_y);
/* func_80157F98 */
void        Area_RunBundleOpcodes(void);
/* func_801580A4 */
void        Area_CyclePalette(void);
/* func_801581B4 */
void        Area_ReadTintRecord(u8* record);
/* func_8015822C */
void        Area_ApplyPaletteTint(s32 column_mask, s32 row_mask, s32 red, s32 green, s32 blue);
/* func_80158400 */
void        Area_WriteCellRecord(u8* cell);
/* func_801584A4 */
extern void Area_RunBundleRecords(void);
/* func_80158550 */
void        Area_AnimateClut(u8* palette_list);
/* func_8015864C */
void        Area_DrawGouraudQuad(u32* record);
/* func_80158B24 */
void        Area_IndexCells(void);
/* func_8015A758 */
void        Area_UpdateParty(void);
/* func_80166CB0 */
s32         Area_GetCellCode(s32 x, s32 y);
/* func_80167344 */
void        Area_SceneDispatch(void);
/* func_801673AC */
void        Area_SceneInit(void);
/* func_800C3254 (boss055), func_8014CE48 (slus), func_801F3DCC (area198) */
extern s32  Area_RoundSpriteCoordinate(s32 pair, s32 step);
/* func_80167800 (slus), func_801BC3B8 (game) */
void        Area_SceneStepTimer(void);
/* func_80154438 */
void        Area_ApplyMapBundleObjects(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_AREA_MAP_H_LOCAL)
#define OVERLAY_AREA_MAP_H_LOCAL

/* func_80198BC4 */
void        Area_WaitWindowEffect(u32 wait_steps);
void        Area_RunFrame(void);
void        Area_RunLoadingFrame(void);
/* func_8019C344 */
s32         Area_GetVx(s32 x, s32 y);
/* func_801A253C */
void        Area_SetXFixed(Actor* entity);
/* func_801A3F3C */
void        Area_RunSetupRecords(u8* script);
/* func_801A3FC0 */
void        Area_RunSetupIf(u8* cursor);
/* func_801A4158 */
void        Area_RunSetupIfNot(u8* cursor);
/* func_801A4400 */
u8*         Area_RunSetupBranch(u8* script);
/* func_801A44A4 */
u8*         Area_SkipSetupBranch(u8* script);
/* func_801A4518 */
u8*         Area_RunSetupIfChain(u8* script);
/* func_801A4798 */
u8*         Area_SkipSetupIf(u8* script);
/* func_801A4844 */
u8*         Area_SkipSetupIfChain(u8* script);
/* func_801A4BF8 */
u8*         Area_RunSetupRecord(u8* script);
/* func_801A72B0 */
void        Area_SetupScrollRoute(void* packed_selector);
/* func_801A72E8 */
void        Area_SetEntityCallback(void* selector);
/* func_801B32A4 */
void        Area_GrabLadder(void);
s32         Area_IsStepTooHigh(s16 from_x0, s16 from_x1, s16 from_y0, s16 from_y1, u8 probe_mode);
/* func_801BDF08 */
s32         Area_GetActorFacingStepX(void);
u8          Area_TestCellCorners(s32 pos_x, s32 pos_y, s32 flag, s32 wanted_code, u8 mask_cells);
/* func_8014BC70 */
extern void Area_DrawGridActors(void);
/* func_801C6FD4 */
u32         Area_GetWidth(s32 map_column, s32 map_row);
extern void Area_DrawSpriteCell(s32 mirror, SpriteCell* cell, u16 clut);
/* func_80152C9C */
void        Area_LoadCellColumnPrev(void);
/* func_80152D9C */
void        Area_LoadCellColumnNext(void);
/* func_80152E94 */
/* func_80152FB0 */
/* func_801530D0 */
extern s32  Area_DrawCellRing(void);
/* func_80153CC4 */
extern void Area_ResetCellPacketLists(void);
/* func_80153D34 */
extern void Area_SortCellPackets(void);
extern void Area_GetCell(s32 px, s32 py, AreaCell* out);
extern s32  Area_UploadCell(s32 column, s32 row, POLY_FT4* context, s32 slot);
extern u16  Area_AllocCellPrimRow(void);
extern void Area_RequestCellRows(AreaCell* entry);
extern void Area_FreeCellPrimRow(u16 row_id);
void        Area_DrawPartQuads(ScenePart* parts, s32 shift_x, s32 shift_y);
void        Area_DrawPartAnimation(ScenePart* parts, s32 origin_x, s32 origin_y);
void        Area_DrawCellAtPoint(u8* unit, s32 x, s32 y);
void        Area_DrawGouraudQuads(ScenePart* parts, s32 shift_x, s32 shift_y);
void        Area_DrawCellSides(u8* record, s32 cell_x, s32 cell_y);

#endif
