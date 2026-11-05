#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "character.h"
#include "encoding.h"
#include "fairy.h"
#include "gene.h"
#include "item.h"
#include "enemy.h"
#include "records.h"
#include "script.h"
#include "spawn.h"
#include "ability.h"
#include "text.h"
#include "common/handler.h"
#include "types.h"

/* One 0xC-byte row of the palette fade table at D_80145BD4. */
typedef struct PaletteFade {
    u8  flags;
    u8  saved_byte; /* the target byte at +0x27, restored on free */
    u8  red_offset;
    u8  green_offset;
    u8  blue_offset;
    u8  table_index;
    u8  step;
    u8  unk_07;
    u8* target;
} PaletteFade;

ASSERT_OFFSET(PaletteFade, target, 0x08);
ASSERT_SIZE(PaletteFade, 0x0C);

/* GAME.EMI#0 exports: the frontend's data and entry points, in address order. */

/* D_80143F14 */
extern u32       g_GameEntryPosX;
/* D_80143F18 */
extern u32       g_GameEntryPosY;
/* D_80143F1F */
extern u8        g_GamePrevSelection;
/* D_80195FE0 */
extern u8        s_FairyConstructionThresholds[]; /* 0x80195FE0 */
/* Image-local data, in retail address order. */
/* D_801C7AC0 */
extern u8        s_PaletteFadeCounts[8];
/* D_801C7AC8 */
extern u8        s_PaletteFadeDivisors[8];
/* D_801C7AD0 */
extern u8        s_PaletteFadeScales[8];
/* D_801C7AD8 */
extern u8        s_PaletteFadeColorCounts[8];
/* D_801C7AE0 */
extern u8        s_PaletteFadeRowDivisors[8];
/* D_801C7AE8 */
extern u8        s_PaletteFadeStrides[16];
/* D_801C7AF8 */
extern u8        s_PaletteSlotDivisors[8];
/* D_801C7B00 */
extern u8        s_PaletteSlotStrides[8];
/* D_801C7B08 */
extern Callback  g_GameCampMenuLoad[];
/* D_801C7B14 */
extern Callback  g_GameStates[];
/* D_801C7B44 */
extern Callback  g_GameEntryHandlers[3];
/* D_801C7B50 */
extern u8        s_DirectionJitters[4];
/* D_801C7B54 */
extern Callback  g_GameModeHandlers[8];
/* D_801C7B7C */
extern Callback  g_GameStateHandlers[3];
/* D_801C7B88 */
extern Callback  g_GameSubstateHandlers[4];
/* D_801C7B98 */
extern Callback  g_MenuAbilityOpen[3];
/* D_801C7BA4 */
extern Callback  g_MenuStatusOpen[3];
/* D_801C7BB0 */
extern Callback  g_GameFlowHandlers[3];
/* D_801C7BBC */
extern u8        s_MenuLine1Run[12];
/* D_801C7BC8 */
extern u8        s_MenuLine2Run[12];
/* D_801C7BD4 */
extern u8        s_MenuLine1FlagRun[12];
/* D_801C7BE0 */
extern u8        s_MenuLine2FlagRun[12];
/* D_801C7BEC */
extern Callback  g_MenuPanelHandlers[5];
/* D_801C7C00 */
extern Callback  g_MenuPanelStateHandlers[3];
/* D_801C7C0C */
extern Callback  g_MenuOptionHandlers[3];
/* D_801C7C18 */
extern Callback  g_MenuActionHandlers[3];
/* D_801C7C24 */
extern Callback  g_MenuTaskHandlers[4];
extern char      D_801C7C34[5][8];
extern u8*       D_801C7C5C[5];
/* D_801C7C70 */
extern Callback  g_ActorHandlers[187];
extern u8        D_801C7F74[];
extern Callback  D_801C8090[3];
/* D_801C809C */
extern u8        s_SceneHandlerIds[8];
extern Callback  D_801C80A4[6];
extern Callback  D_801C80BC[3];
extern Callback  D_801C80C8[6];
extern Callback  D_801C80E0[3];
extern Callback  D_801C80EC[3];
extern Callback  D_801C80F8[4];
extern s32       D_801C8108[3][2];
extern s32       D_801C810C[][2]; /* 0x801C810C */
extern Callback  D_801C8120[3];
extern Callback  D_801C812C[6];
extern Callback  D_801C8144[4];
extern Callback  D_801C8154[4];
extern Callback  D_801C8164[6];
extern Callback  D_801C817C[4];
/* D_801C818C */
extern u8        s_AreaCueIds[12];
extern Callback  D_801C8198[2];
extern Callback  D_801C81A0[4];
extern Callback  D_801C81B0[2];
extern Callback  D_801C81B8[2];
extern Callback  D_801C81C0[3];
extern Callback  D_801C81CC[4];
extern Callback  D_801C81DC[105];
/* D_801C8380 */
extern u8        s_EntityModes[4];
extern u16       D_801C8384[28];
/* D_801C8404 */
extern u8        s_EntityRouteIndices[8][4];
extern u16       D_801C8424[8];
extern u16       D_801C842A[];
extern Callback  D_801C8434[2];
extern Callback  D_801C843C[2];
/* D_801C8444 */
extern u8        s_ScriptOpcodeLengths[16];
/* D_801C84A4 */
extern Callback  g_SceneStates[2];
/* D_801C84AC */
extern u8        s_EventFlagsReset[16];
/* D_801C84BC */
extern Callback  g_SceneEvents[64];
/* D_801C85BC */
extern u8        s_SceneStateStepArgs[8];
extern Callback  D_801C85C4[11];
/* D_801C85F0 */
extern SceneFunc g_SceneObjects[66];
/* D_801C87D8 */
extern u8        s_TalkMessageIds[36];
/* D_801C87FC */
extern u8        s_ScriptOpcodeOffsets[256];
extern Callback  D_801C88FC[2];
extern Callback  D_801C8904[2];
/* D_801C8938 */
extern u8        s_SceneMessages[4];
extern u8        D_801C90EC[];
extern u8        D_801C90EE[];
extern u8        D_801C98B3[];
extern u8        D_801C98B4[];
extern u8        D_801C9E8A[];
extern u8        D_801CA624[232];
extern u8        D_801CA71E[];
/* D_801CD050 */
extern u8        s_ItemSpriteIds[16];
/* D_801CD060 */
extern u8        s_ItemIconIds[12];
/* D_801CD06C */
extern u8        s_RouteStepScratch[32];
/* D_801CD08C */
extern s8        s_EntityPlacementOffsets[32];
extern s8        D_801CD08D[];
extern Callback  D_801CD0AC[15];
extern Callback  D_801CD0E8[3];
extern u16       D_801CD0F4[4];
extern Callback  D_801CD0FC[5];
extern Callback  D_801CD110[2];
extern Callback  D_801CD118[2];
extern Callback  D_801CD120[4];
extern Callback  D_801CD130[4];
extern Callback  D_801CD140[5];
extern Callback  D_801CD154[4];
extern Callback  D_801CD164[19];
extern Callback  D_801CD1B0[2];
/* D_801CD1B8 */
extern u8        s_EncounterStepThresholds[16];
extern u8        D_801CD1B9[];
/* D_801CD1C8 */
extern u8        s_MenuBattlerKinds[4];
/* D_801CD1CC */
extern u8        s_RouteSlotAlternates[12];
extern Callback  D_801CD1D8[19];
extern u8        D_801CD226[];
/* D_801CD29C */
extern u8        s_AreaScenePositions[8];
/* D_801CD2A4 */
extern u8        s_AreaCellKinds[12];
extern Callback  D_801CD2B0[9];
extern Callback  D_801CD2D4[6];
extern Callback  D_801CD2EC[2];
extern Callback  D_801CD2F4[5];
extern Callback  D_801CD308[2];
extern Callback  D_801CD310[8];
extern Callback  D_801CD330[10];
extern Callback  D_801CD358[5];
extern Callback  D_801CD36C[2];
extern Callback  D_801CD374[2];
extern Callback  D_801CD37C[2];
extern u8        D_801CD384[128];
extern Callback  D_801CD404[15];
extern Callback  D_801CD440[2];
extern Callback  D_801CD448[4];
/* D_801CD458 */
extern s8        s_CameraScrollDeltas[8];
extern s8        D_801CD459[];
/* D_801CD460 */
extern u8        s_BattleStartOffsets[12][2];
/* D_801CD478 */
extern u8        s_RouteIndexByMode[4];
extern s32       D_801CD47C[8];
extern s32       D_801CD480;
extern Callback  D_801CD49C[4];
extern Callback* D_801CD4C0[20];
extern Callback* D_801CD510[20];
/* D_801CD560 */
extern u8        s_AreaProbeCellCodes[8];
extern Callback  D_801CD568[2];
extern Callback  D_801CD570[5];
extern u8        D_801CD584[56];
/* D_801CD5BC */
extern s8        s_EntitySpawnOffsets[100];
extern s8        D_801CD5BD[];
/* D_801CD770 */
extern u8        s_EntitySpawnChances[8];
/* D_801CD78C */
extern u8        s_BattleModeRecords[224];
extern u8        D_801CD78D[];
extern u8        D_801CD78F[];
extern u16       D_801CD86C[42];
extern u8        D_801CD8C0;
extern u8        D_801CD8C4;
extern u8        D_801CD8C8;
extern s32       D_801CD8CC;
extern u8        D_801CD8D0[116];
/* D_801CD950 */
extern u8        s_PartySlotOrder[4];
extern s32       D_801CD954;

/* The game system: the records, text and script formats the frontend and every
 * overlay read. A game source reaches it through game.h. */

/* GAME.EMI entry points that other overlays call at their fixed address:
 * emi/etc/game/00 (GAME.EMI#0) is resident beside the field overlays. */

/* Finds the first unused slot in the entry table at 0x80143FC8; the retail
 * callee reads no argument and zeroes $a0 before the scan. */
/* func_8019601C */
u8          Actor_FindFreeSlot();
/* func_801960C0 */
void        Actor_Free(u8 record_index);
/* func_8019611C */
void        Actor_ClearAll(void);
/* func_8019615C */
void        Actor_Create(u8* request);
void        func_8019625C(void);
/* func_80196670 */
void        GFX_FreePaletteFade(u8 index);
/* func_80196784 */
u8          GFX_MarkPaletteCells(u8 mode, u8 value, u8 search);
/* func_801968BC */
u8          GFX_AllocPaletteCell(u8 mode);
/* func_80196B20 */
u8          GFX_FindPaletteCell(u8 value);
/* func_80196B9C */
extern void GFX_UploadPaletteRows(void);
/* func_80196C8C */
void        GFX_UpdatePaletteAnimations(void);
/* func_80196D84 */
void        GFX_StepPaletteAnimation(u8 slot_index);
/* func_80196FFC */
void        Game_LoadCampMenu(void);
/* func_80197068 */
void        Game_RunMainLoop(void);
/* func_801970EC */
void        Game_ResetGameState(void);
void        func_80199440(void);
/* func_8019A0E4 */
void        Actor_DispatchAll(void);
void        func_801A0514(void);
void        func_801A3A08(void);
/* Kept (): retail callers load $a0 in the jal delay slot (`addiu a0,s0,116`; `move a0,s4` in Actor_StepMovement) and the
 * callee never reads it; with (void) that instruction is dropped. */
void        func_801A3D1C();
void        func_801A4D54(u8* script);
/* func_801A7704 */
void        Scene_Start(u8 scenario_index);
/* func_801A7804 */
void        Scene_RequestOverlay(void);
/* func_801A782C */
void        Game_RunScenarioEntry(void);
/* func_801A7878 */
void        Game_DispatchScenarioRecord(void* object);
/* func_801A7A34 */
s8          Game_CallScenarioHandler(u16 handler_arg0, u16 handler_arg1);
/* func_801A7BF0 */
void        Game_RunSceneUpdate(void);
/* func_801A7C2C */
void        Scene_ResetEventState(void);
/* func_801A7CAC */
void        Scene_RunEventHandler(void);
/* func_801A86D4 */
void        Scene_DispatchObject(void* record);
/* Selects a route direction away from the work record's current direction:
 * returns -1 when the current index lies in the selector's four-step span,
 * otherwise 1. */
void        func_801ABBA8(void* sub, s32 route);
void        func_801AC1DC(s32* out, u8 selector);
void        func_801AFFD8(const void* world_position, void* screen_xy, void* projection);
void        func_801B0DFC(void);
s32         func_801B0E44(void);
s32         Actor_GetTurnStep(s32 selector);
/* Awards the proximity reward: sound cue, area request, owned money. */
void        func_801B5E58(s32 cue_value);
/* Returns a field record slot holding a body near (pos_x, pos_y), or -1. */
s32         func_801B6610(s16 map_x, s16 map_y);
void        func_801BDAB8(void);
s8          func_801BDE14(s32 pos_x, s32 pos_y, s32 range_mode);
s8          func_801BE0C0(s32 pos_x, s32 pos_y, s32 range_mode);
/* func_800B254C (battle), func_8019973C (game), func_801EA070 (start) */
void        Menu_SlidePanelLeft(void);
void        func_801C2438(void);
void        func_801C4C48(void);

#endif
