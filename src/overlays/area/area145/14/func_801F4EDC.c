#include "area145_14.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F4EDC(u16 t, u32 stage) {
    s32 elapsed;
    u16 time;
    u32 limit;
    s32 dx;
    s32 dy;
    s32 mx;
    s32 my;
    s32 x;
    s32 y;
    u8* step;
    u32 direction;

    direction = (D_80147A58[(u8)stage].unk_6C >> 9) & 3;
    if (stage == 1) {
        step = D_801F5CEC;
    } else {
        step = D_801F5CFC;
    }
    step += direction * 4;
    elapsed = (s32)t - 5;
    time    = elapsed;
    limit   = step[1];
    dx      = D_80181B00[step[0] * 2] << 16;
    mx      = elapsed;
    if (limit < time) {
        mx = limit;
    }
    x  = D_80147A58[(u8)stage].pos.x.fixed + dx * (u16)mx;
    dy = D_80181B01[step[0] * 2] << 16;
    my = elapsed;
    if (limit < time) {
        my = limit;
    }
    y = D_80147A58[(u8)stage].pos.y.fixed + dy * (u16)my;
    func_801F5190(D_80147A58[(u8)stage].pos.x.fixed, D_80147A58[(u8)stage].pos.y.fixed, x, y);
    if (time < step[1]) {
        return 1;
    }
    if (step[2] == 0) {
        return 1;
    }
    if (time == step[1]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
    }
    return func_801F504C(time, step[2]);
}
#else
INCLUDE_ASM(func_801F4EDC);
#endif
