#include "area082_13.h"

MATCH void func_801F4B3C(void) {
    Actor* drawCell;
    Actor* incCell;
    Actor* gateCell;
    Actor* resetCell;
    s32    level;
    u32    color;

    drawCell   = SELF(Actor);
    level      = drawCell->timer;
    color      = (u32)1 << 28 | ((u32)(0x1F - level * 27 / 100) << 10) | ((u32)(0x19 - level * 27 / 100) << 5) | (u32)(u8)((u32)level / 17);
    D_8014933A = 0;
    Area_DrawGradient((s32)color);
    incCell = SELF(Actor);
    incCell->timer++;
    gateCell = SELF(Actor);
    if (gateCell->timer >= 0x5B) {
        gateCell->timer = 0;
        resetCell       = SELF(Actor);
        resetCell->header.step++;
    }
}
