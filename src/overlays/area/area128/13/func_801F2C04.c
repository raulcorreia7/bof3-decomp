#include "area128_13.h"

/* Draws the six translucent glow quads of the ring: each spans two ring points and fades from their shade to black where it reaches out along the camera angle. */
MATCH void func_801F2C04(void) {
    POLY_G4* prim;
    s32      quad;
    s32      i;
    long     depth;
    long     flag;

    g_AreaSceneMode = 1;
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5);
    for (quad = 0; quad < AREA128_GLOW_QUAD_COUNT; quad++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        for (i = 0; i < 2; i++) {
            g_ScratchPadVectors[i].vx = D_801F32E0[D_801F334C[quad] + i].x;
            g_ScratchPadVectors[i].vy = D_801F32E0[D_801F334C[quad] + i].y;
            g_ScratchPadVectors[i].vz = D_801F32E0[D_801F334C[quad] + i].z;
        }
        for (i = 0; i < 2; i++) {
            g_ScratchPadVectors[i + 2].vx = D_801F32E0[D_801F334C[quad] + i].x + D_801F3328[D_801F334C[quad] + i].radius * rsin(g_AreaCameraAngle.vz + 0x200) / 4096;
            g_ScratchPadVectors[i + 2].vy = D_801F32E0[D_801F334C[quad] + i].y + D_801F3328[D_801F334C[quad] + i].radius * rcos(g_AreaCameraAngle.vz + 0x200) / 4096;
            g_ScratchPadVectors[i + 2].vz = D_801F3328[D_801F334C[quad] + i].z;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        prim->r0 = prim->g0 = prim->b0 = D_801F32E0[D_801F334C[quad]].shade;
        prim->r1 = prim->g1 = prim->b1 = D_801F32E0[D_801F334C[quad] + 1].shade;
        prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_G4));
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x225 : 0x95);
}
