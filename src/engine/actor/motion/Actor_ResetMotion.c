#include "engine/game/00/game_00.h"

/* func_801A4AA8 */
MATCH void Actor_ResetMotion(void) {
    Actor* actor;
    Actor* motion;
    Actor* animation;

    SELF(Actor)->unk_04            = 0;
    SELF(Actor)->unk_03            = 0;
    SELF(Actor)->active_flags      = 0;
    actor                          = SELF(Actor);
    actor->unk_0A                  = 0;
    actor->timer                   = 0;
    motion                         = SELF(Actor);
    animation                      = g_CurrentActor;
    motion->scale.y                = 0x10000;
    motion->scale.x                = 0x10000;
    motion->angle_z                = 0;
    motion->angle_y                = 0;
    motion->angle_x                = 0;
    /* 0x74 is a flag byte and 0x75 a byte timer (Actor.interaction_flags /
     * timer_75); every access in the module is byte-wide, so both stores are
     * byte-wide. */
    animation->interaction_flags   = 0;
    g_CurrentActor->timer_75       = 0;
    g_CurrentActor->pad_76         = 0;
    g_CurrentActor->unk_79         = 0;
    g_CurrentActor->callback_index = GAME_NONE;
    g_CurrentActor->unk_7B         = 0;
    g_CurrentActor->unk_7E         = 0;
    g_CurrentActor->roll_90        = 0;
}
