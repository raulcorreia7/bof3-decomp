#include "area152_13.h"

/* func_801F30E8 */
MATCH void Actor_ZoomIn(void) {
    u8* scratch;
    u8* check;

    Actor_SetScreenOrigin();

    scratch = SELF(u8);
    scratch[0x09] -= 1;

    check = SELF(u8);
    *(s32*)(scratch + 0x40) += 0x2000;

    if (check[0x09] == 0) {
        check[0x48]              = 0;
        SELF(Actor)->header.mode = 3;
    }

    Area_AddActor();
}
