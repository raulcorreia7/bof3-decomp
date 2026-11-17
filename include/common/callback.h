#ifndef COMMON_CALLBACK_H
#define COMMON_CALLBACK_H

#include "types.h"

/* Callback is the plain void(void) entry used by dispatch tables and engine
 * registrations. Every other signature is named <Role>Callback, for what the
 * function does in the game; subsystem headers own their own. Shared here:
 *
 *   SceneActorCallback   a scene actor and the scenario's flags
 *   ActorModeCallback    the actor routine a task mode selects
 */
typedef void (*Callback)(void);
typedef void (*SceneActorCallback)(void* entity, void* scene_flags);
typedef void (*ActorModeCallback)(void* actor);

#endif
