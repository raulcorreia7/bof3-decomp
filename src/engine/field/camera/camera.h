#ifndef OVERLAY_FIELD_CAMERA_H
#define OVERLAY_FIELD_CAMERA_H

#include "types.h"
#include "psx/psyq.h"
/* func_801527E4 */
extern void Area_UpdateCamera(void);
/* func_8015B4B0 */
void        Area_ApplyCameraMatrix(void* matrix);
/* func_8015BC14 */
u8          Area_StepCameraX(s16 target, s8 step);
/* func_8015BD14 */
u8          Area_StepCameraY(s16 target, s8 step);
/* func_8015BE10 */
u8          Area_StepCameraZ(s16 target, s8 step);
/* func_8015BEA0 */
bool        Area_StepCameraAngle(s16 degrees, s8 duration);

/* func_801AFE18 */
void* Area_SetCameraMatrix(void* out_matrix);
/* func_801AFF04 */
void  Area_ProjectPoint(s32* pos, DVECTOR* screen_xy);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_FIELD_CAMERA_H_LOCAL)
#define OVERLAY_FIELD_CAMERA_H_LOCAL

/* func_801C7244 */
void Area_SetEncounterCamera(s32 mode);

#endif
