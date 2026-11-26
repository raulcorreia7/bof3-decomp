#include "area098_13.h"

MATCH void func_801F3124(void) {
    u8        order[16];
    TrailDot* dot;
    u16       i;
    u16       j;
    u8        a;
    u8        b;
    u8        tmp;

    for (i = 0; i < 16; i++) {
        order[i] = i & 1;
    }

    dot = AREA_TRAIL_DOTS;
    j   = 0;
    for (i = 0; i < D_801F651C; i++) {
        if ((i & 0xF) == 0) {
            j = 0;
            do {
                a = rand() & 0xF;
                j++;
                b        = rand() & 0xF;
                tmp      = order[b];
                order[b] = order[a];
                order[a] = tmp;
            } while (j < 16);
            j = 0;
        }
        dot->active = order[j++];
        dot->dx     = (rand() & 0x1F) - 16;
        dot->dy     = (rand() & 0x1F) - 16;
        if (SELF(Actor)->unk_06 == 0) {
            dot->life = (rand() & 0x1E) + 10;
            dot->x -= dot->dx * dot->life;
            dot->y -= dot->dy * dot->life;
        } else {
            dot->life = 40 - (rand() & 0x1E);
        }
        dot++;
    }

    SELF(Actor)->timer = 80;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
}
