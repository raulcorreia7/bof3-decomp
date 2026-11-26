#ifndef OVERLAY_UI_TEXT_H
#define OVERLAY_UI_TEXT_H

#include "types.h"
#include "gfx/prim.h"

/* The executable's window and menu text functions, in address order. */
/* func_8014ECAC */
void        UI_ModeSet(u16 local_mode);
/* func_8014F800 */
void        UI_TextDraw(s16 x, s16 y, s32 palette, u32 byte_count, u8* text);
/* func_8014F84C */
u8*         UI_TextDrawGlyphs(u8 palette, u8 byte_count, u8* text);
/* func_8014FC00 */
void        UI_TextAddDrawMode(s32 mode);
/* func_8014FC90 */
const u8*   UI_TextDrawString(s16 x, s16 y, s32 palette, u8 byte_count, const u8* text);
/* func_8014FF0C */
void        UI_TextDrawAscii(s16 left, s16 top, s32 flags, u8* text);
/* func_80150098 */
void        UI_TextDrawGlyphString(s16 x, s16 y, u32 clut, const u8* text);
/* func_80150304 */
void        UI_MessageReset(void);
/* func_801503E0 */
extern s32  UI_MessageUpdateLayout(void);
/* func_80150470 */
extern void UI_MessageDrawScript(void);
/* func_80150E14 */
void        UI_MessageTickChoiceTimer(void);
/* func_80151210 */
void        UI_MessageUpdateChoiceInput(void);
/* func_801515A8 */
void        UI_MessageClosePanel(void);
/* func_80151628 */
void        UI_MessageScrollChoice(void);
/* func_8015196C */
void        UI_MessageUpdateChoice(void);
/* func_801526F4 */
extern void UI_MessageDrawWaitMarker(s16 x, s16 y);
/* UI_IconDrawCell */
/* func_801644D8 */
void        UI_IconDrawCell(s32 index, s32 x, s32 y, s32 width, s32 height, s32 shade);
/* func_801AE3F0 */
void        UI_WindowDraw(u16 x, u16 y, u16 width, u16 height, s32 frame_flags, u8 palette);
/* UI_IconDraw */
/* func_801AEA80 */
void        UI_IconDraw(s32 sprite_x, s32 sprite_y, s32 icon_id, s32 dimmed);
/* UI_WindowDrawFrame */
/* func_801AEBA0 */
void        UI_WindowDrawFrame(s16 frame_x, s16 frame_y, s16 frame_width, s16 frame_height, s32 mode_pair_flag);
/* func_801AED54 */
void        UI_WindowDrawOutline(s32 x, s32 y, s32 width, s32 height, s32 flags);
/* UI_SpriteGetRect */
/* func_801AF270 */
UvRect*     UI_SpriteGetRect(u8 sprite_id, u8 flags);
/* func_801AF2A0 */
void        UI_SpriteDraw(s16 x, s16 y, u8 sprite_id, u8 flags);
/* func_801AF390 */
void        UI_SpriteDrawRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
/* func_801AF800 */
void        UI_ListDrawItemRow(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);
/* func_801AFA1C */
void        UI_ListDrawScrollbar(u8* marks, u8 thumb_top, s16 x, s16 y, u8 thumb_size, u8 total, u8 track_size);
void        UI_WindowDrawBoxOutline(s32 x, s32 y, u8 width, u8 height);

#endif
/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */

#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_UI_TEXT_H_LOCAL)

#define OVERLAY_UI_TEXT_H_LOCAL
/* func_801519F8 */
void        UI_MessageNextChoice(void);
/* func_80151A48 */
void        UI_MessagePrevChoice(void);
void        UI_TextDrawGlyph(s32 color, u8* text);
/* func_80159B9C */
extern void UI_WindowDrawPanelBox(s16 x, s16 y, u8 w, u8 h);
/* func_8015A2B0 */
void        UI_WindowDrawLine(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u8 gray);
extern u8*  UI_TextDrawAt(s32 x, s32 y, u8* text);
void        UI_ModeDispatchLocal(void);

#endif
