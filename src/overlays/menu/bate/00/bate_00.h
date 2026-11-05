#ifndef OVERLAY_ETC_BATE_00_H
#define OVERLAY_ETC_BATE_00_H

/* The etc/bate/00 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"
#include <stdio.h>

extern u8 D_80148654;

#define g_SceneState (*(struct SceneState*)&g_SceneState)

/* The ability-list record. @source: read:func_801D73B4 */
typedef struct BateAbilityPanel {
    u8  pad_00[4];
    u16 x;
    u16 y;
    u8  unk_08;
    u8  flags;
    u8  unk_0A;
    u8  unk_0B;
    u8  unk_0C;
    u8  selected;
    u8  pad_0E[2];
    s16 unk_10;
    u8  pad_12[0xE];
    u8* names;
} BateAbilityPanel;

extern u8            D_80145FCC[][BATTLE_PARTY_STRIDE];
extern u8            D_80148656;
extern u8            D_8018E244;
extern OverlayHeader D_801D0C00;
extern char          g_MenuStatFormat[];
extern char          g_MenuZennyFormat[];
extern u8            D_801D0C48[];
extern char          g_MenuClockFormat[];
extern u8            D_801D0D80[];
extern u8            D_801D0D84[];
extern u8            D_801D0D90[];
extern u8            D_801D0D94[];
extern u8            D_801D0D98[];
/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, selected by the shared menu step bytes. */
extern Callback      D_801D86E0[];
extern Callback      D_801D8700[];
extern Callback      D_801D870C[];
extern Callback      D_801D8720[];
extern Callback      D_801D8764[];
extern Callback      D_801D8770[];
extern u8            MENU_CAPTION_GLYPH_2[];
extern u8            MENU_CLOCK_CAPTION[];
extern u8            MENU_COMMAND_FRAME[];
extern u8            MENU_COMMAND_FRAME_SELECTED[];
extern u8            D_801D893C[];
extern u8            D_801D8954[];
extern u8            D_801D896C[];
extern u8            D_801D8978[];
extern u8            D_801D8A3C[];
extern u8            g_MenuLabelAgility[];
extern u8            D_801D8B38[];
extern u8            D_801D8B40[];
extern u8            g_MenuPortraitAtlas[];
extern u8            D_801D8B84[];
extern u8            MENU_CAPTION_ICON[];
extern u8            MENU_CLOCK_COLON[];
extern u8*           g_MenuCommandLabels[];
extern u8            g_MenuCommandRows[][5];
extern u8*           D_801D8E80[];
extern s8            D_80148658;
extern s8            D_80144DE4;
extern s8            D_801D86F0;
extern u8            D_80144DF2;
extern u8            D_80144DF3;
extern u8            D_80144DF4;
extern u8            D_80144DF5;
extern u8            D_80144DF6;
extern u8            D_80144DF7;
extern u8            D_80148338;
extern s8            D_80148511;
extern u8            D_801D8EE0;
extern u8            D_801D8EE1;
extern u8            D_801D8EE2;
extern u8            D_801D8EE3;
extern u8            D_801D8EE4;

typedef struct BateState {
    u8 unk_00;
    u8 pad_01[3];
    u8 unk_04;
    u8 pad_05[3];
    u8 unk_08;
} BateState;

extern s8        D_80148659;
extern BateState D_801D8ED4;

void UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags);
void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);
void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
s32  Char_GetExpForLevel(s32 character, s32 level);
void func_801D73B4(BateAbilityPanel* panel);

void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);

void UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags);

s32 Party_CountItem(u8 category, u8 item, u8 mode);

#endif
