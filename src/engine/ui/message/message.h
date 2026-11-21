#ifndef OVERLAY_UI_MESSAGE_H
#define OVERLAY_UI_MESSAGE_H

#include "types.h"

/* The area functions the resident tables and the area images call. */
void UI_MessageRunArea(void);
/* func_80150224 */
void UI_MessageStartArea(s32 message_index);
/* func_80150284 */
void UI_MessageRequest(s32 request_id);
/* func_801502D0 */
u8*  UI_MessageGetText(u32 resource_id);
/* func_8016620C */
void UI_MessageSetVariable(u8 slot, u8 length, const u8* text);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_UI_MESSAGE_H_LOCAL)
#define OVERLAY_UI_MESSAGE_H_LOCAL

/* func_801507BC */
extern void UI_MessageDispatchState(void);
/* func_8015083C */
void        UI_MessageRunScript(void);
void        UI_MessageDispatchAnswerStep(void);
/* func_8015142C */
void        UI_MessageRestartRequest(void);
void        UI_MessageStartRequest(void);
/* func_801518F4 */
void        UI_MessageDispatchChoiceMode(void);
void        UI_MessageDispatchStep(void);

#endif
