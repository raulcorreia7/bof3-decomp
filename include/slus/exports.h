#ifndef SLUS_EXPORTS_H
#define SLUS_EXPORTS_H

/* The main executable's exports to the overlays, in address order. */

#include "types.h"
#include "common/fixed.h"
#include "common/vector.h"
#include "menu/gameui.h"
#include "menu/panel.h"
#include "slus/functions.h"
#include "battle/records.h"
#include "common/callback.h"
#include "sys/sched.h"
#include <rand.h>

/* The menu, shop and start overlays dispatch on the step, then the sub-step and the state within it. */
typedef struct MenuStep {
    u8 step;
    u8 sub_step;
    u8 state;
} MenuStep;

ASSERT_SIZE(MenuStep, 3);

/* The g_SceneEvents handlers with a known role; the other handlers stay numeric. */
typedef enum SceneEventMode {
    SCENE_EVENT_NONE           = 0,
    SCENE_EVENT_MASTER         = 4,
    SCENE_EVENT_MINE_ENTRY     = 5,
    SCENE_EVENT_MESSAGE        = 6,
    SCENE_EVENT_INN            = 10,
    SCENE_EVENT_LOCATION_GUIDE = 27,
    SCENE_EVENT_GENE_FOUND     = 44,
    SCENE_EVENT_FAIRY_ENTRY    = 55,
} SceneEventMode;

/* The rows of g_SndXAStates, the steps of one XA stream: seek, read, pause. */
typedef enum XAState {
    SND_XA_STATE_IDLE          = 0,
    SND_XA_STATE_SEEK          = 1,
    SND_XA_STATE_SEEK_RESULT   = 2,
    SND_XA_STATE_READ          = 3,
    SND_XA_STATE_READ_PROGRESS = 4,
    SND_XA_STATE_READ_RESULT   = 5,
    SND_XA_STATE_PAUSE         = 6,
    SND_XA_STATE_PAUSE_RESULT  = 7,
    SND_XA_STATE_WAIT_SYNC     = 8,
    SND_XA_STATE_COUNT         = 9,
} XAState;

/* The area message table offset the HUD value text reads (AREA_MESSAGE_TABLE slot 4). */
extern u16          D_80010008;
/* 0x80143xxx: shared area and UI state. */
extern u8           D_80142CC4[];
/* D_80143B92 */
extern u16          g_GameEntrySubstate;
/* D_80143C10 */
extern volatile u16 g_UiTitleState;
/* D_80143C12 */
extern volatile u16 g_UiTitleSubstate;
/* D_80143C20 */
extern u16          g_UiTitleTimer;
/* D_80143C22 */
extern volatile u16 g_UiTitleBannerScroll;
/* D_80143C24 */
extern volatile u16 g_UiTitleBannerAlpha;
/* D_80143C26 */
extern volatile u16 g_UiTitlePrimaryAlpha;
/* D_80143C28 */
extern volatile u16 g_UiTitleSecondaryAlpha;
/* D_80143C31 */
extern volatile u8  g_UiTitleFadePhase;
/* D_80143C32 */
extern volatile u8  g_UiTitleChoicePhase;
/* D_80143C33 */
extern u8           g_UiTitleInputGate;
/* D_80143D40 */
extern Thread*      g_SysCurrentThread;
/* D_80143D44 */
extern u8           g_GfxBufferIndex;

/* The double-buffered display record: the display and draw environments and the eight ordering-table heads, 0x90 bytes per buffer. */
typedef struct GfxFrame {
    DISPENV disp;  /* 0x00 */
    DRAWENV draw;  /* 0x14 */
    u_long  ot[8]; /* 0x70 */
} GfxFrame;

ASSERT_OFFSET(GfxFrame, draw, 0x14);
ASSERT_OFFSET(GfxFrame, ot, 0x70);
ASSERT_SIZE(GfxFrame, 0x90);

/* D_80143D48 */
extern GfxFrame  g_GfxBuffers[2];
/* D_80143E68 */
extern GfxFrame* g_GfxCurrentBuffer;
/* D_80143E6C */
extern u32       g_FrameCount;
/* D_80143EF8 */
extern s32       g_SysLastVSync;
/* The VSync count captured when drawing finished. */
/* D_80143EFC */
extern s32       g_SysDrawTime;
/* D_80143F10 */
extern u16       g_GameEntryAreaId;
/* D_80143F1C */
extern u8        g_GameEntryFacing;
extern u8        g_GameRequestType;
/* 0x80144xxx: party and menu state. */
extern u16       D_80143F20;

/* D_80143F44 */
extern u8          g_SysResetHoldFrames;
extern u8          D_80143F50;
extern u8          D_80143FC0;
extern u8          D_801448D8;
extern s8          D_801448E9;
extern s8          g_SceneEventMode;
extern s8          g_SceneEventStep;
extern u8          g_SceneEventSelection;
extern volatile u8 g_SndMono;
extern u8          g_WindowStyle;
extern u8          g_SavedScriptVars[4];
extern u8          D_80144955;
/* D_80144E98 */
extern u8          g_Scenario2Flags[];
/* 0x80145xxx: pad state, shared text buffer and field words. */
/* g_SaveData.return_point.area_id as a scalar. */
extern u16         D_80145048;
extern u8          D_801454F2;
/* D_801459F4 */
extern u8*         g_SceneActorDefs;
/* Event descriptors opened by the executable's card setup. */
/* The palette cell map: 4 rows of 16 cells, 0xFF where a cell is free. */
#define PALETTE_MAP_ROWS    4
#define PALETTE_MAP_COLUMNS 16
/* The palette cell map: which palette cells are in use. */
/* D_80145D54 */
extern u8                  g_PaletteCells[PALETTE_MAP_ROWS][PALETTE_MAP_COLUMNS];
/* D_80145E14 */
extern s32                 g_SysCardSoftwareIoEvent;
/* D_80145E18 */
extern s32                 g_SysCardSoftwareTimeoutEvent;
/* D_80145E1C */
extern s32                 g_SysCardSoftwareNewEvent;
/* D_80145E20 */
extern s32                 g_SysCardSoftwareErrorEvent;
/* D_80145E24 */
extern s32                 g_SysCardHardwareIoEvent;
/* D_80145E28 */
extern s32                 g_SysCardHardwareTimeoutEvent;
/* D_80145E2C */
extern s32                 g_SysCardHardwareErrorEvent;
/* D_80145E5C */
extern u8                  g_FairyVillagePendingQueueCount;
/* D_80145E5D */
extern u8                  g_FairyVillageUpdateCount;
extern u8                  D_80145E94[];
extern u8                  D_80145F1E[];
/* 0x80146xxx-0x80149xxx: UI buffers, area queries and shared tables. */
extern u16                 D_8014625C;
extern u8                  D_8014626D;
/* FAKE: g_Battle.choose_ending_hook as a global of its own; the sites that use it match only with a separate symbol. */
extern Callback            g_BattleChooseEndingHook;
extern EncounterEnemy      D_801463DC[];
/* D_8014682D */
extern s8                  g_EmiServiceState;
extern volatile u8         D_80146880;
extern volatile u8         D_80146881;
extern u8                  D_80146889[];
extern u16                 D_801481DC;
extern u8                  D_80148356;
extern s16                 D_80148358;
extern s16                 D_8014835A;
extern u8                  D_8014835C;
extern u8                  D_8014835E;
extern u8                  D_80148378[];
extern s16                 D_8014837C;
extern s16                 D_8014837E;
extern u8                  D_801483C0;
extern s16                 D_80148574;
extern u8                  D_80148578;
extern u8                  D_80148579;
extern u8                  D_8014857A;
extern u8                  D_8014857B;
extern u8                  D_8014857C;
extern u8                  D_8014857D;
extern s16                 D_80148580;
extern u8                  D_8014859C;
extern u8                  D_8014859E;
/* D_8014859F */
extern u8                  g_BattleListCursor;
extern u8                  D_801485A0;
/* D_801485BB */
extern volatile u8         g_BattlePanelMode;
/* D_801485C2 */
extern u8                  g_BattleEquipSlot;
extern u8                  D_801485C3;
extern u8                  D_801485C4;
/* D_801485C8 */
extern s16                 g_BattleTargetCursorCol;
extern volatile u8         D_801485DC;
extern volatile u16        D_801485E0;
extern volatile u16        D_801485E2;
extern volatile u8         D_8014862E;
/* D_8014864C */
extern u8                  g_UiPanelMode;
extern MenuStep            g_MenuStep;
/* FAKE: retail reads the three bytes as separate symbols; where the shared base
 * of g_MenuStep changes the code, the shop and start overlays keep these. */
extern u8                  D_80148650;
extern u8                  D_80148651;
extern u8                  D_80148652;
extern u8                  D_8014866C[];
extern u8                  D_80148A50[];
/* D_80148FC0 */
extern s8                  g_SelectionEffectVoices[SND_SLOT_COUNT];
/* D_801490A1 */
extern u8                  g_UiMessageStep;
/* D_801490D8 */
extern u8                  g_TextVariables[16][0x20];
extern u8                  D_801490E4[];
extern u8                  D_801490F8[];
extern u8                  D_80149104;
/* D_8014930A */
extern s16                 g_AreaTargetCellX;
/* D_8014930E */
extern s16                 g_AreaTargetCellY;
/* D_80149314 */
extern u32                 g_AreaCameraY;
/* D_8014931C */
extern u8*                 g_AreaCellCodes;
/* D_80149338 */
extern u16                 g_AreaTileRemainderY;
/* D_8014933E */
extern u8                  g_AreaDrawMode;
extern u8                  D_8014933F;
extern const char          g_LogoExePath[];
extern const char          D_80149814[];
/* D_8017F504 */
extern const void*         g_ExceptionTitle; /* 0x8017F504 */
/* D_8017F508 */
extern const void*         g_ExceptionCauseNames[]; /* 0x8017F508 */
/* D_8017F53C */
extern const u8            g_SpriteSizes[16][2];
/* D_8017F55C */
extern const s8            g_SpriteCellRotations[16];
/* D_8017F580 */
extern const u8            g_NumberRowShades[32];
/* D_8017F5A0 */
extern const u8            g_TextRowShades[20];
/* D_8017F620 */
extern const u8            g_TextRowOffsets[8];
/* D_8017F79C */
extern const u8            g_SpriteCellPartCounts[12];
/* D_8017F894 */
extern const u8            g_SpriteCellTopV[20];
/* D_8017F8A8 */
extern const u8            g_SpriteCellBottomV[20];
/* D_8017F8BC */
extern const u8            g_SpriteCellLeftU[12];
/* D_8017F8C8 */
extern const u8            g_SpriteCellRightU[12];
/* D_8017F8D4 */
extern const u8            g_SpriteCellCluts[12];
/* D_8017F90C */
extern const UIPanelOrigin g_UiPanelOrigins[UI_PANEL_ORIGIN_BANKS][UI_PANEL_ORIGIN_COUNT];
/* The other tables of the tail 0x80181484..0x801821D0 are defined by g_SceneFlagPairs.c, data_80181AC0.c, D_80181C7C.c,
 * data_80181CA8.c, g_BGMTracks.c and data_8018214C.c without slus.h; their consumers keep the interior or scalar
 * views they declare (gameui.h, local externs) because one merged base symbol moves the generated bytes. */
/* D_80181B98 */
extern s32                 g_FacingStepY[];
/* D_80183224 */
extern char                g_EmiHeaderTag[12];
extern u8                  D_801839F4;
extern u8                  D_801839F8;
extern u8                  D_80183A00;
extern u8                  D_80183A04;
extern u8                  D_80183A0C;
extern u8                  D_80183A10;
extern u8                  D_80183A18;
/* D_8018B300 */
extern u8                  g_SysHardwareInitialized;
/* D_8018E140 */
extern s32                 g_SndVoiceStatus[];

/* Card event result codes, in event order: the software events (EvSpIOE, EvSpTIMOUT, EvSpNEW, EvSpERROR) and the hardware events that follow them. */
typedef enum CardEvent {
    CARD_EVENT_PENDING  = -1,
    CARD_EVENT_OK       = 0,
    CARD_EVENT_TIMEOUT  = 1,
    CARD_EVENT_NEW      = 2,
    CARD_EVENT_ERROR    = 3,
    CARD_EVENT_CAPACITY = 4,
} CardEvent;

/* D_8018E228 */
extern s32 g_SaveCardStatus; /* CardEvent */
/* D_8018E260 */
extern s32 g_SaveCardPort;

/* func_8017E3D4 */

/* Start scene event `event` at `step` with the script marked active. */
static inline void Scene_StartEvent(s32 event, s32 step) {
    Game_SetScriptActive();
    g_SceneEventMode = event;
    g_SceneEventStep = step;
}

#endif
