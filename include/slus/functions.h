#ifndef SLUS_FUNCTIONS_H
#define SLUS_FUNCTIONS_H

#include "types.h"
#include "audio/bgm.h"
#include "audio/cue.h"
#include "sys/cd_format.h"
#include "psx/psyq.h"
#include "game/character.h"
#include "game/item.h"
#include "common/handler.h"

volatile u8* func_800AC754(u8 entry_id);
/* Functions. */
/* Retail functions (one declaration each). */
/* func_8014AEE0 */
void         SYS_StartLogo(void);
/* func_8014AFC0 */
void         SYS_UpdateKeyState(void);
/* func_8014B020 */
void         SYS_PrepareFrame(void);
/* func_8014B0F0 */
void         SYS_SubmitFrame(void);
/* func_8014B17C */
void         SYS_CaptureDrawTime(void);
/* func_8014B1A4 */
extern void  SYS_InitCard(void);
/* func_8014B33C */
void         CallbackStopAll(void);
/* func_8014B3C4 */
extern void  SYS_ShowException(void);
/* func_8014B6B4 */
void         CallbackInitThreads(void);
/* func_8014B73C */
void         CallbackRun(void);
/* func_8014B854 */
void         CallbackRegister(s32 callback_slot, Callback callback);
/* func_8014B87C */
void         CallbackWait(u16 countdown);
/* func_8014B8B0 */
void         CallbackExit(void);
/* func_8014B900 */
void         CallbackCloseThread(s32 callback_slot);
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
/* func_8014D6B8 */
void         Actor_SelectScript(u8 selector);
/* func_8014D8D4 */
u32          Actor_RequestScript(u8 selector);
/* func_8014D910 */
void         Actor_SeekScript(u16 position);
/* func_8014D978 */
u8           Actor_StepAnimLoop(void);
/* func_8014DAEC */
u8           Actor_StepAnimOnce(void);
/* func_8014DC08 */
extern void  Actor_SelectSprite(u32 record_index);
/* func_8014DD3C */
bool         Area_FindSceneRecord(s32 wanted_id);
/* func_8014E0A8 */
extern s32   SYS_ReadCD(s32 size, void* buffer, s32 sectors);
/* func_8014E284 */
void         GFX_ResetPalette(void);
/* func_8014E3A0 */
void         GFX_CopyPalette(s32 slot);
/* func_8014E3F4 */
void         GFX_ResetPaletteFades(void);
/* func_8014E484 */
extern void  GFX_FreePaletteSlot(s32 slot);
/* func_8014E4BC */
void         GFX_FreePaletteSlotOwner(void* owner);
/* func_8014E528 */
extern void  GFX_FreeAllPaletteSlots(void);
/* func_8014E564 */
void         GFX_ClearRect(s16 x, s16 y, s16 width, s16 height);
/* func_8014E5A0 */
void         GFX_AddPrim(u32 ot_index, u32 primitive_size);
/* func_8014E640 */
s32          PAD_GetRepeatedButtons(s32 button_mask);
/* func_8014E6D0 */
void         GFX_UpdateTransferQueue(void);
/* func_8014EA80 */
void         SYS_StartFrontend(void);
/* func_8014EC64 */
void         SYS_EnterFrontend(void);
/* func_8014ECAC */
void         UI_SetMode(u16 local_mode);
/* func_8014F704 */
s32          GFX_UpdateScreenFade(u16* level, s32 delta, char semi_trans, u32 order, u8 blend_mode);
/* func_8014F800 */
void         UI_DrawText(s16 x, s16 y, s32 flag, u32 color, u8* text);
/* func_8014F84C */
u8*          UI_DrawTextGlyphs(u8 flags, u8 len, u8* record);
/* func_8014FC00 */
void         func_8014FC00(s32 mode);
/* func_8014FC90 */
const u8*    UI_DrawTextString(s16 x, s16 y, s32 flags, u8 count, const u8* text);
/* func_8014FF0C */
void         UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);
/* func_80150098 */
void         UI_DrawGlyphString(s16 x, s16 y, u32 clut, const u8* text);
/* func_801501E4 */
void         SYS_CopyString(u8* dst, u8* src, s32 limit);
/* func_80150224 */
void         Message_StartAreaMessage(s32 message_index);
/* func_80150284 */
void         Message_Request(s32 request_id);
/* func_801502D0 */
u8*          Message_GetText(u32 resource_id);
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
void         UI_UpdateChoice(void);
/* func_801526F4 */
extern void  UI_DrawWaitMarker(s16 x, s16 y);
/* func_801527E4 */
extern void  Area_UpdateCamera(void);
void         func_80153DE8(void);
/* func_80154698 */
extern void  Area_RefreshCellGrid(void);
/* func_8015477C */
s16          Area_SampleHeight(s32 x, s32 y);
/* func_80154ABC */
s32          func_80154ABC(s32 x, s32 y, u8 mode);
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
u8           Area_ClearCellPalette(s32 x, s32 y);
extern s32   func_80155560(u32 part_word, void* prim, s32 mode);
/* func_801558F0 */
s32          Area_GetCellId(s32 x, s32 y);
/* func_801559AC */
POLY_FT4*    Area_FindCellQuad(s32 column, s32 row);
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
void         Area_AnimateClut(u8* palette_list);
/* func_8015864C */
void         Area_DrawGouraudQuad(u32* record);
/* func_80158B24 */
void         Area_IndexCells(void);
/* func_80158C80 */
void         Menu_UpdatePanelTasks(void);
void         func_80158E20(void);
/* func_80158DB8 */
u8           Menu_OpenPanelTask(u8 menu_id, u8 handler);
/* func_80158E50 */
void         Menu_ResetPanelTasks(void);
/* func_8015A758 */
void         Area_UpdateParty(void);
void         func_8015B410(void* matrix);
void         func_8015B4B0(void* matrix);
/* func_8015B4F4 */
s8           Actor_FindScriptSlot(s32 code);
/* func_8015A944 */
void         func_8015A944(void);
/* func_8015AC8C */
void         func_8015AC8C(u8* panel);
/* func_8015B580 */
void         SYS_SetFlag(void* bits, u8 bit_index);
/* func_8015B5A8 */
void         SYS_ClearFlag(void* bits, u8 bit_index);
/* func_8015B5D4 */
s32          SYS_TestFlag(void* bits, s32 bit_index);
extern void  func_8015BAC4(u8 selector);
/* func_8015B5F4 */
void         SYS_ToggleFlag(void* bits, u8 bit_index);
/* func_8015BC14 */
u8           Area_StepCameraX(s16 target, s8 step);
/* func_8015BD14 */
u8           Area_StepCameraY(s16 target, s8 step);
/* func_8015BE10 */
u8           Area_StepCameraZ(s16 target, s8 step);
/* func_8015BEA0 */
bool         Area_StepCameraAngle(s32 degrees, s8 duration);
/* func_8015C058 */
void         Game_ClearScriptActive(void);
/* func_8015C088; int with no value returned (see its definition) */
extern s32   Game_SetScriptActive(void);
/* func_8015C100 */
extern void  Party_HideBattlers(void);
/* func_8015C148 */
s32          Actor_GetType(void);
void         func_8015C214(s32 slot, u8 value);
/* func_8015C2D4 */
s8           Actor_InitMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C540 */
s8           Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);
/* func_8015C750 */
s8           Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C940 */
s32          Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_delta);
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
bool         SND_FindFreeFxVoice(u8* out_index, u8* out_seq);
/* func_8015D71C */
extern void  SND_QueueSelectionFx(s32 cue_id);
/* func_8015D7C8 */
void         SND_QueueCueVolume(s32 cue_id, s32 left_index, s32 right_index);
/* func_8015DF18 */
void         SND_PlayCue(u16 cue_id);
/* func_80161808 */
void         SND_SetBankLayout(u32 layout);
/* func_80161B24 */
void         SND_StartBGM(u8 bgm_id, u8 cue_level, u8 cue_shape);
/* func_80161BBC */
bool         SND_RequestBGM(s32 requested);
/* func_80161C20 */
void         SND_PlayBGM(s32 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161CD0 */
void         SND_FadeOutBGM(u8 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161D20 */
void         SND_PauseBGM(s32 cue_id);
/* func_80161D74 */
void         SND_ResumeBGM(s32 cue_id);
/* func_80161DC8 */
void         SND_InstallSequenceFuncs(void);
/* func_80161F58 */
void         EMI_Init(void);
/* func_80161FDC */
void         EMI_LoadArchive(u32 emi_id);
/* func_80162160 */
DiscLba      EMI_GetArchiveSector(EMISlotId emi_id);
/* func_80162178 */
void         EMI_StartArchive(void);
/* func_801621E8 */
void         EMI_CdOnSync(s32 status, u8* result);
/* func_80162230 */
void         EMI_CdOnReady(u8 status, u8* result);
/* func_80162C14 */
void         EMI_CopySectorData(void);
/* func_80162CD8 */
void         EMI_EndArchive(void);
/* func_80162D00 */
bool         EMI_IsReady(void);
/* func_80162D18 */
void         EMI_CdUpdate(void);
/* func_80162D9C */
void         EMI_CdIdle(void);
/* func_80162DA4 */
void         EMI_CdSetSpeed(void);
/* func_80162E18 */
void         EMI_CdSeek(void);
/* func_80162E70 */
void         EMI_CdOnSeek(void);
/* func_80162E98 */
void         EMI_CdRead(void);
/* func_80162F04 */
void         EMI_CdOnRead(void);
/* func_80162F34 */
void         EMI_CdPause(void);
/* func_80162F88 */
void         EMI_CdOnPause(void);
/* func_8016305C */
void         EMI_UpdateStream(void);
/* func_80163238 */
void         EMI_DecompressSector(void);
/* func_8016327C */
void         EMI_CopySectorToScratchpad(void);
/* func_80163378 */
void         EMI_UploadSectorImage(void);
/* func_80163418 */
void         EMI_UploadVabBody(void);
/* func_801636A0 */
void         SND_StartXAStream(s32 key, s32 unused);
/* func_80163744 */
void         SND_ResolveXAStream(s32 stream_id);
/* func_80163858 */
void         SND_StoreXASyncResult(s32 intr, u8* result);
/* func_801638B0 */
void         SND_UpdateXA(void);
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
bool         SND_HasXACDError(void);
/* func_80163EA0 */
u8           SND_IsXAIdle(void);
/* func_80163EB0 */
void         SND_SetCDVolume(u8 volume);
/* func_80163F50 */
void         SND_FadeCDVolume(s32 level);
/* func_80164028 */
void         LZ77_DecodeBegin(u8* dst);
/* func_80164064 */
s32          LZ77_DecodeStep(void);
/* Main-exe functions called by this overlay. */
/* func_801644D8 */
void         func_801644D8(s32 index, s32 x, s32 y, s32 width, s32 height, s32 shade);
/* func_801647C4 */
void         Menu_DrawCursorSprite(u16 x, u16 y, s32 unused);
/* func_80164A44 */
void         Char_RebuildStats(Character* record);
/* func_80164D2C */
void         Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values);
/* func_801651DC */
s32          Char_AddAbility(s32 ability_id, s32 character_index, s32 to_stock, s32 mode);
/* func_80165280 */
bool         Char_RestoreHP(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016534C */
s32          Char_RestoreAP(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016546C */
s32          Char_AddCappedStat(u16* value, s32 delta);
/* func_801654B0 */
s32          Char_AddWillpower(u8* value, u16 delta);
/* func_80165570 */
s16          Char_AddPoints(u16* value, u16 limit, s16 delta);
/* func_80165694 */
u32          Char_AddPercent(u8* value, u8 delta);
/* func_801656EC */
u32          Char_ClearStatus(u8 index, u16 mask, u8 mode);
/* func_80165D48 */
u8*          Item_GetRecord(s32 category, s32 item);
/* func_80165E04 */
s32          Item_GetIcon(ItemCategory category, s32 item_id);
/* func_80165EC0 */
u8           Item_GetEquipability(u8 category, u8 item);
/* func_80165F68 */
u32          Item_GetFlags(u32 category, u32 item);
/* func_801660DC */
s32          Char_GetAbilityElement(s32 ability_id);
/* func_80166140 */
bool         Item_VitalHas(s32 item_id);
/* func_80166180 */
s32          Item_VitalAdd(u8 item_id);
/* func_8016620C */
void         Message_SetVariable(u8 slot, u8 length, const u8* text);
/* formats a game-text buffer; PsyQ declares sprintf on char, the game keeps its text as u8 */
#define TEXT_Format(dst, fmt, args...) sprintf((char*)(dst), (char*)(fmt), ##args)
#define TEXT_FormatLiteral(dst, fmt)   sprintf((char*)(dst), (char*)(fmt))
/* func_80166438 */
u8   Item_CountHeld(u32 category);
/* func_801664A0 */
u8   Party_CountAbilities(u8 character_index, u8 ability_type, u8 mode);
/* func_801665A0 */
u8   Item_Remove(s32 category, u8 item, s32 amount, s32 unused);
/* func_8016663C */
bool Party_SpendZenny(u32 amount, s32 unused);
/* func_8016666C */
s32  Party_AddZenny(s32 amount, s32 skip_earned);
/* func_801666C8 */
s32  Item_GetDescription(s32 category, s32 item_id);
/* func_80166AE4: kind table for (source slot, group, table kind) */
u8*  Party_GetAbilities(u32 formation_index, u32 ability_type, u32 mode);
/* func_80166B94 */
u8*  Char_GetAbilities(u8 character_index, u8 ability_id, u8 mode);
/* 0x40-byte palette staging entries; GFX_LoadPalette copies them out, the second copy lands 0x4000 above. */
#define GAME_PALETTE_STAGE  MEM_PTR(u8, 0x80035600u)
#define GAME_PALETTE_MIRROR MEM_PTR(u8, 0x80039600u)
/* func_80166C48 */
void       GFX_LoadPalette(u8* dst, s32 field);
/* func_80166CB0 */
s32        Area_GetCellCode(s32 x, s32 y);
/* func_80166CEC */
void       Party_ClearBattlerState(s32 character_index);
/* func_80166E88 */
void       EMI_LoadPartyArchives(u8 member_a, u8 member_b, u8 member_c, u8 family);
/* func_8016728C */
void       EMI_GetArchiveId(u8 index, u8 family);
/* func_80167344 */
void       Area_DispatchScene(void);
/* func_801673AC */
void       Area_InitScene(void);
/* func_80167848 */
void       Area_SyncScrollHeight(void);
/* func_80167FDC */
void       Char_AddHP(s32 amount, u8 char_id);
/* func_8016813C */
u16        Char_LoseHP(s32 mode, s32 index);
/* func_80168248 */
s32        Char_SpendAP(s32 requested, s32 character_id);
/* The libsnd internals have no header in this tree; s16 arguments as retail passes them. */
/* PsyQ entry points the LIBCD, LIBGTE, LIBETC and LIBC callers use. */
/* func_800C3254 (boss055), func_8014CE48 (slus), func_801F3DCC (area198) */
extern s32 Area_RoundSpriteCoordinate(s32 pair, s32 step);
/* func_80167800 (slus), func_801BC3B8 (game) */
void       Area_StepSceneTimer(void);

/* Main-exe polygon helper that fills the frame interior. */

#endif
