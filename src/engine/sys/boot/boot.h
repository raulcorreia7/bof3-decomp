#ifndef OVERLAY_SYS_BOOT_H
#define OVERLAY_SYS_BOOT_H

#include "types.h"
#include "common/callback.h"

struct GfxFrame;
/* func_8014AEE0 */
void        SYS_StartLogo(void);
/* func_8014AFC0 */
void        SYS_UpdateKeyState(void);
/* func_8014B020 */
void        SYS_PrepareFrame(void);
/* func_8014B0F0 */
void        SYS_LinkOt(void);
/* func_8014B17C */
void        SYS_CaptureDrawTime(void);
/* func_8014B1A4 */
extern void SYS_InitCard(void);
/* func_8014B33C */
void        SYS_ThreadStopAll(void);
/* func_8014B3C4 */
extern void SYS_ShowException(void);
/* func_8014B6B4 */
void        SYS_ThreadInit(void);
/* func_8014B73C */
void        SYS_ThreadRun(void);
/* func_8014B854 */
void        SYS_ThreadRegister(s32 thread_index, Callback callback);
/* func_8014B87C */
void        SYS_ThreadWait(u16 countdown);
/* func_8014B8B0 */
void        SYS_ThreadExit(void);
/* func_8014B900 */
void        SYS_ThreadClose(s32 thread_index);
/* func_8014B954 */
extern void SYS_ThreadReplace(Callback entry);

/* func_8014BA04 */
void SYS_ClearCurrentThread(void);
void SYS_Main(void);
void SYS_InitRuntime(void);
void SYS_InitHardware(void);
void SYS_InitDisplay(void);
void SYS_ResetDisplayFrame(struct GfxFrame* frame);

#endif
