#include "area198_13.h"

MATCH void func_801F3B98(void) {
    Actor* row;

    row                  = &g_Actors[g_Task->option_flags];
    g_Task->header.flags = row->header.flags;
    Actor_StepAnimLoop();
    Area_AddActor();
    g_Task->tint.bytes.flags     = row->tint.bytes.flags;
    g_Task->tint.bytes.rgb.red   = row->tint.bytes.rgb.red;
    g_Task->tint.bytes.rgb.green = row->tint.bytes.rgb.green;
    g_Task->tint.bytes.rgb.blue  = row->tint.bytes.rgb.blue;
    g_Task->unk_27               = row->unk_27;
    g_Task->unk_48               = row->unk_48;
    g_Task->scale.x              = row->scale.x;
    g_Task->scale.y              = row->scale.y;
    g_Task->screen_x             = row->screen_x;
    g_Task->screen_y             = row->screen_y;
    g_Task->unk_32               = row->unk_32;
    g_Task->unk_60               = row->unk_60;
    g_Task->draw_layer           = 6;
    if (g_Task->unk_48 != 0) {
        g_Task->screen_x += Area_RoundSpriteCoordinate_area198(D_801F43D4[g_Task->unk_06].x * g_Task->scale.x, g_Task->scale.x);
        g_Task->screen_y += Area_RoundSpriteCoordinate_area198(D_801F43D4[g_Task->unk_06].y * g_Task->scale.y, g_Task->scale.y);
    } else {
        g_Task->screen_x += Area_RoundSpriteCoordinate_area198(TO_COORD(D_801F43D4[g_Task->unk_06].x), TO_COORD(1));
        g_Task->screen_y += Area_RoundSpriteCoordinate_area198(TO_COORD(D_801F43D4[g_Task->unk_06].y), TO_COORD(1));
    }
}
