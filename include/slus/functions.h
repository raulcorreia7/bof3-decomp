#ifndef SLUS_FUNCTIONS_H
#define SLUS_FUNCTIONS_H

#include "types.h"
#include "audio/cue.h"
#include "common/handler.h"

volatile u8* func_800AC754(u8 entry_id);
/* Functions. */
/* Retail functions (one declaration each). */
/* func_8014B1A4 */
extern void  SYS_InitCard(void);
/* func_8014B3C4 */
extern void  SYS_ShowException(void);
/* func_8014B954 */
extern void  CallbackReplace(Callback entry);
void         func_8014BA04(void);
/* func_8014BA54 */
extern void  Area_DrawScene(void);
/* func_8014BAB8 */
void         Area_SwapObjects(s32 first, s32 second);
/* func_8014BAEC */
extern void  Area_SwapActors(s32 first, s32 second);
/* func_8014BB20 */
extern void  Area_DrawActors(void);
/* func_8014C4D4 */
extern void  Area_DrawObjectSprite(void);
/* func_8014CE78 */
extern void  Area_BuildClut(u16* dst);
/* func_8014D260 */
void         Area_SetDrawMode(void);
void         func_8014D290(void);
/* func_8014D4E0 */
extern void  Area_AddActor(void);
/* func_8014D54C */
void         Actor_CopyScriptEntry(u32 entry, u8* staging, u32 length);
/* func_8014D5F0 */
void         Actor_SwitchScript(u8 value, u8* dst, s32 size);
/* func_8014D664 */
void         Actor_StageScriptRecord(s32 value, s32 position, u8* dst, s32 size);
/* func_8014D8D4 */
u32          Actor_RequestScript(u8 selector);
/* func_8014D910 */
void         Actor_SeekScript(u16 position);
u8           func_8014D978(void);
u8           func_8014DAEC(void);
/* func_8014DC08 */
extern void  Actor_SelectScriptBank(u32 record_index);
/* func_8014E0A8 */
extern s32   SYS_ReadCd(s32 size, void* buffer, s32 sectors);
/* func_8014E284 */
void         GFX_ResetPalette(void);
/* func_8014E3A0 */
void         GFX_CopyPalette(s32 slot);
/* func_8014E3F4 */
void         GFX_ResetPaletteFades(void);
/* func_8014E484 */
extern void  GFX_FreePaletteSlot(s32 slot);
/* func_8014E4BC */
void         GFX_FreePaletteSlotOwner(s32 match_key);
/* func_8014E528 */
extern void  GFX_FreeAllPaletteSlots(void);
/* func_8014EA80 */
void         SYS_StartFrontend(void);
/* func_8014EC64 */
void         SYS_EnterFrontend(void);
/* func_8014F84C */
u8*          UI_DrawTextGlyphs(u8 flags, u8 len, u8* record);
/* func_80150098 */
void         UI_DrawGlyphString(s16 x, s16 y, u32 clut, const u8* text);
/* func_801501E4 */
void         SYS_CopyString(u8* dst, u8* src, s32 limit);
/* func_80150304 */
void         UI_ResetMessage(void);
/* func_801503E0 */
extern s32   UI_UpdateLayout(void);
/* func_80150470 */
extern void  UI_DrawMessageScript(void);
/* func_80150E14 */
void         UI_TickChoiceTimer(void);
/* func_80151210 */
void         UI_HandleChoiceInput(void);
/* func_801515A8 */
void         UI_ClosePanel(void);
/* func_80151628 */
void         UI_ScrollChoice(void);
/* func_8015196C */
void         UI_RunChoiceStep(void);
/* func_801526F4 */
extern void  UI_DrawWaitMarker(s16 x, s16 y);
extern void  func_801527E4(void);
void         func_80153DE8(void);
/* func_80154698 */
extern void  Area_RefreshCellGrid(void);
/* func_8015477C */
s16          Area_SampleHeight(s32 x, s32 y);
/* func_80154ED0 */
extern void  Area_EnableHeightOffset(void);
/* func_80154F28 */
s16          Area_ReadHeight(s32 x, s32 y);
/* func_80154F78 */
s16          Area_ReadStepHeight(s32 x, s32 y, u8 mode);
/* func_80154FD8 */
void         Area_AdvanceScroll(s16 height);
/* func_80155038 */
void         Area_StoreHeight(s32 x, s32 y, u8 value);
/* Functions exported by SLUS_004.22 for use by overlays. */
/* func_8015507C */
s32          Area_SetCellPalette(s32 x, s32 y);
/* func_80155218 */
s32          Area_ClearCellPalette(s32 x, s32 y);
extern s32   func_80155560(u32 part_word, void* prim, s32 mode);
/* func_801558F0 */
s32          Area_ProbeCellId(s32 x, s32 y);
/* func_80155A08 */
void         Area_AddCellPrim(s32 x, s32 y, s32 depth, s32 size);
/* func_80155AF8 */
void         Area_UpdatePaletteTint(s32 delta);
/* func_80155B40 */
void         Area_DrawCellLayer(s32 layer);
/* func_80155D88 */
void         Area_AddScenePrim(s32 scene);
/* func_80155E7C */
s8           Area_TestCondition(s32 request);
/* func_80156ED4 */
void         Area_DrawCellQuad(s32 mask, s32 index);
/* func_80157358 */
void         Area_DrawParts(u8* part_list, s32 x, s32 y);
/* func_801579A8 */
void         Area_DrawSceneSprite(u8* record, s32 origin_x, s32 origin_y);
/* func_80157F98 */
void         Area_RunBundleOpcodes(void);
/* func_801580A4 */
void         Area_CyclePalette(void);
/* func_801581B4 */
void         Area_ReadTintRecord(u8* record);
/* func_8015822C */
void         Area_ApplyPaletteTint(s32 column_mask, s32 row_mask, s32 red, s32 green, s32 blue);
/* func_80158400 */
void         Area_WriteCellRecord(u8* cell);
/* func_801584A4 */
extern void  Area_RunBundleRecords(void);
/* func_80158550 */
void         Area_LoadPaletteBank(u8* palette_list);
/* func_8015864C */
void         Area_DrawGouraudQuad(u32* record);
/* func_80158B24 */
void         Area_IndexCells(void);
/* func_80158C80 */
void         Menu_RunPanelTasks(void);
void         func_80158E20(void);
/* func_80158E50 */
void         Menu_ResetPanelTasks(void);
/* func_8015A758 */
void         Area_RunParty(void);
void         func_8015B410(void* matrix);
void         func_8015B4B0(void* matrix);
s8           func_8015B4F4(s32 code);
/* func_8015B5D4 */
s32          SYS_TestFlag(void* bits, s32 bit_index);
extern void  func_8015BAC4(u8 selector);
/* func_8015BC14 */
s32          Area_StepCameraX(s16 target, s8 step);
/* func_8015BD14 */
s32          Area_StepCameraY(s16 target, s8 step);
/* func_8015BE10 */
s32          Area_StepCameraZ(s16 target, s8 step);
/* func_8015C058 */
void         Game_ClearScriptActive(void);
/* func_8015C088 */
extern void  Game_SetScriptActive(void);
/* func_8015C100 */
extern void  Party_HideBattlers(void);
/* func_8015C148 */
s32          Actor_GetType(void);
void         func_8015C214(s32 slot, u8 value);
/* func_8015C2D4 */
s8           Actor_InitMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, s32 flags);
/* func_8015C540 */
s8           Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags);
/* func_8015C750 */
s8           Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, s32 flags);
/* func_8015C940 */
s32          Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_step);
/* func_8015C9CC */
void         Actor_ApplyVelocity(void);
/* func_8015CA48 */
s32          Actor_FindFree(void);
/* func_8015CA9C */
u16          Actor_ReadState(void);
/* func_8015CD00 */
void         SND_Init(void);
/* func_8015CE70 */
extern void  SND_Start(void);
/* func_8015CEBC */
void         SND_Exit(void);
/* func_8015D300 */
void         SND_PlaySequence(u16 group, s32 sequence, s32 left_volume, s32 right_volume);
/* func_8015D404 */
void         SND_StopSequence(s32 group, s16 sequence);
/* func_8015D438 */
void         SND_SetSequenceVolume(s32 group, s16 sequence, s16 left_volume, s16 right_volume);
/* func_8015D49C */
void         SND_FadeInSequence(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D4F8 */
void         SND_StartDecrescendo(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D554 */
void         SND_FadeOutSequence(u32 effect_group, s32 effect_id, s32 cue_level, s32 cue_shape);
/* func_8015D5D8 */
void         SND_StopAllSequences(void);
/* func_8015D660 */
s32          SND_FindFreeFxVoice(u8* out_index, u8* out_seq);
/* func_8015D71C */
extern void  SND_QueueSelectionFx(s32 cue_id);
/* func_8015D7C8 */
void         SND_QueueCueVolume(s32 cue_id, s32 left_index, s32 right_index);
/* func_8015DF18 */
void         SND_PlayCue(u16 cue_id);
/* func_80161D20 */
void         SND_PauseBgm(s32 cue_id);
/* func_80161D74 */
void         SND_ResumeBgm(s32 cue_id);
/* func_80161DC8 */
void         SND_InstallSequenceFuncs(void);
/* func_80162D9C */
void         EMI_LoaderIdle(void);
/* func_80162DA4 */
void         EMI_LoaderSetCdSpeed(void);
/* func_80162E18 */
void         EMI_LoaderSeekCd(void);
/* func_80162E70 */
void         EMI_LoaderFinishSeek(void);
/* func_80162E98 */
void         EMI_LoaderStartRead(void);
/* func_80162F04 */
void         EMI_LoaderFinishRead(void);
/* func_80162F34 */
void         EMI_LoaderPauseCd(void);
/* func_80162F88 */
void         EMI_LoaderFinishPause(void);
/* func_8016305C */
void         EMI_LoaderServiceStream(void);
/* func_80163238 */
void         EMI_LoaderReadSector(void);
/* func_8016327C */
void         EMI_LoaderStageSector(void);
/* func_80163378 */
void         EMI_LoaderUploadSector(void);
/* func_80163418 */
void         EMI_LoaderTransferVabBody(void);
/* func_80163744 */
void         SND_ResolveXaStream(s32 stream_id);
/* func_80163858 */
void         SND_StoreXaSyncResult(s32 intr, u8* result);
/* func_801638B0 */
void         SND_ServiceXa(void);
/* func_801639B8 */
void         SND_XaStateIdle(void);
/* func_801639D0 */
void         SND_XaStateSeek(void);
/* func_80163A54 */
void         SND_XaStateSeekResult(void);
/* func_80163AF0 */
void         SND_XaStateRead(void);
/* func_80163B74 */
void         SND_XaStateReadProgress(void);
/* func_80163C58 */
void         SND_XaStateReadResult(void);
/* func_80163D20 */
void         SND_XaStatePause(void);
/* func_80163D80 */
void         SND_XaStatePauseResult(void);
/* func_80163E3C */
void         SND_XaStateWaitSync(void);
/* func_80163E88 */
bool         SND_HasXaCdError(void);
/* func_80163EB0 */
void         SND_SetCdVolume(u8 volume);
/* func_80163F50 */
void         SND_FadeCdVolume(s32 level);
/* func_80164028 */
void         EMI_DecodeBegin(u8* dst);
/* func_80164064 */
s32          EMI_DecodeStep(void);
/* Main-exe functions called by this overlay. */
/* func_801647C4 */
void         Menu_DrawCursorSprite(u16 x, u16 y, s32 unused);
/* func_801651DC */
s32          Char_AddAbility(s32 ability_id, s32 character_index, s32 to_stock, s32 mode);
/* func_801654B0 */
s32          Char_AddWillpower(u8* value, u16 delta);
/* func_80165E04 */
s32          Item_GetKind(s32 kind, s32 index);
/* func_80165EC0 */
u8           Item_GetEquipability(u8 category, u8 item);
/* func_80165F68 */
u32          Item_GetFlags(u32 category, u32 item);
/* func_801660DC */
s32          Char_GetAbilityElement(s32 ability_id);
/* func_80166140 */
bool         Party_HasVitalItem(s32 item_id);
/* func_8016620C */
void         TEXT_SetVariable(u8 slot, u8 length, const u8* text);
/* func_80166438 */
s32          Party_CountInventory(u32 category);
/* func_801664A0 */
s32          Party_CountAbilities(u8 character_index, u8 ability_kind, u8 mode);
/* func_801665A0 */
u8           Party_RemoveItem(s32 category, u8 item, s32 amount, s32 unused);
/* func_8016663C */
s32          Party_SpendZenny(u32 amount, s32 unused);
/* func_8016666C */
s32          Party_AddZenny(s32 amount, s32 skip_earned);
/* func_80166AE4: kind table for (source slot, group, table kind) */
u8*          Party_GetAbilities(u32 formation_index, u32 panel, u32 mode);
/* func_80166B94 */
u8*          Char_GetAbilities(u8 character_index, u8 ability_kind, u8 mode);
/* func_80166CB0 */
s32          Area_GetCellCode(s32 x, s32 y);
/* func_80166CEC */
void         Party_ClearBattlerState(s32 character_index);
/* func_80167344 */
void         Area_DispatchScene(void);
/* func_801673AC */
void         Area_InitScene(void);
/* func_80167848 */
void         Area_SyncScrollHeight(void);
/* func_80167FDC */
void         Char_AddHp(s32 amount, u8 char_id);
/* func_8016813C */
s32          Char_LoseHp(s32 mode, s32 index);
/* func_80168248 */
s32          Char_SpendAp(s32 requested, s32 character_id);
/* The libsnd internals have no header in this tree; s16 arguments as retail passes them. */
/* func_80196CF0 */
u8           GFX_StartPaletteAnimation(u8* owner, u8* source_table);
/* PsyQ entry points the LIBCD, LIBGTE, LIBETC and LIBC callers use. */
/* func_800C3254 (boss055), func_8014CE48 (slus), func_801F3DCC (area198) */
extern s32   Area_RoundSpriteCoordinate(s32 pair, s32 step);
/* func_80167800 (slus), func_801BC3B8 (game) */
void         Area_StepSceneTimer(void);
/* func_8016788C (slus), func_801BC400 (game) */
void         Area_ResetScene(void);

/* Main-exe polygon helper that fills the frame interior. */
extern void func_801AEBA0(s16 frame_x, s16 frame_y, s16 frame_width, s16 frame_height, s32 mode_pair_flag);
/* func_801AFE18 */
void*       Area_SetCameraMatrix(void* out_matrix);

#endif
