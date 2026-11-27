#include "engine/game/00/game_00.h"

/* func_8019B3A8 */
/* Starts a rock: blocks its cell, selects its sprite and clears its motion. */
MATCH void Actor_RockStart(void) {
    Actor* work;

    Area_SceneSelectRecord(SELF(Actor)->param.scene_record_id);
    Actor_RockClaimCell();
    SELF(Actor)->draw_layer   = 6;
    SELF(Actor)->unk_48       = 1;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    ACTOR_CLEAR_TINT();
    work               = SELF(Actor);
    work->option_flags = 0;
    setVector(work, 0, 0, 0);
    work->unk_18        = 0;
    work->unk_1C        = 0;
    work->gravity       = 0;
    SELF(Actor)->unk_0A = 0;
    Script_Select(0);
    SELF(Actor)->header.mode++;
}
