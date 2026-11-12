#ifndef SLUS_DATA_H
#define SLUS_DATA_H

#include "psx/psyq.h"
#include "types.h"
#include "common/util.h"
#include "area/area.h"

/* Set: the battle end does not stop the BGM or the sound sequences. */
#define BATTLE_OPT_KEEP_BGM 0x40

/* SLUS_004.22 data the overlays share, in address order. */
extern s32         D_80033A08;
/* Main-executable RAM state that has no name yet. */
/* retail addresses */
extern u16         D_800C1A70;
extern volatile u8 D_80140000[];
extern u8          D_80143BB0;
extern u16         D_80143F04;
/* D_80143F7C */
extern u32         g_UiPopupRequest;
extern u16         g_GameAreaId;
extern s32         g_PartyX; /* 0x80143F7C */
/* D_80143F80 */
extern s32         g_PartyY; /* 0x80143F80 */
/* D_80144E88 */
extern u16         g_SaveAreaId;
extern u8          g_SaveEntryFacing;
extern u32         g_SaveEntryX;
extern u32         g_SaveEntryY;
extern u8          g_SceneFlagWords[]; /* 0x80144E88 */
extern s8          D_80144950;
extern u8          D_80144953;
extern u8          D_80144954;
/* D_80144956 */
extern u8          g_AutoRun;
/* D_80144F28 */
extern u8          g_SceneEventFlags[];
/* D_80144F58 */
extern u8          g_PartyFormation;
/* D_80144F59 */
extern u8          g_PartyMenuFlags;
extern u8          g_PartyBattleOrder[];
/* One bit per ability id: set once a party member has learned the ability, from a master or by watching an enemy. */
extern u32         g_LearnedAbilities[BIT_ARRAY_WORDS(BYTE_VALUE_COUNT)];
/* One bit per enemy kind byte: set once Identify has examined that kind. */
extern u32         g_IdentifiedEnemies[BIT_ARRAY_WORDS(BYTE_VALUE_COUNT)];
extern u32         D_80145040;
extern u32         D_80145044;
/* The abilities the shop offers, packed to the front. */
#define ABILITY_STOCK_SLOT_COUNT 128

extern u8  D_8014546C[ABILITY_STOCK_SLOT_COUNT];
extern u8  D_801454F4[][3];
extern u32 D_80145548;
/* A unit that must re-read the cell after every store (etc/game/00) defines
 * GRAPHICS_PALETTE_PENDING_VOLATILE before its first include. */
#ifdef GRAPHICS_PALETTE_PENDING_VOLATILE
/* D_80145988 */
extern volatile u8 g_GfxPalettePending; /* 0x80145988 */
#else
/* D_80145988 */
extern u8 g_GfxPalettePending; /* 0x80145988 */
#endif
extern u8  D_80145E91[];
extern u8  D_80145E92[];
extern u8  D_80145E93[];
extern s16 D_80145EC6;
extern s32 D_80145EC8;
extern s16 D_80145ECA;
extern s32 D_80145ECC;
extern s16 D_80145ECE;
extern u8  D_80145ED8;
extern u8  D_80145EDB;
/* Player battle-record copies (stride 0x140), selected by g_Battle.active_battler. */
extern u16 g_InputRepeatDelay;
extern u16 g_InputRepeatButtons;
extern u8  D_80145F04[];
extern u8  D_80145F10[];
extern u16 D_80145F1A[];
extern s8  D_80145FBC;
/* FAKE: g_Battle.phase.mode as a global of its own; the sites that use it match only with a separate symbol. */
extern u8  g_BattleMode;
/* FAKE: g_Battle.phase.step as a global of its own; the sites that use it match only with a separate symbol. */
extern u8  g_BattleStep;
/* FAKE: g_Battle.phase.sub_step as a global of its own; the sites that use it match only with a separate symbol. */
extern u8  g_BattleSubStep;
/* FAKE: g_Battle.state as a global of its own; the sites that use it match only with a separate symbol. */
extern u16 g_BattleState;
/* The bytes the battle code index; the bmagic images that copy its record
 * define BATTLE_PARTY_CELL_RECORD before their first include. A unit that
 * re-reads the cell for each position copy (bmagic/magic056/03) also defines
 * BATTLE_PARTY_CELL_RECORD_VOLATILE. */
#if defined(BATTLE_PARTY_CELL_RECORD) && defined(BATTLE_PARTY_CELL_RECORD_VOLATILE)
extern struct PartyMember* volatile D_8014637C;
#elif defined(BATTLE_PARTY_CELL_RECORD)
extern struct PartyMember* D_8014637C;
#else
extern u8* D_8014637C;
#endif
/* FAKE: g_Battle.target_selector as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8   g_BattleTargetSelector;
/* D_80146854 */
extern u8            g_EmiStreamFlags;
/* D_8014686C */
extern u32*          g_SceneFlags; /* 0x8014686C */
extern u8            D_8014688E[];
extern u8            D_801468BC[];
extern u8            D_801468C0[];
extern s16           D_80146916;
extern s32           D_80147A8C;
extern s32           D_80147A94;
/* Per-slot effect work arrays at a 0x30-byte stride: the accumulators at
 * D_801FD030, the seeded deltas at D_801FCA90 and the per-cell lifetimes at
 * D_801FD5D0.
 */
extern u8*           D_80147AA8;
extern s32           D_80147AC4;
/* D_80148208 */
extern struct Actor* g_ScriptWorkRecord;
extern s16           D_80148334;
extern u16           D_80148336;
extern u8            D_8014837B;
extern u8            D_8014839F;
extern s8            D_801484EA;
/* D_80148573 */
extern u8            g_BattleChoicePhase;
extern volatile u8   D_80148597;
extern u8            D_80148624;
extern u8            D_80148625;
extern u8            D_80148626;
extern volatile u8   D_80148627;
/* D_801492E8 */
extern MATRIX        g_CameraMatrix;

/* Load the GTE with `matrix`, rotated by `rot` and viewed through the camera:
 * the model matrix a 3D effect or scene part draws with. */
static inline void Camera_SetModelMatrix(SVECTOR* rot, MATRIX* matrix) {
    RotMatrix(rot, matrix);
    MulMatrix2(&g_CameraMatrix, matrix);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
}

/* D_80149308 */
/* A unit that must re-read the target after storing it defines
 * AREA_SCROLL_TARGET_VOLATILE before its first include. */
#ifdef AREA_SCROLL_TARGET_VOLATILE
extern volatile s32 g_AreaScrollTargetX;
#else
extern s32 g_AreaScrollTargetX;
#endif
/* D_8014930C */
extern s32         g_AreaScrollTargetY; /* 0x8014930C */
/* D_80149310 */
extern s32         g_AreaCameraX;
/* D_80149318 */
extern s32         g_AreaCameraHeight;
/* D_80149320 */
extern s16         g_AreaTileOriginX;
extern s16         g_AreaTileOriginY;
/* D_80149328 */
extern s16         g_AreaCameraOffsetX;
/* D_8014932A */
extern s16         g_AreaCameraOffsetY;
/* D_8014932C */
extern s16         g_AreaCameraOffsetZ;
/* D_8014932E */
extern s16         g_AreaCameraStep;
/* D_80149330 */
extern s16         g_AreaCameraHeightStep;
/* D_80149332 */
extern u8          g_AreaCameraMoving;
/* D_80149333 */
extern u8          g_AreaCameraRefreshCount;
extern u8          D_8014933A;
/* D_8014933B */
extern u8          g_AreaSceneMode;
/* D_8017F974 */
extern u8          g_AreaHeightOffsetEnabled;
extern void* const g_AreaLoads[200]; /* 0x8017F974 */
extern u8          D_8014933C;
/* D_80181B10 */
extern const u8    D_80149C78[0x18]; /* clut row per icon cell */
extern const u8    g_CharSlot[];
extern const u8    D_80181B88[12];
/* D_80181BD4 */
extern const u8    g_RouteSpeedScale[]; /* 0x80181BD4 */

extern const u8 D_80181B34[20][3];
/* D_80143F22 */
extern s16      g_EncounterSteps;
extern u8       D_80145E44;
/* The main executable keeps the interrupt dispatcher table and SPU handles.
 * D_80185690 stores the table address 0x80185670; libetc wrappers load it and
 * fetch one slot: DMACallback 0x04, InterruptCallback 0x08, ResetCallback
 * 0x0C, StopCallback 0x10 (`lw v0, 0x10(v0); jalr v0`,
 * exe/slus_004_22@0x801749E8) and VSyncCallback 0x14, called with (4,
 * callback). Slots stay offset-named.
 *
 * _spu_RXX and D_80183AC4 point at SPU registers 0x1F801C00 and
 * 0x1F801014 (u16 array read at exe/slus_004_22@0x801690F8, u32
 * read-modify-write at @0x80168E68). D_80184448 and D_8018444C are the sound
 * callbacks the engine installs (0x8016C548 sits in the image, the second is
 * null-checked before the call). D_801856A4 is an s32 slot array whose address
 * is taken (`addiu v0, v0, %lo(D_801856A4)`, exe/slus_004_22@0x801750C4). */
/* D_801862D8 */
extern s16      SQRT[192];
#endif
