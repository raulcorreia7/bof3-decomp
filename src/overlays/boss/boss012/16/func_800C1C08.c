#include "boss012_16.h"
#include "overlays/battle/battle.h"

MATCH void func_800C1C08(s32 mode) {
    SPRT*  sprt;
    Actor* task;
    s32    y1;
    s32    y2;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100));

    sprt = (SPRT*)g_GfxPrimCursor;
    setRGB0(sprt, 0x80, 0x80, 0x80);
    task     = SELF(PartyMember);
    sprt->x0 = task->unk_18 - 0x28;
    y1       = task->unk_1C;
    y2       = task->gravity - 0x3C;
    sprt->w  = 0x68;
    setUV0(sprt, 0, mode);
    sprt->h  = 0x56;
    sprt->y0 = y1 + y2;
    SetSprt(sprt);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}
