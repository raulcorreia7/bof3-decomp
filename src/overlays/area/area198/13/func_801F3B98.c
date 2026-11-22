#include "area198_13.h"

MATCH void func_801F3B98(void) {
    Actor* actor;

    actor                     = &g_Actors[TASK(Actor)->option_flags];
    TASK(Actor)->header.flags = actor->header.flags;
    Script_AnimStepLoop();
    Area_AddActor();
    TASK(Actor)->tint.bytes.flags = actor->tint.bytes.flags;
    TASK(Actor)->tint.bytes.rgb.r = actor->tint.bytes.rgb.r;
    TASK(Actor)->tint.bytes.rgb.g = actor->tint.bytes.rgb.g;
    TASK(Actor)->tint.bytes.rgb.b = actor->tint.bytes.rgb.b;
    TASK(Actor)->clut_select      = actor->clut_select;
    TASK(Actor)->unk_48           = actor->unk_48;
    TASK(Actor)->scale.x          = actor->scale.x;
    TASK(Actor)->scale.y          = actor->scale.y;
    TASK(Actor)->screen_x         = actor->screen_x;
    TASK(Actor)->screen_y         = actor->screen_y;
    TASK(Actor)->unk_32           = actor->unk_32;
    TASK(Actor)->unk_60           = actor->unk_60;
    TASK(Actor)->draw_layer       = 6;
    if (TASK(Actor)->unk_48 != 0) {
        TASK(Actor)->screen_x += Area_RoundSpriteCoordinate_801F3DCC(D_801F43D4[TASK(Actor)->unk_06].x * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
        TASK(Actor)->screen_y += Area_RoundSpriteCoordinate_801F3DCC(D_801F43D4[TASK(Actor)->unk_06].y * TASK(Actor)->scale.y, TASK(Actor)->scale.y);
    } else {
        TASK(Actor)->screen_x += Area_RoundSpriteCoordinate_801F3DCC(TO_COORD(D_801F43D4[TASK(Actor)->unk_06].x), TO_COORD(1));
        TASK(Actor)->screen_y += Area_RoundSpriteCoordinate_801F3DCC(TO_COORD(D_801F43D4[TASK(Actor)->unk_06].y), TO_COORD(1));
    }
}
