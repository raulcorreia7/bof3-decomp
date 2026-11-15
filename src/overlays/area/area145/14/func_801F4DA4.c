#include "area145_14.h"

MATCH u8 func_801F4DA4(u32 frame) {
    s32 elapsed;
    u16 t;
    u32 off;
    u32 limit;
    s32 dx;
    s32 dy;
    s32 mx;
    s32 my;
    s32 x;
    s32 y;

    elapsed = (s32)frame - 5;
    t       = elapsed;
    off     = ((s32)D_80147AC4 >> 7) & 0xC;
    limit   = D_801F5CDD[off];
    dx      = D_80181B00[D_801F5CDC[off] * 2] << 16;
    mx      = elapsed;
    if (limit < t) {
        mx = limit;
    }
    x  = D_80147A8C + dx * (u16)mx;
    dy = D_80181B01[D_801F5CDC[off] * 2] << 16;
    my = elapsed;
    if (limit < t) {
        my = limit;
    }
    y = g_AreaFocusY + dy * (u16)my;
    func_801F5190(0x3D8000, 0x638000, x, y);
    if (t < D_801F5CDD[off]) {
        return 1;
    }
    if (D_801F5CDE[off] == 0) {
        return 1;
    }
    if (t == D_801F5CDD[off]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
    }
    return func_801F4EDC(t, D_801F5CDE[off]);
}
