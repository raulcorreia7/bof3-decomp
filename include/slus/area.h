#ifndef SLUS_AREA_H
#define SLUS_AREA_H

#include "types.h"
#include "gfx/prim.h"
#include "slus/part.h"

/* The executable's area map, camera, cell and scene functions, in address order. */
/* func_8014BA54 */
extern void Area_DrawScene(void);
/* func_8014BAB8 */
void        Area_SwapObjects(s32 first, s32 second);
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
bool        Area_SelectSceneRecord(s32 wanted_id);
/* func_801527E4 */
extern void Area_UpdateCamera(void);
void        Area_LoadCellRowsPrev(void);
void        Area_LoadCellRowsNext(void);
/* func_80153DE8 */
void        Area_InitMapRenderer(void);
/* func_80154698 */
extern void Area_RefreshCellGrid(void);
/* func_8015477C */
s16         Area_SampleHeight(s32 x, s32 y);
/* Area_GetHeight */
/* func_80154ABC */
s32         Area_GetHeight(s32 x, s32 y, u8 mode);
/* func_80154ED0 */
extern void Area_EnableHeightOffset(void);
/* func_80154F28 */
s16         Area_ReadHeight(s32 x, s32 y);
/* func_80154F78 */
s16         Area_ReadStepHeight(s32 x, s32 y, u8 mode);
/* func_80154FD8 */
void        Area_AdvanceScroll(s16 height);
/* func_80155038 */
void        Area_StoreHeight(s32 x, s32 y, u8 value);
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
void        Area_AddScenePrim(s32 scene);
/* func_80155E7C */
s8          Area_TestCondition(s32 request);
/* func_80156ED4 */
void        Area_DrawCellQuad(s32 mask, s32 index);
/* func_80157358 */
void        Area_DrawParts(ScenePart* part_list, s32 x, s32 y);
/* func_801579A8 */
void        Area_DrawSceneSprite(u8* record, s32 origin_x, s32 origin_y);
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
/* func_8015BC14 */
u8          Area_StepCameraX(s16 target, s8 step);
/* func_8015BD14 */
u8          Area_StepCameraY(s16 target, s8 step);
/* func_8015BE10 */
u8          Area_StepCameraZ(s16 target, s8 step);
/* func_8015BEA0 */
bool        Area_StepCameraAngle(s16 degrees, s8 duration);
/* func_80166CB0 */
s32         Area_GetCellCode(s32 x, s32 y);
/* func_80167344 */
void        Area_DispatchScene(void);
/* func_801673AC */
void        Area_InitScene(void);
/* func_80167848 */
void        Area_SyncScrollHeight(void);
/* func_800C3254 (boss055), func_8014CE48 (slus), func_801F3DCC (area198) */
extern s32  Area_RoundSpriteCoordinate(s32 pair, s32 step);
/* func_80167800 (slus), func_801BC3B8 (game) */
void        Area_StepSceneTimer(void);

#endif
