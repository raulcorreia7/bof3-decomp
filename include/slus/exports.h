#ifndef SLUS_EXPORTS_H
#define SLUS_EXPORTS_H

/* The main executable's exports to the overlays, in address order. The
 * subsystem headers keep the names they already own; this file lists the
 * remaining SLUS_004.22 symbols the overlays read or call. */

#include "types.h"
#include "sys/gameui.h"
#include "slus/functions.h"
#include "battle/records.h"
#include "common/handler.h"
#include "sys/sched.h"

/* 0x80010000: overlay text and image offsets. */
extern u16            D_80010008;
extern u16            D_8001008A;
extern u16            D_8001008C;
extern u16            D_8001008E;
extern u16            D_80010090;
extern u16            D_80010092;
extern u16            D_80010094;
extern u16            D_80010096;
extern u16            D_80010098;
extern u16            D_8001009A;
extern u16            D_8001009C;
/* 0x80143xxx: shared area and UI state. */
extern u8             D_80142CC4[];
/* D_80143B92 */
extern u16            g_GameEntrySubstate;
/* D_80143C10 */
extern volatile u16   g_UiTitleState;
/* D_80143C12 */
extern volatile u16   g_UiTitleSubstate;
/* D_80143C20 */
extern u16            g_UiTitleTimer;
/* D_80143C22 */
extern volatile u16   g_UiTitleBannerScroll;
/* D_80143C24 */
extern volatile u16   g_UiTitleBannerAlpha;
/* D_80143C26 */
extern volatile u16   g_UiTitlePrimaryAlpha;
/* D_80143C28 */
extern volatile u16   g_UiTitleSecondaryAlpha;
/* D_80143C31 */
extern volatile u8    g_UiTitleFadePhase;
/* D_80143C32 */
extern volatile u8    g_UiTitleChoicePhase;
/* D_80143C33 */
extern u8             g_UiTitleInputGate;
/* D_80143D40 */
extern CallbackSlot*  g_CallbackSlot;
/* D_80143D44 */
extern u8             g_FrameBufferIndex;
/* D_80143D48 */
extern u8             g_GfxDisplayFrames[];
/* D_80143E68 */
extern u8*            g_GfxCurrentDisplayFrame;
/* D_80143E6C */
extern u32            g_FrameCount;
/* D_80143EF8 */
extern s32            g_SysLastVSync;
extern s32            D_80143EFC;
extern u8             D_80143F03;
/* D_80143F10 */
extern u16            g_GameContextSeed;
/* D_80143F1C */
extern u8             g_GameContextKind;
/* 0x80144xxx: party and menu state. */
extern u16            D_80143F20;
extern s32            D_80143F24;
extern s32            D_80143F28;
extern u8             D_80143F2C[];
extern u8             D_80143F30[];
/* D_80143F44 */
extern u8             g_SysResetHoldFrames;
extern u8             D_80143F50;
extern u8             D_80143FC0;
extern u8             D_801448D8;
extern s8             D_801448E9;
extern s8             D_801448EB;
extern s8             D_801448EC;
extern u8             D_801448ED;
extern u8             D_80144952;
extern u8             D_80144955;
extern u8             D_80144E98[];
extern u8             D_80144F59;
/* 0x80145xxx: pad state, shared text buffer and field words. */
extern u16            D_80145048;
extern u8             D_801454F2;
extern u8*            D_801459F4;
/* D_80145AA8 */
extern u16            g_InputPressed;
extern u16            D_80145ABA;
extern u16            D_80145AC2;
extern u16            D_80145AC4;
/* Event descriptors opened by the executable's card setup. */
extern u8             D_80145D54[][16];
/* D_80145E14 */
extern s32            g_SysCardSoftwareIoEvent;
/* D_80145E18 */
extern s32            g_SysCardSoftwareTimeoutEvent;
/* D_80145E1C */
extern s32            g_SysCardSoftwareNewEvent;
/* D_80145E20 */
extern s32            g_SysCardSoftwareErrorEvent;
/* D_80145E24 */
extern s32            g_SysCardHardwareIoEvent;
/* D_80145E28 */
extern s32            g_SysCardHardwareTimeoutEvent;
/* D_80145E2C */
extern s32            g_SysCardHardwareErrorEvent;
/* D_80145E5C */
extern u8             g_FairyVillagePendingQueueCount;
/* D_80145E5D */
extern u8             g_FairyVillageUpdateCount;
extern u8             D_80145E94[];
extern u8             D_80145EB7;
extern u8             D_80145EB9;
extern u8             D_80145F1E[];
extern u8             D_80146189;
/* D_80146258 */
extern u16            g_GameFlags;
/* D_8014625A */
extern u16            g_AreaWalkFlags;
/* 0x80146xxx-0x80149xxx: UI buffers, area queries and shared tables. */
extern u16            D_8014625C;
extern u8             D_8014626D;
extern u8             D_80146277;
extern s32            D_801462A0;
extern s32            D_801462A4;
/* D_801462EA */
extern u8             g_BattleEncounter;
/* D_801462EF */
extern volatile u8    g_BattleSelectionLatch;
/* D_801462F2 */
extern volatile u8    g_BattleEnemyCount;
/* D_801462F4 */
extern u8             g_BattlePanelSlot;
/* D_801462FC */
extern u8             g_BattlePanelWidths[];
/* D_80146380 */
extern BattleAction*  g_BattleAction;
/* D_801463A4 */
extern Callback       g_BattleChooseEndingHook;
/* D_801463A8 */
extern Callback       g_BattleEndHook;
/* D_801463C7 */
extern u8             g_BattleGeneCount[];
/* D_801463C9 */
extern u8             g_DragonForm;
/* D_801463CE */
extern volatile u8    g_BattleActionLock;
extern EncounterEnemy D_801463DC[];
/* D_8014682D */
extern s8             g_EmiServiceState;
extern volatile u8    D_80146880;
extern volatile u8    D_80146881;
extern u8             D_80146889[];
extern u16            D_801481DC;
extern u8             D_80148356;
extern s16            D_80148358;
extern s16            D_8014835A;
extern u8             D_8014835C;
extern u8             D_8014835E;
extern u8             D_80148378[];
extern s16            D_8014837C;
extern s16            D_8014837E;
extern u8             D_801483C0;
extern u8             D_801483E4;
extern s16            D_80148574;
extern u8             D_80148578;
extern u8             D_80148579;
extern u8             D_8014857A;
extern u8             D_8014857B;
extern u8             D_8014857C;
extern u8             D_8014857D;
extern s16            D_80148580;
extern u8             D_8014859C;
extern u8             D_8014859E;
/* D_8014859F */
extern u8             g_BattleListCursor;
extern u8             D_801485A0;
/* D_801485BB */
extern volatile u8    g_BattlePanelMode;
/* D_801485C2 */
extern u8             g_BattleItemRow;
extern u8             D_801485C3;
extern u8             D_801485C4;
/* D_801485C8 */
extern s16            g_BattleTargetCursorCol;
extern volatile u8    D_801485DC;
extern volatile u16   D_801485E0;
extern volatile u16   D_801485E2;
extern volatile u8    D_8014862E;
/* D_8014864C */
extern u8             g_MenuPanelMode;
extern u8             D_80148650;
extern u8             D_8014866C[];
extern u8             D_80148A50[];
/* D_80148FC0 */
extern s8             g_SelectionFxVoices[];
/* D_801490A1 */
extern u8             g_UiWindowStep;
/* D_801490D8 */
extern u8             g_TextVariables[][0x20];
extern u8             D_801490DD;
extern u8             D_801490E4[];
extern u8             D_801490F8[];
extern u8             D_80149104;
extern s16            D_8014930A;
extern s16            D_8014930E;
extern u32            D_80149314;
/* D_8014931C */
extern u8*            g_AreaCellCodes;
/* D_80149338 */
extern u16            g_AreaTileRemainderY;
/* D_8014933E */
extern u8             g_AreaDrawMode;
extern u8             D_8014933F;
extern const char     s__LOGO_LOGO_EXE_1_80149800[];
extern const char     D_80149814[];
/* D_8017F504 */
extern const void*    PTR_s_EXCEPTION_8017f504; /* 0x8017F504 */
/* D_8017F508 */
extern const void*    PTR_s_INTERRRUPT_8017f508[]; /* 0x8017F508 */
/* D_8017F53C */
extern const u8       g_SpriteSizes[16][2];
/* D_8017F55C */
extern const s8       g_SpriteCellRotations[16];
/* D_8017F580 */
extern const u8       g_NumberRowShades[32];
/* D_8017F5A0 */
extern const u8       g_TextRowShades[20];
/* D_8017F620 */
extern const u8       g_TextRowOffsets[8];
/* D_8017F79C */
extern const u8       g_SpriteCellPartCounts[12];
/* D_8017F894 */
extern const u8       g_SpriteCellTopV[20];
/* D_8017F8A8 */
extern const u8       g_SpriteCellBottomV[20];
/* D_8017F8BC */
extern const u8       g_SpriteCellLeftU[12];
/* D_8017F8C8 */
extern const u8       g_SpriteCellRightU[12];
/* D_8017F8D4 */
extern const u8       g_SpriteCellCluts[12];
/* D_8017F90C */
extern const u8       g_MenuPanelOrigins[32];
/* The other tables of the tail 0x80181484..0x801821D0 are defined by D_80181484.c, data_80181AC0.c, D_80181C7C.c,
 * data_80181CA8.c, D_80181EB8.c and data_8018214C.c without slus.h; their consumers keep the interior or scalar
 * views they declare (gameui.h, local externs) because one merged base symbol moves the generated bytes. */
extern s32            D_80181B98[];
/* D_80183224 */
extern char           g_EmiHeaderTag[12];
extern u8             D_80183298;
extern u8             D_801832C4;
extern u8             D_801839C4;
extern u8             D_801839EC;
extern u8             D_801839F4;
extern u8             D_801839F8;
extern u8             D_80183A00;
extern u8             D_80183A04;
extern u8             D_80183A0C;
extern u8             D_80183A10;
extern u8             D_80183A18;
/* D_8018B300 */
extern u8             g_SysHardwareInitialized;
extern s32            D_8018E140[];
/* D_8018E228 */
extern s32            g_SaveCardStatus; /* CardEvent */
/* D_8018E260 */
extern s32            g_SaveCardPort;

/* func_8017E3D4 */
int rand(void); /* LIBC.LIB; no staged header declares it */

#endif
