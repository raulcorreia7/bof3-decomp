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
void        Message_UpdatePanel(void);
/* func_80158FE0 */
void        Message_UpdateWindow(void);
/* func_80159050 */
void        Message_OpenPanel(void);
/* func_8015920C */
void        Message_GrowPanel(void);
/* func_80159510 */
void        Message_DrawPanel(void);
/* func_80159580 */
void        Message_ShrinkPanel(void);
void        Menu_ClosePanel(void);
/* func_801598F4 */
void        Message_UpdateChoicePanel(void);
/* func_80159964 */
void        Message_OpenChoicePanel(void);
/* func_8015999C */
void        Message_DrawChoicePanel(void);
/* func_80159A00 */
void        Message_ReleasePanel(void);
/* func_80159A20 */
void        Message_UpdatePresetPanel(void);
/* func_80159A90 */
void        Message_OpenPresetPanel(void);
/* func_80159B38 */
void        Message_DrawPresetPanel(void);
/* func_80159FA0 */
/* func_8015A098 */
extern void Message_DrawPresetRows(void);
/* func_8015A1D8 */
extern void Message_DrawPresetCursor(void);
/* func_8015A264 */
extern void Message_DrawChoiceCursor(void);
/* func_8015A554 */
void        Message_LayoutChoicePanel(void);

#endif
