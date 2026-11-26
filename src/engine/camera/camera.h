#ifndef OVERLAY_CAMERA_H
#define OVERLAY_CAMERA_H

#include "types.h"
#include "psx/psyq.h"
/* func_801527E4 */
extern void Camera_Update(void);
/* func_8015B4B0 */
void        Camera_ApplyMatrix(void* matrix);
/* func_8015BC14 */
u8          Camera_StepX(s16 target, s8 step);
/* func_8015BD14 */
u8          Camera_StepY(s16 target, s8 step);
/* func_8015BE10 */
u8          Camera_StepZ(s16 target, s8 step);
/* func_8015BEA0 */
bool        Camera_StepAngle(s16 degrees, s8 duration);

/* func_801AFE18 */
void* Camera_SetMatrix(void* out_matrix);
/* func_801AFF04 */
void  Camera_ProjectPoint(s32* pos, DVECTOR* screen_xy);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_CAMERA_H_LOCAL)
#define OVERLAY_CAMERA_H_LOCAL

/* func_801C7244 */
void Camera_SetEncounter(s32 mode);
/* func_8019A8B4 */
void Camera_PanAngleRun(void);
/* func_8019A904 */
void Camera_PanAngleStart(void);
/* func_8019AA44 */
void Camera_PanAngleStep(void);
/* func_8019AAFC */
void Camera_PanAngleFinish(void);
/* func_8019AC34 */
void Camera_PanZoomRun(void);
/* func_8019AC84 */
void Camera_PanZoomStart(void);
/* func_8019ACF4 */
void Camera_PanZoomStep(void);
/* func_8019AD70 */
void Camera_PanZoomFinish(void);

#endif
