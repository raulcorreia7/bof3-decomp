#ifndef SLUS_UI_H
#define SLUS_UI_H

#include "types.h"

/* The executable's window and menu text functions, in address order. */
/* func_8014ECAC */
void        UI_SetMode(u16 local_mode);
/* func_8014F800 */
void        UI_DrawText(s16 x, s16 y, s32 palette, u32 byte_count, u8* text);
/* func_8014F84C */
u8*         UI_DrawTextGlyphs(u8 palette, u8 byte_count, u8* text);
/* func_8014FC90 */
const u8*   UI_DrawTextString(s16 x, s16 y, s32 palette, u8 byte_count, const u8* text);
/* func_8014FF0C */
void        UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);
/* func_80150098 */
void        UI_DrawGlyphString(s16 x, s16 y, u32 clut, const u8* text);
/* func_80150224 */
void        Message_StartAreaMessage(s32 message_index);
/* func_80150284 */
void        Message_Request(s32 request_id);
/* func_801502D0 */
u8*         Message_GetText(u32 resource_id);
/* func_80150304 */
void        UI_ResetMessage(void);
/* func_801503E0 */
extern s32  UI_UpdateLayout(void);
/* func_80150470 */
extern void UI_DrawMessageScript(void);
/* func_80150E14 */
void        UI_TickChoiceTimer(void);
/* func_80151210 */
void        UI_UpdateChoiceInput(void);
/* func_801515A8 */
void        UI_ClosePanel(void);
/* func_80151628 */
void        UI_ScrollChoice(void);
/* func_8015196C */
void        UI_UpdateChoice(void);
/* func_801526F4 */
extern void UI_DrawWaitMarker(s16 x, s16 y);
/* func_80158C80 */
void        Menu_UpdatePanelTasks(void);
/* func_80158E20 */
void        Menu_ClearPanel(void);
/* func_80158DB8 */
u8          Menu_OpenPanelTask(u8 panel_index, u8 handler_index);
/* func_80158E50 */
void        Menu_ResetPanelTasks(void);
void        UI_DrawBoxOutline(s32 x, s32 y, u8 width, u8 height);
/* UI_DrawIconCell */
/* func_801644D8 */
void        UI_DrawIconCell(s32 index, s32 x, s32 y, s32 width, s32 height, s32 shade);
/* func_801647C4 */
void        Menu_DrawCursorSprite(u16 x, u16 y, s32 unused);
/* func_8016620C */
void        Message_SetVariable(u8 slot, u8 length, const u8* text);

#endif
