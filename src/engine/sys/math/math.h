#ifndef OVERLAY_SYS_MATH_H
#define OVERLAY_SYS_MATH_H

#include "types.h"
#include "psx/psyq.h"

/* func_801AFF64 */
void MATH_SetIdentity(MATRIX* matrix);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_SYS_MATH_H_LOCAL)
#define OVERLAY_SYS_MATH_H_LOCAL

/* func_8014C47C */
void MATH_SwapVectors(Pos3* a, Pos3* b);

#endif
