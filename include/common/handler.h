#ifndef COMMON_HANDLER_H
#define COMMON_HANDLER_H

#include "types.h"

/* Callback is the plain void(void) entry used by dispatch tables and engine
 * registrations. Every other signature is named <Thing>Func:
 *
 *   ObjectFunc      one selected object
 *   ModeFunc        one selected mode
 *   SceneFunc       a scene object and its context
 *
 * Target-specific signatures belong in their owning headers. Reuse these
 * shared types when the signature and contract agree.
 */
typedef void (*Callback)(void);
typedef void (*ObjectFunc)(void* obj);
typedef void (*ModeFunc)(s32 mode);
typedef void (*SceneFunc)(void* entity, void* context);

#endif
