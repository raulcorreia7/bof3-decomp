#include "area198_13.h"

MATCH void func_801F3B98(void) {
    Actor* actor;

    actor                     = &g_Actors[SELF(Actor)->option_flags];
    SELF(Actor)->header.flags = actor->header.flags;
    Script_AnimStepLoop();
    Area_AddActor();
    SELF(Actor)->tint.bytes.flags = actor->tint.bytes.flags;
    SELF(Actor)->tint.bytes.rgb.r = actor->tint.bytes.rgb.r;
    SELF(Actor)->tint.bytes.rgb.g = actor->tint.bytes.rgb.g;
    SELF(Actor)->tint.bytes.rgb.b = actor->tint.bytes.rgb.b;
    SELF(Actor)->clut_select      = actor->clut_select;
    SELF(Actor)->unk_48           = actor->unk_48;
    SELF(Actor)->scale.x          = actor->scale.x;
    SELF(Actor)->scale.y          = actor->scale.y;
    SELF(Actor)->screen_x         = actor->screen_x;
    SELF(Actor)->screen_y         = actor->screen_y;
    SELF(Actor)->unk_32           = actor->unk_32;
    SELF(Actor)->unk_60           = actor->unk_60;
    SELF(Actor)->draw_layer       = 6;
    if (SELF(Actor)->unk_48 != 0) {
        SELF(Actor)->screen_x += Area_RoundSpriteCoordinate_801F3DCC(D_801F43D4[SELF(Actor)->unk_06].x * SELF(Actor)->scale.x, SELF(Actor)->scale.x);
        SELF(Actor)->screen_y += Area_RoundSpriteCoordinate_801F3DCC(D_801F43D4[SELF(Actor)->unk_06].y * SELF(Actor)->scale.y, SELF(Actor)->scale.y);
    } else {
        SELF(Actor)->screen_x += Area_RoundSpriteCoordinate_801F3DCC(TO_COORD(D_801F43D4[SELF(Actor)->unk_06].x), TO_COORD(1));
        SELF(Actor)->screen_y += Area_RoundSpriteCoordinate_801F3DCC(TO_COORD(D_801F43D4[SELF(Actor)->unk_06].y), TO_COORD(1));
    }
}
