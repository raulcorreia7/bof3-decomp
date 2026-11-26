#ifndef OVERLAY_AREA_COLLISION_H
#define OVERLAY_AREA_COLLISION_H

#include "types.h"

/* func_8015477C */
s16         Area_HeightSample(s32 x, s32 y);
/* Area_HeightGet */
/* func_80154ABC */
s32         Area_HeightGet(s32 x, s32 y, u8 mode);
/* func_80154ED0 */
extern void Area_HeightEnableOffset(void);
/* func_80154F28 */
s16         Area_HeightRead(s32 x, s32 y);
/* func_80154F78 */
s16         Area_HeightReadStep(s32 x, s32 y, u8 mode);
/* func_80155038 */
void        Area_HeightSet(s32 x, s32 y, u8 value);
/* func_80167848 */
void        Area_HeightSyncScroll(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_AREA_COLLISION_H_LOCAL)
#define OVERLAY_AREA_COLLISION_H_LOCAL

s8   Area_IsStepBlocked(s32 handler_x, s32 handler_y);
/* func_801A20F8 */
s32  Area_CellIsBlocked(s16 cell_x, s16 cell_y);
/* func_801B3260 */
void Area_Climb(void);
/* func_801B32D0 */
void Area_ClimbMount(void);
/* func_801B3314 */
void Area_ClimbMountApproachBeginStep(void);
/* func_801B3388 */
void Area_ClimbMountApproachStep(void);
/* func_801B33C4 */
void Area_ClimbMountTurnStep(void);
/* func_801B3400 */
void Area_ClimbMountTurnWaitStep(void);
/* func_801B343C */
void Area_ClimbMountLowerStep(void);
/* func_801B3488 */
void Area_ClimbLadder(void);
/* func_801B3540 */
void Area_ClimbDismount(void);
/* func_801B3584 */
void Area_ClimbDismountBeginStep(void);
/* func_801B35B0 */
void Area_ClimbDismountRiseStep(void);
/* func_801B35EC */
void Area_ClimbDismountExitBeginStep(void);
/* func_801B3670 */
void Area_ClimbDismountExitStep(void);
/* func_801BD7F8 */
void Area_ClimbFollower(void);
/* func_801BD83C */
void Area_ClimbFollowerLadder(void);
/* func_801C4D1C */
void Area_ClimbStartGrab(void);
/* func_801C4D58 */
void Area_ClimbMountApproachBegin(void);
/* func_801C4E14 */
s32  Area_ClimbMountApproach(void);
/* func_801C4EC4 */
bool Area_ClimbMountTurn(void);
/* func_801C4F88 */
bool Area_ClimbMountTurnWait(void);
/* func_801C4FE0 */
s32  Area_ClimbMountLower(void);
/* func_801C51B0 */
void Area_ClimbDismountBegin(void);
/* func_801C520C */
s32  Area_ClimbDismountRise(void);
/* func_801C539C */
bool Area_ClimbDismountExitBegin(void);
/* func_801C5474 */
s32  Area_ClimbDismountExit(void);
/* func_801C5558 */
void Area_ClimbUp(void);
/* func_801C5620 */
void Area_ClimbDown(void);
/* func_801C56E4 */
void Area_ClimbJumpOff(void);

#endif
