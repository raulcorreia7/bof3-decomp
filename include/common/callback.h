#ifndef COMMON_CALLBACK_H
#define COMMON_CALLBACK_H

#include "types.h"

/* Callback is the plain void(void) entry used by dispatch tables and engine registrations. */
typedef void (*Callback)(void);
typedef void (*SceneActorCallback)(void* entity, void* scene_flags);
typedef void (*ActorModeCallback)(void* actor);

#endif
