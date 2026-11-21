#ifndef OVERLAY_FIELD_COLLISION_H
#define OVERLAY_FIELD_COLLISION_H

#include "types.h"

/* func_8015477C */
s16         Area_SampleHeight(s32 x, s32 y);
/* Area_GetHeight */
/* func_80154ABC */
s32         Area_GetHeight(s32 x, s32 y, u8 mode);
/* func_80154ED0 */
extern void Area_EnableHeightOffset(void);
/* func_80154F28 */
s16         Area_ReadHeight(s32 x, s32 y);
/* func_80154F78 */
s16         Area_ReadStepHeight(s32 x, s32 y, u8 mode);
/* func_80155038 */
void        Area_StoreHeight(s32 x, s32 y, u8 value);
/* func_80167848 */
void        Area_SyncScrollHeight(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_FIELD_COLLISION_H_LOCAL)
#define OVERLAY_FIELD_COLLISION_H_LOCAL

s8   Area_IsStepBlocked(s32 handler_x, s32 handler_y);
/* func_801A20F8 */
s32  Area_IsCellBlocked(s16 cell_x, s16 cell_y);
/* func_801B3260 */
void Area_Climb(void);
/* func_801B32D0 */
void Area_ClimbMount(void);
/* func_801B3488 */
void Area_ClimbLadder(void);
/* func_801B3540 */
void Area_ClimbDismount(void);

#endif
