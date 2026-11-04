#ifndef OVERLAY_ETC_GAME_01_H
#define OVERLAY_ETC_GAME_01_H

/* The etc/game/01 frontend overlay's local declarations: the banner and glyph
 * records, the window masks and the handler entry points. Only this image
 * includes the file. */

#include "shared/etc.h"

#define WIN_POPUP_PENDING_MASK   0x00FFFF00u
#define WIN_POPUP_PENDING_OPEN   0x00020000u
#define WIN_GLYPH_GEOMETRY_COUNT 20
#define WIN_GEOMETRY_STRIDE      5u

typedef enum InputFlags {
    INPUT_START = PADstart,
} InputFlags;

typedef struct WinGlyphGeometry {
    u16 u0;     /* 0x00; copied to primitive[12] */
    u16 v0;     /* 0x02; copied to primitive[13] */
    u16 w;      /* 0x04; copied to primitive[16] */
    u16 h;      /* 0x06; copied to primitive[18] */
    u16 clut_y; /* 0x08; shifted left 6 for primitive[14] */
} WinGlyphGeometry;

typedef struct GameUIBannerState {
    u16 scroll;
    u16 alpha;
    u8  reserved_04[11];
    u8  phase;
} GameUIBannerState;

extern volatile u16 D_80143B40;
extern volatile u16 D_80143C2A;
extern volatile u32 g_UiPopupRequest;
/* Address symbols name the first record's interior fields. */
extern const u16    D_801D1C6E;
extern const u16    D_801D1C70;
extern const u16    D_801D1C72;
extern const u16    D_801D1C74;

void Game_RunTitle(void);
void Game_BeginTitle(void);
void Game_WaitTitleFade(void);
void Game_AdvanceTitleFade(void);
void SND_StartTitleBgm(void);
void Game_StartSelectedGame(void);
void UI_WaitTitleInput(void);
void UI_UpdateChoicePrompt(void);
void Game_LeaveTitle(void);
void UI_HandleStartButton(void);
void SND_StartSelectionEffect(void);
void SND_StopSelectionEffect(void);
void UI_DrawChoicePrompt(void);
void UI_DrawChoicePanels(u8 selected, u8 alpha);
void UI_DrawLabelPair(s16 x, s16 y, u8 selected, u8 alpha);
void UI_DrawIconPair(s16 x, s16 y, u8 selected, u8 alpha);
u8*  GFX_BuildGlyphPrimitive(s32 x, s32 y, s32 glyph, s32 palette, u8 flags);
void GFX_SetPrimitiveAlpha(u8* primitive, u8 alpha);
void UI_UpdateBannerFade(void);
void UI_UpdateWindowFade(void);

#endif
