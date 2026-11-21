#ifndef OVERLAY_UI_MESSAGE_H
#define OVERLAY_UI_MESSAGE_H

#include "types.h"

/* The area functions the resident tables and the area images call. */
void Message_RunAreaMessage(void);
/* func_80150224 */
void Message_StartAreaMessage(s32 message_index);
/* func_80150284 */
void Message_Request(s32 request_id);
/* func_801502D0 */
u8*  Message_GetText(u32 resource_id);
/* func_8016620C */
void Message_SetVariable(u8 slot, u8 length, const u8* text);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_UI_MESSAGE_H_LOCAL)
#define OVERLAY_UI_MESSAGE_H_LOCAL

/* func_801507BC */
extern void Message_DispatchState(void);
/* func_8015083C */
void        Message_RunScript(void);
void        Message_DispatchAnswerStep(void);
/* func_8015142C */
void        Message_RestartRequest(void);
void        Message_StartRequest(void);
/* func_801518F4 */
void        Message_DispatchChoiceMode(void);
void        Message_DispatchStep(void);

#endif
