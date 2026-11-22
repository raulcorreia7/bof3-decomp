#include "area144_13.h"

/* Seeds the six light rows, points each at its five projected points and averages the corners of the eight-point star into its six midpoints. */
MATCH void func_801F2E18(void) {
    /* 16 bytes of frame the function never uses. */
    VECTOR unused;
    s32    i;

    for (i = 0; (u16)i < 6; i++) {
        g_LightRows[i].active = 1;
        g_LightRows[i].timer  = (u16)i * 15;
        g_LightRows[i].step   = 0;
        g_LightRows[i].r      = 0xF0;
        g_LightRows[i].g      = 0xF0;
        g_LightRows[i].b      = 0xF0;
        if ((i & 1) == 0) {
            g_LightRows[i].unk_1B = 3;
        } else {
            g_LightRows[i].unk_1B = 1;
        }
    }

    g_LightRows[0].points[0] = &g_LightPoints[0];
    g_LightRows[0].points[1] = &g_LightPoints[1];
    g_LightRows[0].points[2] = &g_LightPoints[4];
    g_LightRows[0].points[3] = &g_LightPoints[5];
    g_LightRows[0].points[4] = &g_LightPoints[8];
    g_LightRows[0].script    = 1;
    func_801F376C(0, 5, 8);

    g_LightRows[1].points[0] = &g_LightPoints[0];
    g_LightRows[1].points[1] = &g_LightPoints[1];
    g_LightRows[1].points[2] = &g_LightPoints[2];
    g_LightRows[1].points[3] = &g_LightPoints[3];
    g_LightRows[1].points[4] = &g_LightPoints[9];
    g_LightRows[1].script    = 1;
    func_801F376C(0, 3, 9);

    g_LightRows[2].points[0] = &g_LightPoints[2];
    g_LightRows[2].points[1] = &g_LightPoints[0];
    g_LightRows[2].points[2] = &g_LightPoints[6];
    g_LightRows[2].points[3] = &g_LightPoints[4];
    g_LightRows[2].points[4] = &g_LightPoints[10];
    g_LightRows[2].script    = 7;
    func_801F376C(2, 4, 0xA);

    g_LightRows[3].points[0] = &g_LightPoints[2];
    g_LightRows[3].points[1] = &g_LightPoints[3];
    g_LightRows[3].points[2] = &g_LightPoints[6];
    g_LightRows[3].points[3] = &g_LightPoints[7];
    g_LightRows[3].points[4] = &g_LightPoints[11];
    func_801F376C(2, 7, 0xB);

    g_LightRows[3].script    = 5;
    g_LightRows[4].points[0] = &g_LightPoints[4];
    g_LightRows[4].points[1] = &g_LightPoints[5];
    g_LightRows[4].points[2] = &g_LightPoints[6];
    g_LightRows[4].points[3] = &g_LightPoints[7];
    g_LightRows[4].points[4] = &g_LightPoints[12];
    g_LightRows[4].script    = 5;
    func_801F376C(4, 7, 0xC);

    g_LightRows[5].points[0] = &g_LightPoints[3];
    g_LightRows[5].points[1] = &g_LightPoints[1];
    g_LightRows[5].points[2] = &g_LightPoints[7];
    g_LightRows[5].points[3] = &g_LightPoints[5];
    func_801F376C(3, 5, 0xD);
    g_LightRows[5].script    = 3;
    g_LightRows[5].points[4] = &g_LightPoints[13];
}
