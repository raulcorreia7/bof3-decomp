#ifndef OVERLAY_UI_MENU_H
#define OVERLAY_UI_MENU_H

#include "types.h"
/* func_80158C80 */
void Menu_UpdatePanelTasks(void);
/* func_80158DB8 */
u8   Menu_OpenPanelTask(u8 panel_index, u8 step_index);
/* func_80158E20 */
void Menu_ClearPanel(void);
/* func_80158E50 */
void Menu_ResetPanelTasks(void);
/* func_801647C4 */
void Menu_DrawCursorSprite(u16 x, u16 y, s32 unused);

/* func_80199678 */
void Menu_DrawPanelCursor(void);
/* func_8019973C */
void Menu_SlidePanelLeft(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_UI_MENU_H_LOCAL)
#define OVERLAY_UI_MENU_H_LOCAL

/* func_80198C38 */
void        Menu_WaitWindowEffect(u8 wait_steps);
/* func_8019982C */
void        Menu_SetPosX(void);
void        Menu_OpenMaster(void);
/* func_80158F80 */
void        Menu_UpdateMessagePanel(void);
/* func_80158FE0 */
void        Menu_UpdateMessageWindow(void);
/* func_80159050 */
void        Menu_OpenMessagePanel(void);
/* func_8015920C */
void        Menu_GrowMessagePanel(void);
/* func_80159510 */
void        Menu_DrawMessagePanel(void);
/* func_80159580 */
void        Menu_ShrinkMessagePanel(void);
void        Menu_ClosePanel(void);
/* func_801598F4 */
void        Menu_UpdateMessageChoice(void);
/* func_80159964 */
void        Menu_OpenMessageChoice(void);
/* func_8015999C */
void        Menu_DrawMessageChoice(void);
/* func_80159A00 */
void        Menu_ReleaseMessagePanel(void);
/* func_80159A20 */
void        Menu_UpdateMessagePreset(void);
/* func_80159A90 */
void        Menu_OpenMessagePreset(void);
/* func_80159B38 */
void        Menu_DrawMessagePreset(void);
/* func_80159FA0 */
/* func_8015A098 */
extern void Menu_DrawMessagePresetRows(void);
/* func_8015A1D8 */
extern void Menu_DrawMessagePresetCursor(void);
/* func_8015A264 */
extern void Menu_DrawMessageChoiceCursor(void);
/* func_8015A554 */
void        Menu_LayoutMessageChoice(void);

#endif
