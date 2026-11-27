#include "area196_13.h"

MATCH void func_801F2E48(void) {
    u8* shade0;
    u8* shade1;
    u8* shade2;
    u8* shade3;
    u8* end;
    s32 timer;
    u8  actor;

    SELF(Actor)->timer += 1;
    shade3 = D_801F412C + 3;
    shade2 = shade3 - 1;
    shade1 = shade3 - 2;
    shade0 = shade3 - 3;
    end    = shade3 + 9;

    do {
        if (*shade0 == 0) {
            shade3++;
            shade2++;
            shade1++;
            shade0++;
            continue;
        }
        if ((u8)(*shade0 -= 2) >= 0x61) {
            break;
        }
        if ((u8)(*shade1 -= 2) >= 0x61) {
            break;
        }
        if ((u8)(*shade2 -= 2) >= 0x61) {
            break;
        }
        *shade3 -= 2;
        break;
    } while ((s32)shade3 < (s32)end);

    timer = SELF(Actor)->timer;
    actor = 0x60;
    if (timer < 0x61) {
        actor = timer;
    }
    func_801F3030(actor);
    SELF(Actor)->unk_0A += 4;
    SELF(Actor)->unk_0A &= 0x3F;
    func_801F3850();

    if (D_801F412C[8] == 0) {
        SELF(Actor)->timer = 0x60;
        SELF(Actor)->header.step += 1;
    }
}
