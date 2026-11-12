#include "game_00.h"

MATCH void func_801A4AA8(void) {
    Actor* step;
    Actor* motion;
    Actor* animation;

    g_Task->unk_04                 = 0;
    g_Task->unk_03                 = 0;
    g_Task->active_flags           = 0;
    step                           = g_Task;
    step->unk_0A                   = 0;
    step->timer                    = 0;
    motion                         = g_Task;
    animation                      = g_CurrentActor;
    motion->scale.y                = ONE;
    motion->scale.x                = ONE;
    motion->unk_6C                 = 0;
    motion->unk_68                 = 0;
    motion->unk_64                 = 0;
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
