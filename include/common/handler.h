#ifndef COMMON_HANDLER_H
#define COMMON_HANDLER_H

#include "types.h"

/* Callback is the plain void(void) entry used by dispatch tables and engine registrations. */
typedef void (*Callback)(void);
typedef void (*ObjectFunc)(void* obj);
typedef void (*ModeFunc)(s32 mode);
typedef void (*SceneFunc)(void* entity, void* context);

#endif
