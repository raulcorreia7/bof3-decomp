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
    u8  reserved[11];
    u8  phase;
} GameUIBannerState;

extern volatile u16 D_80143B40;
extern volatile u16 D_80143C2A;
/* Address symbols name the first record's interior fields. */
extern const u16    D_801D1C6E;
extern const u16    D_801D1C70;
extern const u16    D_801D1C72;
extern const u16    D_801D1C74;

void Title_Run(void);
void Title_Begin(void);
void Title_WaitFade(void);
void Title_AdvanceFade(void);
void Title_StartFade(void);
void Title_StartSelectedGame(void);
void Title_WaitInput(void);
void Title_UpdateChoicePrompt(void);
void Title_Leave(void);
void Title_UpdateStartButton(void);
void SND_StartSelectionEffect(void);
void SND_StopSelectionEffect(void);
void Title_DrawChoicePrompt(void);
void Title_DrawChoicePanels(u8 selected, u8 alpha);
void Title_DrawLabelPair(s16 x, s16 y, u8 selected, u8 alpha);
void Title_DrawIconPair(s16 x, s16 y, u8 selected, u8 alpha);
u8*  GFX_BuildGlyphPrimitive(s32 x, s32 y, s32 glyph, s32 palette, u8 flags);
void GFX_SetPrimitiveAlpha(u8* primitive, u8 alpha);
void Title_UpdateBannerFade(void);
void Title_UpdateWindowFade(void);

#endif
