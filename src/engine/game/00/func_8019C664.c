#include "game_00.h"

MATCH void func_8019C664(void) {
    Actor* work;
    void*  flags;
    Actor* state;

    SELF(Actor)->direction = (u8)g_Game.members[0].facing;
    func_8019EE10();
    SELF(Actor)->clut_select = 0x7B;
    Script_Select(((u8)SELF(Actor)->direction >> 1) + 0x4A);
    GFX_PaletteLoad(GAME_PALETTE_STAGE + 0xC0, 1);
    work                   = SELF(Actor);
    work->pos.x.fixed      = g_Game.members[0].pos.x.fixed;
    work->pos.y.fixed      = g_Game.members[0].pos.y.fixed;
    COORD_INT(work->pos.z) = (s16)((u16)COORD_INT(g_Game.members[0].pos.z) + 0xC0);
    work->vx               = (s32)(g_FacingOffsets[work->direction].x * 0x10);
    work->vy               = (s32)(g_FacingOffsets[work->direction].y * 0x10);
    if (g_Game.members[0].chr.character_id == CHAR_ID_NINA_YOUNG) {
        work->unk_0A = 0xA;
    } else {
        work->unk_0A = 0x12;
    }
    flags              = SELF(void);
    *(u8*)(flags)      = (u8)(*(u8*)(flags) | ACTOR_FLAG_SKIP_PALETTE_STAGE);
    state              = SELF(Actor);
    state->header.mode = (u8)(state->header.mode + 1);
}
