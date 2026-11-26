#include "area189_13.h"

/* Runs the task script, places the task at the scroll target on screen and flashes red in scene mode 2. */
MATCH void func_801F3514(void) {
    SVECTOR* vertex;
    u16*     screen;
    TILE*    tile;
    long     depth;
    long     flag;
    s32      tpage;
    u8       count;
    u8*      script;
    s16*     out;

    script = &g_Game.members[0].unk_4B;
    if (SELF(Actor)->script_record != *script) {
        Script_Request(*script);
        SELF(Actor)->script_record = *script;
    }
    if (D_80145E92[0] == 3) {
        Script_AnimStepLoop();
    }

    if (g_AreaSceneMode == 1) {
        SELF(Actor)->tint.steps.delta.r = 0x7F;
        SELF(Actor)->tint.steps.delta.g = -0x80;
        SELF(Actor)->tint.steps.delta.b = -0x80;
        g_AreaSceneMode                 = 0;
    } else {
        SELF(Actor)->tint.steps.delta.r = 0;
        SELF(Actor)->tint.steps.delta.g = 0;
        SELF(Actor)->tint.steps.delta.b = 0;
    }

    vertex                    = g_ScratchPadVectors;
    screen                    = D_1F800034;
    /* Stored through a pointer: a member store lets the scroll loads move above it. */
    out                       = &SELF(Actor)->unk_32;
    *out                      = 0x3200;
    vertex->vx                = (s16)(((((g_AreaScrollTargetX - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    g_ScratchPadVectors[0].vy = (s16)(((((g_AreaScrollTargetY - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    g_ScratchPadVectors[0].vz = (s16)(-g_Game.members[0].pos.z.part.integer / 2);
    RotTransPers(vertex, (long*)screen, &depth, &flag);

    SELF(Actor)->screen_x = 0xA0;
    if (g_Game.members[0].unk_14 != 0) {
        SELF(Actor)->screen_y                   = D_1F800034[1];
        g_Game.members[0].screen_y.signed_value = D_1F800034[1];
    } else {
        SELF(Actor)->screen_y = g_Game.members[0].screen_y.signed_value;
    }

    if (g_AreaGridActorCount < 0x28) {
        count                   = g_AreaGridActorCount;
        g_AreaGridActorCount    = count + 1;
        g_AreaGridActors[count] = (s32)g_Self;
    }

    if (g_AreaSceneMode == 2) {
        tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
        GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT, tpage);
        tile = (TILE*)g_GfxPrimCursor;
        SetTile(tile);
        SetSemiTrans(tile, 1);
        setXY0(tile, 0, 0);
        setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
        setRGB0(tile, 0xFF, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(TILE));
        g_AreaSceneMode = 0;
    }
}
