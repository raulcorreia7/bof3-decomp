#ifndef OVERLAY_UI_MENU_H
#define OVERLAY_UI_MENU_H

#include "types.h"
/* func_80158C80 */
void UI_PanelUpdateTasks(void);
/* func_80158DB8 */
u8   UI_PanelOpenTask(u8 panel_index, u8 step_index);
/* func_80158E20 */
void UI_PanelClear(void);
/* func_80158E50 */
void UI_PanelResetTasks(void);
/* func_801647C4 */
void UI_CursorDraw(u16 x, u16 y, s32 unused);

/* func_80199678 */
void UI_CursorDrawPanel(void);
/* func_8019973C */
void UI_PanelSlideLeft(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_UI_MENU_H_LOCAL)
#define OVERLAY_UI_MENU_H_LOCAL

/* func_80198C38 */
void        UI_WindowWaitEffect(u8 wait_steps);
/* func_8019982C */
void        UI_PanelSetPosX(void);
void        UI_PanelOpenMaster(void);
/* func_80158F80 */
void        UI_MessageUpdatePanel(void);
/* func_80158FE0 */
void        UI_MessageUpdateWindow(void);
/* func_80159050 */
void        UI_MessageOpenPanel(void);
/* func_8015920C */
void        UI_MessageGrowPanel(void);
/* func_80159510 */
void        UI_MessageDrawPanel(void);
/* func_80159580 */
void        UI_MessageShrinkPanel(void);
void        UI_PanelClose(void);
/* func_801598F4 */
void        UI_MessageUpdateChoicePanel(void);
/* func_80159964 */
void        UI_MessageOpenChoicePanel(void);
/* func_8015999C */
void        UI_MessageDrawChoicePanel(void);
/* func_80159A00 */
void        UI_MessageReleasePanel(void);
/* func_80159A20 */
void        UI_MessageUpdatePresetPanel(void);
/* func_80159A90 */
void        UI_MessageOpenPresetPanel(void);
/* func_80159B38 */
void        UI_MessageDrawPresetPanel(void);
/* func_80159FA0 */
/* func_8015A098 */
extern void UI_MessageDrawPresetRows(void);
/* func_8015A1D8 */
extern void UI_MessageDrawPresetCursor(void);
/* func_8015A264 */
extern void UI_MessageDrawChoiceCursor(void);
/* func_8015A554 */
void        UI_MessageLayoutChoicePanel(void);
/* func_8019959C */
void        UI_PanelStepIdle(void);
/* func_801995A4 */
void        UI_PanelRunMenu(void);
/* func_801995F8 */
void        UI_PanelSlideOutMenu(void);
/* func_80199638 */
void        UI_PanelSlideInMenu(void);
/* func_801996A8 */
void        UI_PanelRunOption(void);
/* func_801996FC */
void        UI_PanelSlideOutOption(void);
/* func_8019977C */
void        UI_PanelRunAction(void);
/* func_801997EC */
void        UI_PanelSlideOutAction(void);
/* func_8019986C */
void        UI_PanelRunTask(void);
/* func_80199938 */
void        UI_PanelSlideOutTask(void);
/* func_80199978 */
void        UI_PanelSlideInTaskTop(void);
/* func_801999B8 */
void        UI_PanelSlideInTaskLow(void);

#endif
