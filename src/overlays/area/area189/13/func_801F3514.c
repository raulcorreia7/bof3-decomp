#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3514(void) {
    SVECTOR* vertex;
    u16*     screen;
    TILE*    tile;
    long     depth;
    long     flag;
    s32      tpage;
    u8       count;
    u8*      script;

    script = &D_80145EDB;
    if (g_Task->unk_4B != *script) {
        Actor_RequestScript(*script);
        g_Task->unk_4B = *script;
    }
    if (D_80145E92[0] == 3) {
        Actor_StepAnimLoop();
    }

    if (g_AreaSceneMode == 1) {
        g_Task->tint.signed_bytes.delta.red   = 0x7F;
        g_Task->tint.signed_bytes.delta.green = -0x80;
        g_Task->tint.signed_bytes.delta.blue  = -0x80;
        g_AreaSceneMode                       = 0;
    } else {
        g_Task->tint.signed_bytes.delta.red   = 0;
        g_Task->tint.signed_bytes.delta.green = 0;
        g_Task->tint.signed_bytes.delta.blue  = 0;
    }

    vertex         = D_1F800014;
    screen         = D_1F800034;
    g_Task->unk_32 = 0x3200;
    vertex->vx     = (s16)(((((g_AreaScrollTargetX - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    D_1F800016     = (s16)(((((g_AreaScrollTargetY - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    D_1F800018     = (s16)(-D_80145ECE / 2);
    RotTransPers(vertex, (long*)screen, &depth, &flag);

    g_Task->screen_x = 0xA0;
    if (D_80145EA4 != 0) {
        g_Task->screen_y = D_1F800034[1];
        D_80145EC0       = D_1F800034[1];
    } else {
        g_Task->screen_y = D_80145EC0;
    }

    if (D_8014832D < 0x28) {
        count             = D_8014832D;
        D_8014832D        = count + 1;
        D_8014828C[count] = (s32)g_Task;
    }

    if (g_AreaSceneMode == 2) {
        tpage = getTPage(1, 2, 448, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
        GFX_AddPrim(3, sizeof(DR_MODE));
        tile = (TILE*)g_GfxPrimCursor;
        SetTile(tile);
        SetSemiTrans(tile, 1);
        setXY0(tile, 0, 0);
        setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
        setRGB0(tile, 0xFF, 0, 0);
        GFX_AddPrim(3, sizeof(TILE));
        g_AreaSceneMode = 0;
    }
}
#else
INCLUDE_ASM(func_801F3514);
#endif
